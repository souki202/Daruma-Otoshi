#include <iostream>
#include <cstring>
#include <algorithm>

constexpr int NUM = 300;
int w[NUM] = { 0 };
bool dp[NUM][NUM] = { {false} };
int ddp[NUM+1] = { 0 };

//a~a+1とa+2~b、･･･、a~dとd+1~r、･･･、a~b-2とb-1~bのどれかが落とせる判定。
bool isDroped(int a, int b) {
	if (b - a <= 1) return false;
	for (int i = a + 1; i < b; i += 2) {
		if (dp[a][i] && dp[i + 1][b]) return true;
	}
	return false;
}

int main() {
	int n;
	while (std::cin >> n && n) {
		std::memset(dp, 0, sizeof(dp));
		for (int i = 0; i < n; i++) std::cin >> w[i];

		for (int d = 1; d < n; d += 2) { //落とす間隔
			for (int i = 0; i < n - d; i++) { //落とす場所
				if ((d == 1 || dp[i + 1][i + d - 1]) && std::abs(w[i] - w[i + d]) <= 1){
					dp[i][i + d] = true; //間のブロックを全て落とせる
				}
				if (isDroped(i, i + d)) {
					dp[i][i + d] = true;
				}
			}
		}
		std::memset(ddp, 0, sizeof(ddp));
		for (int i = 0; i < n; ++i) {
			ddp[i + 1] = std::max(ddp[i + 1], ddp[i]);
			for (int j = i + 1; j < n; j += 2) {
				if (dp[i][j]) {
					ddp[j + 1] = std::max(ddp[j + 1], ddp[i] + j - i + 1);
				}
			}
		}
		std::cout << ddp[n] << std::endl;
	}
	return 0;
}
