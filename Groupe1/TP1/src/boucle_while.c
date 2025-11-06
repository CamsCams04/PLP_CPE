#include <stdio.h>

int main(){
    int i = 0;
    int size;

    scanf("%d", &size);
    printf("%d < %d \n",i, size);

    while(i < size){
        int j = 0;
        while(j <= i ){
            if(j==0 || j==i || i == size-1){
                printf("*");
            } else {
                printf("#");
            }
            j++;
       }
       printf("\n");
       i++;
    }

    return 0;
}
