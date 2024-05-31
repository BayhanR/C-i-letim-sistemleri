#include <stdio.h>

int main(){
    int** p;
    int* p2;
    int a;
    p2 =&a;
    p=&p2;
    **p=20;
    printf("%d",a);
}