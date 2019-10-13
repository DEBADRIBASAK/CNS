#ifndef __AES
#define __AES
//using namespace std;
#include "../../utils.h"
class AES
{
private:
	std::string key;
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
	AES(std::string key,int block_size=16,int no_of_rounds=10);

	int substitute_bits(unsigned char c1,bool inv=false);
	
	void sub_bit(unsigned char **block,bool inv=false);
	void shift_n_row(unsigned char* arr,int n,int k,bool left=true);

	void shift_rows(unsigned char **block,bool left=true);
	
	unsigned char** mix_col(unsigned char** block,bool enc=true);
	
	void add_round_key(int round_no,unsigned char **block);
	
	void test();
	
	void schedule_key();
	
	void print(int round_no,unsigned char** block);
	
	std::string encrypt(std::string plain_text);
	
	std::string decrypt(std::string plain_text);

	~AES();
	
};
#endif