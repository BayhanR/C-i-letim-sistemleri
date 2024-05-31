#include <stdio.h>
#include <windows.h>

// Thread fonksiyonu
DWORD WINAPI thread_func(LPVOID lpParam) {
    printf("Merhaba, ben yeni bir thread'im!\n");
    Sleep(3000); // 3000 milisaniye uyku
    printf("Thread calismayi tamamladi.\n");
    return 0;
}

int main() {
    HANDLE thread_handle;
    thread_handle = CreateThread(NULL, 0, thread_func, NULL, 0, NULL);
    if (thread_handle == NULL) {
        fprintf(stderr, "Thread olusturma hatasi\n");
        return 1;
    }
    WaitForSingleObject(thread_handle, INFINITE);
    CloseHandle(thread_handle);
    return 0;
}
