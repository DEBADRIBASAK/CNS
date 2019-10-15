#include <bits/stdc++.h>
#include "utils.h"
using namespace std;



int main(int argc, char const *argv[])
{
	int xA,xB,yA,yB,g,n;
	
	cout<<"Enter the Order of field\n";
	cin>>n;
	vector<int> v;
	vector<bool> prime(n+1,true);
	vector<int> factors;
	factors = seive(prime,n);

	for(int i=0;i<factors.size();i++)
	{
		cout<<factors[i]<<" ";
	}
	cout<<endl;

	g = generator(factors,n);
	//g = 9;

	cin>>xA;
	yA = modular_exponentiation(g,xA,n);

	cin>>xB;
	yB = modular_exponentiation(g,xB,n);

	cout<<"generator = "<<g<<endl<<"xA = "<<xA<<endl<<"xB = "<<xB<<endl<<"yA = "<<yA<<endl<<"yB = "<<yB<<endl;

	int K = modular_exponentiation(yA,xB,n);
	int K1 = modular_exponentiation(yB,xA,n);
	cout<<"K = "<<K<<"\nK1 = "<<K1<<endl;
	cout<<"True value = "<<(K==K1)<<endl;

	return 0;
}