#include "Chapter1.h"
#include "Chapter2.h"

#define PAUSE_ON_EXIT 0

int
main(void)
{
	u32 x = 0x00F000FF;
	int r = 12;

	u32 result = AO_bitcount(x);

	printf("We expected %u, got %u, which is %s.\n", r, result, r == result ? "Correct!": "Wrong! :(");

	if (PAUSE_ON_EXIT) 
		Console_Delay_Exit();
}
