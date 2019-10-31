#include <bits/stdc++.h>
#include "ECC.h"
using namespace std;

// y3 = x2-3x+b


int main(int argc, char const *argv[])
{
	mpz_t xA,xB,n;
	mpz_inits(xA,xB,n,NULL);

	//mpz_set_str(n,"6277101735386680763835789423176059013767194773182842284081",10);

	mpz_set_str(n,"1000",10);

	Point G("188da80e b03090f6 7cbf20eb 43a18800 f4ff0afd 82ff1012",
		"07192b95 ffc8da78 631011ed 6b24cdd5 73f977a1 1e794811",
		"-3",
		"64210519 e59c80e7 0fa7e9ab 72243049 feb8deec c146b9b1",
		"6277101735386680763835789423207666416083908700390324961279",
		10,16,16,16,10),PA,PB,K1,K2;

	cout<<G<<endl;

	gmp_randstate_t state;
	gmp_randinit_mt(state);
	gmp_randseed_ui(state,time(NULL));
	mpz_urandomm(xA,state,n);
	mpz_urandomm(xB,state,n);

	PA = G*xA;
	PB = G*xB;
	//cout<<"nA = "<<xA<<"nB = "<<xB<<endl;
	gmp_printf("nA = %Zd\nnB = %Zd\n",xA,xB);
	cout<<"PA = "<<PA<<endl<<"PB = "<<PB<<endl;

	K1 = PA*xB;
	K2 = PB*xA;

	cout<<"K1 = "<<K1<<endl<<"K2 = "<<K2<<endl;

	if(K1==K2)
	{
		cout<<"YES\n";
	}
	else
	{
		cout<<"NO\n";
	}

	return 0;
}