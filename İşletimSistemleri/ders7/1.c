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

  