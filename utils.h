#include <bits/stdc++.h>
using namespace std;
#ifndef __UTILS
#define __UTILS

class GF_2n
{
private:
	int degree,bin;
	map<int,int> m,rev_m;
	string irr_poly;
public:
	GF_2n(string poly) // x8+x4+x3+x+1
	{
		irr_poly = poly;
		bin = poly_to_bin(poly,degree);	
	}
	int poly_to_bin(string poly,int &degree)
	{
		degree = -1;bin = 0;
		int n;
		for(int i=0;i<poly.length();i++)
		{
			if(poly[i]=='x')
			{
				if(i+1==poly.length()||poly[i+1]=='+')
				{
					bin|=(1<<1);
					degree = (degree==-1)?1:degree;
				}
				else 
				{
					n = poly[i+1]-'0';
					bin|=(1<<n);
					degree = (degree==-1)?n:degree;
				}
			}
			else
			{
				if(poly[i]=='+'||(i<poly.length()-1&&poly[i+1]=='+'))
					continue;
				bin|=1;
			}
		}
		return bin;
	}
	void generate()
	{
		m[-1] = 0;rev_m[0] = -1;
		for(int i=0;i<degree;i++)
		{
			m[i] = 1<<i;
			rev_m[1<<i] = i;
		} 
		m[degree] = bin^(1<<degree);
		for(int i=degree+1;i<(1<<degree)-1;i++)
		{
			m[i] = m[i-1]<<1;
			if(m[i]&(1<<degree))
			{
				m[i]^=bin;
			}
			rev_m[m[i]] = i;
		}
	}
	int add(string a,string b)
	{
		int degA,degB;
		int k1 = poly_to_bin(a,degA);
		int k2 = poly_to_bin(b,degB);
		degA = (degA>degB)?degA:degB;
		k1^=k2;
		int n = bin<<degA;
		for(int i=degA;i>=degree;i--)
		{
			if(k1&(1<<i))
			{
				k1^=(n);
			}
			n>>=1;
		}
		return k1;
	}
	int add_num(int k1,int k2)
	{
		return k1^k2;
	}
	int multiply_num(int k1,int k2)
	{
		int rtn = 0;
		for(int i=1;i<=k2;i<<=1)
		{
			if(k2&i)
				rtn^=k1;
			k1<<=1;
			if(k1&(1<<degree))
				k1^=bin;
		}
		return rtn;
	}
	void print_table()
	{
		for(int i=0;i<(1<<degree)-1;i++)
		{
			for(int j=0;j<(1<<degree)-1;j++)
			{
				printf("%X   ",multiply_num(m[i],m[j]));
			}
			printf("\n");
		}
	}
	int get_degree(int k)
	{
		return rev_m[k];
	}
	int get_value(int d)
	{
		return m[d];
	}
	int find_degree(int a)
	{
		if(a==0)
			return 0;
		int i=0;
		while((1<<i)<a)
		{
			i++;
		}
		return ((1<<i)==a)?i:i-1;
	}
	int div(int a,int degA,int b,int degB,int& r)
	{
		int q = 0;
		if(degA>=degB)
		b<<=(degA-degB);
		for(int i=degA;i>=degB;i--)
		{
			if(a&(1<<i))
			{
				a^=b;
				q|=(1<<(i-degB));
			}
			b>>=1;
		}
		r = a;
		return q;
	}
	int mul_inv(int a)
	{
		int degA;
		int degB;
		int b = bin;
		int x0 = 1,y0 = 0,x1 = 0,y1 = 1,q,r,t;
		while(b!=0)
		{
			degA = find_degree(a);
			degB = find_degree(b);
			q = div(a,degA,b,degB,r);
			a = b;
			b = r;
			t = x1;
			x1 = add_num(x0,multiply_num(q,x1));x0 = t;
			t = y1;
			y1 = add_num(y0,multiply_num(q,y1));y0 = t;
		}
		return x0;
	}
};

#endif