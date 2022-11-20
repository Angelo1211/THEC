#include "Chapter1.h"
#include "Chapter2.h"

#define PAUSE_ON_EXIT 1

int
main(void)
{
	char s1[] = "123aaa123bbb456test777";
	char s2[] = "123456";

	// NOTE(AO) This worked, but gave a value +1 larger than I thought it would. That's because s1 is a character array, so we stuff an '\0' at the end to signal 
	//			That the string terminated.
	printf("This string is %d characters long: %s\n", (s32)NELEM(s1), s1);

	printf("Prev string:\n%s\n\n", s1);


	AO_squeeze(s1, s2);

	printf("Squeezed String:\n%s\n", s1);

	if (PAUSE_ON_EXIT) 
		Console_Delay_Exit();
}
