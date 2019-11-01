#include <bits/stdc++.h>
#include <gmp.h>
#include <unistd.h>

using namespace std;


/*

Size of p = 20 bits
Size of q = 9 bits

// if it does not run on the first go, stop it and run again

*/

int main(int argc, char const *argv[])
{
	mpz_t t,m,q,p,g,h,t1,r,s,x,u1,u2,y;
	mpz_inits(t,m,q,p,g,h,t1,r,s,x,u1,u2,y,NULL);
	mpz_setbit(t1,11);
	gmp_randstate_t state;
	gmp_randinit_mt(state);
	gmp_randseed_ui(state,time(NULL));
	mpz_urandomb(q,state,9);
	mpz_nextprime(q,q);
	int k;
	gmp_printf("q = %Zd\n",q);
	while(1)
	{
		//cout<<"trial = "<<tr++<<endl;
		mpz_urandomb(t,state,9);
		mpz_mul_ui(t,t,2);
		mpz_add(t,t,t1);
		mpz_mul(p,q,t);
		mpz_add_ui(p,p,1);
		k = mpz_probab_prime_p(p,15);
		if(k==2)
		break; 
		else
			gmp_printf("p = %Zd (non prime)\n",p);
		//sleep(1);
	}
	gmp_printf("Final = \np = %Zd\nq = %Zd\n",p,q);

	mpz_sub_ui(t,p,1);
	mpz_set(t1,t);
	mpz_div(t,t,q);
	do
	{
		mpz_urandomm(h,state,t1);
		mpz_powm(g,h,t,p);
	}while(mpz_cmp_ui(g,1)<=0);
	gmp_printf("g = %Zd\n",g);
	mpz_urandomm(h,state,q); //k
	gmp_printf("k = %Zd\n",h);
	mpz_powm(r,g,h,p);
	mpz_mod(r,r,q);
	gmp_printf("r = %Zd\n",r);
	mpz_gcdext(t,t,t1,q,h); // k^-1
	gmp_printf("k^-1 = %Zd\n",t1);
	mpz_mul(t,t1,h);
	mpz_mod(t,t,q);
	gmp_printf("Verify = %Zd\n",t);
	//mpz_t m;
	//mpz_inits(m,NULL);
	cout<<"Enter a number"<<endl;
	gmp_scanf("%Zd",m);

	mpz_urandomm(x,state,q);
	mpz_powm(y,g,x,p);

	// verification stage

	mpz_mul(t,x,r);
	mpz_add(t,t,m);
	mpz_mul(t,t,t1);
	mpz_mod(s,t,q);

	mpz_gcdext(t,t,t1,q,s);
	mpz_mod(t1,t1,q);
	mpz_mul(u1,t1,m);
	mpz_mod(u1,u1,q);
	mpz_mul(u2,r,t1);
	mpz_mod(u2,u2,q);

	mpz_powm(t,g,u1,p);
	mpz_powm(t1,y,u2,p);
	mpz_mul(t,t,t1);
	mpz_mod(t,t,p);
	mpz_mod(t,t,q);
	gmp_printf("r = %Zd\nv = %Zd\n",r,t);
	if(mpz_cmp(r,t)==0)
	{
		cout<<"YES, they are matching\n";
	}
	else
	{
		cout<<"NO, they are\'nt matching\n";
	}


	return 0;
}