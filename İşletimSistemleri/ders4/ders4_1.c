#include <stdio.h>
#include <conio.h>
int main(){
    int a,toplam=0;
    printf("bir sayi giriniz");
    scanf("%d",&a);
    printf("girilen sayi:%d",a);
    if(a%2==0){
        printf("sayi cifttir");}
    else
        {printf("sayi tektir");}
    for (int i = 1; i < a; i++)
    {
        toplam+=i;
    }
    printf("Toplam:%d",toplam);
    getch();
    return 0;
}