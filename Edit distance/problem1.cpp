#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

class Solution {
public:
    int dp[502][502]{};

    int minDistance(string str1, string str2) {
        for (int i = 0; i < str1.size(); i++)
            dp[i + 1][0] = i + 1;
        for (int j = 0; j < str2.size(); j++)
            dp[0][j + 1] = j + 1;

        for (int i = 1; i <= str1.size(); i++)
        {
            for (int j = 1; j <= str2.size(); j++)
            {
                if (str1[i - 1] == str2[j - 1])
                    dp[i][j] = dp[i - 1][j - 1];
                else
                    dp[i][j] = min(min(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]) + 1;
            }
        }
        return dp[str1.size()][str2.size()];
    }

    void printDPTable(string str1, string str2) {
        for (int i = 0; i <= str1.size(); i++) {
            for (int j = 0; j <= str2.size(); j++) {
                printf("%3d ", dp[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }
};


int main(void) {
    Solution solution;
    string str1;
    printf("str1 : ");
    getline(cin, str1);
    string str2;
    printf("str2 : ");
    getline(cin, str2);

    int result = solution.minDistance(str1, str2);
    solution.printDPTable(str1, str2);
    printf("ÃÖ¼Ò edit distance: %d\n", result);

    return 0;
}