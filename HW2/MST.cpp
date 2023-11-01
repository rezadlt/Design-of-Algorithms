#include <bits/stdc++.h>
#define pb push_back
#define F first
#define S second
#define debug(a) cout << (&a) << " : " << a << '\n'
#define fast ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0)
typedef long long ll;
typedef long double ld;
using namespace std;

const int MAX_N = 3e5 + 10;

set<pair<int, int>> inp;
pair<int, pair<int, int>> edges[MAX_N];
pair<int, int> idnt[MAX_N];
int par[MAX_N], level[MAX_N];

int get(int v) {
	if (par[v] != v) {
		par[v] = get(par[v]);
	}
	return par[v];
}

void join(int u, int v) {
	u = get(u), v = get(v);

	if (u == v) return;

	if (level[u] > level[v]) swap(u, v);
	par[u] = v;

	if (level[u] == level[v]) level[v]++;
}

int main() {
    fast;

    for (int i = 0; i < MAX_N; i++)
    	par[i] = i;

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
    	int u, v, w;
    	cin >> u >> v >> w;

    	inp.insert({w, i});
    	edges[i] = {w, {u, v}};
    }

    for (auto i = inp.begin(), j = inp.begin(); i != inp.end() && j != inp.end();) {
    	while (i != inp.end() && i->F == j->F) {
    		idnt[i->S].F = get(edges[i->S].S.F);
    		idnt[i->S].S = get(edges[i->S].S.S);

    		i++;
    	}

    	while (j != i) {
    		join(edges[j->S].S.F, edges[j->S].S.S);

    		j++;
    	}
    }

    for (int i = 0; i < MAX_N; i++) {
    	par[i] = i;
    	level[i] = 0;
    }

    int q;
    cin >> q;

    while (q--) {
    	int cnt;
    	cin >> cnt;

    	int c[cnt];
    	for (int i = 0; i < cnt; i++)  {
    		cin >> c[i];
    		c[i]--;
    	}

    	bool ans = true;
    	for (int i = 0; i < cnt; i++) {
    		if (get(idnt[c[i]].F) == get(idnt[c[i]].S)) {
    			ans = false;
    			break;
    		}

    		join(idnt[c[i]].F, idnt[c[i]].S);
    	}

    	if (ans) {
    		cout << "YES\n";
    	} else {
    		cout << "NO\n";
    	}

    	for (int i = 0; i < cnt; i++) {
    		par[idnt[c[i]].F] = idnt[c[i]].F;
    		par[idnt[c[i]].S] = idnt[c[i]].S;

    		level[idnt[c[i]].F] = 0;
    		level[idnt[c[i]].S] = 0;
    	}
    }

    return 0;
}