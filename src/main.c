#include "Chapter1.h"
#include "Chapter2.h"

#define PAUSE_ON_EXIT 0

int
main(void)
{
	u32 x = 0x000000FF;
	u32 r = 0xF000000F;

	u32 result = AO_rightrot(x, 8);

	printf("We expected %u, got %u, which is %s.\n", r, result, r == result ? "Correct!": "Wrong! :(");

	if (PAUSE_ON_EXIT) 
		Console_Delay_Exit();
}
