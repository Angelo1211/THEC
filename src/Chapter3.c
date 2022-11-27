#include "Chapter3.h"

// 3.4 - Switch
// ----------------------------------------------------------------------------------------------------------
// Ex 3-2 DONE Write a function escape (s, t) that converts characters like newline and tab into visible escape sequences
// like \n and \t as it copies the string t to s. Use a switch. Write a function for the other direction as well,
// converting escape sequences into the real characters.
void AO_Test_escape()
{
	char source[] = "This is the test string with \n sneaky \t escape characters we want \n to make \t visible to the \nnake\nd eye.";

	// NOTE(AO) 2x the other one's size because they could all be escape sequences, which once revealed would take two characters
	//			Then +1 for the null terminating char.
	size_t destination_size = strlen(source) * 2 + 1;

	char *chars_revealed = malloc(destination_size);
	char *chars_hidden = malloc(destination_size);

	AO_escape_to_chars(chars_revealed, source);
	printf("The Old string was: %s\nThe string with escape chars revealed is: %s\n", source, chars_revealed);

	AO_chars_to_escape(chars_hidden, chars_revealed);

	printf("We %s in converting the string back to it's previous representation.\n\nGot %s\n", strcmp(chars_hidden, source) == 0 ? "succeeded" : "failed", chars_hidden);

	free(chars_revealed);
	free(chars_hidden);
}

void AO_chars_to_escape(char d[], char s[])
{
	int srci = 0;
	int dsti= 0;

	while (s[srci])
	{
		switch (s[srci])
		{
			// This is a \ but we gotta make sure if it's actually an escape sequence
			case '\\':
			{
				// Look ahead one char, check if it's any of our recognized escape sequences
				switch (s[srci+1])
				{
					case 'n':
					{
						d[dsti++] = '\n';
						srci += 2;
					}break;

					case 't':
					{
						d[dsti++] = '\t';
						srci += 2;
					}break;

					// Not an escape sequence we recognize, just insert the '\'
					default:
					{
						d[dsti++] = s[srci++];
					}break;
				}

			}break;

			default:
			{
				d[dsti++] = s[srci++];
			}break;
		}
	}

	// Null termination char
	d[dsti] = 0;
}

void AO_escape_to_chars(char d[], char s[])
{
	int srci = 0;
	int dsti= 0;

	while (s[srci])
	{
		switch (s[srci])
		{
			case '\n':
			{
				d[dsti++] = '\\';
				d[dsti++] = 'n';

			}break;

			case '\t':
			{
				d[dsti++] = '\\';
				d[dsti++] = 't';

			}break;

			default:
			{
				d[dsti++] = s[srci];
			}break;
		}
		srci += 1;
	}

	// Null termination char
	d[dsti] = 0;
}

// 3.3 - Else-If
// ----------------------------------------------------------------------------------------------------------
// Ex 3-1 DONE Make a binary search with only a single test inside the loop. Measure perf.

// 1*2^30 numbers in order 
#define ARRAY_SIZE ((1ull << 30))

typedef enum Search_t
{
	s_linear,
	s_binary_c,
	s_binary_ao,
	s_count,
}Search_t;

char *Search_Names[] = 
{
	"Linear",
	"Binary_C",
	"Binary_AO"
};

void AO_RunSearch(Search_t type, s64 number, s64 array[], s64 size)
{
	clock_t start = clock();

	s64 result = -1;
	switch (type)
	{
		case s_linear:
		{
			for (s64 i = 0; i < ARRAY_SIZE; ++i)
			{
				if (array[i] == number)
				{
					result = i;
					break;
				}
			}
		}break;

		case s_binary_c:
		{
			result = C_binsearch(number, array, size);
		}break;

		case s_binary_ao:
		{
			result = AO_binsearch(number, array, size);
		}break;

		default:
		{
			printf("Unrecognized search type!\n");
			return;
		}
	}

	f64 delta_t = (double)(clock() - start)/ CLOCKS_PER_SEC;
	printf("Finished running a %s search in %fms \n", Search_Names[type], delta_t * 1000.0f);
	printf("Search for %lld %s, and it was %s\n", number, (result != -1) ? "succeeded" : "failed", (result == number) ? "correct" : "incorrect" );
}

#define RUN_ALL_SEARCHES(number, array, size) 	\
AO_RunSearch(s_linear, number, array, size);	\
AO_RunSearch(s_binary_c, number, array, size);	\
AO_RunSearch(s_binary_ao, number, array, size);	\
putchar('\n');									\

void AO_Test_binsearch()
{

	// Alloc and fill the giant array
	s64 *array = malloc(ARRAY_SIZE * sizeof(s64));
	for (s64 i = 0; i < ARRAY_SIZE; ++i)
		array[i] = i;

	// Test a small number
	RUN_ALL_SEARCHES(123456, array, ARRAY_SIZE);

	// Test a larger number
	RUN_ALL_SEARCHES((1ull << 29), array, ARRAY_SIZE);

	// Test a number you don't have
	RUN_ALL_SEARCHES((1ull << 40), array, ARRAY_SIZE);

	free(array);
}

s64 AO_binsearch(s64 x, s64 v[], s64 n)
{
	s64 low = 0;
	s64 high = n -1;

	s64 mid = (low + high) / 2;
	s64 val = v[mid];
	while (((x > val) ? (low = mid + 1) : low) <= ((x < val) ? (high = mid -1) : high))
	{
		mid = (low + high) / 2;
		val = v[mid];
		if (x == val)
		{
			return mid;
		}
	}
	return -1;
}

s64 C_binsearch(s64 x, s64 v[], s64 n)
{
	s64 low, high, mid;

	low = 0;
	high = n -1;

	while (low <= high)
	{
		mid = (low + high) / 2;
		if (x  < v[mid])
		{
			high = mid - 1;
		}
		else if (x > v[mid])
		{
			low = mid + 1;
		}
		else 
			return mid;
	}
	return -1;
}
