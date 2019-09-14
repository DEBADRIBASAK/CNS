#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

int main()
{
	mpz_t a,b,c;
	mpz_inits(a,b,c,NULL);
	gmp_scanf("%Zd%Zd",a,b);
	mpz_mul(c,a,b);
	gmp_printf("The product = %Zd\n",c);
	return 0;
}
