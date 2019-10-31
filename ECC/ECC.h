#include <bits/stdc++.h>
#include <gmp.h>
using namespace std;

#ifndef __ECC
#define __ECC

// this ECC curve is over Zp



void mul_inv(mpz_t inv,mpz_t a1,mpz_t p1)
{
	mpz_t x0,x1,y0,y1,q,g,r,t,a,p;
	//int x0 = 1,x1 = 0,y0 = 0,y1 = 1,q,g,r,t;
	mpz_inits(x0,x1,y0,y1,q,g,r,t,a,p,NULL);
	mpz_set(a,a1);
	mpz_set(p,p1);
	mpz_set_ui(x0,1);
	mpz_set_ui(x1,0);
	mpz_set_ui(y0,0);
	mpz_set_ui(y1,1);
	while(mpz_cmp_ui(p,1)!=0)
	{
		//gmp_printf("a = %Zd p = %Zd\n",a,p);
		mpz_mod(r,a,p);
		mpz_div(q,a,p);
		//gmp_printf("q = %Zd r = %Zd\n",q,r);
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
		}
		Point(const char* a1,const char* b1,const char* a,const char* b,const char* p,int bA=10,int bB=10,int bX=10,int bY=10,int bP=10)//,bool negA=false,bool negB=false)
		{
			//x = a1;y = b1;this->p = p;this->a = a;this->b = b;
			mpz_inits(this->a,this->b,this->x,this->y,this->p,this->INF,NULL);
			mpz_set_str(x,a1,bX);
			mpz_set_str(y,b1,bY);
			mpz_set_str(this->a,a,bA);
				// if(negA)
				// mpz_mul_ui(this->a,this->a,-1);
			mpz_set_str(this->b,b,bB);
			// if(negB)
			// 	mpz_mul_ui(this->b,this->b,-1);
			mpz_set_str(this->p,p,bP);
			mpz_set_str(INF,"6277101735386680763835789423207666416083908700390324961279000000",10);
		}
		Point(mpz_t a1,mpz_t b1,mpz_t a,mpz_t b,mpz_t p)
		{
			//x = a1;y = b1;this->p = p;this->a = a;this->b = b;
			mpz_inits(this->a,this->b,this->x,this->y,this->p,this->INF,NULL);
			mpz_set(x,a1);
			mpz_set(y,b1);
			 mpz_set(this->a,a);
			 //if(negA)
			// 	mpz_mul_ui(this->a,this->a,-1);
			mpz_set(this->b,b);
			// if(negB)
			// 	mpz_mul_ui(this->b,this->b,-1);
			mpz_set(this->p,p);
			mpz_set_str(INF,"6277101735386680763835789423207666416083908700390324961279000000",10);
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
				//gmp_printf(" den = %Zd\nnum = %Zd\n",den,num);
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
			Point p;//(0,0,a,b,p);
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
				out<<"( INF , INF )";//<<endl;
			}
			else
			gmp_printf("( %Zd , %Zd )",p.x,p.y);
			return out;
		}
	};

// class ECC
// {

// private:
// 	int a,b,p;
// private:
// 	vector<Point> points;
// public:
// 	ECC(int a,int b,int p) // p is a prime
// 	{
// 		this->a = a;
// 		this->b = b;
// 		this->p = p;int x,y;
// 		for(int i=0;i<p;i++)
// 		{
// 			for(int j=0;j<p;j++)
// 			{
// 				y = (j*j)%p;
// 				x = ((i*i*i)%p+((a%p)*i)%p+b%p)%p;
// 				if(y==x)
// 					points.push_back(Point(i,j,a,b,p));
// 			}
// 		}
// 	}
// 	void print_points()
// 	{
// 		for(int i=0;i<points.size();i++)
// 		{
// 			cout<<points[i]<<endl;
// 		}
// 	}

// };


#endif