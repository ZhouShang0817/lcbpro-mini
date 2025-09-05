#include<iostream>
#include<algorithm>
#include<set>
using namespace std;
int main() {
	long long t; cin >> t;
	while (t--) {
		set<long long> s;
		int a[100005];
		long long ans = 0, sum = 0;
		s.clear();
		s.insert(0);
		long long n; cin >> n;
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
			sum += a[i];
			if (s.count(sum)) {
				ans++;
				sum = 0;
				s.clear();
				s.insert(0);
			}
			else {
				s.insert(sum);
			}
		}
		cout << ans << endl;
	}
	return 0;
}