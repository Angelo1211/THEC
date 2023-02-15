#include "Chapter5.h"


// 5.2 - Pointers and Function Arguments
// ----------------------------------------------------------------------------------------------------------
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