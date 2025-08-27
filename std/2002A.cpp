#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m, k;
        cin >> n >> m >> k;
        if (k > max(n, m)) {
            cout << n * m << endl;
        } else {
            cout << min(n, k) * min(m, k) << endl;
        }
    }
    return 0;
}