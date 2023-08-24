#include <cstring>
#include <iostream>
#include <vector>

const int DIAGONAL = -3;
const int RIGHT = -1;
const int DOWN = -2;

int m, n, o, dp[101][101][101], backtrack[100][100][100];
char s1[101], s2[101], virus[101];

inline void maxify(int i, int j, int k, int val, int back) {
  if (dp[i][j][k] < val) {
    dp[i][j][k] = val;
    backtrack[i][j][k] = back;
  }
}

int lcs() {
  m = std::strlen(s1);
  n = std::strlen(s2);
  o = std::strlen(virus);

  std::memset(dp, 0, sizeof(dp));

  for (int i = m - 1; i >= 0; i--) {
    for (int j = n - 1; j >= 0; j--) {
      for (int k = o - 1; k >= 0; k--) {
        maxify(i, j, k, dp[i + 1][j][k], DOWN);
        maxify(i, j, k, dp[i][j + 1][k], RIGHT);
        if (s1[i] == s2[j]) {
          if (s1[i] != virus[k]) {
            maxify(i, j, k, dp[i + 1][j + 1][0] + 1, 0);
          } else if (k < o - 1) {
            maxify(i, j, k, dp[i + 1][j + 1][k + 1] + 1, k + 1);
          }
        }
      }
    }
  }

  return dp[0][0][0];
}

int main() {
  std::cin >> s1 >> s2 >> virus;

  if (lcs() == 0) {
    std::cout << "0" << std::endl;
    return 0;
  }
  int i = 0, j = 0, k = 0;

  while (i < m && j < n) {
    int ni, nj, nk;
    switch (backtrack[i][j][k]) {
    case DOWN:
      ni = i + 1;
      nj = j;
      nk = k;
      break;
    case RIGHT:
      ni = i;
      nj = j + 1;
      nk = k;
      break;
    default:
      ni = i + 1;
      nj = j + 1;
      nk = backtrack[i][j][k];
      break;
    }

    int value = (ni < m && nj < n ? dp[ni][nj][nk] : 0);
    if (value != dp[i][j][k]) {
      std::cout << s1[i];
    }

    i = ni, j = nj, k = nk;
  }

  std::cout << std::endl;

  return 0;
}
