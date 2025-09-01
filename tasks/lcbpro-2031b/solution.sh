#!/bin/bash
# Oracle solution for lcbpro-2031b
cat > /app/main.cpp << 'EOF'
#include <iostream>

using namespace std;

int main() {
	int t;
	cin >> t;
	int n;
	int b;
	for (int i = 0; i < t; i++) {
		int tracker = 0;
		cin >> n;
		for (int j = 0; j < n; j++) {
			cin >> b;
			if (b == j || b == j + 1 || b == j + 2);
			else{
				tracker = 1;
			}
		}
		if (tracker == 0) {
			cout << "yes
";
		}
		else { cout << "no
"; }
	}
	return 0;
}
EOF