#include "types.h"
#include "user.h"


int main(int argc, char *argv[])
{
	settickets(20);
	int i,k;
	const int loop=100000;
	for(i=0;i<loop;i++)
		for(k=0;k<loop;k++)
			asm("nop");
		
	showpinfo();
	exit();
}