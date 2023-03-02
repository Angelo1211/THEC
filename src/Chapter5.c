#include "Chapter5.h"


// 5.2 - Pointers and Function Arguments
// ----------------------------------------------------------------------------------------------------------
// EX 5-2 DONE Write getfloat, the floating-point analog of geting. What type does getfloat return as its function value?
//	- Well, I'm going for the same strat the book does, return an int with the status
int 
AO_getfloat(float *pn)
{
	int c = 0;
	int sign = 0;

	// Skip whitespace
	while (isspace(c = getch()))
		;

	// If you're not a digit and also not done
	if (!isdigit(c) && c != EOF)
	{
		if ( c != '+' && c != '-' && c != '.' )
		{
			ungetch(c);
			return 0;
		}
	}

	sign = (c == '-') ? -1 : 1;

	if (c == '+' || c == '-' || c == '.')
	{
		int p = c;
		c = getch();

		// +-. followed by a non-digit is not a valid representation of zero
		if ( !isdigit(c) )
		{
			ungetch(c);
			ungetch(p);
			return 0;
		}
	}

	// This will keep going until it encounters a dot
	for (*pn = 0.0f; isdigit(c); c = getch())
		*pn = (10.0f * (*pn)) + (c - '0');

	// Check if we stopped because of a dot, in which case we gotta collect the fractional part
	if (c == '.')
	{
		c = getch();

		// NOTE(AO) There are surely better ways to do this
		float fract = 0.0f;
		float pow = 1.0f;
		while ( isdigit(c) )
		{
			pow /= 10.0f;
			fract += pow * (c - '0');
			c = getch();
		}
		*pn += fract;
	}

	*pn *= sign;

	if (c != EOF)
		ungetch(c);

	return c;
}

// EX 5-1 DONE As written getint treats a + or a - not followed by a digit as a valid representation of
//        zero. Fix it to push those chars back on the input.
int
AO_getint(int *pn)
{
	int c = 0;
	int sign = 0;

	// Skip whitespace
	while (isspace(c = getch()))
		;

	// If you're not a digit and also not done
	if (!isdigit(c) && c != EOF)
	{
		if ( c != '+' && c != '-' )
		{
			ungetch(c);
			return 0;
		}
	}

	sign = (c == '-') ? -1 : 1;

	if (c == '+' || c == '-')
	{
		int p = c;
		c = getch();

		// +- followed by a non-digit is not a valid representation of zero
		if ( !isdigit(c) )
		{
			ungetch(c);
			ungetch(p);
			return 0;
		}
	}

	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');

	*pn *= sign;

	if (c != EOF)
		ungetch(c);

	return c;
}

int
C_getint(int *pn)
{
	int c, sign;

	while (isspace(c = getch())) /*Skip whitespace*/
		;

	if (!isdigit(c) && c != EOF && c != '+' && c != '-')
	{
		ungetch(c); // Not a number
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-')
		c = getch();
	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	*pn *= sign;
	if (c != EOF)
		ungetch(c);
	return c;
}
