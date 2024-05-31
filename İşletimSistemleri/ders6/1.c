int main(){
    int*p;
    int a;
    p=&a;
    *p=10;
    printf("%p",&p);
    printf("%d",&a);
}