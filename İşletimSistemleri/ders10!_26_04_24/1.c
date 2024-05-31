#include <stdio.h>
#include <stdlib.h>
typedef struct ProcessControlBlock {
    unsigned int program_counter;
} PCB;

typedef struct ProcessTable {
    unsigned int pid;
    PCB process_control_block;
    struct ProcessTable* next;
    struct ProcessTable* prev;
} PT;

int main() {
    PT* first = NULL;
    PT* last = NULL;
    
    PT* P = (PT*) malloc(sizeof(PT));
    if (P == NULL) {
        printf("Yer tahsis edilemedi");
        exit(1);
    }
    return 0;
}
typedef struct {
    unsigned int program_counter;
} PCB;

// Çift yönlü bağlı listemizin düğümü
typedef struct Node {
    unsigned int pid; // Process ID
    PCB pcb; // Process Control Block
    struct Node* next; // Sonraki düğümün adresi
    struct Node* prev; // Önceki düğümün adresi
} Node;

// Çift yönlü bağlı listemizin başlangıç düğümü
typedef struct {
    Node* head; // Listenin başı
    Node* tail; // Listenin sonu
} DoublyLinkedList;

// Yeni bir düğüm oluşturur ve veri ile doldurur
Node* createNode(unsigned int pid, PCB pcb) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Bellek tahsisi basarisiz!\n");
        exit(EXIT_FAILURE);
    }
    newNode->pid = pid;
    newNode->pcb = pcb;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Çift yönlü bağlı listeye bir düğüm ekler
void insertNode(DoublyLinkedList* list, unsigned int pid, PCB pcb) {
    Node* newNode = createNode(pid, pcb);
    if (list->head == NULL) {
        // Liste boşsa, yeni düğümü listenin başı ve sonu olarak ata
        list->head = newNode;
        list->tail = newNode;
    } else {
        // Listenin sonuna yeni düğümü ekle
        list->tail->next = newNode;
        newNode->prev = list->tail;
        list->tail = newNode;
    }
}

// Belirli bir PID'ye sahip işlemi sonlandırır
void terminateProcess(DoublyLinkedList* list, unsigned int pid) {
    Node* current = list->head;
    while (current != NULL) {
        if (current->pid == pid) {
            if (current == list->head && current == list->tail) {
                list->head = NULL;
                list->tail = NULL;
            } else if (current == list->head) {
                list->head = current->next;
                list->head->prev = NULL;
            } else if (current == list->tail) {
                list->tail = current->prev;
                list->tail->next = NULL;
            } else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
            }
            free(current);
            printf("Process with PID %u terminated.\n", pid);
            return;
        }
        current = current->next;
    }
    printf("Process with PID %u not found.\n", pid);
}
void listProcess(DoublyLinkedList* list) {
    Node* current = list->head;
    printf("Process List:\n");
    while (current != NULL) {
        printf("PID: %u, Program Counter: %u\n", current->pid, current->pcb.program_counter);
        current = current->next;
    }
}

int main() {

    return 0;
}
    