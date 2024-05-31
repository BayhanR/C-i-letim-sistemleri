#include <stdio.h>
int topla(int a,int b);
int main(){
    int toplam=topla(3,8);
    printf("%d",toplam);
    return 0;
}
int topla(int a,int b)
{
    return a+b;
}
//stack'e atılacak ifadeler neler
//stack pointer,base pointer,argümanlar nasıl gönderilir