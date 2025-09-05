#include <bits/stdc++.h>
using namespace std;

#define forn(i, n) for(int i = 0; i < int(n); i++) 
const int N = 100;
 
bool dp[N][N];
pair<int, int> nxt[N][N][2];
bitset<N> cur;
bitset<N> form[N][N];
 
int main(){
	forn(i, N) forn(j, N) dp[i][j] = (i + j) % 2;
	for (int len = 1; len < N; len += 2){
		forn(x, len + 1){
			int y = len - x;
			int nx = x, ny = y;
			int i = 0;
			while (nx > 1 || ny > 1){
				if (nx > 1){
					nx -= 2;
					++i;
				}
				if (ny > 1){
					form[x][y][i] = form[x][y][len - i - 1] = 1;
					ny -= 2;
					++i;
				}
			}
			if (ny > 0){
				form[x][y][i] = 1;
			}
		}
	}
	for (int len = N - 3; len >= 1; len -= 2){
		forn(x, len + 1){
			int y = len - x;
			cur = form[x][y];
			forn(c, 2){
				cur[len] = c;
				bool found = false;
				forn(l, len + 1){
					forn(r, l + 1){
						if (cur[l] != cur[r]) cur[l].flip(), cur[r].flip();
						bool ok = true;
						forn(d, 2){
							cur[len + 1] = d;
							int nx = x + (c == 0) + (d == 0);
							int ny = y + (c == 1) + (d == 1);
							if ((cur ^ form[nx][ny]).count() > 2){
								ok = false;
								break;
							}
						}
						if (ok){
							found = true;
							nxt[x][y][c] = {l, r};
						}
						if (cur[l] != cur[r]) cur[l].flip(), cur[r].flip();
						if (found) break;
					}
					if (found) break;
				}
				if (!found){
					dp[x][y] = false;
					break;
				}
			}
		}
	}
	string s;
	cur.reset();
	for (int i = 0;; ++i){
		cin >> s;
		if (s == "0") break;
		int c = s[0] - 'a';
		int py = cur.count(), px = i - py;
		cur[i] = c;
		int nx = px + (c == 0), ny = py + (c == 1);
		int l = -1, r = -1;
		if (i % 2 == 1){
			auto res = nxt[px][py][c];
			if (res.first != res.second){
				l = res.first;
				r = res.second;
			}
		}
		else{
			assert(dp[nx][ny]);
			bitset<N> dif = cur ^ form[nx][ny];
			assert(dif.count() <= 2);
			if (dif.count() == 2){
				l = dif._Find_first();
				r = dif._Find_next(l);
			}
		}
		if (l == -1){
			cout << 0 << " " << 0 << endl;
		}
		else{
			cout << l + 1 << " " << r + 1 << endl;
			if (cur[l] != cur[r]) cur[l].flip(), cur[r].flip();
		}
	}
}