#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int a, b;
        cin >> a >> b;
        if (a >= b) {
            cout << a << endl;
        } else {
            if (b <= 2 * a && (b - a) <= (b / 2)) {
                cout << 2 * a - b << endl;
            } else {
                cout << 0 << endl;
            }
        }
    }
    return 0;
}