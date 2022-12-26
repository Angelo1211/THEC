#include "Chapter1.h"
#include "Chapter2.h"
#include "Chapter3.h"
#include "Chapter4.h"

#define PAUSE_ON_EXIT 0

#define MAX_STRING (1 << 10)

int
main(void)
{
	int result = -1;
	result = AO_strrindex("The test string test is a testThe test string test is a test", "test");
	printf("The result was %d\n", result);

	result = AO_strrindex("The test string test is a", "test");
	printf("The result was %d\n", result);

	result = AO_strrindex("test The string is a ", "test");
	printf("The result was %d\n", result);

	if (PAUSE_ON_EXIT) 
		Console_Delay_Exit();
}
