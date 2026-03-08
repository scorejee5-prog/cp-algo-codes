#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// Helper function: Print "YES" and the answer, then exit
// ans: vector containing the digits that form a number divisible by 8
void yes(const vector<int> ans) {
  cout << "YES\n";
  for (const int x : ans) {
    cout << x;
  }
  cout << "\n";
  exit(0);  // Exit immediately after finding first valid answer
}

// Helper function: Convert character digit to integer
// c: character ('0' to '9')
// Returns: integer value (0 to 9)
int integer(const char c) {
  return c - '0';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  string s;
  cin >> s;
  const int n = s.size();
  
  // KEY INSIGHT: A number is divisible by 8 if its last 3 digits are divisible by 8
  // We need to find any subsequence (not substring) of length 1, 2, or 3 that's divisible by 8
  
  // Try all possible subsequences of length 1, 2, and 3
  for (int i = 0; i < n; i++) {
    const int x = integer(s[i]);
    
    // Check single digit: Is x divisible by 8?
    // Only 0 and 8 are single digits divisible by 8
    if (x % 8 == 0) {
      yes({x});  // Found! Print and exit
    }
    
    // Try two-digit numbers: x followed by some digit y (maintaining order)
    for (int j = i + 1; j < n; j++) {
      const int y = integer(s[j]);
      
      // Form two-digit number: xy (e.g., if x=1, y=6, number is 16)
      if (((10 * x) + y) % 8 == 0) {
        yes({x, y});  // Found! Print and exit
      }
      
      // Try three-digit numbers: x followed by y followed by some digit z
      for (int k = j + 1; k < n; k++) {
        const int z = integer(s[k]);
        
        // Form three-digit number: xyz (e.g., if x=1, y=2, z=8, number is 128)
        // 128 = 100*1 + 10*2 + 8
        if (((100 * x) + (10 * y) + z) % 8 == 0) {
          yes({x, y, z});  // Found! Print and exit
        }
      }
    }
  }
  
  // If we reach here, no valid subsequence was found
  cout << "NO\n";
}