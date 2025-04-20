#include<stdio.h>
#include <iostream>

#define SET_SIZE 10
#define SUBSET_SIZE 10
#define TRUE 1
#define FALSE 0


using namespace std;

int flag[SET_SIZE];

void flagInit() {
    for (int i = 0; i < SET_SIZE; i++) {
        flag[i] = TRUE;
    }
}

typedef struct Subsets {
    int* sub;
    int size;
} Subsets;

void subsetIncoding(Subsets subsets[], int* sub[], int subSize[]) {
    for (int i = 0; i < SUBSET_SIZE; i++) {
        subsets[i].sub = sub[i];
        subsets[i].size = subSize[i];
    }
}


bool isEmpty() {
    for (int i = 0; i < SET_SIZE; i++) {
        if (flag[i] == TRUE)
            return FALSE;
    }
    return TRUE;
}


int selectSet(int u[], Subsets subsets[]) {
    int index = 0, selectedIndex = -1, count = 0, preCount = 0;

    for (int i = 0; i < SUBSET_SIZE; i++) {
        count = 0;
        for (int j = 0; j < SET_SIZE; j++) {

            if (flag[j] == FALSE) {
                continue;
            }
            for (int k = 0; k < subsets[i].size; k++) {

                if (u[j] == subsets[i].sub[k]) {
                    count++;
                    break;
                }
            }
        }

        if (count == 0) {
            continue;
        }


        if (preCount < count) {
            selectedIndex = i;
            preCount = count;
        }
    }

    return selectedIndex;
}


void subtractSet(int u[], Subsets subsets[], int selectedIndex) {
    for (int i = 0; i < SET_SIZE; i++) {

        if (flag[i] == FALSE) {
            continue;
        }
        for (int j = 0; j < subsets[selectedIndex].size; j++) {
            if (u[i] == subsets[selectedIndex].sub[j]) {
                flag[i] = FALSE;
                break;
            }
        }
    }
}

void printSubset(Subsets subsets[], int selectedIndex) {
    printf("선택된 집합 s%d = { %d", selectedIndex + 1, subsets[selectedIndex].sub[0]);
    for (int x = 1; x < subsets[selectedIndex].size; x++) {
        printf(", %d", subsets[selectedIndex].sub[x]);
    }
    printf(" }\n");
}

void printRemaining(int u[], Subsets subsets[], int selectedIndex) {
    cout << "선택된 집합을 제외한 나머지 원소: ";
    for (int i = 0; i < SET_SIZE; i++) {
        if (flag[i] == TRUE) {
            cout << u[i] << " ";
        }
    }
    cout << endl;
}

void setCover(int u[], Subsets subsets[]) {
    flagInit();

    while (!isEmpty()) {
        int selectedIndex = selectSet(u, subsets);
        if (selectedIndex == -1) {
            cout << "더이상 커버링할 수 있는 부분집합이 없습니다." << endl;
            printRemaining(u, subsets, selectedIndex);
            break;
        }

        subtractSet(u, subsets, selectedIndex);
        printSubset(subsets, selectedIndex);
    }
}

void printAllsets(int u[], Subsets subsets[]) {
    printf("전체집합: \n");
    printf("{ %d", u[0]);
    for (int i = 1; i < SET_SIZE; i++) {
        printf(", %d ", u[i]);
    }
    printf(" }\n");

    printf("모든 부분집합:\n");
    for (int i = 0; i < SUBSET_SIZE; i++) {
        printf("s%d = { %d", i + 1, subsets[i].sub[0]);
        for (int j = 1; j < subsets[i].size; j++) {
            printf(", %d", subsets[i].sub[j]);
        }
        printf(" }\n");
    }
    printf("-------------------------\n");
}



int main(void) {
    int u[SET_SIZE] = { 1,2,3,4,5,6,7,8,9,10 };
    int s1[] = { 1,2,3,8 };
    int s2[] = { 1,2,3,4,8 };
    int s3[] = { 1,2,3,4 };
    int s4[] = { 2,3,4,5,7,8 };
    int s5[] = { 4,5,6,7 };
    int s6[] = { 5,6,7,9,10 };
    int s7[] = { 4,5,6,7 };
    int s8[] = { 1,2,4,8 };
    int s9[] = { 6,9 };
    int s10[] = { 6,10 };
    Subsets subsets[SUBSET_SIZE];
    int* sub[SUBSET_SIZE] = { s1, s2, s3, s4, s5, s6, s7, s8, s9, s10 };
    int subSize[SUBSET_SIZE] = { 4,5,4,6,4,5,4,4,2,2 };
    subsetIncoding(subsets, sub, subSize);

    printAllsets(u, subsets);

    setCover(u, subsets);

    return 0;
}