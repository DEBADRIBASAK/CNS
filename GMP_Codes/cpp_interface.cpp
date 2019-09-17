#include <bits/stdc++.h>
#include <gmpxx.h>
using namespace std;

int main(int argc, char const *argv[])
{
	mpz_class a,b,c;
	cin>>a>>b;c = a+b;
	cout<<c<<endl;
	c = a*b;
	cout<<c<<endl;
	c = a/b;
	cout<<c<<endl;
	c = a%b;
	cout<<c<<endl;
	return 0;
}