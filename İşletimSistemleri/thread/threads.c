#include <stdio.h>
#include <windows.h>
#include <pthread.h>

#define MAX_THREAD 10

typedef struct MyArguments{

    int vall;
}*PMYARG
int common_Thread_function(int n){
    int sonuc=2;
    if(n<0){
        printf("Argüman 0 dan küçük olamaz");
        ExitProcess();
    }
    switch(n){
        case 0: printf("0!=1\n");return 1;
        case 1: printf("1!=1\n");return 1;
        case 2: printf("2!=2\n");return 2;
    }
    for(int i=3; i<=n;i++){
        sonuç*=i;
    }
    return sonuc;
}
DWORD WINAPI threa_function_WIN32(LPVOID IpParam){
    PMYARG pDataArray=(PMYARG)IpParam;
    DWORD sonuc = common_Thread_function(pDataArray->vall);
    return sonuc;
}
void create_thread_WIN32(){
    PMYARG pDataArray(MAX_THREAD,);
    DWORD dwThreadIdArray(MAX_THREAD);
    HANDLE hThreadArray(MAX_THREAD);
    for(int i=0;i<MAX_THREAD;i++){
        pDataArray[i] =(PMYARG)HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,sizeof(struct MyArguments));
    }
    if(pDataArray[i]==NULL){
        printf("Argümanlar için yer tahsis edilmedi");
        ExitProcess(i);
    }
    pDataArray[i]->vall=i;

    hThreadArray[i]=CreateThread(NULL,0,thread_function_WIN32,pDataArray[i],0,&dwThreadIdArray(i));
    if(hThreadArray(i)==NULL){
        printf("Thread oluşturulmadı");
        ExitProcess(2);
    }
    WaitForMultipleObjects(MAX_THREAD,hThreadArray,TRUE,INFINITE);

    for(int i =0;i<MAX_THREAD;i++)<{
        CloseHandle(hThreadArray[i]);
        if(pDataArray[i] !=NULL){
         HeapFree(GetProcessHeap(),0,pDataArray[i]);
         pDataArray[i]=NULL;
        }
}
}
void* WINAPI thread_function_POSIX(void* IpParam){
        PMYARG pDataArray =(PMAYARG)IpParam;
        common_Thread_function(pDataArray->vall);
        return NULL;
}
void create_thread_POSIX(){
    PMYARG pDataArray(MAX_THREAD);
    PTHREAD_T TİD(MAX_THREAD);

    for(int i =0;i<MAX_THREAD;i++){
        pDataArray[i]=(PMYARG) malloc(sizeof(struct MyArgument));
        if(pDataArray[i]==NULL){
            printf("argümanlar için yer tahsis edilemedi");
            ExitProcess(i);
        }
    }
    pDataArray[i]->vall=i;

    int err=pthread_create(&tid[i],NULL,thread_function_POSIX,(void*)pDataArray[i]);

    if(err !=0){
        printf("thread oluşturulamadı");
        ExitProcess(2);
    }
}
 void create_thread(const char* arg){
    if(strcmp(arg,"WIN32")==0)create_thread_WIN32();
    else if(strcmp(arg,"POSIX")==0)
    create_thread_POSIX();
    else printf("HATALI ARGÜMAN");
    for(int i=0;i<MAX_THREAD;i++){
        pthread_join(tid[i],NULL);
    }
    for(int i =0;i<MAX_THREAD;i++){
        if(pDataArray[i]!=NULL){
            free(pDataArray[i]);
            pDataArray[i]=NULL;
        }
    }
 }


pthread_mutex_t mutex_lock;

void* hello(void* arg){
    char* name = (char*)arg;
    pthread_mutex_lock(&mutex_lock);
    printf("Hello, %s!\n", name);
    pthread_mutex_unlock(&mutex_lock);
    return NULL;
}

void* greet_each_other_thread(void* arg) {
    char* name = (char*)arg;
    pthread_mutex_lock(&mutex_lock);
    printf("Hello, %s!\n", name);
    pthread_mutex_unlock(&mutex_lock);
    return NULL;
}

void greet_each_other() {
    pthread_t tid[2];
    char* names[2] = {"Ahmet", "Zeynep"};

    if(pthread_mutex_init(&mutex_lock, NULL) != 0) {
        printf("Mutex hatası\n");
        exit(EXIT_FAILURE);
    }

    // İki iş parçacığını aynı anda oluştur
    int err1 = pthread_create(&tid[0], NULL, hello, (void*)names[0]);
    int err2 = pthread_create(&tid[1], NULL, greet_each_other_thread, (void*)names[1]);
    if (err1 != 0 || err2 != 0) {
        printf("İş parçacığı oluşturulamadı\n");
        exit(EXIT_FAILURE);
    }

    // İş parçacıklarını birleştir
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);

    pthread_mutex_destroy(&mutex_lock);
}

int main() {
    greet_each_other();
    return 0;
}
