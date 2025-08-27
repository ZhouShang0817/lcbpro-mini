#include <iostream>

int main() {
    int t;
    std::cin >> t;  // number of test cases
    
    while (t--) {
        int n;
        std::cin >> n;
        
        // For a two-digit number:
        // First digit = n/10
        // Second digit = n%10
        int sum = (n/10) + (n%10);
        
        std::cout << sum << std::endl;
    }
    
    return 0;
}