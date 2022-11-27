#include "Chapter1.h"
#include "Chapter2.h"
#include "Chapter3.h"

#define PAUSE_ON_EXIT 0

int
main(void)
{
	AO_Test_escape();

	if (PAUSE_ON_EXIT) 
		Console_Delay_Exit();
	
}
