#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TRIPLETS 100
#define MAX_LENGTH 50

typedef struct {
    char op[MAX_LENGTH];
    char arg1[MAX_LENGTH];
    char arg2[MAX_LENGTH];
} Triplet;

typedef struct {
    Triplet triplets[MAX_TRIPLETS];
    int triplet_count;
    int temp_counter;
} TripletGenerator;

void init_triplet_generator(TripletGenerator* generator) {
    generator->triplet_count = 0;
    generator->temp_counter = 0;
}

char* new_temp(TripletGenerator* generator) {
    generator->temp_counter++;
    static char temp_var[MAX_LENGTH];
    snprintf(temp_var, sizeof(temp_var), "t%d", generator->temp_counter);
    return temp_var;
}

void emit(TripletGenerator* generator, const char* op, const char* arg1, const char* arg2) {
    if (generator->triplet_count >= MAX_TRIPLETS) {
        printf("Maximum triplets reached!\n");
        return;
    }
    strcpy(generator->triplets[generator->triplet_count].op, op);
    strcpy(generator->triplets[generator->triplet_count].arg1, arg1);
    strcpy(generator->triplets[generator->triplet_count].arg2, arg2);
    generator->triplet_count++;
}

void process_term(TripletGenerator* generator, const char* term, char* result) {
    char arg1[MAX_LENGTH], arg2[MAX_LENGTH];
    sscanf(term, "%s * %s", arg1, arg2);

    if (arg2[0] == '-') {
        char neg_arg[MAX_LENGTH];
        strcpy(neg_arg, arg2 + 1);  // Remove '-' sign
        emit(generator, "-", neg_arg, "");  
        char temp_var[MAX_LENGTH];
        strcpy(temp_var, new_temp(generator));
        emit(generator, "*", arg1, neg_arg);  // Multiply arg1 with neg_arg
        strcpy(result, temp_var); // Store the temporary variable
    } else {
        emit(generator, "*", arg1, arg2); // Normal multiplication
        strcpy(result, arg2); // Store the result
    }
}

void generate_code(TripletGenerator* generator, const char* expression) {
    char left_term[MAX_LENGTH], right_term[MAX_LENGTH];
    char left_result[MAX_LENGTH], right_result[MAX_LENGTH];

    // Split the expression into left and right terms
    sscanf(expression, "%[^+] + %s", left_term, right_term);

    // Process each term separately
    process_term(generator, left_term, left_result);
    process_term(generator, right_term, right_result);

    // Emit the addition operation
    char temp_var[MAX_LENGTH];
    strcpy(temp_var, new_temp(generator));
    emit(generator, "+", left_result, right_result); 
    // Assign the result to a temporary variable
    emit(generator, "=", temp_var, "");  
}

void print_triplets(TripletGenerator* generator) {
    printf("    OP      arg1    arg2\n");
    for (int i = 0; i < generator->triplet_count; i++) {
        printf("%d  %s     %s     %s\n", i, generator->triplets[i].op, generator->triplets[i].arg1, generator->triplets[i].arg2);
    }
}

int main() {
    TripletGenerator generator;
    init_triplet_generator(&generator);

    // Generate code for the expression 'a = b * -c + b * -c'
    generate_code(&generator, "b * -c + b * -c");
    
    // Print generated triplets
    print_triplets(&generator);

    return 0;
}
