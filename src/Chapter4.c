#include "Chapter4.h"

// 4.3 - External Variables
// ----------------------------------------------------------------------------------------------------------
// EX 4-3 DONE Given the basic framework, it's straightforward to extend the calculator. Add the modulus operator
// and provisions for negative numbers.
// EX 4-4 DONE Add commands to print the top element of the stack without popping, to duplicate it and to swap the 
// top two elements. Add a commmand to clear the stack.
// EX 4-5 DONE Add access to library functions like sin, exp, and pow. See <math.h> in Appendix B, Section 4.
// Check: https://clc-wiki.net/wiki/K%26R2_solutions:Chapter_4:Exercise_5
#define MAXOP 100
enum Calculator_Commands
{
	CC_NUMBER,
	CC_IDENTIFIER,
};

void C_calculator(void)
{
	int type;
	char s[MAXOP];
	bool showing_top = false;

	while ( (type = C_getop(s))  != EOF)
	{
		switch (type)
		{
			case CC_NUMBER:
			{
				push(atof(s));
			}break;

			case CC_IDENTIFIER:
			{
				dealWithName(s);
			}break;

			case '+':
			{
				push(pop() + pop());
			}break;

			case '*':
			{
				push(pop() * pop());
			}break;

			case '%':
			{
				int op2 = abs((int)pop());
				int op1 = abs((int)pop());

				push(op1 % op2);
			}break;

			case '-':
			{
				double op2 = pop();
				push(pop() - op2);
			}break;

			case '/':
			{
				double op2 = pop();
				if (op2 != 0.0)
					push(pop() - op2);
				else 
					printf("error: dividing by zero.\n");
			}break;

			// 4-4 Show the top of the stack without popping
			case '?':
			{
				showing_top = true;
				printf("\t%.8g\n", peek());
			}break;

			// 4-4 Duplicating the top of the stack
			case '~':
			{
				dupe();
			}break;

			// 4-4 Swapping top stack elements
			case '$':
			{
				swap();
			}break;

			// 4-4 Clear the stack
			case '`':
			{
				clear();
			}break;

			case '\n':
			{
				if (!showing_top)
					printf("\t%.8g\n", pop());
				showing_top = false;
			}break;

			default:
			{
				printf("error: unknown command %s\n", s);
			}break;
		}
	}
}

#define MAXVAL 100
int sp = 0;
double _val[MAXVAL];

void dealWithName(char s[])
{

	if (STRCMP(s, "sin"))
	{
		push(sin(pop()));
	}
	else if (STRCMP(s, "cos"))
	{
		push(cos(pop()));
	}
	else if (STRCMP(s, "exp"))
	{
		push(exp(pop()));
	}
	else if (STRCMP(s, "pow"))
	{
		f64 op2 = 0.0;
		push(pow(pop(), op2));
	}
	else
	{
		// Unrecognized keyword
		printf("Unrecognized keyword!.\n");
		clear();
	}
}

void push(double f)
{
	if (sp < MAXVAL)
		_val[sp++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
}

double pop(void)
{
	if (sp > 0)
		return _val[--sp];
	else
		printf("error: stack empty\n");
		return 0.0;
}

double peek(void)
{
	if (sp > 0)
		return _val[sp - 1];
	else
		printf("error: stack empty\n");
		return 0.0;
}

void dupe(void)
{
	if ( sp <= 0 )
	{
		printf("error: stack empty\n");
		return;
	}

	double val = pop();
	push(val);
	push(val);
}

void swap(void)
{
	if ( sp <= 1 )
	{
		printf("error: stack doesn't have enough things in it\n");
		return;
	}

	double a = pop();
	double b = pop();
	push(a);
	push(b);
}

void clear(void)
{
	sp = 0;
}

// This is by far the ugliest function I've seen in this book.
// So needlessly obfuscated and compact
// 2023-01-02 This BS is flagging all kinds of warnings due to type 
// 			  conversion issues
// 2023-02-06 Those are fixed easily nowadays, but it required some creative
//			  use of right associativity and casting.
int C_getop(char s[])
{
	int r = 0;
	int i = 0;
	int c = 0;

	// Skip whitespace, until the first non space or tab char.
	// Copy that char into s and add a null terminator
	while ((s[0] = (char)(c = getch())) == ' ' || c == '\t')
		;
	s[1] = '\0'; 

	// Check if we've found an identifier
	if ( isalpha(c) )
	{
		while ( isalpha(s[++i] = (char)(c = getch())))
			;
		r = CC_IDENTIFIER;
	}
	else
	{
		// Not a number, probably an operator?
		if (!isdigit(c) && c != '.')
			return c;
		
		// collect integer part
		if (isdigit(c))
			while (isdigit(s[++i] = (char)(c = getch())))
				;
		
		// Collect fractional part
		if (c == '.')
			while (isdigit(s[++i] = (char)(c = getch())))
				;
		r = CC_NUMBER;
	}

	s[i] = '\0';
	if (c != EOF)
		ungetch(c);
	
	return r;
}

#define BUFSIZE 100
int buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

// 4.2 - Functions Returning Non-Integers
// ----------------------------------------------------------------------------------------------------------
// EX 4-2 TODO Extend atof to handle scientific notation of the form 123.45e-6
double AO_atof(char s[])
{
	int i = 0;

	// Skip whitespace
	while (isspace(s[i]))
		i++;

	// Check sign, and eat the sign char
	int sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')
		i++;

	// Parse the non-fractional part
	double val = 0.0;
	while (isdigit(s[i]))
	{
		val = 10.0 * val + (s[i] - '0');
		i++;
	}

	// Is this a fractional number?
	if (s[i] == '.')
		i++;
	
	double power = 1.0;
	while (isdigit(s[i]))
	{
		val = 10.0 * val + (s[i] - '0');
		power *= 10.0;
		i++;
	}

	if (s[i] == 'e' ||  s[i] == 'E')
	{
		i++;
		int sign2 = (s[i] == '-') ? -1 : 1;
		if (s[i] == '+' || s[i] == '-')
			i++;

		double exp = 0.0;
		while (isdigit(s[i]))
		{
			exp = 10.0 * exp + (s[i] - '0');
			i++;
		}

		// We've got the exponent, now we gotta make it affect the power

		while(exp--)
			power *= (sign2 > 0) ? 0.1 : 10.0;
	}

	return sign * val / power;
}

double C_atof(char s[])
{
	double val, power;
	int i, sign;

	// Skip white-space
	for (i = 0; isspace(s[i]); i++)
		;
	
	sign = (s[i] == '-') ? -1 : 1;

	if (s[i] == '+' || s[i] == '-')
		i++;

	for (val = 0.0; isdigit(s[i]); i++)
		val = 10.0 * val + (s[i] - '0');
	
	if (s[i] == '.')
		i++;
	
	for (power = 1.0; isdigit(s[i]); i++)
	{
		val = 10.0 * val + (s[i] - '0');
		power *= 10.0;
	}

	return sign * val / power;
}

// 4.1 - Basics of Functions
// ----------------------------------------------------------------------------------------------------------
#define MAXLINE_4 1000
// EX 4-1 DONE Write the function strrindex(s, t), which returns the position of the rightmost ocurrance of t in s
// or -1 if there is none
int AO_strrindex(char s[], char t[])
{
	int result = -1;
	int s_len = (int)strlen(s);
	int t_len = (int)strlen(t);

	if (t_len == 0 || s_len == 0 || (s_len < t_len))
		return result;
	
	for (int si = s_len - 1; si >= 0; --si)
	{
		bool found = true;

		int temp = 0;
		for (int ti = t_len - 1; ti >= 0; --ti, ++temp)
		{
			if ((si - temp < 0) || (s[si - temp] != t[ti]))
			{
				found = false;
				break;
			}
		}

		if (found)
		{
			result = si - t_len + 1;
			break;
		}
	}

	return result;
}

int C_minigrep(char pattern[])
{
	char line[MAXLINE_4];
	int found = 0;

	while (C_getline_4(line, MAXLINE_4) > 0)
	{
		if (C_strindex(line, pattern) >= 0)
		{
			printf("%s", line);
			found++;
		}
	}

	return found;
}

int C_strindex(char s[], char t[])
{
	int i, j, k;

	// Iterate the entire length of the source string
	for (i = 0; s[i] != '\0'; ++i)
	{
		// NOTE(AO) Should we not also check for s[j] != '0'?
		//			So I thought about it, no you don't,
		//			As soon as s[j] == 0 t[k] will be different

		// Iterate the string we're trying to match
		// Stop at any point if they don't match
		for ( j=i, k = 0; 
			  t[k] != '\0' && s[j]==t[k];
			  j++, k++)
			;// Do nothing

		// k > 0 checks if there was any match at all
		// t[k] == 0 checks if the match for the string in T
		// was a complete match as only if we iterated the entire
		// string would t[k] == 0
		if (k > 0 && t[k] == '\0')
			return i;
	}

	// Safe to return -1 in the case where no match ocurred 
	// because match indices can only be >= 0, never negative
	return -1;
}

int C_getline_4(char s[], int lim)
{
	int c = 0;
	int i = 0;

	// While you've not travelled a string as large as the limit
	// And your next char is not the EOF char (or a new line)
	// Keep grabbing the chars
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
		s[i++] = (char)c;
	
	// If you were a newline you should write it
	if (c == '\n')
		s[i++] = (char)c;
	
	// Also write the null terminating char at the end
	s[i] = '\0';

	return i;
}
