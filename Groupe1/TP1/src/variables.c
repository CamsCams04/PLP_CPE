/* Fichier : variables.c
   Auteur : Baptiste Rousselot, Camille Morfin
   Description : assignation et affichage des différentes variables
*/
#include <stdio.h>
#include <limits.h>
#include <float.h>

int main() {
    /* --- caractères --- */
    char a = 'a';
    signed char b = -2;
    unsigned char c = UCHAR_MAX;

    /* --- entiers courts --- */
    short d = -5000;
    unsigned short e = USHRT_MAX;

    /* --- entiers --- */
    int f = -100000;
    unsigned int g = UINT_MAX;

    /* --- long --- */
    long int h = -1000000L;
    unsigned long int i = ULONG_MAX;

    /* --- long long --- */
    long long int j = -9223372036854775807LL;
    unsigned long long int n = ULLONG_MAX;

    /* --- flottants --- */
    float k = -3.14f;
    double l = -1.23456789;
    long double m = -1.234567890123456789L;

    /* --- affichage --- */
    printf("char a as char: '%c'  as int: %d\n", a, a);
    printf("signed char b: %hhd\n", b);
    printf("unsigned char c: %hhu\n\n", c);

    printf("short d: %hd\n", d);
    printf("unsigned short e: %hu\n\n", e);

    printf("int f: %d\n", f);
    printf("unsigned int g: %u\n\n", g);

    printf("long int h: %ld\n", h);
    printf("unsigned long int i: %lu\n\n", i);

    printf("long long int j: %lld\n", j);
    printf("unsigned long long int n: %llu\n\n", n);

    printf("float k: %f (FLT_MAX = %e)\n", k, FLT_MAX);
    printf("double l: %f (DBL_MAX = %e)\n", l, DBL_MAX);
    printf("long double m: %Lf (LDBL_MAX = %Le)\n", m, LDBL_MAX);

    return 0;
}