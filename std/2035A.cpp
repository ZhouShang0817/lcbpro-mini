#include <iostream>
using namespace std;

int main() {
    int t;
    cin >> t;
    
    while (t--) {
        long long n, m, r, c;
        cin >> n >> m >> r >> c;
        
        long long total_distance = 2 * (n-r)*m + m - c - n + r;
        
        cout << total_distance << endl;
    }
    
    return 0;
}