#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<int> tree;

// Build the tree bottom-up
void build(vector<int>& arr) {
    int size = 1 << n; // 2^n
    
    // Copy leaves (array elements) to the second half of tree
    for (int i = 0; i < size; i++) {
        tree[size + i] = arr[i];
    }
    
    // Build internal nodes from bottom to top
    // level 0 = leaves, level increases as we go up
    for (int i = size - 1; i >= 1; i--) {
        int level = __builtin_clz(i) - __builtin_clz(size); // which level are we at?
        
        if (level % 2 == 1) {
            // ODD level -> OR operation
            tree[i] = tree[2*i] | tree[2*i + 1];
        } else {
            // EVEN level -> XOR operation
            tree[i] = tree[2*i] ^ tree[2*i + 1];
        }
    }
}

// Update position pos (1-indexed in problem) to value val
void update(int pos, int val) {
    int size = 1 << n; // 2^n
    pos--; // convert to 0-indexed
    
    int idx = size + pos; // position in tree
    tree[idx] = val; // update leaf
    
    // Propagate upward
    int level = 0;
    idx /= 2;
    while (idx >= 1) {
        level++;
        if (level % 2 == 1) {
            // ODD level -> OR
            tree[idx] = tree[2*idx] | tree[2*idx + 1];
        } else {
            // EVEN level -> XOR
            tree[idx] = tree[2*idx] ^ tree[2*idx + 1];
        }
        idx /= 2;
    }
}

int main() {
    cin >> n >> m;
    
    int size = 1 << n; // 2^n elements
    tree.resize(2 * size); // 2^(n+1) nodes
    
    vector<int> arr(size);
    for (int i = 0; i < size; i++) {
        cin >> arr[i];
    }
    
    build(arr);
    
    for (int i = 0; i < m; i++) {
        int p, b;
        cin >> p >> b;
        update(p, b);
        cout << tree[1] << "\n"; // root is at index 1
    }
    
    return 0;
}