#include<bits/stdc++.h>
using namespace std;
int t , n , a , b , c;
bool flag;
int main()
{
	cin >> t;
	while(t--)
	{
		cin >> n;
		if(n == 3)
		{
			cout << "? 1 2" << endl;
			cin >> a;
			cout << "? 2 1" << endl;
			cin >> b;
			if(a == b)
			{
				cout << "! 3" << endl;
				continue;
			}
			cout << "? 1 3" << endl;
			cin >> a;
			cout << "? 3 1" << endl;
			cin >> b;
			if(a == b)
			{
				cout << "! 2" << endl;
			}
			else
			{
				cout << "! 1" << endl;
			}
			continue;
		}
		if(n == 4)
		{
			cout << "? 1 2" << endl;
			cin >> a;
			cout << "? 2 1" << endl;
			cin >> b;
			if(a == b)
			{
				cout << "? 1 3" << endl;
				cin >> a;
				cout << "? 3 1" << endl;
				cin >> b;
				if(a == b)
				{
					cout << "! 4" <<endl;
				}
				else
				{
					cout << "! 3" << endl;
				}
				continue;
			}
			cout << "? 1 3" << endl;
			cin >> a;
			cout << "? 3 1" << endl;
			cin >> b;
			if(a == b)
			{
				cout << "! 2" << endl;
			}
			else
			{
				cout << "! 1" << endl;
			}
			continue;
		}
		if(n == 5)
		{
			int a12 , a23 , a31;
			cout << "? 1 2" << endl;
			cin >> a12;
			cout << "? 2 3" << endl;
			cin >> a23;
			cout << "? 3 1" << endl;
			cin >> a31;
			if((a12 + a23 + a31) % 2 == 1)
			{
				cout << "? 1 4" << endl;
				cin >> a;
				cout << "? 4 1" << endl;
				cin >> b;
				if(a == b)
				{
					cout << "! 5" << endl;
				}
				else
				{
					cout << "! 4" << endl;
				}
			}
			else
			{
				cout << "? 2 1" << endl;
				cin >> a;
				if(a12 == a)
				{
					cout << "! 3" << endl;
				}
				else
				{
					cout << "? 3 2" << endl;
					cin >> a;
					if(a23 == a)
					{
						cout << "! 1" << endl;
					}
					else
					{
						cout << "! 2" << endl;
					}
				}
			}
			continue;
		}
		if(n % 2 == 1)
		{
			cout << "? 1 2" << endl;
			cin >> a;
			cout << "? 2 3" << endl;
			cin >> b;
			cout << "? 3 1" << endl;
			cin >> c;
			if((a + b + c) % 2 == 1)
			{
				flag = 1;
				for(int i = 4 ; i + 2 <= n ; i += 2)
				{
					cout << "? " << i << ' ' << i + 1 << endl;
					cin >> a;
					cout << "? " << i + 1 << ' ' << i << endl;
					cin >> b;
					if(a != b)
					{
						cout << "? 1 " << i << endl;
						cin >> a;
						cout << "? " << i << " 1" << endl;
						cin >> b;
						if(a == b)
						{
							cout << "! " << i + 1 << endl;
						}
						else
						{
							cout << "! " << i << endl;
						}
						flag = 0;
						break;
					}
				}
				if(flag)
				{
					cout << "? 1 " << n << endl;
					cin >> a;
					cout << "? " << n << " 1" << endl;
					cin >> b;
					if(a == b)
					{
						cout << "! " << n - 1 << endl;
					}
					else
					{
						cout << "! " << n << endl;
					}
				}
			}
			else
			{
				cout << "? 2 1" << endl;
				cin >> c;
				if(a == c)
				{
					cout << "! 3" << endl;
				}
				else
				{
					cout << "? 3 2" << endl;
					cin >> a;
					if(a == b)
					{
						cout << "! 1" << endl;
					}
					else
					{
						cout << "! 2" << endl;
					}
				}
			}
			continue;
		}
		else
		{
			cout << "? 1 2" << endl;
			cin >> a;
			cout << "? 2 1" << endl;
			cin >> b;
			if(a == b)
			{
				flag = 1;
				for(int i = 3 ; i + 2 <= n ; i += 2)
				{
					cout << "? " << i << ' ' << i + 1 << endl;
					cin >> a;
					cout << "? " << i + 1 << ' ' << i << endl;
					cin >> b;
					if(a != b)
					{
						cout << "? 1 " << i << endl;
						cin >> a;
						cout << "? " << i << " 1" << endl;
						cin >> b;
						if(a == b)
						{
							cout << "! " << i + 1 << endl;
						}
						else
						{
							cout << "! " << i << endl;
						}
						flag = 0;
						break;
					}
				}
				if(flag)
				{
					cout << "? 1 " << n << endl;
					cin >> a;
					cout << "? " << n << " 1" << endl;
					cin >> b;
					if(a == b)
					{
						cout << "! " << n - 1 << endl;
					}
					else
					{
						cout << "! " << n << endl;
					}
				}
			}
			else
			{
				cout << "? 1 3" << endl;
				cin >> a;
				cout << "? 3 1" << endl;
				cin >> b;
				if(a == b)
				{
					cout << "! 2" << endl;
				}
				else
				{
					cout << "! 1" << endl;
				}
			}
		}
	}
	return 0;
}
