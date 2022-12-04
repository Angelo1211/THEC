#include "Chapter1.h"
#include "Chapter2.h"
#include "Chapter3.h"

#define PAUSE_ON_EXIT 0

int
main(void)
{
	int t = 100;
	char temp[100];
	C_itoa(t , temp);
	printf("We converted the numer %d into the string %s.\n", t, temp);

	if (PAUSE_ON_EXIT) 
		Console_Delay_Exit();
}
