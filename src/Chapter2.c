#include "Chapter2.h"
#include <limits.h>
#include <float.h>

// 2.6 - Relational and Logical Operators
// ----------------------------------------------------------------------------------------------------------
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
#define FIND_INT_LIKE_LIMITS(type)  					\
do 														\
{														\
type current =0, previous = 0, max = 0; 				\
while(true)												\
{														\
	current += 1;										\
	if (current < previous)								\
	{													\
		max = previous;									\
		break;											\
	}													\
	previous = current;									\
}														\
current = previous = 0;									\
type min = 0;											\
while(true)												\
{														\
	current -= 1;										\
	if (current > previous)								\
	{													\
		min = previous;									\
		break;											\
	}													\
	previous = current;									\
}														\
printf(#type":\n Min-Max Signed %d, %d \n", min, max);	\
unsigned type current_u = 0, previous_u = 0, max_u = 0; \
while(true) 											\
{														\
	current_u += 1;										\
	if (current_u < previous_u)							\
	{													\
		max_u = previous_u;								\
		break;											\
	}													\
	previous_u = current_u;								\
}														\
current = previous_u = 0;								\
unsigned char min_u = 0;								\
while(true)												\
{														\
	current_u -= 1;										\
	if (current_u > previous_u)							\
	{													\
		min_u = previous_u;								\
		break;											\
	}													\
	previous_u = current_u;								\
}														\
printf(" Min-Max Unsigned %d, %d \n", min, max);		\
}														\
while(false)

// Ex 2-1 DONE: Write a program to determine the ranges of char, short, int, long, float and double
void 
AO_Find_Type_Numerical_Limits(void)
{
	printf("Reading Min and Max from standard Headers:\n");
	printf("------------------------------------------\n");
	{
		printf("Char:\n\tSigned \t%d, %d \n\tUnsigned  %d, %d", SCHAR_MIN, SCHAR_MAX, 0, UCHAR_MAX);
		printf("\nShort:\n\tSigned %d, %d \n\tUnsigned  %d, %d", SHRT_MIN, SHRT_MAX, 0, USHRT_MAX);
		printf("\nInt:\n\tSigned %d, %d \n\tUnsigned  \t%d, %u", INT_MIN, INT_MAX, 0, UINT_MAX);
		printf("\nLong(millions):\n\tSigned  %ld, %ld \n\tUnsigned  \t%ld, \t%lu", LONG_MIN / (u32)1e6, LONG_MAX / (u32)1e6, (long)0, ULONG_MAX / (u32)1e6);
		printf("\nFloat(12 digits, ):\n\t%.12f, %.12f ", FLT_MIN, FLT_MAX);
		printf("\nDouble: Min-Max (12 digits max) %.12f, (Divided by 1e300!!!) %.1f ", DBL_MIN, DBL_MAX / 1e300);
	}

	bool run_int_calcs = 0;
	bool run_flt_calcs = 1;

	// Computed
	printf("\n\nComputed Values:\n");
	printf("----------------\n");
	{
		if (run_int_calcs)
		{
			// Char
			FIND_INT_LIKE_LIMITS(char);

			// Short
			FIND_INT_LIKE_LIMITS(short);

			// Int
			FIND_INT_LIKE_LIMITS(int);

			// Long
			// NOTE(AO) Running this is not a good idea, it would work but it's a major time waste and is awfully slow
			//			We could do some kind of incremental stepping to avoid this, but it's not really worth the effort IMO.
			//FIND_INT_LIKE_LIMITS(long);
		}

		/*
			So the obvious solution of adding +1 and having it overflow is not going to be enough anymore. When we were doing this for ints
			the idea was that we were incrementing by the smallest possible increment (1) and this way we could be confident that the number we saw before
			overflowing was the largest possible number. This is not the case with floating point numbers because the smallest possible increment is different
			depending on the exponent we're currently at. So, we'll leverage the internal details of FP numbers to instead approach it this way for min and max:
			Min:
				- Get the smallest possible exponent (-127 for floats IIRC) then increment the mantissa by 1 bit. This is the smallest possible number
			Max:
				- Get the largest possible exponent (127 for floats)  then set all bits in the mantissa to 1. This should be the largest possible number

			I might be wrong as I don't really remember where stuff like +- inf , NaN and +- 0 are located.

			More details in:
			https://fabiensanglard.net/floating_point_visually_explained/

			I've thought about this some more and I think if I'm going to be using values from the mantissa it's kind of like using knowledge of
			how the float is structured, which is basically the same as reading the header. So I think there's a simpler way to do this though.
			Just exhaustively search every bit on a float
		*/
		if (run_flt_calcs)
		{
			// Float
			float min = 0.0f, max = 0.0f;
			for (u32 bitPattern = 0; bitPattern < U32_MAX; ++bitPattern)
			{
#if 0

				// How to cast u32 as floats
				// Get the address of the bits
				// Then say that this is actually pointing to a 
				float v = *(float *)&bitPattern;
#else
				union 
				{
					float f;
					 u32 b;
				} u = {.b = bitPattern};
				float v = u.f;
#endif
				max = v > max ? v : max;
				min = v < min ? v : min;
			}
			printf("\nFloat(12 digits, ):\n\t%.12f, %.12f ", min, max);

			// Double
			// It's going to be the same at the above

		}

	}

}
