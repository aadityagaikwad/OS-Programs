#include <stdio.h>
#include <stdlib.h>

struct Block {
    int size;
    int alloc; // 0 for free, 1 for allocated
};

void firstfit(struct Block *memory, int nblocks, int prosize) {
    for (int i = 0; i < nblocks; i++) {
        if (!memory[i].alloc && memory[i].size >= prosize) {
            memory[i].alloc = 1;
            printf("\nProcess allocated to Block %d", i + 1);
            return;
        }
    }
    printf("\nNo suitable block found for the process");
}

int main() {
    int nblocks;
    printf("\nEnter number of blocks: ");
    scanf("%d", &nblocks);

    if (nblocks <= 0) {
        printf("\nPlease enter a valid input.");
        return 1;
    }

    struct Block *memory = (struct Block *)malloc(nblocks * sizeof(struct Block));

    for (int i = 0; i < nblocks; i++) {
        printf("\nEnter block size: ");
        scanf("%d", &memory[i].size);
        memory[i].alloc = 0; // Initially, all blocks are free
    }

    int numpro;
    printf("\nEnter number of processes: ");
    scanf("%d", &numpro);

    for (int j = 0; j < numpro; j++) {
        int prosize;
        printf("\nEnter size of process: ");
        scanf("%d", &prosize);

        firstfit(memory, nblocks, prosize);
    }

    free(memory);

    return 0;
}
