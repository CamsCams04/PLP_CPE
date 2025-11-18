#include <stdio.h>

int main() {

    char text[255] = "toto";

    int length = strlen(text);

    printf("length : %d",length);

    lengthexo();

    return 0;
}

int lengthexo() {

    char text[255] = "toto 2";

    int totlen = 0;

    for(int i = 0; text[i] !='\0';i++){
        totlen++;
    }

    printf("\n length 2 : %d",totlen);

    return 0;
}
