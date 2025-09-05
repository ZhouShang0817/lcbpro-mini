#include <iostream>

int main() {
    int t;
    std::cin >> t;
    
    while (t--) {
        int n, k;
        std::cin >> n >> k;
        
        if (n == 1) {
            std::cout << 0 << std::endl;
        } else {
            // Compute ceiling of (n-1)/(k-1) using integer division
            std::cout << (n - 1 + (k - 2)) / (k - 1) << std::endl;
        }
    }
    
    return 0;
}