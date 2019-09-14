#include <bits/stdc++.h>
using namespace std;
#ifndef __UTILS
#define __UTILS
string remove_punctuations_and_capitalise(string s)
{
	int i = 0,j = 0;bool f = false;
	while(j<s.length())
	{
		if((s[j]<'a'||s[j]>'z')&&(s[j]<'A'||s[j]>'Z'))
		{
			f = true;j++;
		}
		else
		{
			s[i] = (s[j]>='a'&&s[j]<='z')?s[j]-'a'+'A':s[j];i++;j++;
		}
		
	}

	if(f)
	while(s.length()!=i+1)
	{
		s.pop_back();
	}
	return s;
}

string format(string s)
{
	for(int i=0;i<s.length();i++)
	{
		if(i<s.length()-1&&s[i]==s[i+1])
		{
			s = s.substr(0,i+1)+"X"+s.substr(i+1,s.length()-i-1);
			i++;
		}
	}
	if(s.length()%2==1)
		s+="X";
	return s;
}
#endif