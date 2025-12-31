#ifndef VARIABLES_H
#define VARIABLES_H

typedef enum {
    VAR_INT,
    VAR_DOUBLE,
    VAR_STRING
} VarType;

typedef struct {
    char *name;     // nom UTF-8
    VarType type;
    union {
        int i;
        double d;
        char *s;
    } value;
} Variable;

Variable *find_variable(const char *name);
int set_variable(const char *name, VarType type, const char *value_str);
void print_variable(const Variable *var);
VarType detect_type(const char *value);

#endif
