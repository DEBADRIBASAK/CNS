#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstring>
#include "DES.h"
using namespace std;
int main(int argc, char const *argv[])
{
	// if(argc<3)
	// {
	// 	cout<<"Usage : ./a.out input_file output_file"<<endl;exit(0);
	// }
	// cout<<"size = "<<sizeof(char)<<endl;
	// char block[8];
	// ifstream in;
	// ofstream out;//,out1("log.txt");
	// in.open(argv[1],ios::in|ios::binary);
	// out.open(argv[2],ios::out);
	 string key;
	 cout<<"Enter the key";
	 cin>>key;
	 DES encrypter(key);
	 encrypter.generate_all_keys();
	// int sz;
	// cout<<"Encryption..."<<endl;
	// // vector<string> v;
	// while(!in.eof())
	// {
	// 	memset(block,0,sizeof(block));
	// 	in.read(block,sizeof(block));
	// 	if(in.eof())
	// 		break;
	// 	string cipher = encrypter.encrypt(string(block));
	// 	//encrypter.test(string(block));
	// 	//v.push_back(cipher);
	// 	out<<cipher;
	// }
	// in.close();
	// out.close();
	encrypter.test("hellowor");
	// in.open(argv[2],ios::in|ios::binary);
	// out.open("decr.txt",ios::out);
	// cout<<"Decryption..."<<endl;
	// while(!in.eof())
	// {
	// 	memset(block,0,sizeof(block));
	// 	in.read(block,sizeof(block));
	// 	// cout<<block<<endl;
	// 	string s(block);
	// 	//cout<<"s = "<<s<<endl;
	// 	if(in.eof())
	// 		break;
	// 	//cout<<"Hello1\n";
	// 	string cipher = encrypter.decrypt(s);
	// 	//cout<<"Hello2\n";
	// 	//cout<<cipher;
	// 	out<<cipher;
	// }
	return 0;
}