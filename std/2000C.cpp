#include <bits/stdc++.h>
using namespace std;

void done (){
    int n; cin >> n; 
    vector<int> v;
    for (int i=0; i<n; i++){
        int x; cin >> x;
        v.push_back(x);
    }
    int m; cin >> m;
    while (m--){
        string s;
        cin >> s;
        if (n!= (int)s.size()){
            cout << "NO" << endl;
            continue;
        }
        map<int, char>mp1;
        map<char, int>mp2;
        bool ok=true;
        for (int i=0; i<n; i++){
            if (mp1.count(v[i]) && mp1[v[i]]!=s[i]) ok = false;
            if (mp2.count(s[i]) && mp2[s[i]]!=v[i]) ok = false;
            mp1[v[i]]=s[i];
            mp2[s[i]]=v[i];
        }
        if (!ok) cout << "NO" << endl;
        else cout << "YES" << endl;
    }
}

int main (){
    int t; cin >> t;
    while (t--){
        done ();
    }
}