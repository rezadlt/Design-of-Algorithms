#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 500 + 2, MAX_K = 100 + 2;

int dp[MAX_N][MAX_N][MAX_K];
int inp[MAX_N][MAX_N];

int main() {
    
    int n, k;
    cin >> n >> k;

    for (int i = 0; i < n; i++) {
    	for (int j = 0; j < n; j++) {
    		cin >> inp[i][j];
    	}
    }

    for (int i = 0; i < n; i++) {
    	for (int j = 0; j < n; j++) {
    		for (int c = 0; c <= k; c++) {
    			if (i > 0) {
	    			if (c > 0)
	    				dp[i][j][c] = dp[i - 1][j][c - 1];
	    			if (j > 0)
	    				dp[i][j][c] = max(dp[i][j][c], dp[i - 1][j - 1][c]);
	    			if (j < n - 1)
	    				dp[i][j][c] = max(dp[i][j][c], dp[i - 1][j + 1][c]);
    			}

    			dp[i][j][c] += inp[i][j];
    		}
    	}
    }

    int ans = 0;

    for (int i = 0; i < n; i++) {
    	for (int j = 0; j <= k; j++) {
    		ans = max(ans, dp[n - 1][i][j]);
    	}
    }

    cout << ans;

    return 0;
}