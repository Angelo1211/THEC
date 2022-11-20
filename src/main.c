#include "Chapter1.h"
#include "Chapter2.h"

#define PAUSE_ON_EXIT 1

int
main(void)
{
	// 32 bits - 4 bytes - 1 byte = 0-255 = 0xFF
	// So this is the max we could fit 0xFF_FF_FF_FF | 0xDE_AD_BE_EF 
	// Hence our dumb test value should fit in a u32 no problem
	char number[] = "0xDEADBEEF";
	u32 result = 0;
	bool success = AO_htoi(number, &result);
	printf("Our number in hex was %s, after parsing we got %u, we %s\n", number, result, success ? "succeeded! :)" : "failed! :'(");

	if (PAUSE_ON_EXIT) 
		Console_Delay_Exit();
}
