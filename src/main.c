#include "Chapter1.h"
#include "Chapter2.h"

#define PAUSE_ON_EXIT 0

int
main(void)
{
	char c = 'A';
	printf("We started with %c, now have %c\n", c, AO_lower(c));

	if (PAUSE_ON_EXIT) 
		Console_Delay_Exit();
}
