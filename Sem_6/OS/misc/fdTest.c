#include <fcntl.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
  int buff[1024];
  int fd = open("/dev/zero", O_RDONLY);
  read(fd, buff, 6);
  write(1, buff, 6);
  close(fd);

  return 0;
}
