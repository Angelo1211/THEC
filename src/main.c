#include "Chapter1.h"
#include "Chapter2.h"
#include "Chapter3.h"
#include "Chapter4.h"

#define PAUSE_ON_EXIT 0

#define MAX_STRING (1 << 10)

int
main(void)
{
	int number = 2468;
	char s[MAX_STRING] = {0};
	int width = 10;

	AO_itoa_pad(number, s, width);

	printf("We got the number: %d\n", number);
	printf("And after padding got: %s\n", s);
	
	if (PAUSE_ON_EXIT) 
		Console_Delay_Exit();
}
