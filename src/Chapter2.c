#include "Chapter2.h"

// 2.9 - Bitwise Operators
// ----------------------------------------------------------------------------------------------------------
// Ex 2-7 DONE Write a function invert(x, p, n) that returns x with the n bits that begin at position p inverted, leaving the others unchanged
u32 AO_invert(u32 bits, int p, int n)
{
    // We're being very explicit here only because I enjoy stepping through the debugger and
    // seeing the bitmask change. I just think it's neat.
	u32 mask = ~0;
    mask = mask << n;
    mask = ~mask;
    mask = mask << (p - n + 1);

	// xor will do the inverting of the bits (if it was a 1 it'll be a zero, if it was a zero it'll be a one)
    u32 region_of_interest = bits & mask;
    region_of_interest = region_of_interest ^ mask;
    u32 rest_of_the_bits = (bits & ~mask);
    
    
	return region_of_interest | rest_of_the_bits;
}

// Ex 2-6 DONE Write a function setbits(x, p, n, y) that returns x with the n bits that begin at position p set to the rightmost n bits of y. Leaves other bits unchanged
u32 AO_setbits(u32 bits, int p, int n, u32 y)
{
	// Remove all bits except for the rightmost n bits in y
	y &= ~(~0 << n);

	// Shift the bits in y that we want into their expected location
	y = y << (p - n + 1);

	u32 mask = ~0; // all ones
	mask = mask << n; // introduce n zeros at the end
	mask = ~mask; // flip all zeros and ones, we should now have n ones in the right most location
	mask = mask << (p - n + 1) ; // move the ones in the rightmost location up till they match p

	bits = bits & ~mask;
	bits = bits | y;

	return bits;
}

u32 C_getbits(u32 bits, int p, int n)
{
	return (bits >> (p - n + 1)) & ~(~0 << n);
}


// 2.8 - Increment and Decrement Operators
// ----------------------------------------------------------------------------------------------------------
// Ex 2-5 DONE Write a function any(s1, s2) which returns the first location in the string s1 of any character that appears in s2. -1 if no characters appear
int AO_any(char s1[], char s2[])
{

	// Go over the entire string array we want to inspect for chars.
	for (int i = 0; s1[i] != '\0'; ++i)
	{
		// Go over all of the characters we should get rid of
		for (int j = 0; s2[j] != '\0'; ++j)
		{
			if (s1[i] == s2[j])
			{
				return i;
			}
		}
	}

	return -1;
}

// Ex 2-4 DONE Write a version of squeeze (s1, s2) that deletes each character in s1 that matches any character in s2
void AO_squeeze(char s1[], char s2[])
{
	int j = 0;
	// Go over the entire string array we want to squeeze.
	for (int i = 0; s1[i] != '\0'; ++i)
	{
		// Go over all of the characters we should get rid of
		bool matches_any = false;
		for (int k = 0; s2[k] != '\0'; ++k)
		{
			if (s1[i] == s2[k])
			{
				// Skip past this
				matches_any = true;
				break;
			}
		}

		if (!matches_any)
		{
			s1[j++] = s1[i];
		}
	}
	s1[j] = '\0';
}

// 2.7 - Type Conversions
// ----------------------------------------------------------------------------------------------------------
// Ex 2-3 DONE Write the function htoi(s) which converts a string of hexadecimal digits into it's equivalent int value
bool AO_htoi(char value_as_hex_string[], u32 *value_as_int)
{
	u32 result = 0;
	int i = 0;

	if (value_as_hex_string[i] == '\0')
		return false;
	
	// Moving past the optional 0x or 0X
	if (value_as_hex_string[i] == '0' )
	{
		if (value_as_hex_string[i + 1] == 'x' || value_as_hex_string[i + 1] == 'X')
		{
			i += 2;
		}
	}

	while (value_as_hex_string[i] != '\0')
	{
		char c = value_as_hex_string[i];

		result *= 16;

		if (c >= '0' && c <= '9')
		{
			result += c - '0';
		}
		else if (c >= 'A' && c <= 'F')
		{
			result += 10 + c - 'A';
		}
		else if (c >= 'a' && c <= 'f')
		{
			result += 10 + c - 'a';
		}
		else
			return false;
		
		i += 1;
	}

	*value_as_int = result;
	return true;
}


// NOTE(AO) This stuff is only really valid in ASCII
//			Also I did not bother doing a C_ version because it's pretty much the same implementation
int AO_lower(int c)
{
	if (c < 'A' || c > 'Z')
		return c;

	// Get the offset from the letter uppercase A, move that same offset forwards staring from lowercase a
	return (c - 'A') + 'a';
}

int C_atoi(char s[])
{
	int i,n;
	
	n = 0;
	for (i = 0; s[i] >= '0' && s[i] <= '9'; ++i)
		n = 10 * n + (s[i] - '0'); // this is how you get the numerical value of a number char like 0

	return n;
}

bool AO_atoi(char value_as_string[], int *value_as_int)
{
	int result = 0;
	int i = 0;
	bool is_negative_number = false;

	// NOTE(AO) We assume whitespace has been taken care of elsewhere. Also, we only attempt to parse ints.

	if (value_as_string[i] == '-')
	{
		is_negative_number = true;
		i += 1;
	}

	// feels kind of unecessary, but it seems more correct to me that this function would return false on empty strings
	if (value_as_string[i] == '\0')
		return false;

	while (value_as_string[i] != '\0')
	{
		char c = value_as_string[i];
		if ( c < '0' || c > '9')
			return false;

		result *= 10; // Shift the previous value up by ten

		result += c - '0';
		i += 1;
	}

	*value_as_int = is_negative_number ? -result : result;
	return true;
}

// 2.6 - Relational and Logical Operators
// ----------------------------------------------------------------------------------------------------------
// for (i=O; i<lim-1 && (c=getchar()) != '\n' && c != EOF; ++i) s[i] =c;
// EX 2-2 DONE: Write a loop equivalent to the loop above without using && or ||
void AO_New_For(void)
{
	int lim = 10;
	int i = 0;
	char c = 0;

	char s[10] = {};

	while (true)
	{
		if (i >= lim -1) 
			break;

		c = getchar();

		if (c == '\n')
			break;
		
		if (c == EOF)
			break;
		
		s[i] = c;

		++i;
	}

	printf("You wrote: %s", s);
}

// 2.3 - Constants
// ----------------------------------------------------------------------------------------------------------
int C_strlen(char s[])
{
	int size = 0;

	// NOTE(AO) The first time you wrote this you compared the char to "0" not "\0". This means this code
	//			wouldn't stop running until it encountered the integer representation of "0" (which is 48)
	//			somewhere in the memory of our program. This actually did not take too long, like 900 chars
	//			or so, but it's funny that it happened as it's a classic beginner mistake to make on my part.
	while (s[size] != '\0')
	{
		size += 1;
	}

	return size;
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
