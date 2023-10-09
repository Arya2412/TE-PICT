#include <stdio.h>
#include <stdbool.h>

#define MAX_FRAMES 10
#define MAX_PAGES 100

int frames[MAX_FRAMES];
int pageReference[MAX_PAGES];
int numFrames, numPages;

int hit = 0, miss = 0;

void displayFrames() {
    printf("Frames: ");
    for (int i = 0; i < numFrames; i++) {
        if (frames[i] == -1)
            printf("X ");
        else
            printf("%d ", frames[i]);
    }
    printf("\n");
}

int findLRUIndex(int usedTime[]) {
    int minTime = usedTime[0];
    int index = 0;
    for (int i = 1; i < numFrames; i++) {
        if (usedTime[i] < minTime) {
            minTime = usedTime[i];
            index = i;
        }
    }
    return index;
}

bool isPageInFrame(int page) {
    for (int i = 0; i < numFrames; i++) {
        if (frames[i] == page)
            return true;
    }
    return false;
}

void FCFS() {
    for (int i = 0; i < numFrames; i++)
        frames[i] = -1;

    for (int i = 0; i < numPages; i++) {
        if (!isPageInFrame(pageReference[i])) {
            frames[miss % numFrames] = pageReference[i];
            miss++;
        }
        displayFrames();
    }
    hit = numPages - miss;
}

void LRU() {
    for (int i = 0; i < numFrames; i++)
        frames[i] = -1;

    int usedTime[MAX_FRAMES] = {0};

    for (int i = 0; i < numPages; i++) {
        if (!isPageInFrame(pageReference[i])) {
            int lruIndex = findLRUIndex(usedTime);
            frames[lruIndex] = pageReference[i];
            usedTime[lruIndex] = 0;
            miss++;
        }

        for (int j = 0; j < numFrames; j++)
            usedTime[j]++;

        displayFrames();
    }
    hit = numPages - miss;
}

void Optimal() {
    for (int i = 0; i < numFrames; i++)
        frames[i] = -1;

    for (int i = 0; i < numPages; i++) {
        if (!isPageInFrame(pageReference[i])) {
            int farthest = -1;
            int farthestIndex = -1;

            for (int j = 0; j < numFrames; j++) {
                int found = 0;
                for (int k = i + 1; k < numPages; k++) {
                    if (frames[j] == pageReference[k]) {
                        found = 1;
                        if (k > farthest) {
                            farthest = k;
                            farthestIndex = j;
                        }
                        break;
                    }
                }
                if (!found) {
                    farthestIndex = j;
                    break;
                }
            }

            frames[farthestIndex] = pageReference[i];
            miss++;
        }
        displayFrames();
    }
    hit = numPages - miss;
}

int main() {
    printf("Enter the number of frames: ");
    scanf("%d", &numFrames);

    printf("Enter the number of pages: ");
    scanf("%d", &numPages);

    printf("Enter the page reference string:\n");
    for (int i = 0; i < numPages; i++) {
        scanf("%d", &pageReference[i]);
    }

    int choice;
    do {
        printf("\nPage Replacement Algorithms:\n");
        printf("1. FCFS\n");
        printf("2. LRU\n");
        printf("3. Optimal\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                FCFS();
                break;
            case 2:
                LRU();
                break;
            case 3:
                Optimal();
                break;
            case 4:
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
        
        if (choice >= 1 && choice <= 3) {
            float hitRatio = (float)hit / numPages;
            printf("\nPage Hit Ratio: %.2f\n", hitRatio);
        }

    } while (choice != 4);

    return 0;
}
