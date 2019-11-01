#include <bits/stdc++.h>
using namespace std;

#ifndef __DES
#define __DES

class DES
{
private:
	string key;
	int initial_perm[64]=  
    {   58,50,42,34,26,18,10,2, 
        60,52,44,36,28,20,12,4, 
        62,54,46,38,30,22,14,6, 
        64,56,48,40,32,24,16,8, 
        57,49,41,33,25,17,9,1, 
        59,51,43,35,27,19,11,3, 
        61,53,45,37,29,21,13,5, 
        63,55,47,39,31,23,15,7 
    }; 
    int exp_d[48]=  
    {   32,1,2,3,4,5,4,5, 
        6,7,8,9,8,9,10,11, 
        12,13,12,13,14,15,16,17, 
        16,17,18,19,20,21,20,21, 
        22,23,24,25,24,25,26,27, 
        28,29,28,29,30,31,32,1 
    }; 
    int s[8][4][16]= 
    {{ 
        14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7, 
        0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8, 
        4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0, 
        15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13 
    }, 
    { 
        15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10, 
        3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5, 
        0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15, 
        13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9 
    }, 
  
  
    { 
        10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8, 
        13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1, 
        13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7, 
        1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12 
    }, 
    { 
        7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15, 
        13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9, 
        10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4, 
        3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14 
    }, 
    { 
        2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9, 
        14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6, 
        4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14, 
        11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3 
    }, 
    { 
        12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11, 
        10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8, 
        9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6, 
        4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13 
    }, 
    { 
        4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1, 
        13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6, 
        1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2, 
        6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12 
    }, 
    { 
        13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7, 
        1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2, 
        7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8, 
        2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11 
    }}; 
    
    int per[32]= 
    {   16,7,20,21, 
        29,12,28,17, 
        1,15,23,26, 
        5,18,31,10, 
        2,8,24,14, 
        32,27,3,9, 
        19,13,30,6, 
        22,11,4,25 
    }; 
    int final_perm[64]=  
    {   40,8,48,16,56,24,64,32, 
        39,7,47,15,55,23,63,31, 
        38,6,46,14,54,22,62,30, 
        37,5,45,13,53,21,61,29, 
        36,4,44,12,52,20,60,28, 
        35,3,43,11,51,19,59,27, 
        34,2,42,10,50,18,58,26, 
        33,1,41,9,49,17,57,25 
    }; 
    int keyp[56]=  
    {   57,49,41,33,25,17,9, 
        1,58,50,42,34,26,18, 
        10,2,59,51,43,35,27, 
        19,11,3,60,52,44,36,           
        63,55,47,39,31,23,15, 
        7,62,54,46,38,30,22, 
        14,6,61,53,45,37,29, 
        21,13,5,28,20,12,4 
    }; 
    int shift_table[16]= 
    {   1, 1, 2, 2, 
        2, 2, 2, 2,  
        1, 2, 2, 2,  
        2, 2, 2, 1 
    }; 
    int key_comp[48]= 
    {   14,17,11,24,1,5, 
        3,28,15,6,21,10, 
        23,19,12,4,26,8, 
        16,7,27,20,13,2, 
        41,52,31,37,47,55, 
        30,40,51,45,33,48, 
        44,49,39,56,34,53, 
        46,42,50,36,29,32 
    }; 
    vector<string> subkeys;
    string perm_key;
    //ofstream cout;
public:
	DES(string key)
	{
		this->key = key;
        perm_key = key;
       // cout.open("log.txt",ios::out);
	}
	void circular_left_shift(int shift)
	{
		string left_key = key.substr(0,4);
		string right_key = key.substr(3,4);
		char k = (1<<5)-1;
		left_key[3]&=(k<<4);
		
		char f = 0;
		f = left_key[0]>>(8-shift);
		for(int i=0;i<4;i++)
		{
			if(i<3)
			left_key[i] = (left_key[i]<<shift)^(left_key[i+1]>>(8-shift));
			else
			{
				left_key[i] = (left_key[i]<<shift)^(f<<4);
			}
		}

		right_key[0]&=k;
        f = right_key[0]>>(4-shift);
		for(int i=0;i<4;i++)
		{
			if(i<3)
			right_key[i] = (right_key[i]<<shift)^(right_key[i+1]>>(8-shift));
			else
			{
				right_key[i] = (right_key[i]<<shift)^(f);
			}
		}
		right_key[0]&=k;
		for(int i=0;i<7;i++)
		{
			if(i<3)
				key[i] = left_key[i];
			else if(i==3)
				key[i] = left_key[i]^right_key[i];
			else
				key[i] = right_key[i];
		}
	}
	void drop_parity()
	{
		string k = string({0,0,0,0,0,0,0});
        char c = 1;
		for(int i=0;i<56;i++)
		{
			if(key[(keyp[i]-1)/8]&(c<<((8-((keyp[i]-1)%8))%8)))
			k[i/8]|=(c<<((8-(i%8))%8));
		}
		key = k;
	}
	string compress()
	{
		string k = string({0,0,0,0,0,0});
        	char c = 1;
		for(int i=0;i<48;i++)
		{
			if(key[(key_comp[i]-1)/8]&(c<<((8-((key_comp[i]-1)%8))%8)))
			k[i/8]|=(c<<((8-(i%8))%8));
		}
        	return k;
	}
	string key_scheduling(int round_no)
	{
		int shift = shift_table[round_no-1];
		circular_left_shift(shift);
		return compress();
	}
	string perm(string plain_text,int* p,int sz)
	{
		string k(sz/8,0);char c = 1;
		for(int i=0;i<sz;i++)
		{
			if(plain_text[(p[i]-1)/8]&(c<<((8-((p[i]-1)%8))%8)))
			k[i/8]|=(c<<((8-(i%8))%8));
		}
		return k;
	}
    string substitute(string st)
    {
        string k(4,0);
        int i = 0,j = 7;
        for(int l=0;l<8;l++)
        {
            int helper = 0;
            for(int m=0;m<6;m++)
            {
                helper*=2;
                if(st[i]&(1<<j))
                {
                    helper++;
                }
                if(j>0)
                    j--;
                else
                {
                    j = 7;i++;
                }
            }
            int row = (helper>>5)*2+(helper&1);
            int col = (helper>>1)^(1<<5);
            if(l%2)
            {
                k[l/2]|=((char)s[l][row][col]);
            }
            else
                k[l/2]|=((char)s[l][row][col]<<4);
        }
        return k;
    }
	string round(string plain_text,string key,int no)
	{
		string left = plain_text.substr(0,4);
		string right = plain_text.substr(4,4);
		string dummy;
		dummy = perm(right,exp_d,48);
		for(int i=0;i<6;i++)
        {
            char c1 = key[i],c2 = dummy[i];
			dummy[i] = c1^c2;
        }
        dummy = substitute(dummy);
        dummy = perm(dummy,per,32);
        for(int i=0;i<4;i++)
        {
           dummy[i]^=left[i];
        }
        return (no==15)?(dummy+right):(right+dummy);
	}
    void reset_key(string key)
    {
        key = perm_key;
    }
    void generate_all_keys()
    {
         drop_parity();
         for(int i=1;i<=16;i++)
        {
            string k = key_scheduling(i);
            subkeys.push_back(k);
        }
    }
    void log(string p)
    {
        for(int i=0;i<p.length();i++)
        {
            cout<<(int)p[i]<<" ";
        }
        cout<<endl;
    }
	string encrypt(string plain_text)
	{    
        plain_text = perm(plain_text,initial_perm,64);
        for(int i=1;i<=16;i++)
        {
            plain_text = round(plain_text,subkeys[i-1],i-1);
        }     
        plain_text = perm(plain_text,final_perm,64);
        return plain_text;
	}
    string decrypt(string plain_text)
    {
        plain_text = perm(plain_text,initial_perm,64);
        for(int i=16;i>=1;i--)
        {
            plain_text = round(plain_text,subkeys[i-1],16-i);
        }     
        plain_text = perm(plain_text,final_perm,64);
        return plain_text;
    }
    void test(string plain_text)
    {
        plain_text = perm(plain_text,initial_perm,64);
        cout<<"After intial permutation = ";//<<plain_text<<endl;
        log(plain_text);
        for(int i=1;i<=16;i++)
        {
            plain_text = round(plain_text,subkeys[i-1],i-1);
            cout<<"Round: "<<i<<" = ";//<<plain_text<<endl;
            log(plain_text);
        } 
        plain_text = perm(plain_text,final_perm,64);
        cout<<"cipher text = ";//<<plain_text<<endl;
       log(plain_text);
        cout<<endl;
        //cout<<"cipher text = "<<plain_text<<endl;
         plain_text = perm(plain_text,initial_perm,64);
          cout<<"After intial permutation = ";//<<plain_text<<endl;
          log(plain_text);
        cout<<endl;
        for(int i=16;i>=1;i--)
        {
            plain_text = round(plain_text,subkeys[i-1],16-i);
            cout<<"Round: "<<i<<" = ";//<<plain_text<<endl;
            log(plain_text);
        }     
         plain_text = perm(plain_text,final_perm,64);
         cout<<"plain text = "<<plain_text<<endl;
    }
};

#endif
