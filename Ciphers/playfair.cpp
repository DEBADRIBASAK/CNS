#include <bits/stdc++.h>
#include "./ciphers.h"

using namespace std;

int main(int argc, char const *argv[])
{
	string s="";
	cin>>s;
	string key="";
	cin>>key;
	cout<<playfair_encrypt(s,key)<<endl;
	return 0;
}