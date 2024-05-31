
// #include <stdio.h>
 
// int main() {
    
    // int* p; // pointer tanımlama
//     int a;
//     p = &a; // pointer değer atama
//     printf("p adresi: %p\n", &p);
//     printf("a adresi: %p\n", &a);
//     a = 5;
//     printf("a degeri: %d\n", a);
//     *p = 10; // pointer kullanarak a'yı değiştirmek
//     printf("a degeri: %d", a);
 
//     return 0;
    
 
 
 
    
//     int a = 5;
//     int b = 10;
//     int* const pointer = &a;
//     //p = &b; // adres değişikliği yapılamaz
 
//     return 0;
 
 

//     int a = 5;
//     int b = 10;
//     const int* p = &a; // gösterdiği yerin değerini değiştirtmez
//     p = &b;
//     *p = 20; // hata verir
 
//     return 0;
    
//  }

// #include <stdio.h>
 
// int main() {
    
//     int* p; // pointer tanımlama
//     int a;
//     p = &a; // pointer değer atama
//     printf("p adresi: %p\n", &p);
//     printf("a adresi: %p\n", &a);
//     a = 5;
//     printf("a degeri: %d\n", a);
//     *p = 10; // pointer kullanarak a'yı değiştirmek
//     printf("a degeri: %d", a);
 
//     return 0;
    
 
 
 
    
//     int a = 5;
//     int b = 10;
//     int* const pointer = &a;
//     //p = &b; // adres değişikliği yapılamaz
 
//     return 0;
    
 
 
    
//     int a = 5;
//     int b = 10;
//     const int* p = &a; // gösterdiği yerin değerini değiştirtmez
//     p = &b;
//     *p = 20; // hata verir
 
//     return 0;
    
// }
// semafor kullanımı, mutex (kilit mekanizmaları)
// faktoriyel hesaplayıcı (posix ve win32de)
 
#include <stdio.h>
#include <windows.h>
#include <pthread.h>
 
#define MAX_THREADS 10
 
// thread'a giden argümanın yapısını tanımlıyor
typedef struct MyArguments
{
    int val1;
} *PMYARG;
 
int common_thread_function(int n)
{
    int sonuc = 2;
 
    if (n < 0)
    {
        printf("Argüman sıfırdan küçük olamaz!");
        ExitProcess(3);
    }
 
    switch (n)
    {
    case 0:
        printf("0! = 1 \n");
        return 1;
    case 1:
        printf("1! = 1 \n");
        return 1;
    case 2:
        printf("2! = 2 \n");
        return 2;
    }
 
    for (int i = 3; i <= n; i++)
        sonuc *= i;
 
    printf("%d! = %d\n", n, sonuc);
 
    return sonuc;
}
 
DWORD WINAPI thread_function_WIN32(LPVOID lpParam)
{
    PMYARG pDataArray = (PMYARG)lpParam;
 
    DWORD sonuc = common_thread_function(pDataArray->val1);
 
    return sonuc;
}
 
void create_thread_WIN32()
{
    PMYARG pDataArray[MAX_THREADS];
    DWORD dwThreadIdArray[MAX_THREADS];
    HANDLE hThreadArray[MAX_THREADS];
 
    for (int i = 0; i < MAX_THREADS; i++)
    {
        // thread fonksiyonuna gönderilecek argümanlar için bellekte yer tahsis et
        pDataArray[i] = (PMYARG)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(struct MyArguments));
 
        if (pDataArray[i] == NULL)
        {
            printf("Argümanlar için yer tahsis edilemedi!");
            ExitProcess(1);
        }
 
        pDataArray[i]->val1 = i;
 
        // thread oluştur
        hThreadArray[i] = CreateThread(NULL, 0, thread_function_WIN32, pDataArray[i], 0, &dwThreadIdArray[i]);
 
        if (hThreadArray[i] == NULL)
        {
            printf("Thread oluşturulamadı!");
            ExitProcess(2);
        }
    }
 
    // Threadları sonlanana kadar bekle
    WaitForMultipleObjects(MAX_THREADS, hThreadArray, TRUE, INFINITE);
 
    // tüm threadları handlelarını kapat ve tahsis edilen belleği serbest bırak
    for (int i = 0; i < MAX_THREADS; i++)
    {
        CloseHandle(hThreadArray[i]);
        if (pDataArray[i] != NULL)
        {
            HeapFree(GetProcessHeap(), 0, pDataArray[i]);
            pDataArray[i] = NULL;
        }
    }
}
 
void *WINAPI thread_function_POSIX(void *lpParam)
{
    PMYARG pDataArray = (PMYARG)lpParam;
 
    common_thread_function(pDataArray->val1);
 
    return NULL;
}
 
void create_thread_POSIX()
{
    PMYARG pDataArray[MAX_THREADS];
    pthread_t tid[MAX_THREADS];
 
    for (int i = 0; i < MAX_THREADS; i++)
    {
        // Thread fonksiyonuna gönderilecek argümanlar için bellekten yer tahsis et
        pDataArray[i] = (PMYARG)malloc(sizeof(struct MyArguments));
        if (pDataArray[i] == NULL)
        {
            printf("Argümanlar İçin Yer Tahsis Edildi!");
            ExitProcess(1);
        }
 
        pDataArray[i]->val1 = i;
 
        // Thread oluştur
        int err = pthread_create(&tid[i], NULL, thread_function_POSIX, (void *)pDataArray[i]);
 
        if (err != 0)
        {
            printf("Thrad oluşturlamadı!");
            ExitProcess(2);
        }
    }
 
    // threadlar sonlanana kadar bekle
    for (int i = 0; i < MAX_THREADS; i++)
        pthread_join(tid[i], NULL);
 
    // tüm thread handlelarını kapat ve tahsis edilen belleği serbest bırak
    for (int i = 0; i < MAX_THREADS; i++)
    {
        if (pDataArray[i] != NULL)
        {
            free(pDataArray[i]);
            pDataArray[i] = NULL;
        }
    }
}
 
void create_thread(const char *arg)
{
    if (strcmp(arg, "WIN32") == 0)
        create_thread_WIN32();
    else if (strcmp(arg, "POSIX") == 0)
        create_thread_POSIX();
    else
        printf("HATALI ARGÜMAN");
}
 
int main()
{
    create_thread("WIN32");
    return (EXIT_SUCCESS);
}
[09:39] ÖZGÜR YURT
// 1 fonksiyon olacak tüm threadlar o fonksiyonu kullanacak
 
#include <pthread.h>
#include <stdio.h>
 
// bu programı birden fazla threadın tek bir fonksiyonu ortak kullanabileceği şekilde düzenle
// posix ile yapılmış bu programı winapi ile yap
pthread_mutex_t mutex_lock;     // kilit değişkeni
typedef void *(*funcs)(void *); // fonksiyonların başlangıç adresini tutan yapı (typedef = delegate)
 
void *hello(void *arg)
{
    pthread_mutex_lock(&mutex_lock);
 
    printf("Hello %s\n", arg);
    for (int i = 0; i < (0xFFFFFF); i++)
        ; // beklet
 
    pthread_mutex_unlock(&mutex_lock);
 
    return NULL;
}
 
int greet_each_other()
{
    int i = 0, err;
    pthread_t tid[2];
    funcs f[1] = {&hello};
    void *args[2] = {"Ahmet", "Zeynep"};
 
    if (pthread_mutex_init(&mutex_lock, NULL) != 0)
    {
        printf("mutex hatası!");
        return 1;
    }
 
    while (i < 2)
    {
        err = pthread_create(&(tid[i]), NULL, f[0], args[i]);
        if (err != 0)
        {
            printf("Thread-%d oluşturulamadı!", i);
            return 2;
        }
        i++;
    }
 
    for (int i = 0; i < 2; i++)
        pthread_join(tid[i], NULL);
 
    pthread_mutex_destroy(&mutex_lock);
 
    return 0;
}
 
int main(int argc, char **argv)
{
    greet_each_other();
 
    return (1);
}