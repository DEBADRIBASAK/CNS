#include <bits/stdc++.h>
using namespace std;

#ifndef __UTILS
#define __UTILS

vector<int> seive(vector<bool> &v,int n)
{
	v[0] = v[1] = false;
	n--;
	vector<int> rtn;int i;
	for(i=2;i*i<=n+1&&n!=1;i++)
	{
		if(v[i])
		{
			//cout<<"v[i] = "<<i<<endl;
			for(int j=2*i;j<=n+1;j+=i)
			{
				v[j] = false;
			}
			if(n%i==0)
			{
				//cout<<"i = "<<i<<endl;
				rtn.push_back(i);
			}
			while(n%i==0)
			{
				n/=i;
			}
		}
	}
	for(;i<=n+1&&n!=1;i++)
	{
		if(n%i==0)
			rtn.push_back(i);
		while(n%i==0)
		{
			n/=i;
		}
	}
	return rtn;
}

int modular_exponentiation(int a,int e,int n)
{
	//cout<<"n = "<<n<<endl;
	int p = 1,base = a;
	while(e>0)
	{
		if(e&1)
		{
			p = ((p%n)*(base%n))%n;
		}
		base = ((base%n)*(base%n))%n;
		e>>=1;
		//cout<<"p = "<<p<<endl<<"e = "<<e<<endl<<"base = "<<base<<endl;
	}
	return p;
}

int generator(vector<int> v,int n)
{
	int a,b;bool f;
	srand(time(NULL));
	for(a=2;a<n;a++)
	{
		f = false;
		for(int i=0;i<v.size();i++)
		{
			b = modular_exponentiation(a,(n-1)/v[i],n);
			if(b==1)
			{
				f = true;
				break;
			}
		}
		if(!f)
			return a;
	}
	return -1;
}

#endif