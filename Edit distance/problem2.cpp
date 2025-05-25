#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

string dictionaryWord[3] = { "definitely", "defiantly", "define" };


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
    printf("사전 단어 : [%s, %s, %s]\n\n", dictionaryWord[0].c_str(), dictionaryWord[1].c_str(), dictionaryWord[2].c_str());

    Solution solution;
    string str;
    printf("str1 : ");
    getline(cin, str);
    int distance[3] = { 0, };
    string str_min = "";
    int distance_min = 0;
    for(int i = 0; i < 3; i++) {
        distance[i] = solution.minDistance(str, dictionaryWord[i]);
        if (i == 0) {
            str_min = dictionaryWord[i];
            distance_min = distance[i];
        }
        else if(i!=0&& distance[i]< distance[i-1]) {
            str_min = dictionaryWord[i];
            distance_min = distance[i];
        }
	}
    printf("추천: \"%s\" (edit distance %d)", str_min.c_str(), distance_min);
    return 0;
}