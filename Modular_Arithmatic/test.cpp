#include <bits/stdc++.h>
#include "ZP.h"
using namespace std;

int main(int argc, char const *argv[])
{
	GFp a(23),b(23);
	a = 12;
	b = 11;
	cout<<"a = "<<a<<"\nb = "<<b<<endl;
	cout<<"Add = "<<(a+b)<<"\nMul = "<<(a*b)<<"\nSub = "<<(a-b)<<"\nDiv = "<<(a/b)<<endl;
	cout<<"Inv(a) = "<<a.inverse()<<"\nInv(b) = "<<b.inverse()<<endl;
	return 0;
}