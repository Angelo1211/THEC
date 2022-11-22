#include "Chapter1.h"
#include "Chapter2.h"

#define PAUSE_ON_EXIT 0

int
main(void)
{
	u32 x = 0b100001;
	u32 y = 0b000011;
	u32 r = 0b101101;

	u32 result = AO_setbits(x, 4, 3, y);

	printf("We expected %u, but got %u", r, result);

	if (PAUSE_ON_EXIT) 
		Console_Delay_Exit();
}
