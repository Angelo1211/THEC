#include "Chapter1.h"
#include "Chapter2.h"
#include "Chapter3.h"
#include "Chapter4.h"
#include "Chapter5.h"

#define PAUSE_ON_EXIT 0

#define MAX_STRING (1 << 10)

int
main(void)
{
    int result = 0;
    AO_getint(&result);

    printf("Result: %d\n", result);

	if (PAUSE_ON_EXIT)
		Console_Delay_Exit();
}
