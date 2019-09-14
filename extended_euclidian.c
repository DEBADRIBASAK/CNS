#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <gmp.h>

int main(int argc, char const *argv[])
{
	mpz_t a,b,c,x0,y0,x1,y1,t,q;
	mpz_inits(a,b,c,x0,y0,x1,y1,t,q,NULL);
	printf("Enter two numbers\n");
	gmp_scanf("%Zd%Zd",a,b);
	mpz_set_ui(x0,1);
	mpz_set_ui(y1,1);
	bool f = false;
	while(mpz_cmp_ui(b,0)!=0)
	{
		mpz_div(q,a,b);
		mpz_set(t,b);
		mpz_mod(b,a,b);
		mpz_set(a,t);
		if(!f)
		{
			mpz_mul(t,x1,q);
			mpz_sub(x0,x0,t);
			mpz_mul(t,y1,q);
			mpz_sub(y0,y0,t);
		}
		else
		{
			mpz_mul(t,x0,q);
			mpz_sub(x1,x1,t);
			mpz_mul(t,y0,q);
			mpz_sub(y1,y1,t);
		}
		f = !f;
	}
	gmp_printf("The GCD is %Zd\n",a);
	if(f)
	{
		gmp_printf("x = %Zd\ny = %Zd\n",x1,y1);
	}
	else
		gmp_printf("x = %Zd\ny = %Zd\n",x0,y0);
	return 0;
}