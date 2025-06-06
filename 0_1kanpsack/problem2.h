#include <stdio.h>
#include <limits.h>
#define max(x, y) ((x) > (y) ? (x) : (y))
#define n 4
#define bag_capacity 10

struct Thing {
    int weight, val;
};
struct State {
    int val;    // 총 가치
    int weight; // 달성한 총 무게
};

State state[5][5][11]; // [i][k][j]

void print_state_table() {
    for (int i = 0; i <= n; i++) {
        printf("==== i = %d 번째 물건까지 고려 ====\n", i);
        for (int k = 0; k <= n; k++) {
            printf("선택한 물건 개수 k = %d:\n", k);
            for (int j = 0; j <= bag_capacity; j++) {
                State s = state[i][k][j];
                if (s.val == 0 && s.weight == 0)
                    printf("  -   ");
                else
                    printf("(%2d,%2d) ", s.val, s.weight);
            }
            printf("\n");
        }
        printf("\n");
    }
}

int main() {
    Thing thing[5];
    thing[1] = { 5 ,10 };
    thing[2] = { 4 ,40 };
    thing[3] = { 6 ,30 };
    thing[4] = { 3 ,50 };

    // 초기화
    for (int i = 0; i <= n; i++)
        for (int k = 0; k <= n; k++)
            for (int j = 0; j <= bag_capacity; j++)
                state[i][k][j] = { 0, 0 };

    for (int i = 1; i <= n; i++) {
        for (int k = 0; k <= i; k++) {
            for (int j = 0; j <= bag_capacity; j++) {
                // 이전 상태 복사
                state[i][k][j] = state[i - 1][k][j];

                if (k > 0 && j >= thing[i].weight) {
                    State prev = state[i - 1][k - 1][j - thing[i].weight];
                    int new_val = prev.val + thing[i].val;
                    int new_weight = prev.weight + thing[i].weight;

                    if (new_val > state[i][k][j].val ||
                        (new_val == state[i][k][j].val && new_weight < state[i][k][j].weight)) {
                        state[i][k][j] = { new_val, new_weight };
                    }
                }
            }
        }
    }

    // 최적 결과 찾기
    State best = { 0, 0 };
    for (int k = 0; k <= n; k++) {
        for (int j = 0; j <= bag_capacity; j++) {
            State s = state[n][k][j];
            if (s.val <= 80 && (s.val > best.val || (s.val == best.val && s.weight < best.weight))) {
                best = s;
            }
        }
    }

    // dp 표 출력하기
    print_state_table();

    // 선택한 물건 찾기
    int difference_vaㅣ = 0, difference_weight = 0;

    printf("===================================================================================\n");
    printf("선택한 물건: \n");
    for (int j = 1; j <= bag_capacity; j++) {
        difference_vaㅣ = state[n][n][j].val - state[n][n][j - 1].val;
        difference_weight = state[n][n][j].weight - state[n][n][j - 1].weight;

        if (difference_weight != 0) {
            for (int index = 1; index <= n; index++) {

                if (thing[index].val == difference_vaㅣ && thing[index].weight == difference_weight) {
                    printf("   Item %d (%d kg, %d 만원)\n", index, thing[index].weight, thing[index].val);
                }
            }
        }
    }
    printf("===================================================================================\n");
    printf("최대 가치: %d, 총 무게: %d\n", best.val, best.weight);
    return 0;
}
