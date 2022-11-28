#include "Chapter1.h"
#include "Chapter2.h"
#include "Chapter3.h"

#define PAUSE_ON_EXIT 1

int
main(void)
{
	AO_Test_shellsort();

	if (PAUSE_ON_EXIT) 
		Console_Delay_Exit();
	
}
