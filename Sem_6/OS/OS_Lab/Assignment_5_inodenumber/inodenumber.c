#define _LARGEFILE64_SOURCE

#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define BASE_OFF 1024
#define EXT2_MAGIC 0xEF53

typedef struct {
  uint32_t inodes;
  uint32_t blocks;
  uint32_t free_blocks;
  uint32_t free_inodes;
  uint32_t first_data_blk;
  uint32_t log_blk_size;
  uint32_t log_frag_size;
  uint32_t blks_per_grp;
  uint32_t frags_per_grp;
  uint32_t inodes_per_grp;
  uint32_t mtime;
  uint32_t wtime;
  uint16_t mnt_count;
  uint16_t max_mnt_count;
  uint16_t magic;
  uint16_t state;
  uint16_t errors;
  uint16_t minor_rev;
  uint32_t last_chk;
  uint32_t chk_intvl;
  uint32_t first_ino;
  uint16_t inode_sz;
  uint16_t block_grp;  // Add missing field
  uint32_t feat_compat;
  uint32_t feat_incompat;
  uint32_t feat_ro_compat;
} __attribute__((packed)) sblk_t;

typedef struct {
  uint32_t blk_bmp;
  uint32_t ino_bmp;
  uint32_t ino_tbl;
  uint16_t free_blks;  // Changed order to match EXT2 spec
  uint16_t free_inodes;
  uint16_t used_dirs;
  uint16_t pad;        // Added padding for alignment
  uint32_t res[3];
} __attribute__((packed)) grp_t;

typedef struct {
  uint16_t mode;
  uint16_t uid;
  uint32_t size;
  uint32_t atime;
  uint32_t ctime;
  uint32_t mtime;
  uint32_t dtime;
  uint16_t gid;
  uint16_t links;
  uint32_t blocks;
  uint32_t flags;
  uint32_t osd1;
  uint32_t block[15];  // Direct, indirect, double-indirect, triple-indirect blocks
  uint32_t gen;
  uint32_t file_acl;
  uint32_t dir_acl;
  uint32_t faddr;
} __attribute__((packed)) inode_t;

void get_sblk(int fd, sblk_t *sblk) {
  if (lseek64(fd, BASE_OFF, SEEK_SET) < 0) { // Use lseek64 for large file support
    perror("Seek failed: Superblock");
    exit(1);
  }

  ssize_t bytes_read = read(fd, sblk, sizeof(sblk_t));
  if (bytes_read != sizeof(sblk_t)) {
    fprintf(stderr, "Read failed: Superblock (read %zd bytes, expected %zu)\n",
            bytes_read, sizeof(sblk_t));
    perror("Read failed");
    exit(1);
  }

  printf("Superblock Magic: 0x%X\n", sblk->magic); // Debug output
  printf("Superblock Size: %zu bytes\n", sizeof(sblk_t));
  printf("Inode Size: %u bytes\n", sblk->inode_sz);
  printf("Block Size: %u bytes\n", 1024 << sblk->log_blk_size);

  if (sblk->magic != EXT2_MAGIC) {
    fprintf(stderr, "Invalid EXT2 FS (magic: 0x%X)\n", sblk->magic);
    exit(1);
  }
}

void get_grp(int fd, grp_t *grp, uint32_t blk_size) {
  off_t offset = (blk_size == 1024) ? 2 * blk_size : blk_size;

  if (lseek64(fd, offset, SEEK_SET) < 0) {
    perror("Seek failed: Group Desc");
    exit(1);
  }

  if (read(fd, grp, sizeof(grp_t)) != sizeof(grp_t)) {
    perror("Read failed: Group Desc");
    exit(1);
  }
  
  printf("\n[ Group Descriptor Info ]\n");
  printf("Block Bitmap: %u\n", grp->blk_bmp);
  printf("Inode Bitmap: %u\n", grp->ino_bmp);
  printf("Inode Table: %u\n", grp->ino_tbl);
  printf("Free Blocks: %u\n", grp->free_blks);
  printf("Free Inodes: %u\n", grp->free_inodes);
  printf("Used Directories: %u\n", grp->used_dirs);
}

void get_inode(int fd, uint32_t ino, inode_t *node, sblk_t *sblk, grp_t *grp,
               uint32_t blk_size) {
  uint32_t ino_tbl = grp->ino_tbl;
  uint32_t ino_sz = sblk->inode_sz;
  uint32_t index = ino - 1;

  uint64_t tbl_off = (uint64_t)ino_tbl * blk_size;
  uint64_t ino_off = tbl_off + (index * ino_sz);

  printf("\n[ Inode Info ]\n");
  printf("Inode No.: %u\n", ino);
  printf("Index: %u\n", index);
  printf("Inode Table Blk: %u\n", ino_tbl);
  printf("Table Offset: %lu bytes\n", tbl_off);
  printf("Inode Offset: %lu bytes\n", ino_off);
  printf("Inode Size: %u bytes\n", ino_sz);

  if (lseek64(fd, ino_off, SEEK_SET) < 0) {
    perror("Seek failed: Inode");
    exit(1);
  }

  if (read(fd, node, sizeof(inode_t)) != sizeof(inode_t)) {
    perror("Read failed: Inode");
    exit(1);
  }
}

void print_inode(const inode_t *node) {
  printf("\n[ Inode Details ]\n");
  printf("Mode: 0x%X\n", node->mode);
  printf("UID: %u\n", node->uid);
  printf("Size: %u bytes\n", node->size);
  printf("Accessed: %u\n", node->atime);
  printf("Created: %u\n", node->ctime);
  printf("Modified: %u\n", node->mtime);
  printf("Deleted: %u\n", node->dtime);
  printf("GID: %u\n", node->gid);
  printf("Links: %u\n", node->links);
  printf("Blocks: %u\n", node->blocks);
  printf("Flags: 0x%X\n", node->flags);

  printf("Block Pointers:\n");
  for (int i = 0; i < 15; i++) {
    printf("  [%d] -> %u\n", i, node->block[i]);
  }
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Usage: %s <dev> <inode>\n", argv[0]);
    exit(1);
  }

  const char *dev = argv[1];
  uint32_t ino = atoi(argv[2]);

  if (ino == 0) {
    fprintf(stderr, "Invalid inode (>= 1 required)\n");
    exit(1);
  }

  int fd = open(dev, O_RDONLY | O_LARGEFILE);  // Added O_LARGEFILE for large file support
  if (fd < 0) {
    perror("Failed to open device");
    exit(1);
  }

  sblk_t sblk;
  get_sblk(fd, &sblk);

  uint32_t blk_size = 1024 << sblk.log_blk_size;

  grp_t grp;
  get_grp(fd, &grp, blk_size);

  inode_t node;
  get_inode(fd, ino, &node, &sblk, &grp, blk_size);

  print_inode(&node);

  close(fd);
  return 0;
}
