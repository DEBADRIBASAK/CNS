#include <bits/stdc++.h>
#include <gmp.h>
using namespace std;

#ifndef __ECC
#define __ECC

// this ECC curve is over Zp

#define inf "6277101735386680763835789423207666416083908700390324961279000000"


void mul_inv(mpz_t inv,mpz_t a1,mpz_t p1)
{
	mpz_t x0,x1,y0,y1,q,g,r,t,a,p;
	mpz_inits(x0,x1,y0,y1,q,g,r,t,a,p,NULL);
	mpz_set(a,a1);
	mpz_set(p,p1);
	mpz_set_ui(x0,1);
	mpz_set_ui(x1,0);
	mpz_set_ui(y0,0);
	mpz_set_ui(y1,1);
	while(mpz_cmp_ui(p,1)!=0)
	{
		mpz_mod(r,a,p);
		mpz_div(q,a,p);
		mpz_set(a,p);
		mpz_set(p,r);
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


class Point
	{
	private:
		mpz_t a,b,x,y,p,INF;
	public:
		Point()
		{
			mpz_inits(a,b,x,y,p,INF,NULL);
			mpz_set_str(INF,inf,10);
		}
		Point(const char* a1,const char* b1,const char* a,const char* b,const char* p,int bA=10,int bB=10,int bX=10,int bY=10,int bP=10)//,bool negA=false,bool negB=false)
		{

			mpz_inits(this->a,this->b,this->x,this->y,this->p,this->INF,NULL);
			mpz_set_str(x,a1,bX);
			mpz_set_str(y,b1,bY);
			mpz_set_str(this->a,a,bA);
			mpz_set_str(this->b,b,bB);
			mpz_set_str(this->p,p,bP);
			mpz_set_str(INF,inf,10);
		}
		Point(mpz_t a1,mpz_t b1,mpz_t a,mpz_t b,mpz_t p)
		{

			mpz_inits(this->a,this->b,this->x,this->y,this->p,this->INF,NULL);
			mpz_set(x,a1);
			mpz_set(y,b1);
			mpz_set(this->a,a);
			mpz_set(this->b,b);
			mpz_set(this->p,p);
			mpz_set_str(INF,inf,10);
		}
		bool isInf()
		{
			return (mpz_cmp(this->x,INF)==0)&&(mpz_cmp(this->y,INF)==0);
		}
		bool operator ==(Point p1)
		{
			return (mpz_cmp(this->x,p1.x)==0)&&(mpz_cmp(this->y,p1.y)==0);
		}
		void operator=(Point p)
		{
			mpz_set(this->x,p.x);
			mpz_set(this->y,p.y);
			mpz_set(this->p,p.p);
			mpz_set(this->a,p.a);
			mpz_set(this->b,p.b);
		}
		Point operator +(Point p1)
		{
			mpz_t slope,num,den,t;
			mpz_inits(slope,num,den,t,NULL);
			if(*this==p1)
			{
				mpz_mul(t,p1.x,p1.x);
				mpz_mul_ui(t,t,3);
				mpz_add(t,t,a);
				mpz_mod(t,t,p);
				mpz_set(num,t);
				mpz_set(t,p1.y);
				mpz_mul_ui(t,t,2);
				mpz_mod(t,t,p);
				mpz_set(den,t);
			}
			else
			{
				mpz_set(t,p1.x);
				mpz_sub(t,t,this->x);
				mpz_mod(den,t,p);
				mpz_set(t,p1.y);
				mpz_sub(t,t,this->y);
				mpz_mod(num,t,p);
			}
			if(mpz_cmp_ui(den,0)==0)
			{
				return Point(INF,INF,a,b,p); // The No point
			}
			else
			{
				mpz_t xr,yr;
				mpz_inits(xr,yr,NULL);
				mul_inv(t,den,p);
				mpz_mul(slope,num,t);
				mpz_mod(slope,slope,p);
				mpz_mul(t,slope,slope);
				mpz_sub(t,t,this->x);
				mpz_sub(t,t,p1.x);
				mpz_add(t,t,p);
				mpz_mod(xr,t,p);
				mpz_sub(t,this->x,xr);
				mpz_add(t,t,p);
				mpz_mul(t,t,slope);
				mpz_mod(t,t,p);
				mpz_sub(t,t,this->y);
				mpz_add(t,t,p);
				mpz_mod(yr,t,p);
				return Point(xr,yr,a,b,p);
			}
		}
		Point operator*(mpz_t m1)
		{
			mpz_t m;
			mpz_inits(m,NULL);
			mpz_set(m,m1);
			Point p;
			p = *this;
			while(mpz_cmp_ui(m,1)!=0)
			{
				p = p+(*this);
				mpz_sub_ui(m,m,1);
			}
			return p;
		}
		friend ostream& operator <<(ostream& out,Point p)
		{
			if(p.isInf())
			{
				out<<"( INF , INF )";
			}
			else
			gmp_printf("( %Zd , %Zd )",p.x,p.y);
			return out;
		}
	};


#endif