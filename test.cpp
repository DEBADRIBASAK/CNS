#include "utils.h"
using namespace std;

int main(int argc, char const *argv[])
{
	string poly="";
	cin>>poly;
	GF_2n g(poly);
	g.generate();
	//g.print_table();
	return 0;
}