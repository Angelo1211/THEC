#include "Chapter1.h"
#include "Chapter2.h"

#define PAUSE_ON_EXIT 0

int
main(void)
{
	char s1[] = "The Pied Piper Piped His Pipes.";
	char s2[] = "H";

	int result = AO_any(s1, s2);

	printf("We tried to find any ocurrance of %s in the string:\n\t>>%s\nWe found an ocurrance at index: %d\n", s2, s1, result);

	if (PAUSE_ON_EXIT) 
		Console_Delay_Exit();
}
