#include "Chapter3.h"

// 3.6 - Loops - Do-While
// ----------------------------------------------------------------------------------------------------------
// Ex 3-4 DONE In a two's complement number representation, our version of itoa does not handle the largest 
// negative number, that is, the value of n equal to -(2^(wordsize - 1)). Explain why not. Modify it to print
// that value correctly, regardless of the machine it runs.
void AO_itoa(int n, char s[])
{
	int i = 0;
	bool negative = n < 0;
	u32 a = abs(n);

	do
	{
		s[i++] = a % 10 + '0';
	} while((a /= 10) > 0);

	if ( negative )
		s[i++] = '-';

	s[i] = '\0';
	C_reverse(s);
}

// NOTE(AO) This code failed to work because there is no equivalently sized positive number
//			To the largest negative oneWhen we try to make the maximum negative number positive. 
//			For example here's a table of two's complement values for a 4 bit number.
//			Binary | Decimal
//			-------|--------
//			0111   |   +7
//			0110   |   +6
//			0101   |   +5
//			0100   |   +4
//			0011   |   +3
//			0010   |   +2
//			0001   |   +1
//			0000   |   0
//			1111   |   -1
//			1110   |   -2
//			1101   |   -3
//			1100   |   -4
//			1011   |   -5
//			1010   |   -6
//			1001   |   -7
//			1000   |   -8
void C_itoa(int n, char s[])
{
	int i, sign;

	if ((sign = n) < 0) // Record the sign
		n = -n;			// Make n positive

	i = 0;

	do {						// Generate digits in reverse order
		s[i++] = n % 10 + '0'; 	// Get next digit
	} while((n /= 10) > 0); 	// Delete it 

	if (sign < 0)
		s[i++] = '-';

	s[i] = '\0';

	C_reverse(s);
}

// 3.5 - Loops - While and For
// ----------------------------------------------------------------------------------------------------------
// Ex 3-3 DONE Write a function expand(s1, s2) that expands shorthand notations like a-z in the string s1 into
// the equivalent complete list abc...xyz in s2. Allow for letters of either case and digits, and be prepared
// to handle cases like a-b-c and a-z0-9 and -a-z. Arrange that a leading or trailng - is taken literally.
void AO_Test_expand()
{
	char *strings_to_test[] = {
		"0-9",
		"-1-6-",
		"1-5-9",
		"1-9-1",
		"5-5",
		"a-z",
		"a-e",
		"d-z",
		"a-z-",
		"z-a-",
		"a-ee-a",
		"a-r-l",
		"A-Z",
		"a-W",
		"A-w",
		"a-8",
		"%-3",
		NULL,
	};

	char result[1000] = {0};

	int i = 0;
	while (strings_to_test[i])
	{
		AO_expand(strings_to_test[i], result);
		++i;
	}
}

void AO_expand(char src[], char dst[])
{
	printf("Original: %s\n", src);

	size_t readID = 0;
	size_t writeID = 0;

	// All expansions are of the form:
	//	(-)start-end(-)
	// And can be chained together:
	// start-end-end2
	// With end2 not necessarily being larger than end

	while(src[readID])
	{
		char first  = src[readID];
		char middle = src[readID + 1];
		char last   = src[readID + 2];

		// Trailing / leading dash
		if (first == '-')
		{
			// This tripped me up for a while, leading - are not treated as expansions but simply literals, you don't need to do anyting with them
			// Same deal with trailing -, we just write it
			if ((readID == 0) || (middle == '\0'))
			{
				dst[writeID++] = src[readID++];
				continue;
			}

			assert(0 && "We encountered a mid-string dash. Should not have happened!");
		}

		// Text that doesn't need expansion just gets copied! Alternatively:
		// If we don't have a dash we don't need to expand so just copy the text
		// If we do have a dash but the character after that is null it's a trailing dash
		if ( middle != '-' || last == 0) 
		{
			// In both of these cases we want to copy the current letter and move on
			dst[writeID++] = src[readID++];
			continue;
		}

		// Recap: We know theres something that kinda looks like an expansion of the form
		//	x - y here, but we're not sure what x and y are let's rule out bad cases
		// If it's not alphanumeric or not a matching range we don't have any way to expand this, so skip
		// We can only expand values of x and y that are of the same type (both alpha, or both numeric) not mixed
		if ( !isalnum(first) || !isalnum(last) || ((bool)isalpha(first) != (bool)isalpha(last)) || ((bool)isdigit(first) != (bool)isdigit(last)) )	
		{
			// Just copy it all without expanding!
			dst[writeID++] = src[readID++]; // first
			dst[writeID++] = src[readID++]; // middle
			dst[writeID++] = src[readID++]; // last
			continue;
		}

		// Slightly trickier case, we want to respect the case of the characters, but if the user mixed them we will force lower case
		if (isalpha(first) && isalpha(last))
		{
			if ( ( islower(first) != islower(last) ) ||  ( isupper(first) != isupper(last) ))
			{
				first = (char)tolower(first);
				last  = (char)tolower(last);
			}
		}

		// We should be cool with doing an expansion now! This works for first > last && first < last && first == last
		for (int k = first; k != last; k += (first < last) ? 1 : -1 )
		{
			dst[writeID++] = (char)k;
		}

		// Expansion complete! Move past this text
		// But don't move past the last char in the expansion
		// This is to allow concatenated expansions, of the form "1-3-5"
		// Which will now be treated as 1-23-5
		readID += 2; 
	}

	// We're done here, write a null terminator
	dst[writeID] = 0;

	printf("Expanded: %s\n\n", dst);
}

void C_reverse(char s[])
{
	int c, i, j;

	for (i = 0, j = (int)strlen(s) - 1; i < j; i++, j--)
	{
		c = s[i];
		s[i] = s[j];
		s[j] = (char)c;
	}
}

void AO_reverse_ip(char s[])
{
	int n = (int)strlen(s);
	for (int i = 0; i < n / 2; ++i)
	{
		int b = n - 1 - i;
		char c = s[i];
		s[i] = s[b];
		s[b] = c;
	}
}

void AO_Print_IntArray(int v[], int n, int highlight_a, int highlight_b)
{
	printf("[ ");
	for (int i = 0; i < n; ++i)
	{
		if (highlight_a == i)
		{
			printf("*%d*,", v[i]);
		}
		else if (highlight_b == i)
		{
			printf("$%d$,", v[i]);
		}
		else
			printf(" %d, ", v[i]);
	}
	printf("]\n");
}

void AO_Test_shellsort()
{
	int test[] = {18, 23, 3, 7, 5, 8, 9, 1, 3, 9, 118, 38, 2, 3};
	int n = sizeof(test) / sizeof(test[0]);

	// Before sorting
	AO_Print_IntArray(test, n, -1, -1);

	C_shellsort(test, n);

	// After sorting, duh
	AO_Print_IntArray(test, n, -1, -1);
}

void C_shellsort(int v[], int n)
{
	int gap, i, j, temp;

	printf("Iter | gap | i | j | v[j] | v[j+gap]\n");
	int iter = 0;
	for (gap = n / 2; gap > 0; gap /= 2)
	{
		for (i = gap; i < n; i++)
		{
			for (j = i - gap; j >= 0 && v[j] > v[j + gap]; j -= gap)
			{
				printf("%5d|%5d|%3d|%3d|%6d| %d\n", iter, gap, i, j, v[j], v[j + gap]);
				AO_Print_IntArray(v, n, j, j + gap);
				printf("\n");

				temp = v[j];
				v[j] = v[j + gap];
				v[j + gap] = temp;
				iter++;
			}
		}
	}
}

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
	int dsti = 0;

	while (s[srci])
	{
		switch (s[srci])
		{
		// This is a \ but we gotta make sure if it's actually an escape sequence
		case '\\':
		{
			// Look ahead one char, check if it's any of our recognized escape sequences
			switch (s[srci + 1])
			{
			case 'n':
			{
				d[dsti++] = '\n';
				srci += 2;
			}
			break;

			case 't':
			{
				d[dsti++] = '\t';
				srci += 2;
			}
			break;

			// Not an escape sequence we recognize, just insert the '\'
			default:
			{
				d[dsti++] = s[srci++];
			}
			break;
			}
		}
		break;

		default:
		{
			d[dsti++] = s[srci++];
		}
		break;
		}
	}

	// Null termination char
	d[dsti] = 0;
}

void AO_escape_to_chars(char d[], char s[])
{
	int srci = 0;
	int dsti = 0;

	while (s[srci])
	{
		switch (s[srci])
		{
		case '\n':
		{
			d[dsti++] = '\\';
			d[dsti++] = 'n';
		}
		break;

		case '\t':
		{
			d[dsti++] = '\\';
			d[dsti++] = 't';
		}
		break;

		default:
		{
			d[dsti++] = s[srci];
		}
		break;
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
} Search_t;

char *Search_Names[] =
	{
		"Linear",
		"Binary_C",
		"Binary_AO"};

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
	}
	break;

	case s_binary_c:
	{
		result = C_binsearch(number, array, size);
	}
	break;

	case s_binary_ao:
	{
		result = AO_binsearch(number, array, size);
	}
	break;

	default:
	{
		printf("Unrecognized search type!\n");
		return;
	}
	}

	f64 delta_t = (double)(clock() - start) / CLOCKS_PER_SEC;
	printf("Finished running a %s search in %fms \n", Search_Names[type], delta_t * 1000.0f);
	printf("Search for %lld %s, and it was %s\n", number, (result != -1) ? "succeeded" : "failed", (result == number) ? "correct" : "incorrect");
}

#define RUN_ALL_SEARCHES(number, array, size)       \
	AO_RunSearch(s_linear, number, array, size);    \
	AO_RunSearch(s_binary_c, number, array, size);  \
	AO_RunSearch(s_binary_ao, number, array, size); \
	putchar('\n');

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
	s64 high = n - 1;

	s64 mid = (low + high) / 2;
	s64 val = v[mid];
	while (((x > val) ? (low = mid + 1) : low) <= ((x < val) ? (high = mid - 1) : high))
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
	high = n - 1;

	while (low <= high)
	{
		mid = (low + high) / 2;
		if (x < v[mid])
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
