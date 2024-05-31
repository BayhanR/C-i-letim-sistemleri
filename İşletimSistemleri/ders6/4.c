#include <stdio.h>
int main(){
    int arr[10];
    int* p;
    p=arr;
    for (int i = 0; i < 10; i++)
    {
        *p++=i;
    }
    for (int i = 0; i < 10; i++)
    {
        printf("%d\n",arr[i]);
    }
    return 0;

}
int fonksiyon(){

}

