#include "Chapter1.h"
#include "Chapter2.h"
#include "Chapter3.h"
#include "Chapter4.h"

#define PAUSE_ON_EXIT 0

#define MAX_STRING (1 << 10)

int
main(void)
{
	char test[]  = "3.14159265359";
	char test2[] = "123.45e-6";
	
	printf("The input was %s\nAfter parsing we got %0.10f\n", test2, AO_atof(test2));

	if (PAUSE_ON_EXIT) 
		Console_Delay_Exit();
}
