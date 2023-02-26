#include "Chapter5.h"


// 5.2 - Pointers and Function Arguments
// ----------------------------------------------------------------------------------------------------------
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
