#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

// Function to check if a number is a power of 2
bool isPowerOfTwo(long long n) {
    return (n > 0) && ((n & (n - 1)) == 0);
}

// Calculate turns needed to reduce a grid of size x×y to 1×1
long long futureGridTurns(long long x, long long y) {
    if (x <= 0 || y <= 0) return 0;
    
    long long turns = floor(log2(x)) + floor(log2(y));
    
    // Add 1 for each dimension that's not a power of 2
    if (!isPowerOfTwo(x)) turns++;
    if (!isPowerOfTwo(y)) turns++;
    
    return turns;
}

long long solve(long long n, long long m, long long a, long long b) {
    // If grid is already 1×1, no turns needed
    if (n == 1 && m == 1) return 0;
    
    long long minFutureTurns = LLONG_MAX;
    
    // Try horizontal cut
    long long horizontalGridSize = min(a, n - a + 1);
    minFutureTurns = min(minFutureTurns, futureGridTurns(horizontalGridSize, m));
    
    // Try vertical cut
    long long verticalGridSize = min(b, m - b + 1);
    minFutureTurns = min(minFutureTurns, futureGridTurns(n, verticalGridSize));
    
    // 1 turn for the first cut + minimum future turns
    return 1 + minFutureTurns;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    
    while (t--) {
        long long n, m, a, b;
        cin >> n >> m >> a >> b;
        cout << solve(n, m, a, b) << "\n";
    }
    
    return 0;
}