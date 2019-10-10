#include "../utils.h"
#include <stdbool.h>
using namespace std;
#ifndef __AES
#define __AES
class AES
{
private:
	string key;
	const int c = 0x63,d1 = 0x05,rc[10] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x1B,0x36};
	int block_size,no_of_rounds;
	int mix_col_enc[4][4] = 
	{
		{2,3,1,1},
		{1,2,3,1},
		{1,1,2,3},
		{3,1,1,2}
	};
	int mix_col_dec[4][4] = 
	{
		{0x0e,0x0b,0x0d,0x09},
		{0x09,0x0e,0x0b,0x0d},
		{0x0d,0x09,0x0e,0x0b},
		{0x0b,0x0d,0x09,0x0e}
	};
	GF_2n *g;
	unsigned char **round_keys;
public:
	AES(string key,int block_size=16,int no_of_rounds=10)
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
	int substitute_bits(unsigned char c1,bool inv=false)
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
	void sub_bit(unsigned char **block,bool inv=false)
	{
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				//printf("%c,%04X = ",block[i][j],(int)block[i][j]);
				block[i][j] = substitute_bits(block[i][j],inv);
				//printf("%04X\n",(int)block[i][j]);
			}
		}
	}
	void shift_n_row(unsigned char* arr,int n,int k,bool left=true)
	{
		// for(int i=0;i<n;i++)
		// {
		// 	printf("%c  ",arr[i]);
		// }
		// printf("\n");
		if(!left)
			k = n-k;
		//if(left)
		//{
			for(int i=0;i<k/2;i++)
			{
				swap(arr[i],arr[k-i-1]);
			}
			for(int i=k;i<k+(n-k)/2;i++)
			{
				swap(arr[i],arr[n+k-i-1]);
			}
		//}
		for(int i=0;i<n/2;i++)
		{
			swap(arr[i],arr[n-i-1]);
		}
	}
	void shift_rows(unsigned char **block,bool left=true)
	{
		for(int i=1;i<4;i++)
		{
			shift_n_row(block[i],4,i,left);
		}
	}
	unsigned char** mix_col(unsigned char** block,bool enc=true)
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
	void add_round_key(int round_no,unsigned char **block)
	{
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				//cout<<block[j][i]<<"^"<<round_keys[4*round_no+i][j]<<" = ";//<<(block[j][i]^round_keys[4*round_no+i][j])<<endl;
				//printf("%04X ^ %04X",block[j][i],round_keys[4*round_no+i][j]);
				block[j][i]^=round_keys[4*round_no+i][j];
				//cout<<block[j][i]<<endl;
			}
		}
	}
	void test()
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
	void schedule_key()
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

		// cout<<"Keys = "<<endl;
		// for(int i=0;i<44;i++)
		// {
		// 	for(int j=0;j<4;j++)
		// 	cout<<round_keys[i][j]<<" ";
		// cout<<endl;
		// }
	}
	void print(int round_no,unsigned char** block)
	{
		//cout<<"=========================================\n\n";
		cout<<"Round "<<round_no<<" = ";
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				cout<<(int)block[j][i]<<" ";
			}
			//cout<<endl;
		}
		//cout<<"\n=========================================\n\n";
		cout<<endl;
	}
	string encrypt(string plain_text)
	{
		cout<<"Encrypt = "<<endl;
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
		print(0,block);
		add_round_key(0,block);
		for(int i=1;i<no_of_rounds+1;i++){
			sub_bit(block);
			shift_rows(block);
			if(i!=no_of_rounds)
			{
				block = mix_col(block);
			}
			add_round_key(i,block);
			print(i,block);
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
	string decrypt(string plain_text)
	{
		cout<<"Decrypt = "<<endl;
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
		print(10,block);
		add_round_key(10,block);
		for(int i=no_of_rounds-1;i>=0;i--){
			shift_rows(block,false);
			sub_bit(block,true);
			add_round_key(i,block);
			if(i!=0)
			block = mix_col(block,false);
		print(i,block);
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
};
#endif