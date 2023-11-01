#include <stdio.h>

int n, nf;
int in[100];
int p[50];
int hit = 0;
int i, j, k;
int pgfaultcnt = 0;

void getData() {
    printf("Enter the length of the page reference sequence: ");
    scanf("%d", &n);
    printf("Enter the page reference sequence: ");
    for (i = 0; i < n; i++)
        scanf("%d", &in[i]);
    printf("Enter the number of frames: ");
    scanf("%d", &nf);
}

void initialize() {
    pgfaultcnt = 0;
    for (i = 0; i < nf; i++)
        p[i] = 9999;
}

int isHit(int data) {
    hit = 0;
    for (j = 0; j < nf; j++) {
        if (p[j] == data) {
            hit = 1;
            break;
        }
    }
    return hit;
}

void dispPages(char *algoName) {
    printf("Current Pages in Memory for %s: ", algoName);
    for (k = 0; k < nf; k++) {
        if (p[k] != 9999)
            printf("%d ", p[k]);
    }
    printf("\n");
}

void dispPgFaultCnt(int pageFaults, char *algoName) {
    printf("Total number of page faults for %s: %d\n", algoName, pageFaults);
}

void fifo() {
    char algoName[] = "FIFO";
    initialize();
    for (i = 0; i < n; i++) {
        printf("For page %d using %s: ", in[i], algoName);
        if (isHit(in[i]) == 0) {
            for (k = 0; k < nf - 1; k++)
                p[k] = p[k + 1];
            p[k] = in[i];
            pgfaultcnt++;
            dispPages(algoName);
        } else
            printf("No page fault\n");
    }
    dispPgFaultCnt(pgfaultcnt, algoName);
}

void optimal() {
    char algoName[] = "Optimal";
    initialize();
    int near[50];
    for (i = 0; i < n; i++) {
        printf("For page %d using %s: ", in[i], algoName);
        if (isHit(in[i]) == 0) {
            for (j = 0; j < nf; j++) {
                int pg = p[j];
                int found = 0;
                for (k = i; k < n; k++) {
                    if (pg == in[k]) {
                        near[j] = k;
                        found = 1;
                        break;
                    } else
                        found = 0;
                }
                if (!found)
                    near[j] = 9999;
            }
            int max = -9999;
            int repindex;
            for (j = 0; j < nf; j++) {
                if (near[j] > max) {
                    max = near[j];
                    repindex = j;
                }
            }
            p[repindex] = in[i];
            pgfaultcnt++;
            dispPages(algoName);
        } else
            printf("No page fault\n");
    }
    dispPgFaultCnt(pgfaultcnt, algoName);
}

void lru() {
    char algoName[] = "LRU";
    initialize();
    int least[50];
    for (i = 0; i < n; i++) {
        printf("For page %d using %s: ", in[i], algoName);
        if (isHit(in[i]) == 0) {
            for (j = 0; j < nf; j++) {
                int pg = p[j];
                int found = 0;
                for (k = i - 1; k >= 0; k--) {
                    if (pg == in[k]) {
                        least[j] = k;
                        found = 1;
                        break;
                    } else
                        found = 0;
                }
                if (!found)
                    least[j] = -9999;
            }
            int min = 9999;
            int repindex;
            for (j = 0; j < nf; j++) {
                if (least[j] < min) {
                    min = least[j];
                    repindex = j;
                }
            }
            p[repindex] = in[i];
            pgfaultcnt++;
            dispPages(algoName);
        } else
            printf("No page fault\n");
    }
    dispPgFaultCnt(pgfaultcnt, algoName);
}

int main() {
    int choice;
    while (1) {
        printf("Page Replacement Algorithms\n");
        printf("1. Enter data\n2. FIFO\n3. Optimal\n4. LRU\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                getData();
                break;
            case 2:
                fifo();
                break;
            case 3:
                optimal();
                break;
            case 4:
                lru();
                break;
            default:
                return 0;
                break;
        }
    }
}
