#include "Chapter1.h"
#include "Chapter2.h"
#include "Chapter3.h"

#define PAUSE_ON_EXIT 0

int
main(void)
{
	int t = INT_MIN;
	char temp[100];
	C_itoa(t , temp);
	printf("We converted the numer %d into the string %s.\n", t, temp);

	AO_itoa(t , temp);
	printf("We converted the numer %d into the string %s.\n", t, temp);

	t = -120;
	AO_itoa(t , temp);
	printf("We converted the numer %d into the string %s.\n", t, temp);

	t = -1;
	AO_itoa(t , temp);
	printf("We converted the numer %d into the string %s.\n", t, temp);

	if (PAUSE_ON_EXIT) 
		Console_Delay_Exit();
}
