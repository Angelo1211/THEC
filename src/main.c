#include "Chapter1.h"
#include "Chapter2.h"
#include "Chapter3.h"
#include "Chapter4.h"
#include "Chapter5.h"

#define PAUSE_ON_EXIT 1

#define MAX_STRING (1 << 10)

int
main(void)
{
	float result = 0.0f;
	int ret = AO_getfloat(&result);

	printf("Result: %f\nRet: %d\n", result, ret);

	if (PAUSE_ON_EXIT)
		Console_Delay_Exit();
}
