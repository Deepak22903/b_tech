#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUADRUPLES 100
#define MAX_LENGTH 50

typedef struct {
    char op[MAX_LENGTH];
    char arg1[MAX_LENGTH];
    char arg2[MAX_LENGTH];
    char result[MAX_LENGTH];
} Quadruple;

typedef struct {
    Quadruple quadruples[MAX_QUADRUPLES];
    int quadruple_count;
    int temp_counter;
} QuadrupleGenerator;

void init_quadruple_generator(QuadrupleGenerator* generator) {
    generator->quadruple_count = 0;
    generator->temp_counter = 0;
}

char* new_temp(QuadrupleGenerator* generator) {
    generator->temp_counter++;
    static char temp_var[MAX_LENGTH];
    snprintf(temp_var, sizeof(temp_var), "t%d", generator->temp_counter);
    return temp_var;
}

void emit(QuadrupleGenerator* generator, const char* op, const char* arg1, const char* arg2, const char* result) {
    if (generator->quadruple_count >= MAX_QUADRUPLES) {
        printf("Maximum quadruples reached!\n");
        return;
    }
    strcpy(generator->quadruples[generator->quadruple_count].op, op);
    strcpy(generator->quadruples[generator->quadruple_count].arg1, arg1);
    strcpy(generator->quadruples[generator->quadruple_count].arg2, arg2);
    strcpy(generator->quadruples[generator->quadruple_count].result, result);
    generator->quadruple_count++;
}

char* process_term(QuadrupleGenerator* generator, const char* term) {
    char arg1[MAX_LENGTH], arg2[MAX_LENGTH];
    sscanf(term, "%s * %s", arg1, arg2);

    if (arg2[0] == '-') {
        char neg_arg[MAX_LENGTH];
        strcpy(neg_arg, arg2 + 1);  // Remove '-' sign
        char* temp_neg = new_temp(generator);
        emit(generator, "-", neg_arg, "", temp_neg);
        char* temp_mul = new_temp(generator);
        emit(generator, "*", arg1, temp_neg, temp_mul);
        return temp_mul; // Return the temporary variable for multiplication
    }
    // If no negation, return the multiplication directly
    char* temp_mul = new_temp(generator);
    emit(generator, "*", arg1, arg2, temp_mul);
    return temp_mul;
}

char* generate_code(QuadrupleGenerator* generator, const char* expression) {
    char left_term[MAX_LENGTH], right_term[MAX_LENGTH];

    // Split the expression into left and right terms
    sscanf(expression, "%[^+] + %s", left_term, right_term);

    char* left_result = process_term(generator, left_term);
    char* right_result = process_term(generator, right_term);
    char* temp_result = new_temp(generator);

    emit(generator, "+", left_result, right_result, temp_result);
    return temp_result;
}

void assign_variable(QuadrupleGenerator* generator, const char* var) {
    if (generator->quadruple_count > 0) {
        // Get the last quadruple's result
        char temp_result[MAX_LENGTH];
        strcpy(temp_result, generator->quadruples[generator->quadruple_count - 1].result);
        emit(generator, "=", "", "", var);  
    }
}

void print_quadruples(QuadrupleGenerator* generator) {
    printf("    OP  arg1        arg2      result\n");
    for (int i = 0; i < generator->quadruple_count; i++) {
        printf("%d   %s   %s   %s\n", i, generator->quadruples[i].op, generator->quadruples[i].arg1, generator->quadruples[i].result);
    }
}

int main() {
    QuadrupleGenerator generator;
    init_quadruple_generator(&generator);

    // Generate code for the expression 'a = b * -c + b * -c'
    generate_code(&generator, "b * -c + b * -c");
    assign_variable(&generator, "a");

    // Print generated quadruples
    print_quadruples(&generator);

    return 0;
}
