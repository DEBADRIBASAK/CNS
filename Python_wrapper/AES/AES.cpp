#include "../../utils.h"
#include "AES.h"
#include <stdbool.h>
using namespace std;


	AES::AES(string key,int block_size=16,int no_of_rounds=10)
	{
		this->key = key;
		this->block_size = block_size;
		this->no_of_rounds = no_of_rounds;
		round_keys = (unsigned char**)malloc(sizeof(unsigned char*)*44);
		for(int i=0;i<44;i++)
			round_keys[i] = (unsigned char*)malloc(sizeof(unsigned char)*4);
		g = new GF_2n("x8+x4+x3+x+1");
		//g->generate();
		schedule_key();
	}
	int AES::substitute_bits(unsigned char c1,bool inv=false)
	{
		unsigned char c2 = 0;int bit;
		int d = c1;
		if(!inv)
		{
			d = g->mul_inv((int)c1);
		}
		if(!inv)
		{
			for(int i=0;i<8;i++)
			{
				bit = 0;
				if(d&(1<<i))
					bit^=1;
				if(d&(1<<((i+4)%8)))
					bit^=1;
				if(d&(1<<((i+5)%8)))
					bit^=1;
				if(d&(1<<((i+6)%8)))
					bit^=1;
				if(d&(1<<((i+7)%8)))
					bit^=1;
				if(c&(1<<i))
					bit^=1;
				if(bit)
					c2|=(1<<i);
			}
		}
		else
		{
			for(int i=0;i<8;i++)
			{
				bit = 0;
				if(c1&(1<<((i+2)%8)))
					bit^=1;
				if(c1&(1<<((i+5)%8)))
					bit^=1;
				if(c1&(1<<((i+7)%8)))
					bit^=1;
				if(d1&(1<<i))
					bit^=1;
				if(bit)
					c2|=(1<<i);
			}
		}
		if(inv)
		{
			c2 = g->mul_inv((int)c2);
		}
		return c2;
	}
	void AES::sub_bit(unsigned char **block,bool inv=false)
	{
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				block[i][j] = substitute_bits(block[i][j],inv);
			}
		}
	}
	void AES::shift_n_row(unsigned char* arr,int n,int k,bool left=true)
	{
		if(!left)
			k = n-k;
		for(int i=0;i<k/2;i++)
		{
			swap(arr[i],arr[k-i-1]);
		}
		for(int i=k;i<k+(n-k)/2;i++)
		{
			swap(arr[i],arr[n+k-i-1]);
		}
		
		for(int i=0;i<n/2;i++)
		{
			swap(arr[i],arr[n-i-1]);
		}
	}
	void AES::shift_rows(unsigned char **block,bool left=true)
	{
		for(int i=1;i<4;i++)
		{
			shift_n_row(block[i],4,i,left);
		}
	}
	unsigned char** AES::mix_col(unsigned char** block,bool enc=true)
	{
		unsigned char** arr;
		arr = (unsigned char**)malloc(sizeof(unsigned char*)*4);
		for(int i=0;i<4;i++)
		arr[i] = (unsigned char*)malloc(sizeof(unsigned char)*4);
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				arr[i][j] = 0;
				for(int k=0;k<4;k++)
				{
					if(enc)
					arr[i][j]^=(g->multiply_num(mix_col_enc[i][k],(int)block[k][j]));
					else
					arr[i][j]^=(g->multiply_num(mix_col_dec[i][k],(int)block[k][j]));
				}
			}
		} 
		return arr;
	}
	void AES::add_round_key(int round_no,unsigned char **block)
	{
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				block[j][i]^=round_keys[4*round_no+i][j];
			}
		}
	}
	void AES::test()
	{
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				int ind = 0;
				for(int k=0;k<4;k++)
				{
					ind^=g->multiply_num(mix_col_enc[i][k],mix_col_dec[k][j]);
				}
				cout<<ind<<" ";
			}
			cout<<endl;
		}
	}
	void AES::schedule_key()
	{
		unsigned char temp[4];
		for(int i=0;i<4;i++) //16
		{
			for(int j=0;j<4;j++)
			{
				round_keys[i][j] = key[4*i+j];
			}
		}
		for(int i=4;i<44;i++)
		{
			for(int l=0;l<4;l++)
				temp[l] = round_keys[i-1][l];
			if(i%4==0)
			{
				unsigned char ch = temp[0];
				for(int l=0;l<=2;l++)
				{
					temp[l] = substitute_bits(temp[l+1]);
				}
				temp[3] = substitute_bits(ch);
				temp[0]^=rc[i/4-1];
			}
			for(int l=0;l<4;l++)
			round_keys[i][l] = temp[l]^round_keys[i-4][l];
		}
	}
	void AES::print(int round_no,unsigned char** block)
	{
		cout<<"Round "<<round_no<<" = ";
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				cout<<(int)block[j][i]<<" ";
			}
		}
		cout<<endl;
	}
	string AES::encrypt(string plain_text)
	{
		//cout<<"Encrypt = "<<endl;
		unsigned char **block;//[4][4];
		block = (unsigned char**)malloc(sizeof(unsigned char*)*4);
		for(int l=0;l<4;l++)
			block[l] = (unsigned char*)malloc(sizeof(unsigned char)*4);
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				block[j][i] = plain_text[i*4+j];
			}
		}
		//print(0,block);
		add_round_key(0,block);
		for(int i=1;i<no_of_rounds+1;i++){
			sub_bit(block);
			shift_rows(block);
			if(i!=no_of_rounds)
			{
				block = mix_col(block);
			}
			add_round_key(i,block);
			//print(i,block);
		}
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				plain_text[i*4+j] = block[j][i];
			}
		}
		return plain_text;
	}
	string AES::decrypt(string plain_text)
	{
		//cout<<"Decrypt = "<<endl;
		unsigned char **block;//[4][4];
		block = (unsigned char**)malloc(sizeof(unsigned char*)*4);
		for(int l=0;l<4;l++)
			block[l] = (unsigned char*)malloc(sizeof(unsigned char)*4);
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				block[j][i] = plain_text[i*4+j];
			}
		}
		//print(10,block);
		add_round_key(10,block);
		for(int i=no_of_rounds-1;i>=0;i--){
			shift_rows(block,false);
			sub_bit(block,true);
			add_round_key(i,block);
			if(i!=0)
			block = mix_col(block,false);
		//print(i,block);
		}
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				plain_text[i*4+j] = block[j][i];
			}
		}
		return plain_text;
	}

	AES::~AES()
	{
		delete g;
		for(int i=0;i<44;i++)
		{
			delete []round_keys[i];
		}
		delete []round_keys;
	}
