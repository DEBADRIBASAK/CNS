#include <bits/stdc++.h>
#include "utils.h"
using namespace std;
#ifndef __CIPHERS
#define __CIPHERS
string caeser_encrypt(string pt,int displacement)
{
	pt = remove_punctuations_and_capitalise(pt);
	for(int i=0;i<pt.length();i++)
	{
		pt[i] = (pt[i]-'A'+displacement)%26+'A';
	}
	return pt;
}
string caeser_decrypt(string pt,int displacement)
{
	pt = remove_punctuations_and_capitalise(pt);
	for(int i=0;i<pt.length();i++)
	{
		pt[i] = (pt[i]-'A'-displacement)%26+'A';
	}
	return pt;
}
string playfair_encrypt(string pt,string key)
{
	pt = remove_punctuations_and_capitalise(pt);
	pt = format(pt);
	vector<vector<char> > playfair_encryption_table(5,vector<char>(5,0));
	map<char,pair<int,int> > m;
	int i = 0,j = 0;
	for(int k=0;k<key.size();k++)
	{
		playfair_encryption_table[i][j] = key[k];
		m[key[k]] = make_pair(i,j);
		if(j<4)
			j++;
		else if(i<4)
		{
			i++;j = 0;
		}
		else
			break;
	}
	for(char k='A';k<='Z';k++)
	{
		if(m.find(k)==m.end())
		{
			if(k!='J')
			{
				playfair_encryption_table[i][j] = k;
				m[k] = make_pair(i,j);
				if(j<4)
					j++;
				else if(i<4)
				{
					i++;j = 0;
				}
				else
					break;
			}
		}
	}
	if(m.find('J')==m.end())
	{
		m['J'] = m['I'];
	}
	else
		m['Z'] = m['I'];
	string c1="";pair<int,int> p1,p2;
	for(int i=0;i<pt.length();i+=2)
	{
		p1 = m[pt[i]];
		p2 = m[pt[i+1]];
		if(p1.first==p2.first)
		{
			c1.push_back(playfair_encryption_table[p1.first][(p1.second+1)%5]);
			c1.push_back(playfair_encryption_table[p2.first][(p2.second+1)%5]);
		}
		else if(p1.second==p2.second)
		{
			c1.push_back(playfair_encryption_table[(p1.first+1)%5][p1.second]);
			c1.push_back(playfair_encryption_table[(p2.first+1)%5][p2.second]);
		}
		else
		{
			c1.push_back(playfair_encryption_table[p1.first][p2.second]);
			c1.push_back(playfair_encryption_table[p2.first][p1.second]);
		}
	}
	return c1;
}

#endif