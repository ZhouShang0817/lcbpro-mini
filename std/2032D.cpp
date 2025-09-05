#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int n;
        cin >> n;
        vector<int> parent(n, 0);

        int r = n - 1;
        for (int l = n - 2; l >= 1; --l) {
            cout << "? " << l << ' ' << r << endl; 
            int resp;
            if (!(cin >> resp)) return 0;
            if (resp == -1) return 0;     
            if (resp == 0) {
                parent[r] = l;
                --r;
            }
        }

        cout << "!";
        for (int i = 1; i < n; ++i) cout << ' ' << parent[i];
        cout << endl;
    }

    return 0;
}