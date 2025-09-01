#!/bin/bash
# Oracle solution for lcbpro-1992b
cat > /app/main.cpp << 'EOF'
#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    long total(0), mx(0);
    for (long p = 0; p < k; p++) {
      long x;
      scanf("%ld", &x);
      mx = (mx > x ? mx : x);
      total += (2 * x - 1);
    }

    total -= (2 * mx - 1);
    printf("%ld
", total);
  }
}
EOF