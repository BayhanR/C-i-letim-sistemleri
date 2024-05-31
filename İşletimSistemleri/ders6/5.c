#include <stdio.h>
int sum(int array[], int size) {
    int total = 0;
    for (int i = 0; i < size; i++){
        total += array[i];
    }
    return total;
}
int arrayLength(int array[], int size) {
    return size;
}
int main() {
    int myArray[] = {1, 2, 3, 4, 5};
    int length = arrayLength(myArray, sizeof(myArray) / sizeof(myArray[0])); // Dizinin uzunluğunu hesaplayarak geçiriyoruz
    int result = sum(myArray, length);
    printf("Toplam: %d\n", result);
    return 0;
}
//malloc calloc realloc #include <stdlib.h>
