#include "AES.h"
#include <cstdio>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char const *argv[])
{
	int fd = open(argv[1],O_RDONLY);
	ofstream fd1("encryption.txt"),fd2("decryption.txt");
	char block[17] = {0};
	int sz;
	sz = read(fd,block,16);
	string key = "abcdABCD1234#@$&",dummy;
	AES g(key);
	while(sz>0)
	{
		if(sz<16)
			block[sz] = '\0';
		dummy = g.encrypt(string(block));
		//cout<<"cipher text = "<<dummy<<endl;
		fd1<<dummy;
		dummy = g.decrypt(dummy);
		//cout<<"decrypted = "<<dummy<<endl;
		fd2<<dummy;
		memset(block,0,sizeof(block));
		sz = read(fd,block,16);
	}
	close(fd);
	fd1.close();
	fd2.close();
	return 0;
}