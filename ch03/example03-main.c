#include <stdlib.h>

void file1(char *);
void file2(char *);

int main(int argc, char **argv)
{
	if(argc!=3) exit(0);
	
	file1(argv[1]);
	file2(argv[2]);
}

