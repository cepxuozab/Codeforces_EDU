#include <iostream>
#include <vector>
using namespace std;

class DSU {
private:
    vector<int> parent, rank;

public:
    DSU(int n) {
        parent.resize(n + 1);
        rank.resize(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY) {
            if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n, m;
        cin >> n >> m;

        DSU dsu(n);

        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            dsu.unite(u, v);
        }

        // ѕодсчитываем количество уникальных корней
        vector<bool> isRoot(n + 1, false);
        for (int i = 1; i <= n; i++) {
            isRoot[dsu.find(i)] = true;
        }

        int components = 0;
        for (int i = 1; i <= n; i++) {
            if (isRoot[i]) {
                components++;
            }
        }

        cout << components << "\n";
        
    }

    return 0;
}