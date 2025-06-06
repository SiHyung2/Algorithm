#include <stdio.h>
#include <limits.h>
#define max(x, y) ((x) > (y) ? (x) : (y))
#define n 4
#define bag_capacity 10

struct Thing {
    int weight, val;
};
struct State {
    int val;    // �� ��ġ
    int weight; // �޼��� �� ����
};

State state[5][5][11]; // [i][k][j]

void print_state_table() {
    for (int i = 0; i <= n; i++) {
        printf("==== i = %d ��° ���Ǳ��� ��� ====\n", i);
        for (int k = 0; k <= n; k++) {
            printf("������ ���� ���� k = %d:\n", k);
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

    // �ʱ�ȭ
    for (int i = 0; i <= n; i++)
        for (int k = 0; k <= n; k++)
            for (int j = 0; j <= bag_capacity; j++)
                state[i][k][j] = { 0, 0 };

    for (int i = 1; i <= n; i++) {
        for (int k = 0; k <= i; k++) {
            for (int j = 0; j <= bag_capacity; j++) {
                // ���� ���� ����
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

    // ���� ��� ã��
    State best = { 0, 0 };
    for (int k = 0; k <= n; k++) {
        for (int j = 0; j <= bag_capacity; j++) {
            State s = state[n][k][j];
            if (s.val <= 80 && (s.val > best.val || (s.val == best.val && s.weight < best.weight))) {
                best = s;
            }
        }
    }

    // dp ǥ ����ϱ�
    print_state_table();

    // ������ ���� ã��
    int difference_va�� = 0, difference_weight = 0;

    printf("===================================================================================\n");
    printf("������ ����: \n");
    for (int j = 1; j <= bag_capacity; j++) {
        difference_va�� = state[n][n][j].val - state[n][n][j - 1].val;
        difference_weight = state[n][n][j].weight - state[n][n][j - 1].weight;

        if (difference_weight != 0) {
            for (int index = 1; index <= n; index++) {

                if (thing[index].val == difference_va�� && thing[index].weight == difference_weight) {
                    printf("   Item %d (%d kg, %d ����)\n", index, thing[index].weight, thing[index].val);
                }
            }
        }
    }
    printf("===================================================================================\n");
    printf("�ִ� ��ġ: %d, �� ����: %d\n", best.val, best.weight);
    return 0;
}
