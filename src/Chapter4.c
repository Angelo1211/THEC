#include "Chapter4.h"

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

	if (s[i++] == 'e')
	{
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
	int s_len = strlen(s);
	int t_len = strlen(t);

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
	int c, i;
	i = 0;

	// While you've not travelled a string as large as the limit
	// And your next char is not the EOF char (or a new line)
	// Keep grabbing the chars
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
		s[i++] = c;
	
	// If you were a newline you should write it
	if (c == '\n')
		s[i++] =c;
	
	// Also write the null terminating char at the end
	s[i] = '\0';

	return i;
}