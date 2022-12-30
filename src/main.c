#include "Chapter1.h"
#include "Chapter2.h"
#include "Chapter3.h"
#include "Chapter4.h"

#define PAUSE_ON_EXIT 0

#define MAX_STRING (1 << 10)

int
main(void)
{
	C_calculator();

	if (PAUSE_ON_EXIT) 
		Console_Delay_Exit();
}
