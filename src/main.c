#include "Chapter1.h"
#include "Chapter2.h"

#define PAUSE_ON_EXIT 0

int
main(void)
{
	char number[] = "0xDEADBEEF";
	u32 result = 0;
	bool success = AO_htoi(number, &result);
	printf("Our number in hex was %s, after parsing we got %x, we %s\n", number, result, success ? "succeeded! :)" : "failed! :'(");

	if (PAUSE_ON_EXIT) 
		Console_Delay_Exit();
}
