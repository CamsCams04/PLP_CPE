#ifndef EVALUATION_H
#define EVALUATION_H

double evaluation_calc(char operateur, double lhs, double rhs);
double eval_postfix(char **tokens, int count);

#endif