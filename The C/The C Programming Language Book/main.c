#include "Chapter1.h"
#include "common.h"

int
main(void)
{
	AO_Fold_Test();
	Exit_Console();
}

void
Exit_Console(void)
{
	printf("\nPress any key to exit!...\n");
	getchar();
}
