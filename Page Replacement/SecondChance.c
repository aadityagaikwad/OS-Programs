#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int page;
    int second_chance;
} Frame;

void SecondChance(int n, int ref_string[], int m) {
    Frame *memory = (Frame *)malloc(n * sizeof(Frame));
    for (int i = 0; i < n; i++) {
        memory[i].page = -1;
        memory[i].second_chance = 0;
    }

    int pointer = 0;
    int page_faults = 0;

    for (int i = 0; i < m; i++) {
        int page = ref_string[i];
        int found = 0;

        for (int j = 0; j < n; j++) {
            if (memory[j].page == page) {
                memory[j].second_chance = 1;
                found = 1;
                break;
            }
        }

        if (!found) {
            while (memory[pointer].second_chance == 1) {
                memory[pointer].second_chance = 0;
                pointer = (pointer + 1) % n;
            }

            memory[pointer].page = page;
            memory[pointer].second_chance = 1;
            pointer = (pointer + 1) % n;
            page_faults++;
        }

        printf("\nFrame status after accessing page %d: ", page);
        for (int j = 0; j < n; j++) {
            if (memory[j].page != -1) {
                printf("%d ", memory[j].page);
            } else {
                printf("- ");
            }
        }
        printf("\n");
    }

    printf("\nTotal Page Faults: %d\n", page_faults);

    free(memory);
}

int main() {
    int n, m;
    printf("\nEnter number of frames: ");
    scanf("%d", &n);

    printf("\nEnter number of pages: ");
    scanf("%d", &m);

    int ref_string[m];
    printf("\nEnter the reference string: ");
    for (int i = 0; i < m; i++) {
        scanf("%d", &ref_string[i]);
    }

    SecondChance(n, ref_string, m);

    return 0;
}
