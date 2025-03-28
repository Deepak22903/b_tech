#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

    if (fscanf(fp1, "%s%s%s", label, opcode, operand) == 3 && strcmp(opcode, "START") == 0) {
        start = atoi(operand);
        locctr = start;
        fprintf(fp4, "\t%s\t%s\t%s\n", label, opcode, operand);
    }

    while (fscanf(fp1, "%s%s%s", label, opcode, operand) == 3) {
        fprintf(fp4, "%d\t", locctr);

        if (strcmp(label, "**") != 0) {
            fprintf(fp3, "%s\t%d\n", label, locctr);
        }

        rewind(fp2);
        while (fscanf(fp2, "%s%s", code, mnemonic) == 2) {
            if (strcmp(opcode, code) == 0) {
                locctr += 3;
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
            locctr += strlen(operand) - 3; // subtract 3 for the X' or C'
        }

        fprintf(fp4, "%s\t%s\t%s\n", label, opcode, operand);
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