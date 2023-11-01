#include <bits/stdc++.h>
#define pb push_back
#define F first
#define S second
#define debug(a) cout << (&a) << " : " << a << '\n'
#define fast ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0)
typedef long long ll;
typedef long double ld;
using namespace std;

const int MAX_N = 200 + 10;

set<int> G[MAX_N];
int par[MAX_N];
int weight[MAX_N][MAX_N];
bool check[MAX_N], pick[MAX_N];

bool bfs(int s, int t) {
	queue<int> q;

    bool mark[MAX_N];
    memset(mark, 0, MAX_N);

	q.push(s);
	mark[s] = true;
	par[s] = -1;

	while (!q.empty()) {
		int v = q.front();
		q.pop();

		for (auto u : G[v]) {
            if (!mark[u] && weight[v][u] != 0 && !check[u]) {
                if (u == t) {
                    par[u] = v;
                    return true;
                }

                q.push(u);
                par[u] = v;
                mark[u] = true;
            }
        }
	}

	return false;
}

int maxFlow(int s, int t) {
	int ans = 0;

	while (bfs(s, t)) {
		int pathFlow = -1;
		for (int k = t; k != s; k = par[k]) {
			if (weight[par[k]][k] == -1) continue;

			if (pathFlow == -1)
				pathFlow = weight[par[k]][k];
			pathFlow = min(pathFlow, weight[par[k]][k]);
		}
		for (int k = t; k != s; k = par[k]) {
			if (weight[par[k]][k] != -1) weight[par[k]][k] -= pathFlow;
			if (weight[k][par[k]] != -1) weight[k][par[k]] += pathFlow;
		}

		ans += pathFlow;
	}

	return ans;
}

int main() {
    fast;

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; i++) {
    	int c;
    	cin >> c;

    	G[2 * (i + 1) + 1].insert(MAX_N - 2);
    	G[MAX_N - 2].insert(2 * (i + 1) + 1);

    	weight[2 * (i + 1) + 1][MAX_N - 2] = c;
    }
	for (int i = 0; i < n; i++) {
    	int c;
    	cin >> c;

    	G[MAX_N - 1].insert(2 * (i + 1));
    	G[2 * (i + 1)].insert(MAX_N - 1);

    	weight[MAX_N - 1][2 * (i + 1)] = c;

    }

    for (int i = 0; i < m; i++) {
    	int u, v;
    	cin >> u >> v;

    	G[2 * u].insert(2 * v + 1);
    	G[2 * v + 1].insert(2 * u);

    	weight[2 * u][2 * v + 1] = -1;
    }

    cout << maxFlow(MAX_N - 1, MAX_N - 2) << '\n';

    do {
    	bool did = false;
    	for (int i = 1; i <= n; i++) {
    		if (weight[MAX_N - 1][2 * i] && !check[2 * i]) {
    			did = true;
    			check[2 * i] = true;
    			for (auto j : G[2 * i]) {
    				if (j != MAX_N - 1) {
    					pick[j] = true;
    					check[j] = true;

    					weight[j][MAX_N - 2] = weight[j][2 * i];
    					weight[j][2 * i] = 0;
    				}
    			}
    		}
    		if (weight[2 * i + 1][MAX_N - 2] && !check[2 * i + 1]) {
    			did = true;
    			check[2 * i + 1] = true;
    			for (auto j : G[2 * i + 1]) {
    				if (j != MAX_N - 2) {
    					pick[j] = true;
    					check[j] = true;

    					weight[MAX_N - 1][j] = weight[2 * i + 1][j];
    					weight[2 * i + 1][j] = 0;
    				}
    			}
    		}
    	}

    	if (!did) {
    		for (int i = 1; i <= n; i++) {
	    		if (!check[2 * i]) {
	    			pick[2 * i] = true;
	    			check[2 * i] = true;
	    		}
    		}
    	}
    } while (maxFlow(MAX_N - 1, MAX_N - 2));

    int cnt = 0;
    for (int i = 0; i < 2 * (n + 1); i++)
    	if (pick[i])
    		cnt++;

    cout << cnt << '\n';

    for (int i = 0; i < 2 * (n + 1); i++) {
    	if (pick[i]) cout << i / 2 << ' ' << (i % 2 ? "in" : "out") << '\n';
    }

    return 0;
}