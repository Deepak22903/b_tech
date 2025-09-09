#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_VARS 100
#define MAX_VAR_NAME 32
#define MAX_FUNCS 100
#define MAX_FUNC_NAME 32

typedef enum { INT, FLOAT, VOID, UNKNOWN } VarType;

typedef struct {
    char name[MAX_VAR_NAME];
    VarType type;
} Variable;

typedef struct {
    char name[MAX_FUNC_NAME];
    VarType returnType;
} Function;

typedef struct {
    Variable vars[MAX_VARS];
    int count;
} SymbolTable;

typedef struct {
    Function funcs[MAX_FUNCS];
    int count;
} FunctionTable;

// add a variable to symbol table
void add_variable(SymbolTable *table, const char *name, VarType type) {
    for (int i = 0; i < table->count; i++) {
        if (strcmp(table->vars[i].name, name) == 0) {
            printf("Error: Variable '%s' already declared.\n", name);
            return;
        }
    }

    strcpy(table->vars[table->count].name, name);
    table->vars[table->count].type = type;
    table->count++;
}

// get the type of a variable from the symbol table
VarType get_variable_type(SymbolTable *table, const char *name) {
    for (int i = 0; i < table->count; i++) {
        if (strcmp(table->vars[i].name, name) == 0) {
            return table->vars[i].type;
        }
    }
    return UNKNOWN; 
}

// add a function to the function table
void add_function(FunctionTable *table, const char *name, VarType returnType) {
    for (int i = 0; i < table->count; i++) {
        if (strcmp(table->funcs[i].name, name) == 0) {
            printf("Error: Function '%s' already declared.\n", name);
            return;
        }
    }

    strcpy(table->funcs[table->count].name, name);
    table->funcs[table->count].returnType = returnType;
    table->count++;
}

// get the return type of a function from the function table
VarType get_function_return_type(FunctionTable *table, const char *name) {
    for (int i = 0; i < table->count; i++) {
        if (strcmp(table->funcs[i].name, name) == 0) {
            return table->funcs[i].returnType;
        }
    }
    return UNKNOWN; // Not declared
}

// check if a string is a valid variable name
int is_valid_var_name(const char *name) {
    if (!isalpha(name[0]) && name[0] != '_') return 0; 
    for (int i = 1; name[i] != '\0'; i++) {
        if (!isalnum(name[i]) && name[i] != '_') return 0; 
    }
    return 1; // Valid variable name
}

// remove trailing semicolon from a string
void remove_semicolon(char *line) {
    char *semicolon = strchr(line, ';');
    if (semicolon) *semicolon = '\0'; // Replace ';' with null terminator
}

// parse a line and check for semantic errors
void parse_line(SymbolTable *table, FunctionTable *func_table, const char *line) {
    char var_name[MAX_VAR_NAME], func_name[MAX_FUNC_NAME], rhs[MAX_VAR_NAME];
    VarType declared_type;

    char modifiable_line[256];
    strcpy(modifiable_line, line);

    remove_semicolon(modifiable_line);

    if (sscanf(modifiable_line, "int %s", var_name) == 1) {
        if (!is_valid_var_name(var_name)) {
            printf("Error: Invalid variable name '%s'.\n", var_name);
            return;
        }
        add_variable(table, var_name, INT);
    } else if (sscanf(modifiable_line, "float %s", var_name) == 1) {
        if (!is_valid_var_name(var_name)) {
            printf("Error: Invalid variable name '%s'.\n", var_name);
            return;
        }
        add_variable(table, var_name, FLOAT);
    }
    else if (sscanf(modifiable_line, "void %s", func_name) == 1) {
        if (!is_valid_var_name(func_name)) {
            return;
        }
        add_function(func_table, func_name, VOID);
    }
    else if (sscanf(modifiable_line, "%s = %s", var_name, rhs) == 2) {
        if (!is_valid_var_name(var_name)) {
            printf("Error: Invalid variable name '%s'.\n", var_name);
            return;
        }

        if (isdigit(rhs[0]) || (rhs[0] == '-' && isdigit(rhs[1]))) {
        } else if (get_variable_type(table, rhs) == UNKNOWN) {
            printf("Error: Variable '%s' is not declared.\n", rhs);
            return;
        }

        declared_type = get_variable_type(table, var_name);
        if (declared_type == UNKNOWN) {
            printf("Error: Variable '%s' is not declared.\n", var_name);
            return;
        }
    }
    else if (sscanf(modifiable_line, "%s()", func_name) == 1) {
        if (get_function_return_type(func_table, func_name) == UNKNOWN) {
            // printf("Error: Function '%s' is not declared.\n", func_name);
        }
    }
    else if (strcmp(modifiable_line, "}") == 0) {
        // No action needed for function ending braces
    }
    else if (strlen(line) > 0) {
        printf("Error: Unrecognized command in line: '%s'\n", line);
    }
}

int main() {
    SymbolTable table = { .count = 0 };
    FunctionTable func_table = { .count = 0 };
    char line[256];
    FILE *file;

    file = fopen("input.c", "r");
    if (file == NULL) {
        printf("Error: Could not open file.\n");
        return 1;
    }

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0; 
        parse_line(&table, &func_table, line);
    }

    fclose(file);
    return 0;
}
