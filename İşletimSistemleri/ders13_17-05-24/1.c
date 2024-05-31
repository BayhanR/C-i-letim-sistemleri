#include <stdio.h>

int main() {
    // 100 elemanlı bir dizi tanımla ve değerlerini doldur
    int array[100];
    for (int i = 0; i < 100; i++) {
        array[i] = i + 1;  // 1'den 100'e kadar olan sayılar
    }

    // Toplamı tutacak değişkeni tanımla
    int sum = 0;

    // İşaretçi ile dizi üzerinde dolaşarak elemanları topla
    int *ptr = array;  // Dizinin ilk elemanına işaret eden bir işaretçi
    for (int i = 0; i < 100; i++) {
        sum += *(ptr + i);  // İşaretçinin işaret ettiği değeri toplama ekle
    }

    // Toplamı yazdır
    printf("Dizinin elemanlarının toplamı: %d\n", sum);

    return 0;
}
