#include "stdafx.h"

int main(int argc, char *argv[])
{
	
	if (argc != 1)
	{	
		process(argv[1],argv[2], (int)argv[3]);
	}
	else
	{
		string mode;
		string name;
		int bit;
		cin >> mode >> name >> bit;
		process(mode,name, bit);
	}
	system("pause");//ÔÝÍ£
	return 0;
}