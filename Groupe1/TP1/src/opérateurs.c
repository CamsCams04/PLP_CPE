#include <stdio.h>

int main() {
    short int a = 16; short int b = 3;

    int add = a+b;
    int sous = a-b;
    int mult = a*b;
    int divi = a/b;

    int eq;
    int sup;

    printf("les resultats : %d \n %d \n %d \n %d \n",add,sous,mult,divi);

    if(a == b){
        eq = 1;
        printf("%d c'est equal %d (%d)",a,b,eq);
    }
    if (a>b){
        sup = 1;
        printf("%d c'est superieur a %d (%d)",a,b,sup);
    }
    return 0;
}
