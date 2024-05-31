#include <stdio.h>
struct  Point{
    int x;
    int y;
};
struct a
{
    char ch;
    int x;
};

int main(){
    struct Point p;
    p.x=10;
    p.y=20;
    printf("%d",sizeof(struct  Point));
    sizeof(p);
    struct a ch;
    a.ch='a';
    a.x=10;
    printf("%d",sizeof(struct a));
    
}
