#include <bits/stdc++.h>
#include "ciphers.h"
using namespace std;
int main(int argc, char const *argv[])
{
	string s="";
	int d;
	cin>>s>>d;
	cout<<(s = caeser_encrypt(s,d))<<endl;
	cout<<caeser_decrypt(s,d)<<endl;
	return 0;
}