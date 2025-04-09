#include <stdio.h>


int main(int argc, char const *argv[])
{   
    int la;
    printf("Should say Hi?");
    scanf("%d", &la);

    if(la) goto hi;


    
    printf("HEEELLO MAYTE\n");

    hi: 
    return 0;
}
