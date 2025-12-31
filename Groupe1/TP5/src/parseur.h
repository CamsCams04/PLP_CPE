#ifndef PARSSEUR_H
#define PARSSEUR_H

enum TokenType { TOK_NUMBER, TOK_OPERATOR, TOK_EOF, TOK_INVALID };

struct Token
{
    enum TokenType type;
    double value;       // si TOK_NUMBER
    char op;            // si TOK_OPERATOR
    const char *raw;    // chaine d'origine
};

enum OpType { OP_ADD, OP_SUB, OP_MUL, OP_DIV};

struct Expression
{
    enum OpType op;
    double lhs;
    double rhs;
};

struct Expression *parse_tokens(const struct Token *tokens, int n, char **error_msg);

#endif