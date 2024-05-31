#include <stdio.h>
#include <windows.h>

// Mutex'i tanımla
HANDLE mutex_lock;

// Thread işlevi
DWORD WINAPI hello(LPVOID arg)
{
    // Mutex'i kilitle
    WaitForSingleObject(mutex_lock, INFINITE);

    // Argümanı al ve yazdır
    char *name = (char *)arg;
    printf("Hello %s\n", name);

    // Beklet
    for (int i = 0; i < 0xFFFFFF; i++)
        ;

    // Mutex'i serbest bırak
    ReleaseMutex(mutex_lock);

    return 0;
}

// Her birine selam ver
int greet_each_other()
{
    // Mutex'i oluştur
    mutex_lock = CreateMutex(NULL, FALSE, NULL);
    if (mutex_lock == NULL)
    {
        printf("Mutex hatası!");
        return 1;
    }

    // Threadlerin tanımlandığı ve başlatıldığı bir döngü
    HANDLE threads[2];
    char *names[2] = {"Ahmet", "Zeynep"};
    for (int i = 0; i < 2; i++)
    {
        // Thread oluştur
        threads[i] = CreateThread(NULL, 0, hello, names[i], 0, NULL);
        if (threads[i] == NULL)
        {
            printf("Thread-%d oluşturulamadı!", i);
            return 2;
        }
    }

    // Thread'lerin bitmesini bekle
    WaitForMultipleObjects(2, threads, TRUE, INFINITE);

    // Mutex'i temizle
    CloseHandle(mutex_lock);

    return 0;
}

// Program giriş noktası
int main()
{
    greet_each_other();

    return 0;
}
