#include "Chapter3.h"

// 3.3 - Else-If
// ----------------------------------------------------------------------------------------------------------

// Ex 3-1 TODO Make a binary search with only a single test inside the loop. Measure perf.

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
