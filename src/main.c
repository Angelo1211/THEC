#include "Chapter1.h"
#include "Chapter2.h"

#define PAUSE_ON_EXIT 0

int
main(void)
{
	u32 x = 0b100001;
	u32 r = 0b111111;

	u32 result = AO_invert(x, 4, 4);

	printf("We expected %u, got %u.\n", r, result);

	if (PAUSE_ON_EXIT) 
		Console_Delay_Exit();
}
