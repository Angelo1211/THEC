#include "Chapter1.h"
#include "Chapter2.h"

#define PAUSE_ON_EXIT 0

int
main(void)
{
	int value = -1;
	char number_string[] = "";
	bool success = AO_atoi(number_string, &value);

	printf("We parsed string %s %s and obtained the value: %d\n", number_string, success ? "succesfully" : "unsuccesfully", value);

	if (PAUSE_ON_EXIT) 
		Console_Delay_Exit();
}
