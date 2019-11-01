#include <bits/stdc++.h>
using namespace std;
#ifndef ZP
#define ZP

class GFp
{
private:
	int p;
	int val;
public:
	GFp(int p)
	{
		this->p = p;
		this->val = 0;
	}
	GFp(int p,int val)
	{
		this->p = p;
		this->val = val;
	}
	void operator=(int n)
	{
		this->val = n;
	}
	GFp operator+(GFp x)
	{
		return GFp(p,(this->val+x.val)%p);
	}
	void operator+=(GFp x)
	{
		this->val = (this->val+x.val)%p;
	}
	GFp operator-(GFp x)
	{
		return GFp(p,(this->val-x.val)%p);
	}
	void operator-=(GFp x)
	{
		this->val = (this->val-x.val)%p;
	}
	GFp operator*(GFp x)
	{
		return GFp(p,(this->val*x.val)%p);
	}
	void operator*=(GFp x)
	{
		this->val = (this->val*x.val)%p;
	}
	int inverse()
	{
		if(this->val<=1)
			return this->val;
		int x0=1,x1=0,y0=0,y1=1,r,q,t,a = this->val,b = this->p;
		while(b!=0)
		{
			r = a%b;
			q = a/b;
			a = b;
			b = r;
			t = x1;
			x1 = x0-q*x1;
			x0 = t;
			t = y1;
			y1 = y0-q*y1;
			y0 = t;
		}
		return (x0+this->p)%this->p;
	}
	GFp operator/(GFp x)
	{
		return GFp(p,(this->val*x.inverse())%this->p);
	}
	friend ostream& operator <<(ostream& out,GFp p)
	{
		out<<p.val;
		return out;
	}
};
#endif 