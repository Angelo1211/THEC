#include "Chapter2.h"
#include <limits.h>
#include <float.h>

// 2.6 - Relational and Logical Operators
// ----------------------------------------------------------------------------------------------------------
/**
 * for (i = 0;
	   (i < lim - 1) && 
		((c = getchar()) != '\n') && 
		(c != EOF);
	   ++i)
 */
void AO_New_For(void)
{
	int lim = 10;
	int i = 0;
	while (i < lim - 1)
	{

	}
}

// 2.2 - Data Types and Sizes
// ----------------------------------------------------------------------------------------------------------
void 
AO_Find_Type_Numerical_Limits(void)
{
	printf("Library Macros:\n");
	printf("---------------\n");
	{
		printf("Char: Min-Max Signed %d, %d \t Min-Max Unsigned  %d, %d", SCHAR_MIN, SCHAR_MIN, 0, UCHAR_MAX);
		printf("\nShort: Min-Max Signed %d, %d \t Min-Max Unsigned  %d, %d", SHRT_MIN, SHRT_MAX, 0, USHRT_MAX);
		printf("\nInt: Min-Max Signed %d, %d \t Min-Max Unsigned  %d, %u", INT_MIN, INT_MAX, 0, UINT_MAX);
		printf("\nLong: Min-Max Signed %ld, %ld \t Min-Max Unsigned  %ld, %lu", LONG_MIN, LONG_MAX, 0, ULONG_MAX);
		printf("\nFloat: Min-Max %f, %f ", FLT_MIN, FLT_MAX);
		printf("\nDouble: Min-Max Signed %f, %f ", DBL_MIN, DBL_MAX);
	}

	// Computed
	printf("\n\nComputed Values:\n");
	printf("----------------\n");
	{
		// Char
			// Signed
			// Unsigned

		// Short
			// Signed
			// Unsigned

		// Int
			// Signed
			// Unsigned

		// Long
			// Signed
			// Unsigned

		// Float
			// Signed
			// Unsigned

		// Double
			// Signed
			// Unsigned
	}

}
