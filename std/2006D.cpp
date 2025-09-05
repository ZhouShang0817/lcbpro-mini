#include <bits/stdc++.h>
using namespace std;

// Constants
constexpr int kMaxN = 1e5 + 10;

// Global arrays
int testCases, arraySize, divisor, queryCount;
int inputArray[kMaxN], prefixSum[kMaxN], result[kMaxN], leftBound[kMaxN], rightBound[kMaxN], prefixSumHigh[kMaxN];

/**
 * Solves a single test case by processing input array and queries.
 * @param none
 * @return void
 */
void solveTestCase() {
    int i, j;
    cin >> arraySize >> queryCount >> divisor;
    
    // Read input array
    for (i = 1; i <= arraySize; i++) {
        cin >> inputArray[i];
    }
    
    // Read query bounds and initialize result array
    for (i = 1; i <= queryCount; i++) {
        result[i] = 0;
        cin >> leftBound[i] >> rightBound[i];
    }
    
    // Process for each possible divisor i where i*i <= k
    for (i = 1; i * i <= divisor; i++) {
        // Calculate prefix sums for elements <= i and > k/(i+1)
        for (j = 1; j <= arraySize; j++) {
            prefixSum[j] = prefixSum[j - 1] + (inputArray[j] <= i);
            prefixSumHigh[j] = prefixSumHigh[j - 1] + (inputArray[j] > divisor / (i + 1));
        }
        
        // Process each query
        for (j = 1; j <= queryCount; j++) {
            int left = leftBound[j], right = rightBound[j];
            int countLow = prefixSum[right] - prefixSum[left - 1];
            int countHigh = prefixSumHigh[right] - prefixSumHigh[left - 1];
            result[j] = max(result[j], min((right - left + 1) / 2 - countLow, (countHigh - countLow + 1) / 2));
        }
    }
    
    // Output results for all queries
    for (i = 1; i <= queryCount; i++) {
        cout << result[i] << ' ';
    }
    cout << '
';
}

/**
 * Main function to handle multiple test cases.
 * @return 0 on successful execution
 */
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int testCaseCount = 1;
    cin >> testCaseCount;
    
    while (testCaseCount--) {
        solveTestCase();
    }
    
    return 0;
}