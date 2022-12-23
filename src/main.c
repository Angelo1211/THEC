#include "Chapter1.h"
#include "Chapter2.h"
#include "Chapter3.h"

#define PAUSE_ON_EXIT 0

#define MAX_STRING (1 << 10)

int
main(void)
{
	int number = 123456789;
	char s[MAX_STRING] = {0};
	
	printf("Representing the number % in these bases:\n", number);
	printf("-----------------------------------------\n");

	for (int b = 2; b <= 16; ++b)
	{
		AO_itob(number, s, b);
		printf("%4d | %s ", b, s);
	}

	if (PAUSE_ON_EXIT) 
		Console_Delay_Exit();
}
