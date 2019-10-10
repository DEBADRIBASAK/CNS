#include "AES.h"
using namespace std;
int main()
{
	string key="abcdabcdabcdabcd";
	AES encrypter(key);
	//cout<<"Here = "<<encrypter.substitute_bits(0x00)<<endl;
	for(int i=0;i<16;i++)
	{
		for(int j=0;j<16;j++)
		{
			//cout<<"Here = "<<(unsigned char)((i*16+j))<<endl;
			//encrypter.substitute_bits((unsigned char)((i*16+j)));
			printf("%02X  ",encrypter.substitute_bits(i*16+j));
		}
		cout<<endl;
	}
	cout<<endl;
	for(int i=0;i<16;i++)
	{
		for(int j=0;j<16;j++)
		{
			//cout<<"Here = "<<(unsigned char)((i*16+j))<<endl;
			//encrypter.substitute_bits((unsigned char)((i*16+j)));
			printf("%02X  ",encrypter.substitute_bits(i*16+j,true));
		}
		cout<<endl;
	}
	unsigned char arr[5] = {1,2,3,4,5};
	encrypter.shift_n_row(arr,5,4,false);
	for(int i=0;i<5;i++)
		cout<<(int)arr[i]<<" ";
	cout<<endl;
	encrypter.test();
	GF_2n *g;
	g = new GF_2n("x8+x4+x3+x+1");
	cout<<"confirm = "<<g->mul_inv(0x05)<<endl;
}