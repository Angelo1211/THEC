#include "Chapter1.h"
#include "common.h"

int
main(void)
{
	int n = 10;
	AO_DeTab(n);
	Exit_Console();
}

void
Exit_Console(void)
{
	printf("\nPress any key to exit!...\n");
	getchar();
}
