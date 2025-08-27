#include <iostream>
#include <numeric>

using namespace std;

int query(int a, int b) {
    cout << "? " << a << " " << b << endl;
    cout.flush();
    int response;
    cin >> response;
    return response;
}

void answer(int x) {
    cout << "! " << x << endl;
    cout.flush();
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int low = 2, high = 999;
        int result_x = -1;
        while (low <= high) {
            if (low == high) {
                result_x = low;
                break;
            }
            int mid = low + (high - low) / 2;
            int response = query(1, mid);
            if (response == mid) {
                low = mid + 1;
            } else if (response == mid + 1) {
                high = mid;
            } else {
                // Error condition, should not happen in this problem if queries are valid and implementation is correct.
                // However, for robustness, handle potential error response like -1.
                if (response == -1) {
                    return 0; // Or handle error as needed, maybe terminate program.
                }
            }
        }
        if (result_x != -1) {
            answer(result_x);
        } else {
            // In case binary search loop exited without setting result_x, which should not happen under normal conditions.
            // Handle error or default behavior if needed.
        }
    }
    return 0;
}