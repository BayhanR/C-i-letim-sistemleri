#include <stdio.h>

// Uzunluk fonksiyonu
int uzunluk(const char* str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

int main() {
    const char* str = "Merhabalar efendim";
    printf("Uzunluk: %d\n", uzunluk(str));
    return 0;
}
