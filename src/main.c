#include "Chapter1.h"
#include "Chapter2.h"
#include "Chapter3.h"

#define PAUSE_ON_EXIT 1

int
main(void)
{
	char o[] = "Hello World!";
	char s[] = "Hello World!";
	char r[] = "!dlroW olleH";

	AO_reverse_ip(s);

	C_reverse(o);

	// Funny that I say that I have a method, it's essentially the same thing except the useless comma operator
	printf("We tried to reverse the string %s and %s. Got %s via my method, got %s via the c book method. \n", o, B2S(strcmp(s, r) == 0), s, o);

	if (PAUSE_ON_EXIT) 
		Console_Delay_Exit();
}
