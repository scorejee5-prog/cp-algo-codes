#include <bits/stdc++.h>
using namespace std;

#define int long long

const int MAXN = 5005;
const long long INF = 1e18;

int n, m, T;
vector<pair<int,int>> adj[MAXN];
vector<pair<int,int>> rev_adj[MAXN];

long long dp[MAXN][MAXN];
vector<int> path;

void dijkstra_like() {
    using state = pair<long long, pair<int,int>>;
    priority_queue<state, vector<state>, greater<state>> pq;

    dp[1][1] = 0;
    pq.push({0, {1, 1}});

    while (!pq.empty()) {
        auto [dist, p] = pq.top();
        pq.pop();

        int k = p.first;
        int u = p.second;

        if (dist != dp[u][k]) continue;
        if (dist > T) continue;

        for (auto [v, w] : adj[u]) {
            if (dp[v][k + 1] > dp[u][k] + w) {
                dp[v][k + 1] = dp[u][k] + w;
                pq.push({dp[v][k + 1], {k + 1, v}});
            }
        }
    }
}

void reconstruct(int v, int k) {
    path.push_back(v);
    if (v == 1) return;

    for (auto [u, w] : rev_adj[v]) {
        if (dp[u][k - 1] + w == dp[v][k]) {
            reconstruct(u, k - 1);
            return;
        }
    }
}

void solve() {
    cin >> n >> m >> T;

    for (int i = 0; i < m; i++) {
        int u, v, t;
        cin >> u >> v >> t;
        adj[u].emplace_back(v, t);
        rev_adj[v].emplace_back(u, t);
    }

    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= n; j++)
            dp[i][j] = INF;

    dijkstra_like();

    for (int k = n; k >= 0; k--) {
        if (dp[n][k] <= T) {
            cout << k << "\n";
            reconstruct(n, k);

            reverse(path.begin(), path.end());

            for (int x : path)
                cout << x << " ";

            cout << "\n";
            break;
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
}