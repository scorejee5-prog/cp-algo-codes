#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string s;  // Available weights (10 characters, '1' = available, '0' = not)
    int m;          // Number of steps needed
    std::cin >> s >> m;

    // DP State: dp[step][difference][last_weight]
    // step: current step (0 to m)
    // difference: absolute difference between left and right sides (0 to 10)
    // last_weight: the weight we used in the previous step (0-9, representing weights 1-10)
    // 
    // dp[i][j][x] stores the previous weight used to reach this state
    // -1 means this state is unreachable
    std::vector<std::vector<std::vector<int>>> dp(m + 1, std::vector<std::vector<int>>(11, std::vector<int>(10, -1)));

    // Base case: At step 0, difference is 0, no weight used yet
    // We mark two dummy positions as starting points
    dp[0][0][0] = dp[0][0][1] = 0;
    
    // Main DP: Build all reachable states
    for (int i = 0; i < m; i++) {              // For each step
        for (int j = 0; j <= 10; j++) {        // For each possible difference
            for (int x = 0; x < 10; x++) {     // For each last weight used
                for (int y = 0; y < 10; y++) { // Try placing each new weight
                    
                    // Transition conditions:
                    // 1. x != y: Can't use the same weight consecutively
                    // 2. s[y] == '1': Weight y+1 must be available
                    // 3. y + 1 - j > 0: New weight must overcome current difference
                    //    (to tip the scale to the opposite side)
                    // 4. dp[i][j][x] != -1: Current state must be reachable
                    
                    if (x != y && s[y] == '1' && y + 1 - j > 0 && dp[i][j][x] != -1) {
                        // Transition to next state:
                        // - Step i+1
                        // - New difference: (y+1) - j (weight minus old difference)
                        // - Last weight: y
                        // - Store previous weight x for path reconstruction
                        dp[i + 1][y + 1 - j][y] = x;
                    }
                }
            }
        }
    }

    // Check if we reached step m with any valid final state
    for (int j = 0; j <= 10; j++) {        // Any final difference is ok
        for (int x = 0; x < 10; x++) {     // Any final weight is ok
            if (dp[m][j][x] != -1) {       // Found a valid solution!
                std::cout << "YES\n";
                
                // Reconstruct the path backwards
                std::vector<int> ans;
                
                // Start from final state and work backwards
                for (int i = m; i; i--) {
                    // Add current weight to answer (convert 0-indexed to 1-indexed)
                    ans.push_back(x + 1);
                    
                    // Get the previous weight from DP table
                    int y = dp[i][j][x];
                    
                    // Reverse the difference calculation to get previous difference
                    // If current diff = j and we placed weight (x+1)
                    // Then previous diff = (x+1) - j
                    j = x + 1 - j;
                    
                    // Move to previous weight
                    x = y;
                }
                
                // We built the answer backwards, so reverse it
                std::reverse(ans.begin(), ans.end());
                
                // Print the sequence of weights
                for (int i = 0; i < m; i++) {
                    std::cout << ans[i] << " \n"[i == m - 1];
                }
                
                return 0;
            }
        }
    }

    // No valid solution found
    std::cout << "NO\n";

    return 0;
}