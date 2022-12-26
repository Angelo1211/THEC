#include "Chapter4.h"

#define MAXLINE_4 1000

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