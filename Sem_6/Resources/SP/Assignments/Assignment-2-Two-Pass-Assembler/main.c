#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 100

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

    // First Pass
    while (fscanf(fp1, "%s%s%s", label, opcode, operand) == 3) {
        if (strcmp(opcode, "START") == 0) {
            start = atoi(operand);
            locctr = start;
            fprintf(fp4, "\t%s\t%s\t%s\n", label, opcode, operand);
        } else {
            if (strcmp(label, "**") != 0) {
                fprintf(fp3, "%s\t%d\n", label, locctr);
            }
            if (strcmp(opcode, "END") != 0) {
                locctr += 3; // Increment location counter
            }
        }
    }

    // Reset file pointers for second pass
    rewind(fp1);
    rewind(fp2);

    // Second Pass
    locctr = start; // Reset location counter
    fprintf(fp4, "LOCCTR\tLABEL\tOPCODE\tOPERAND\n"); // Header for the output file
    while (fscanf(fp1, "%s%s%s", label, opcode, operand) == 3) {
        fprintf(fp4, "%d\t%s\t%s\t%s\n", locctr, label, opcode, operand);
        rewind(fp2);
        while (fscanf(fp2, "%s%s", code, mnemonic) == 2) {
            if (strcmp(opcode, code) == 0) {
                locctr += 3; // Increment location counter for instructions found in optab
                break;
            }
        }
        if (strcmp(opcode, "WORD") == 0) {
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
