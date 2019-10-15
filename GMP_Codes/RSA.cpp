#include <bits/stdc++.h>
#include <gmp.h>
using namespace std;

int main(int argc, char const *argv[])
{
	mpz_t p,q,n,e,d,t,phi,num,cipher;
	mpz_inits(n,p,q,e,d,t,num,phi,cipher,NULL);
	gmp_randstate_t state;
	gmp_randinit_default(state);
	mpz_urandomb(p,state,10);
	mpz_nextprime(p,p);
	mpz_urandomb(q,state,10);
	mpz_nextprime(q,q);
	mpz_mul(n,p,q);
	mpz_sub_ui(p,p,1);
	mpz_sub_ui(q,q,1);
	mpz_mul(phi,p,q);
	do
	{
		mpz_urandomm(e,state,phi);
		mpz_gcd(t,e,phi);
	}while(mpz_cmp_ui(t,1)!=0);
	gmp_printf("*************\nP = %Zd\nQ = %Zd\nn = %Zd\nphi = %Zd\ne = %Zd\n",p,q,n,phi,e);
	mpz_gcdext(t,t,d,phi,e);
	if(mpz_cmp_ui(d,0)<0)
	{
		mpz_add(d,d,phi);
	}
	gmp_printf("d = %Zd\n",d);
	cout<<"Enter a number \n";
	gmp_scanf("%Zd",num);
	mpz_powm(cipher,num,e,n);
	gmp_printf("The Ciphertext = %Zd\n",cipher);
	mpz_powm(cipher,cipher,d,n);
	gmp_printf("The original text = %Zd\n",cipher);
	return 0;
}