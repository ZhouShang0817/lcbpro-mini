#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>
 
using namespace std;
 
struct Interval {
  int x, y, i;
 
  auto operator<=>(const Interval &that) const = default;
};
 
void test_case(istream &cin, ostream &cout) {
  int N;
  cin >> N;
  vector<Interval> A(N);
  for (int i = 0; i < N; ++i) {
    cin >> A[i].x >> A[i].y;
    A[i].i = i;
  }
 
  ranges::sort(A);
  bool intersects = false;
  for (int i = 1; i < N; ++i) {
    if (A[i].x <= A[i - 1].y)
      intersects = true;
  }
 
  if (!intersects) {
    cout << 1 << "\n";
    for (int i = 0; i < N; ++i)
      cout << 1 << " ";
    cout << "\n";
    return;
  }
 
  ranges::sort(A, {}, [&](auto &i) { return i.i; });
 
  // try with 2
  vector<tuple<int, int, int>> events;
  for (auto interval : A) {
    events.emplace_back(interval.x, -interval.y, ~interval.i);
    events.emplace_back(interval.y, -interval.y, interval.i);
  }
 
  ranges::sort(events);
  vector<int> answer(N, 0);
  int count[3] = {0, 0, 0};
  int to[3] = {0, 0, 0};
  bool bad2 = false;
  int last_event = -1;
  for (auto [when, _, what] : events) {
    if (when != last_event && count[1] != 1 && count[2] != 1 &&
        count[1] + count[2] > 0) {
      bad2 = true;
      break;
    }
    last_event = when;
 
    if (what < 0) {
      int pick = 1;
 
      if (count[1] == 0 || count[1] > 1)
        pick = 1;
      else if (count[2] == 0 || count[2] > 1)
        pick = 2;
      else if (to[1] < to[2])
        pick = 1;
      else
        pick = 2;
      ++count[pick];
      to[pick] = max(to[pick], A[~what].y);
      answer[~what] = pick;
      continue;
    }
 
    --count[answer[what]];
  }
 
  if (!bad2) {
    cout << 2 << "\n";
    for (int i = 0; i < N; ++i)
      cout << answer[i] << " ";
    cout << "\n";
    return;
  }
  fill(answer.begin(), answer.end(), 0);
 
  ranges::sort(A);
  int last = -1;
  int now = 1;
  for (int i = 0; i < N;) {
    if (last < A[i].x)
      last = A[i].x;
    int whom = i;
    while (i < N && A[i].x <= last) {
      if (A[i].y > A[whom].y)
        whom = i;
      ++i;
    }
    answer[A[whom].i] = now;
    last = A[whom].y;
    now ^= 3;
  }
  cout << 3 << "\n";
  for (int i = 0; i < N; ++i)
    cout << answer[i] + 1 << " ";
  cout << "\n";
}
 
int main() {
  ios::sync_with_stdio(false);
 
  int T;
  cin >> T;
  while (T--)
    test_case(cin, cout);
}