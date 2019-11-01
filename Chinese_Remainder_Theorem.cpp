#include <bits/stdc++.h>
#include <gmp.h>
using namespace std;


void mul_inv(mpz_t a1,mpz_t b1,mpz_t inv)
{
	mpz_t a,b,t,q,r,x0,x1,y0,y1;
	mpz_inits(a,b,t,q,r,x0,x1,y0,y1,NULL);
	mpz_set_ui(x0,1);
	mpz_set_ui(x1,0);
	mpz_set_ui(y0,0);
	mpz_set_ui(y1,1);
	mpz_set(a,a1);mpz_set(b,b1);
	while(mpz_cmp_ui(b,1)!=0)
	{
		mpz_mod(r,a,b);
		mpz_div(q,a,b);
		mpz_set(a,b);
		mpz_set(b,r);
		mpz_set(t,x1);
		mpz_mul(x1,x1,q);
		mpz_sub(x1,x0,x1);
		mpz_set(x0,t);
		mpz_set(t,y1);
		mpz_mul(y1,y1,q);
		mpz_sub(y1,y0,y1);
		mpz_set(y0,t);
	}
	mpz_set(inv,x1);
}

int main(int argc, char const *argv[])
{
	mpz_t num[100],rem[100],prod,x,t1,t;
	mpz_inits(x,prod,t,t1,NULL);
	for(int i=0;i<100;i++)
	{
		mpz_inits(num[i],rem[i],NULL);
	}
	int n;
	cout<<"No of numbers = ";
	cin>>n;
	char a[100];
	for(int i=0;i<n;i++)
	{
		cin>>a;
		mpz_set_str(num[i],a,10);
	}
	for(int i=0;i<n;i++)
	{
		cin>>a;
		mpz_set_str(rem[i],a,10);
	}
	//mpz_set_ui(x,1);
	mpz_set_ui(prod,1);
	for(int i=0;i<n;i++)
	{
		mpz_mul(prod,prod,num[i]);
	}
	for(int i=0;i<n;i++)
	{
		mpz_div(t1,prod,num[i]);
		mul_inv(t1,num[i],t);
		mpz_mul(t,t,t1);
		mpz_mul(t,t,rem[i]);
		mpz_add(x,x,t);
		mpz_mod(x,x,prod);
	}
	gmp_printf("x = %Zd\n",x);
	return 0;
}

/*
3
3 4 5
2 3 1
*/
