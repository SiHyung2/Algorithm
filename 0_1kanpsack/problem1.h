#include <stdio.h>
#define max(x, y) (x) > (y) ? (x) : (y)
#define n 4
#define bag_capacity 10

struct Thing {
    int weight, val;
};

int value[5][11];

int main() {
    Thing thing[5];
    bool selected[5] = { false, };
    thing[1] = { 5 ,10 };
    thing[2] = { 4 ,40 };
    thing[3] = { 6 ,30 };
    thing[4] = { 3 ,50 };
    int vi = 0, wi = 0;


    for (int j = 0; j <= bag_capacity; j++) {
        value[0][j] = 0;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= bag_capacity; j++) {
            wi = thing[i].weight;
            vi = thing[i].val;

            if (wi > j) {
                value[i][j] = value[i - 1][j];
            }
            else {
                value[i][j] = max(value[i - 1][j], vi + value[i - 1][j - wi]);

            }
        }
    }

    int pre_wi = 0;
    for (int j = 1; j <= bag_capacity; j++) {
        if (value[n][j] != value[n][j - 1]) {
            vi = value[n][j] - value[n][j - 1];
            wi = j - pre_wi;
            for (int index = 1; index <= n; index++) {
                if (selected[index] != true && thing[index].val == vi && thing[index].weight == wi) {
                    selected[index] = true;
                }
            }
            pre_wi = j;
        }
    }



    printf("value 표\n");
    for (int j = 0; j <= bag_capacity; j++) {
        printf("%d\t", j);
    }
    printf("\n");
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= bag_capacity; j++) {
            printf("%d\t", value[i][j]);
        }
        printf("\n");
    }

    printf("\n최대 가치 : %d만원 \n", value[n][bag_capacity]);
    printf("선택된 아이템 : ");
    for (int i = 1; i <= n; i++) {
        if (selected[i] == true)
            printf("Item %d  ", i);
    }

    return 0;
}
