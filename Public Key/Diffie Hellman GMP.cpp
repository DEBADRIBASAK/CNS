#include <bits/stdc++.h>
#include <gmp.h>
using namespace std;


void generator(mpz_t g,mpz_t n)
{
	mpz_t arr[100],p,t,n0;
	mpz_inits(t,p,n0,0);
	mpz_sub_ui(n0,n,1);
	for(int i=0;i<100;i++)
	{
		mpz_inits(arr[i],NULL);
		//mpz_set_ui(arr[i],)
	}
	unsigned long int num = mpz_get_ui(n);
	vector<bool> v(num+1,true);
	v[0] = v[1] = false;
	int ind = 0,i = 2,m;
	m = num-1;
	for(;i*i<=num&&m!=1;i++)
	{
		if(v[i])
		{
			for(int j=2*i;j<=num;j+=i)
			{
				v[j] = false;
			}
			if(m%i==0)
			{
				mpz_set_ui(arr[ind],i);ind++;
			}
		}
		while(m%i==0)
		{
			m/=i;
		}
	}
	for(;i<=num&&m!=1;i++)
	{
		if(v[i]&&m%num==0)
		{
			mpz_set_ui(arr[ind],i);ind++;
			while(m%i==0)
				m/=i;
		}
	}
	m = num-1;bool  f;
	for(i=2;i<num;i++)
	{
		f = true;
		for(int j=0;j<ind;j++)
		{
			mpz_div(p,n0,arr[j]);
			mpz_set_ui(t,i);
			mpz_powm(t,t,p,n);
			if(mpz_cmp_ui(t,1)==0)
			{
				f = false;break;
			}
		}
		if(f)
		{
			mpz_set_ui(g,i);
			return;
		}
	}
}

int main(int argc, char const *argv[])
{
	mpz_t n,g,xA,xB,yA,yB,K1,K2;
	mpz_inits(n,g,xA,xB,yA,yB,K1,K2,NULL);
	//cout<<"Enter the order of field"<<endl;
	//gmp_scanf("%Zd",n);
	gmp_randstate_t state;
	gmp_randinit_mt(state);
	gmp_randseed_ui(state,time(NULL));
	mpz_urandomb(n,state,15);
	mpz_nextprime(n,n);
	gmp_printf("n = %Zd\n",n);
	generator(g,n);
	if(mpz_cmp_ui(g,0)==0)
	{
		printf("No generator for this field\n");exit(0);
	}
	else
	{
		gmp_printf("generator = %Zd\n",g);
	}

	//cout<<"Enter x1 and x2"<<endl;
	//gmp_scanf("%Zd%Zd",xA,xB);
	mpz_urandomb(xA,state,10);
	mpz_urandomb(xB,state,10);
	gmp_printf("xA = %Zd\nxB = %Zd\n",xA,xB);

	mpz_powm(yA,g,xA,n);
	mpz_powm(yB,g,xB,n);

	gmp_printf("yA = %Zd\nyB = %Zd\n",yA,yB);

	mpz_powm(K1,yA,xB,n);
	mpz_powm(K2,yB,xA,n);
	gmp_printf("K1 = %Zd\nK2 = %Zd\n",K1,K2);

	cout<<"Equal? = "<<mpz_cmp(K1,K2)<<endl;
	return 0;
}