#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_PRODUCTIONS 100
#define MAX_SYMBOLS 100
#define MAX_RHS 10
#define MAX_TERMINALS 100

typedef struct {
    char lhs;
    char rhs[MAX_RHS][MAX_SYMBOLS];
    int rhs_count;
} Production;

Production productions[MAX_PRODUCTIONS];
int production_count = 0;

char non_terminals[MAX_SYMBOLS];
int non_terminal_count = 0;

char terminals[MAX_SYMBOLS];
int terminal_count = 0;

char first_sets[MAX_SYMBOLS][MAX_TERMINALS];
int first_set_counts[MAX_SYMBOLS];

char follow_sets[MAX_SYMBOLS][MAX_TERMINALS];
int follow_set_counts[MAX_SYMBOLS];

void add_to_set(char *set, int *count, char symbol) {
    for (int i = 0; i < *count; i++) {
        if (set[i] == symbol) {
            return;
        }
    }
    set[(*count)++] = symbol;
}

bool is_non_terminal(char symbol) {
    for (int i = 0; i < non_terminal_count; i++) {
        if (non_terminals[i] == symbol) {
            return true;
        }
    }
    return false;
}

void read_productions(const char *file_path) {
    FILE *file = fopen(file_path, "r");
    if (!file) {
        printf("Error opening file.\n");
        exit(1);
    }

    char line[MAX_SYMBOLS];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0'; // Remove newline character
        if (strlen(line) == 0) continue;

        char *lhs = strtok(line, "->");
        char *rhs = strtok(NULL, "->");

        Production p;
        p.lhs = lhs[0];
        p.rhs_count = 0;

        char *token = strtok(rhs, "|");
        while (token) {
            strcpy(p.rhs[p.rhs_count++], token);
            token = strtok(NULL, "|");
        }

        productions[production_count++] = p;

        // Add lhs to non-terminals if not already present
        if (!is_non_terminal(p.lhs)) {
            non_terminals[non_terminal_count++] = p.lhs;
        }
    }

    fclose(file);
}

void extract_terminals() {
    for (int i = 0; i < production_count; i++) {
        for (int j = 0; j < productions[i].rhs_count; j++) {
            for (int k = 0; k < strlen(productions[i].rhs[j]); k++) {
                char symbol = productions[i].rhs[j][k];
                if (!is_non_terminal(symbol) && symbol != 'e') {
                    add_to_set(terminals, &terminal_count, symbol);
                }
            }
        }
    }
}

void calculate_first_set(char nt) {
    for (int i = 0; i < production_count; i++) {
        if (productions[i].lhs == nt) {
            for (int j = 0; j < productions[i].rhs_count; j++) {
                int k = 0;
                while (k < strlen(productions[i].rhs[j])) {
                    char symbol = productions[i].rhs[j][k];

                    if (!is_non_terminal(symbol)) {
                        add_to_set(first_sets[nt - 'A'], &first_set_counts[nt - 'A'], symbol);
                        break;
                    } else {
                        calculate_first_set(symbol);
                        for (int l = 0; l < first_set_counts[symbol - 'A']; l++) {
                            char f_symbol = first_sets[symbol - 'A'][l];
                            if (f_symbol != 'e') {
                                add_to_set(first_sets[nt - 'A'], &first_set_counts[nt - 'A'], f_symbol);
                            }
                        }
                        if (strchr(first_sets[symbol - 'A'], 'e') == NULL) {
                            break;
                        }
                    }
                    k++;
                }
            }
        }
    }
}

void calculate_follow_set(char nt) {
    if (nt == 'E') {
        add_to_set(follow_sets[nt - 'A'], &follow_set_counts[nt - 'A'], '$');
    }

    for (int i = 0; i < production_count; i++) {
        for (int j = 0; j < productions[i].rhs_count; j++) {
            for (int k = 0; k < strlen(productions[i].rhs[j]); k++) {
                if (productions[i].rhs[j][k] == nt) {
                    if (k == strlen(productions[i].rhs[j]) - 1) {
                        if (productions[i].lhs != nt) {
                            calculate_follow_set(productions[i].lhs);
                            for (int l = 0; l < follow_set_counts[productions[i].lhs - 'A']; l++) {
                                add_to_set(follow_sets[nt - 'A'], &follow_set_counts[nt - 'A'], follow_sets[productions[i].lhs - 'A'][l]);
                            }
                        }
                    } else {
                        char next_symbol = productions[i].rhs[j][k + 1];
                        if (is_non_terminal(next_symbol)) {
                            for (int l = 0; l < first_set_counts[next_symbol - 'A']; l++) {
                                if (first_sets[next_symbol - 'A'][l] != 'e') {
                                    add_to_set(follow_sets[nt - 'A'], &follow_set_counts[nt - 'A'], first_sets[next_symbol - 'A'][l]);
                                }
                            }
                            if (strchr(first_sets[next_symbol - 'A'], 'e') != NULL) {
                                calculate_follow_set(next_symbol);
                                for (int l = 0; l < follow_set_counts[next_symbol - 'A']; l++) {
                                    add_to_set(follow_sets[nt - 'A'], &follow_set_counts[nt - 'A'], follow_sets[next_symbol - 'A'][l]);
                                }
                            }
                        } else {
                            add_to_set(follow_sets[nt - 'A'], &follow_set_counts[nt - 'A'], next_symbol);
                        }
                    }
                }
            }
        }
    }
}

int main() {
    const char *file_path = "grammar.txt";

    // Step 1: Read the file and get the list of productions
    read_productions(file_path);

    // Step 2: Extract terminals
    extract_terminals();

    // Display the results
    printf("Non-terminals:\n");
    for (int i = 0; i < non_terminal_count; i++) {
        printf("%c\n", non_terminals[i]);
    }

    printf("\nTerminals:\n");
    for (int i = 0; i < terminal_count; i++) {
        printf("%c\n", terminals[i]);
    }

    printf("\n-------------------------------------------------------------------\n");

    // Calculate the FIRST set for each non-terminal
    for (int i = 0; i < non_terminal_count; i++) {
        calculate_first_set(non_terminals[i]);
    }

    // Display the FIRST sets
    for (int i = 0; i < non_terminal_count; i++) {
        printf("FIRST(%c) = { ", non_terminals[i]);
        for (int j = 0; j < first_set_counts[non_terminals[i] - 'A']; j++) {
            printf("%c ", first_sets[non_terminals[i] - 'A'][j]);
        }
        printf("}\n");
    }

    printf("\n-------------------------------------------------------------------\n");

    // Calculate the FOLLOW set for each non-terminal
    for (int i = 0; i < non_terminal_count; i++) {
        calculate_follow_set(non_terminals[i]);
    }

    // Remove 'e' from the FOLLOW sets
    for (int i = 0; i < non_terminal_count; i++) {
        char *pos = strchr(follow_sets[non_terminals[i] - 'A'], 'e');
        if (pos != NULL) {
            int index = pos - follow_sets[non_terminals[i] - 'A'];
            for (int j = index; j < follow_set_counts[non_terminals[i] - 'A'] - 1; j++) {
                follow_sets[non_terminals[i] - 'A'][j] = follow_sets[non_terminals[i] - 'A'][j + 1];
            }
            follow_set_counts[non_terminals[i] - 'A']--;
        }
    }

    // Display the FOLLOW sets
    for (int i = 0; i < non_terminal_count; i++) {
        printf("FOLLOW(%c) = { ", non_terminals[i]);
        for (int j = 0; j < follow_set_counts[non_terminals[i] - 'A']; j++) {
            printf("%c ", follow_sets[non_terminals[i] - 'A'][j]);
        }
        printf("}\n");
    }

    return 0;
}
