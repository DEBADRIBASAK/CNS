#include "AES.h"
using namespace std;
int main()
{
	string key="abcdabcdabcdabcd";
	//cout<<"enter the key"<<endl;
	//cin>>key;
	AES encrypter(key);
	string plain_text="1234ABCDabcd#$@!",cipher="";
	cipher = encrypter.encrypt(plain_text);
	cout<<"cipher text = "<<cipher<<endl;
	cout<<"plain_text = "<<encrypter.decrypt(cipher)<<endl;
}