#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    string s; cin >> s;
    int visr = 0, visb = 0, ok = 0;
    for (int i = 0; i < n; ++i) {
        if (s[i] == s[(i+1)%n]) {
            ++ok;
            if (s[i] == 'R') visr = 1;
            else visb = 1;
        }
    }
    // both kinds of consecutive pairs -> impossible
    if (visr && visb) {
        cout << "NO
";
        return;
    }
    // all edges equal -> trivially YES
    if (ok == n) {
        cout << "YES
";
        return;
    }
    // normalize so that only 'R' can have consecutive equal positions
    if (visb) {
        for (char &ch : s) ch = (ch == 'R' ? 'B' : 'R');
    }
    // find a starting position: the index after any 'B'
    int st = 0;
    for (int i = 0; i < n; ++i) if (s[i] == 'B') st = (i+1) % n;
    vector<int> rblocks;
    int cntEven = 0;
    int run = 0;
    for (int i = 0, j = st; i < n; ++i, j = (j+1)%n) {
        if (s[j] == 'B') {
            rblocks.push_back(run);
            if ((run & 1) == 0 && run > 0) ++cntEven;
            run = 0;
        } else {
            ++run;
        }
    }
    // after loop, we've already pushed runs when encountering B; 
    // for circular correctness the code above pushes runs at each B,
    // and covers all R-blocks (including possible zero-length ones).
    // number of R-blocks equals rblocks.size()
    if (rblocks.size() == 1 || cntEven == 1) cout << "YES
";
    else cout << "NO
";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--) solve();
    return 0;
}