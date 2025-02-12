#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 100
#define MAX_PROCEDURES 10
#define MAX_SYMBOLS 100

typedef struct {
    char name[10];
    int start;
} Procedure;

typedef struct {
    char name[10];
    int address;
} Symbol;

Procedure procedures[MAX_PROCEDURES];
Symbol symbols[MAX_SYMBOLS];

int num_procedures = 0;
int num_symbols = 0;

int findProcedure(char *name) {
    for (int i = 0; i < num_procedures; i++) {
        if (strcmp(procedures[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

int findSymbol(char *name) {
    for (int i = 0; i < num_symbols; i++) {
        if (strcmp(symbols[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

void addProcedure(char *name, int start) {
    strcpy(procedures[num_procedures].name, name);
    procedures[num_procedures].start = start;
    num_procedures++;
}

void addSymbol(char *name, int address) {
    strcpy(symbols[num_symbols].name, name);
    symbols[num_symbols].address = address;
    num_symbols++;
}

int main() {
    char opcode[10], operand[10], label[10], code[10], mnemonic[10];
    int locctr = 0, start = 0, length = 0;
    FILE *fp1, *fp2, *fp3, *fp4;

    fp1 = fopen("input.txt", "r");
    fp2 = fopen("optab.txt", "r");
    fp3 = fopen("symtab.txt", "w");
    fp4 = fopen("output.txt", "w");

    if (!fp1 || !fp2 || !fp3 || !fp4) {
        printf("Error opening file(s).\n");
        return 1;
    }

    // Pass 1
    while (fscanf(fp1, "%s%s%s", label, opcode, operand) == 3) {
        if (strcmp(opcode, "START") == 0) {
            start = atoi(operand);
            locctr = start;
            fprintf(fp4, "\t%s\t%s\t%s\n", label, opcode, operand);
        } else if (strcmp(opcode, "PROC") == 0) {
            addProcedure(label, locctr);
        } else if (strcmp(opcode, "END") == 0) {
            break;
        } else {
            if (strcmp(label, "**") != 0) {
                addSymbol(label, locctr);
            }
            locctr += 3;
        }
    }

    // Reset file pointers for pass 2
    rewind(fp1);
    rewind(fp2);

    // Pass 2
    locctr = start;
    fprintf(fp4, "LOCCTR\tLABEL\tOPCODE\tOPERAND\n");
    while (fscanf(fp1, "%s%s%s", label, opcode, operand) == 3) {
        fprintf(fp4, "%d\t%s\t%s\t%s\n", locctr, label, opcode, operand);
        if (strcmp(opcode, "END") == 0) {
            break;
        }
        if (strcmp(opcode, "CALL") == 0) {
            int procIndex = findProcedure(operand);
            if (procIndex != -1) {
                locctr += 3;
            } else {
                printf("Error: Procedure %s not found.\n", operand);
            }
        } else if (strcmp(opcode, "RET") == 0) {
            locctr += 3;
        } else if (strcmp(opcode, "WORD") == 0) {
            locctr += 3;
        } else if (strcmp(opcode, "RESW") == 0) {
            locctr += 3 * atoi(operand);
        } else if (strcmp(opcode, "RESB") == 0) {
            locctr += atoi(operand);
        } else if (strcmp(opcode, "BYTE") == 0) {
            locctr += strlen(operand) - 3; // Subtract 3 for the X' or C'
        }
    }

    length = locctr - start;

    fprintf(fp4, "%d\t%s\t%s\t%s\n", locctr, label, opcode, operand);
    fprintf(fp4, "The length of the code : %d\n", length);

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);

    return 0;
}
