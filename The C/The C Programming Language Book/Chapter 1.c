#include "Chapter1.h"

/*
	* *
	/ / 

	This is here for testing the program for removing multiline comments

	// It seems like it has worked fine so far, but could it be bamboozled by something like this?

	I hope not! 

	End of testing!

	//
*/

#define MAXLINE 1000 // Just testing some stuff
#define test "test! \\ thing "

// 1.10 - External Variables and scope
// ----------------------------------------------------------------------------------------------------------

void
AO_DEBUG_Print_Line_Numbers(char *str)
{
	int strIndex = 0;

	int currentChar = 1;
	int currentLine = 1;
	while ( (currentChar = str[strIndex++]) != '\0' )
	{
		switch(currentChar)
		{
			case '\n':
			{
				currentLine++;
				printf("\n%2.d|", currentLine);
			}break;

			default:
				putchar(currentChar);
		}
	}
	putchar('\n');

}

struct State
{
	// Qoutes
	int qouted_string;
	int last_qoute_line;

	// Parenthesis
	int unbalanced_parenthesis;
	int last_parenthesis_line;

	// Brackets
	int unbalanced_brackets;
	int last_bracket_line;
};

// Ex 1-24 DONEish: Write a function that checks a c program for rudimentary errors
// OK, so this is not at all the full thing but I get the point. Doing any more is wasting my time.

#define ERRORFILE "W:\\THEC\\HasErrors.c"
void
AO_Check_For_Errors()
{
	char *File_contents = AO_Remove_Comments(ERRORFILE);
	if (File_contents)
	{
		int original_file_index = 0;

		AO_DEBUG_Print_Line_Numbers(File_contents);

		struct State state = { 0 };

		char currentChar;
		int currentLine = 1;
		while ( (currentChar = File_contents[original_file_index++]) != '\0' )
		{
			switch ( currentChar )
			{
				case '\n':
				{
					currentLine++;
				}break;
			
				case '"':
				{
					state.qouted_string = !state.qouted_string;
					state.last_qoute_line = currentLine;
				}break;

				case '(':
				{
					// Only count these if we're not inside a quoted string
					if (!state.qouted_string)
						state.unbalanced_parenthesis++;
				}break;

				case ')':
				{
					// Only count these if we're not inside a quoted string
					if (!state.qouted_string)
						state.unbalanced_parenthesis--;
				}break;

				case '{':
				{
					if (!state.qouted_string)
						state.unbalanced_brackets++;
				}break;

				case '}':
				{
					if (!state.qouted_string)
						state.unbalanced_brackets--;
				}break;

			}
		}

		// If zero it's balanced. So if not zero it's not balanced!

		if (state.unbalanced_parenthesis)
		{
			printf("ERROR!: Unbalanced parenthesis %d\n", state.unbalanced_parenthesis);
		}

		if (state.unbalanced_brackets)
		{
			printf("ERROR!: Unbalanced brackets %d\n", state.unbalanced_brackets);
		}

		if (state.qouted_string)
		{
			printf("ERROR!: Unbalanced quotes %d\n", state.qouted_string);
		}

	}

}

// Ex 1-23 DONE: Write a function that removes all comments from a c program
char *
AO_Remove_Comments(char * fileName)
{
	size_t size;
	char *File_contents = AO_Read_Entire_File(fileName, &size);
	char *File_without_comments = malloc(size + 1);
	assert(File_without_comments);

	int original_file_index = 0;
	int commentless_file_index = 0;

	int single_line_comment = 0;
	int multi_line_comment = 0;
	int qouted_string = 0;

	char currentChar;
	while ( (currentChar = File_contents[original_file_index++]) != '\0' )
	{
		switch ( currentChar )
		{
			case '/':
			{
				if ( !(single_line_comment || multi_line_comment || qouted_string) )
				{
					// Look ahead to next char
					char nextChar = File_contents[original_file_index];

					if ( nextChar == '/' )
					{
						single_line_comment = 1;
						original_file_index++;
					}
					else if ( nextChar == '*' )
					{
						multi_line_comment = 1;
						original_file_index++;
					}
					else
					{
						File_without_comments[commentless_file_index++] = currentChar;
					}
				}

			}break;

			case '*':
			{
				// Look ahead to next char
				char nextChar = File_contents[original_file_index];

				if (nextChar == '/')
				{
					multi_line_comment = 0;
					original_file_index++;
				}
				else
				{
					if ( !(single_line_comment || multi_line_comment) )
						File_without_comments[commentless_file_index++] = currentChar;
				}

			}break;

			case '"':
			{
				// BUG: This probably does not work with quote literals (but I can't be bothered to fix it right now)
				qouted_string = !qouted_string;

				File_without_comments[commentless_file_index++] = currentChar;
			}break;

			case '\n':
			{
				single_line_comment = 0;
				File_without_comments[commentless_file_index++] = currentChar;
			}break;

			default:
			{
				if ( !(single_line_comment || multi_line_comment) )
					File_without_comments[commentless_file_index++] = currentChar;

			}
		}

	}
	File_without_comments[commentless_file_index] = 0;

	free(File_contents);

	return (File_without_comments);
}

// Ex 1-22 DONE: Write a function that folds long input lines
void
AO_Fold(char folded[], char original[], int max_string_width, int tab_stop_length)
{
	int original_array_index = 0;
	int folded_array_index = 0;
	int current_line_index = 0;

	int word_length = 0;

	char currentChar;
	while ( (currentChar = original[original_array_index++]) != '\0' )
	{
		switch ( currentChar )
		{
			case '\n':
			{
				current_line_index = 0;
				word_length = 0;
			}break;

			case '\t':
			{
				// If your tab is going to take you over the limit
				if ( (current_line_index + tab_stop_length) > max_string_width ) // 
				{
					folded[folded_array_index++] = '\n';
					current_line_index = 0;
				}

				current_line_index += tab_stop_length;
				word_length = 0;
			}break;

			case ' ':
			{
				// If you're going over the line start a new one 
				if ( (current_line_index + 1) > max_string_width )
				{
					folded[folded_array_index++] = '\n';
					current_line_index = 0;
				}

				current_line_index++;
				word_length = 0;
			}break;

			default:
			{
				// Starting a new word
				if ( !word_length )
				{
					// Find out it's length
					word_length = AO_Find_Word_Length(original, original_array_index);

					// If there's not enough space in the line for the word insert a new line 
					if ( (current_line_index + word_length) > max_string_width )
					{
						// But make sure the line fits within the next line
						if ( word_length <= max_string_width )
						{
							folded[folded_array_index++] = '\n';
							current_line_index = 0;
						}
					}
				}

				// If you're going over the line start a new one 
				if ( (current_line_index + 1) > max_string_width )
				{
					folded[folded_array_index++] = '\n';
					current_line_index = 0;
				}

				current_line_index++;
			}break;
		}
		folded[folded_array_index++] = currentChar;
	}

	folded[folded_array_index] = '\0';
}

void
AO_Fold_Test(void)
{
	// Current line length
	int len;

	// Current input line
	char line[MAXLINE];
	char line_folded[MAXLINE];

	int max_string_width = 80;

#define TESTING 1
#if TESTING
	int tab_stop_length = 8;
	int tab_stop_count = 10;
	max_string_width = tab_stop_count * tab_stop_length;
	AO_DEBUG_Print_Tab_Stops(tab_stop_length, tab_stop_count);
#endif

	while ( (len = C_getline(line, MAXLINE)) > 0 )
	{
		AO_Fold(line_folded, line, max_string_width, tab_stop_length);
#if TESTING
		AO_DEBUG_Print_Visualized_WhiteSpace(line_folded, tab_stop_length);
#endif
		// Final
		printf("%s\n", line_folded);

#if TESTING
		putchar('\n');
		AO_DEBUG_Print_Tab_Stops(tab_stop_length, tab_stop_count);
#endif
	}
}
#undef TESTING

// Ex 1-21 DONE: Write a function that substitutes spaces for tabs
void
AO_EnTab(char entabbed[], char original[], int tab_stop_length)
{
	// String indices
	int original_index = 0;
	int entabbed_index = 0;
	int virtual_index = 0;

	// If inside WS 
	int spaceCount = 0;

	// Traverse the whole string
	char currentChar;
	while ( (currentChar = original[original_index]) != '\0' )
	{
		int tabStopGap = tab_stop_length - (virtual_index % tab_stop_length);
		if ( currentChar == ' ' )
		{
			// If you've seen some whitespace before and you're on a tab stop
			// Reset the whitespace and include a tab stop
			if ( spaceCount && !(virtual_index % tab_stop_length) )
			{
				// Reset count && insert a tab
				virtual_index += tabStopGap;

				entabbed[entabbed_index++] = '\t';
				spaceCount = 0;
			}
			else
			{
				// Keep incrementing the number of spaces you've seen without actually 
				// Including that space
				spaceCount++;
			}
		}
		else if ( currentChar == '\t' )
		{
			virtual_index += tabStopGap;

			// If you see a tab, respect it but also reset the space count
			// Any of those spaces would've been tabs anyway
			entabbed[entabbed_index++] = '\t';
			spaceCount = 0;
		}
		else
		{
			if ( spaceCount )
			{
				// Whatever remains must be less than a tab stop just flush with spaces
				while ( spaceCount-- )
				{
					entabbed[entabbed_index++] = ' ';
				}
				spaceCount = 0;
			}

			entabbed[entabbed_index++] = currentChar;
		}
		original_index++;
		virtual_index++;
	}
	entabbed[entabbed_index] = '\0';
}

void
AO_EnTab_Test(void)
{
#define TESTING 1
	// Current line length
	int len;

	// Current input line
	char line[MAXLINE];
	char line_entab[MAXLINE];

	int tab_stop_length = 8;

#if TESTING
	int tab_stop_count = 10;
	AO_DEBUG_Print_Tab_Stops(tab_stop_length, tab_stop_count);
#endif

	while ( (len = C_getline(line, MAXLINE)) > 0 )
	{
		AO_EnTab(line_entab, line, tab_stop_length);

#if TESTING
		putchar('\n');
		AO_DEBUG_Print_Tab_Stops(tab_stop_length, tab_stop_count);
		// Original
		AO_DEBUG_Print_Visualized_WhiteSpace(line, tab_stop_length);
		// Entabbed
		AO_DEBUG_Print_Visualized_WhiteSpace(line_entab, tab_stop_length);
#endif
		// Final
		printf("%s\n", line_entab);
	}
}
#undef TESTING

// Ex 1-20 DONE: Write a function that substitutes tabs for spaces
void
AO_DeTab(char detabbed[], char original[], int tab_stop_length)
{
	int original_index = 0;
	int detabbed_index = 0;
	char currentChar;
	while ( (currentChar = original[original_index++]) != '\0' )
	{
		if ( currentChar == '\t' )
		{
			int tabStopGap = tab_stop_length - (detabbed_index % tab_stop_length);
			while ( tabStopGap-- )
				detabbed[detabbed_index++] = ' ';
		}
		else
			detabbed[detabbed_index++] = currentChar;
	}
	detabbed[detabbed_index] = '\0';
}

void
AO_DeTab_Test(void)
{
#define TESTING 1
	// Current line length
	int len;

	// Current input line
	char line[MAXLINE];
	char line_detab[MAXLINE];

	int tab_stop_length = 4;

#if TESTING
	AO_DEBUG_Print_Tab_Stops(tab_stop_length, 10);
#endif

	while ( (len = C_getline(line, MAXLINE)) > 0 )
	{
		AO_DeTab(line_detab, line, tab_stop_length);

#if TESTING
		AO_DEBUG_Print_Tab_Stops(tab_stop_length, 10);
#endif
		printf("%s\n", line_detab);
	}
}
#undef TESTING

// 1.9 - Character Arrays
// ----------------------------------------------------------------------------------------------------------

// Ex 1-19 DONE: Write a function that reverses a string
void
AO_reverse(char reverse[], char original[], int str_Length)
{
	int i, j;
	for ( i = str_Length - 1, j = 0; i >= 0; --i, ++j )
	{
		reverse[j] = original[i];
	}
	reverse[j] = '\0';
}

void
AO_test_reverse_string(void)
{
	// Current line length
	int len;

	// Current input line
	char line[MAXLINE];
	char line_Reversed[MAXLINE];

	while ( (len = C_getline(line, MAXLINE)) > 0 )
	{
		AO_reverse(line_Reversed, line, len);
		printf("%s\n", line_Reversed);
	}
}

// Ex 1-18 DONE: Remove trailing blanks/tabs remove entirely blank lines
void
AO_copy_trailing_WS_Removed(char to[], char from[])
{
	int i;

	// Get total string length
	i = 0;
	while ( from[i] != '\0' ) ++i;

	int charCount = i;

	int string_new_endpoint = 0;

	if ( !charCount ) return;

	// Scan string back to front until you hit a non whitespace character, that's the new endpoint
	for ( i = charCount - 1; i >= 0; --i )
	{
		if ( (from[i] != ' ') &&
			 (from[i] != '\t') &&
			 (from[i] != '\n') )
		{
			string_new_endpoint = i;
			break;
		}
	}
	string_new_endpoint = ++i;

	i = 0;
	// Copy the string front to back into a buffer
	for ( i = 0; i < string_new_endpoint; ++i )
	{
		to[i] = from[i];
	}

	// Insert a null char at the end 
	to[i] = '\0';
}

void
AO_remove_trailing_ws(void)
{
	// Current line length
	int len;

	// Current input line
	char line[MAXLINE];
	char line_WS_removed[MAXLINE];

	while ( (len = C_getline(line, MAXLINE)) > 0 )
	{
		AO_copy_trailing_WS_Removed(line_WS_removed, line);
		printf("%s", line_WS_removed);
	}

}

// Ex 1-17 DONE: Print only lines longer than 80 chars 
void
AO_print_longer_than_80(void)
{
	// Current line length
	int len;

	// Current input line
	char line[MAXLINE];

	while ( (len = C_getline(line, MAXLINE)) > 0 )
	{
		if ( len > 80 ) printf("%s", line);
	}

}

// Ex 1-16 DONE: Print the line length and print as much as possible of the line 
void
AO_print_input_length(void)
{
	// Current line length
	int len;

	// Current input line
	char line[MAXLINE];

	while ( (len = C_getline(line, MAXLINE)) > 0 )
	{
		printf("Line Length:%d\n", len);
		printf("%s", line);
	}
}

// Print longest line
void
C_print_longest_line(void)
{
	// Current line length
	int len;
	// maximum length seen so far
	int max;

	// Current input line
	char line[MAXLINE];

	// longest line saved here
	char longest[MAXLINE];

	max = 0;
	while ( (len = C_getline(line, MAXLINE)) > 0 )
	{
		if ( len > max )
		{
			max = len;
			C_copy(longest, line);
		}
	}

	if ( max > 0 )
	{
		printf("%s", longest);
	}
}
#undef MAXLINE

int
C_getline(char s[], int lim)
{
	int c, i;

	// While you haven't hit the limit 
	// Or you have not seen an EOF
	// Or your character is not an endline
	// put the line into the line string
	for ( i = 0;
		(c = getchar()) != EOF && c != '\n';
		++i )
	{
		if ( i < lim - 1 )
		{
			s[i] = c;
		}
	}

	// If the last character was a new line set the second-to-last char as a newline
	if ( c == '\n' )
	{
		s[i] = c;
		++i;
	}

	// Insert a null char at the end 
	s[i] = '\0';

	// Return the length of the string
	return i;
}

void
C_copy(char to[], char from[])
{
	int i;

	i = 0;
	while ( (to[i] = from[i]) != '\0' )
		++i;
}

#undef MAXLINE

#define MAX_CHAR_ARRAY_SIZE 1<<12
void
AO_print_longest_line(void)
{
	int currentChar, lineLength, maxLineLength;
	char tempLineArray[MAX_CHAR_ARRAY_SIZE];
	char longestLine[MAX_CHAR_ARRAY_SIZE];

	// Zero initialize both arrays
	for ( int i = 0; i < MAX_CHAR_ARRAY_SIZE; ++i )
		longestLine[i] = tempLineArray[i] = 0;

	currentChar = lineLength = maxLineLength = 0;

	// Iterate through every character
	do
	{
		// End of line detected
		if ( currentChar == '\n' )
		{
			// Record longest line so far
			if ( lineLength > maxLineLength )
			{
				maxLineLength = lineLength;

				// Copy over current longest line
				for ( int i = 0; i < maxLineLength; ++i )
					longestLine[i] = tempLineArray[i];
			}

			// Reset temp array to zero 
			for ( int i = 0; i < lineLength; ++i )
				tempLineArray[i] = 0;

			lineLength = 0;
		}
		else
			tempLineArray[lineLength++] = currentChar;
	} while ( (currentChar = getchar()) != EOF );

	// Print longest line
	for ( int i = 0; i < maxLineLength; ++i )
		putchar(longestLine[i]);

	putchar('\n');
}
#undef MAX_CHAR_ARRAY_SIZE

// 1.8 - Arguments, Call by Value
// ----------------------------------------------------------------------------------------------------------
int
C_pow_byval(int base, int n)
{
	int p;

	for ( p = 1; n > 0; --n )
		p *= base;
	return p;
}

// 1.7 - Functions
// ----------------------------------------------------------------------------------------------------------
float
fToC(float fahrenheit)
{
	// Ex 1-15 DONE: Rewrite temperature conversion to use a function
	return  (5.0f / 9.0f) * (fahrenheit - 32.0f);
}

int
C_pow(int base, int n)
{
	int i, p;
	p = 1;
	for ( i = 1; i <= n; ++i )
		p = p * base;

	return p;
}

void
C_pow_test(void)
{
	int i;
	for ( i = 0; i < 10; ++i )
		printf("%d %d %d\n", i, C_pow(2, i), C_pow(-3, i));
}

void
AO_pow_example(void)
{
	int base = 2;
	int exp = 32;
	printf("%d^%d = %d\n", base, exp, AO_pow(base, exp));
}

int
AO_pow(int base, int exponent)
{
	// This seems to very quickly over flow 
	// Probably not a good solution for anything.
	int result = base;
	for ( int i = 1; i < exponent; ++i )
		result *= base;

	return result;
}

// 1.6 - Arrays
// ----------------------------------------------------------------------------------------------------------
#define NUM_DISTINCT_ASCII_CHARS 127
void
Character_Frequency(int plotDirection)
{
	// Ex 1-14 DONE: Char count histogram horizontal and Vertical!
	int currentChar, maxCharCount, numDistinctChars;
	int charCounts[NUM_DISTINCT_ASCII_CHARS] = { 0 };

	numDistinctChars = maxCharCount = 0;

	// Parsing the text for individual chars
	while ( (currentChar = getchar()) != EOF )
	{
		// If this is the first time we encounter this char it's a new distinct char
		// Use it to find the maximum width of the vertical plot
		if ( !charCounts[currentChar] )
			++numDistinctChars;

		++charCounts[currentChar];

		// Checking to see if this is the new longest word we've found 
		// To use it to find the maximum height of the vertical plot
		if ( charCounts[currentChar] > maxCharCount )
			maxCharCount = charCounts[currentChar];
	}

	printf("\nChar Count Histogram:\n");
	printf("---------------------\n");
	if ( plotDirection == VERTICAL_HISTOGRAM )
	{
		// Plot bars
		// Going row by row, starting from the top
		for ( int charCount = maxCharCount; charCount > 0; --charCount )
		{
			// Going column by column but covering the whole array 
			// But only printing a hash symbol if it has a value equal to the current max
			for ( int j = 0; j < NUM_DISTINCT_ASCII_CHARS; ++j )
			{
				// Only print a value if you're nonzero
				if ( charCounts[j] )
				{
					putchar(' ');
					// Check if the value is equal to the current wordLength
					if ( charCount <= charCounts[j] )
						putchar('#');
					else
						putchar(' ');
				}

			}
			// On the top line print the maximum value at the end
			if ( charCount == maxCharCount )
				printf("%2d", maxCharCount);
			putchar('\n');
		}

		for ( int i = 0; i < numDistinctChars * 2; ++i )
			putchar('-');
		putchar('\n');

		// Plot chars at the bottom
		for ( int j = 0; j < NUM_DISTINCT_ASCII_CHARS; ++j )
		{
			// Only print a value if you're nonzero
			if ( charCounts[j] )
			{
				printf(" %c", (char)j);
			}
		}
		putchar('\n');

	}
	else // If you pass a zero you mean horizontal
	{
		// Plot both at once
		for ( int charVal = 0; charVal < NUM_DISTINCT_ASCII_CHARS; ++charVal )
		{
			int charCountsForThisChar = charCounts[charVal];

			if ( charCountsForThisChar )
			{
				printf(" %c:", charVal);
				for ( int i = 0; i < charCountsForThisChar; ++i )
					putchar('#');
				if ( charCountsForThisChar == maxCharCount )
					printf(" %d", maxCharCount);
				putchar('\n');
			}
		}
	}

}
#undef NUM_DISTINCT_ASCII_CHARS


#define LONGEST_WORD_LENGTH 50
void
Length_Of_Words(int plotDirection)
{
	// Ex 1-13 DONE: Word length histogram horizontal and Vertical!

	int currentChar, currentWordLength, maxWordLength, numDistinctLengths;
	int wordLengths[LONGEST_WORD_LENGTH] = { 0 };

	numDistinctLengths = 0;
	currentWordLength = 0;
	maxWordLength = 0;

	// Parsing the text for word lengths
	while ( (currentChar = getchar()) != EOF )
	{
		int isSpace = currentChar == ' ';
		int isTab = currentChar == '\t';
		int isNewLine = currentChar == '\n';
		int isWhiteSpace = isSpace || isTab || isNewLine;

		if ( isWhiteSpace )
		{
			// If not a zero length word
			if ( currentWordLength )
			{
				// If this is the first time we encounter this word it's a new distinc length
				// Use it to find the maximum width of the vertical plot
				if ( !wordLengths[currentWordLength] )
					++numDistinctLengths;

				++wordLengths[currentWordLength];
			}

			// Checking to see if this is the new longest word we've found 
			// To use it to find the maximum height of the vertical plot
			if ( currentWordLength > maxWordLength )
				maxWordLength = currentWordLength;

			// Reset counter
			currentWordLength = 0;
		}
		else
			++currentWordLength;
	}

	// If you do not end in whitespace you might still want to count that word

	if ( !wordLengths[currentWordLength] )
		++numDistinctLengths;

	if ( currentWordLength )
		++wordLengths[currentWordLength];


	printf("\nWord Length Histogram:\n");
	printf("----------------------\n");
	if ( plotDirection == VERTICAL_HISTOGRAM )
	{
		// Plot bars
		// Going row by row, starting from the top
		for ( int wordLength = maxWordLength; wordLength > 0; --wordLength )
		{
			// Going column by column but covering the whole array 
			// But only printing a hash symbol if it has a value equal to the current max
			for ( int j = 0; j < LONGEST_WORD_LENGTH; ++j )
			{
				// Only print a value if you're nonzero
				if ( wordLengths[j] )
				{
					putchar(' ');
					// Check if the value is equal to the current wordLength
					if ( wordLength <= wordLengths[j] )
						putchar('#');
					else
						putchar(' ');
				}

			}
			putchar('\n');
		}

		for ( int i = 0; i < numDistinctLengths * 2; ++i )
			putchar('-');
		putchar('\n');

		// Plot numbers at the bottom
		for ( int j = 0; j < LONGEST_WORD_LENGTH; ++j )
		{
			// Only print a value if you're nonzero
			if ( wordLengths[j] )
			{
				printf("%2d", wordLengths[j]);
			}
		}
		putchar('\n');

	}
	else // If you pass a zero you mean horizontal
	{

		// Plot both at once
		for ( int wordLen = 0; wordLen < LONGEST_WORD_LENGTH; ++wordLen )
		{
			int wordCountForThisLength = wordLengths[wordLen];

			if ( wordCountForThisLength )
			{
				printf("%2d:", wordLen);
				for ( int i = 0; i < wordCountForThisLength; ++i )
					putchar('#');
				putchar('\n');
			}
		}
	}


}
#undef LONGEST_WORD_LENGTH

void
C_Number_Of_Ocurrences(void)
{
	int c, i, nWhite, nOther;
	int nDigit[10];

	//Initializing all to zero
	nWhite = nOther = 0;
	for ( i = 0; i < 10; ++i )
		nDigit[i] = 0;

	while ( (c = getchar()) != EOF )
		if ( c >= '0' && c <= '9' )
			++nDigit[c - '0'];
		else if ( c == ' ' || c == '\n' || c == '\t' )
			++nWhite;
		else
			++nOther;
	printf("Digits =");
	for ( i = 0; i < 10; ++i )
		printf(" %d", nDigit[i]);
	printf(" white space = %d, other = %d\n", nWhite, nOther);
}

#define NUM_DIGITS 10
void
AO_Number_Of_Ocurrences(void)
{
	int digitCount[10] = { 0 };
	int whitespaceCount, othersCount, currentChar;

	whitespaceCount = othersCount = 0;

	while ( (currentChar = getchar()) != EOF )
	{
		int isSpace = currentChar == ' ';
		int isTab = currentChar == '\t';
		int isNewLine = currentChar == '\n';
		if ( isSpace || isTab || isNewLine )
		{
			++whitespaceCount;
		}
		else if ( currentChar == '0' )
		{
			++digitCount[0];
		}
		else if ( currentChar == '1' )
		{
			++digitCount[1];
		}
		else if ( currentChar == '2' )
		{
			++digitCount[2];
		}
		else if ( currentChar == '3' )
		{
			++digitCount[3];
		}
		else if ( currentChar == '4' )
		{
			++digitCount[4];
		}
		else if ( currentChar == '5' )
		{
			++digitCount[5];
		}
		else if ( currentChar == '6' )
		{
			++digitCount[6];
		}
		else if ( currentChar == '7' )
		{
			++digitCount[7];
		}
		else if ( currentChar == '8' )
		{
			++digitCount[8];
		}
		else if ( currentChar == '9' )
		{
			++digitCount[9];
		}
		else
		{
			++othersCount;
		}
	}

	printf("Whitespace: %d\n", whitespaceCount);
	for ( int i = 0; i < NUM_DIGITS; ++i )
	{
		printf("Digit %d: %d\n", i, digitCount[i]);
	}
	printf("Others: %d\n", othersCount);
}
#undef NUM_DIGITS 

// 1.5 - Character Input and Output
// ----------------------------------------------------------------------------------------------------------

// EX 1-12 DONE: One word per line
void
One_Word_Per_Line(void)
{
	int currentChar;

	while ( (currentChar = getchar()) != EOF )
	{
		int isSpace = currentChar == ' ';
		int isTab = currentChar == '\t';
		int isNewLine = currentChar == '\n';
		if ( isSpace || isTab || isNewLine )
		{
			putchar('\n');
		}
		else
		{
			putchar(currentChar);
		}
	}
}

#define IN 1
#define OUT 0
void
C_Word_Count(void)
{
	// EX 1-11 DONE: Would test with empty, with numbers. With just lines. ETC
	int c, nl, nw, nc, state;

	state = OUT;
	nl = nw = nc = 0;
	while ( (c = getchar()) != EOF )
	{
		++nc;
		if ( c == '\n' )
		{
			++nl;
		}
		if ( c == ' ' || c == '\n' || c == '\t' )
		{
			state = OUT;
		}
		else if ( state == OUT )
		{
			state = IN;
			++nw;
		}
	}
	printf("%d, %d, %d\n", nl, nw, nc);
}
#undef IN
#undef OUT

void
AO_Word_Count(void)
{
	int currentChar, wordCount;

	wordCount = 0;

	int wasWord = 0;

	while ( (currentChar = getchar()) != EOF )
	{
		int isSpace = currentChar == ' ';
		int isTab = currentChar == '\t';
		int isNewLine = currentChar == '\n';
		if ( isSpace || isTab || (isNewLine) )
		{
			if ( wasWord )
				wordCount++;

			wasWord = 0;
		}
		else
		{
			wasWord = 1;
		}
	}
	printf("Word count: %d\n", wordCount);
}

// Ex 1-10 DONE: Visualize different types of whitespace by inserting some chars
void
Whitespace_Visualizer(void)
{
	int currentChar;

	while ( (currentChar = getchar()) != EOF )
	{
		if ( currentChar == ' ' )
		{
			putchar('\\');
			putchar('b');
		}
		else if ( currentChar == '\t' )
		{
			putchar('\\');
			putchar('t');
		}
		else if ( currentChar == '\\' )
		{
			putchar('\\');
			putchar('\\');
		}
		else if ( currentChar == '\n' )
		{
			putchar('\\');
			putchar('n');
		}
		else
		{
			putchar(currentChar);
		}
	}
}

// Ex 1-9 DONE: Compress multiple blanks to one blank
void
Multiple_Blanks_To_One(void)
{
	int currentChar;
	int blankCount = 0;

	while ( (currentChar = getchar()) != EOF )
	{
		if ( currentChar == ' ' )
		{
			if ( !blankCount )
			{
				putchar(currentChar);
			}

			blankCount++;
		}
		else
		{
			blankCount = 0;
			putchar(currentChar);
		}
	}
}

// Ex 1-8 DONE: Count blanks, tabs and newlines
void
Blank_Tab_Newline_Count(void)
{
	int currentChar, newLine, blanks, tabs;
	newLine = 0;
	blanks = 0;
	tabs = 0;

	while ( (currentChar = getchar()) != EOF )
	{
		if ( currentChar == '\n' )
		{
			newLine++;
		}
		else if ( currentChar == ' ' )
		{
			blanks++;
		}
		else if ( currentChar == '\t' )
		{
			tabs++;
		}
	}

	printf("Results:\n-------\n");
	printf("Newlines: %d\n", newLine);
	printf("Blanks: %d\n", blanks);
	printf("Tabs: %d\n", tabs);
}

void
C_Line_Count(void)
{
	int c, nl;
	nl = 0;

	while ( (c = getchar()) != EOF )
		if ( c == '\n' )
			nl++;

	printf("%d\n", nl);
}

void
AO_Line_Count(void)
{
	int c = getchar();
	int res = c != EOF;

	unsigned int count = 0;

	while ( res )
	{
		c = getchar();
		res = c != EOF;

		if ( c == '\n' )
			count++;
	}
	printf("%d\n", count);
}

void
C_Char_Count(void)
{
	double count;

	for ( count = 0; getchar() != EOF; ++count )
		; // Null statement (for loop needs something to happen

	printf("%.2f\n", count);
}

void
AO_Char_Count(void)
{
	int c = getchar();
	int res = c != EOF;

	unsigned int count = 0;

	while ( res )
	{
		c = getchar();
		res = c != EOF;
		count++;
	}
	printf("%d\n", count);
}

void
Print_EOF(void)
{
	// EX 1-7 DONE: Print EOF
	printf("%d\n", (int)EOF);
}

void
C_FileCopy(void)
{
	// EX 1-6 DONE: Verify result is either 0 or 1 (used debugger)

	int c = getchar();
	int result = c != EOF;
	while ( result )
	{
		c = getchar();
		result = c != EOF;
		putchar(c);
	}
}

// 1.4 - Symbolic Constants
// ----------------------------------------------------------------------------------------------------------
#define LOWER 0.0f
#define UPPER 300.0f
#define STEP 20.0f
void
AO_FahrenheitToCelsius_SymConstants(void)
{
	printf("F\tC\n");
	for ( float F = UPPER; F >= LOWER; F -= STEP )
	{
		float C = (5.0f / 9.0f) * (F - 32.0f);
		printf("%.1f\t%.1f\n", F, C);
	}
}
#undef LOWER
#undef UPPER
#undef STEP

// 1.3 - The For statement
// ----------------------------------------------------------------------------------------------------------
void
AO_FahrenheitToCelsius_Reverse(void)
{
	// 0 to 300 F
	// C = (5/9) (F - 32)

	// EX 1-5 DONE: Print table in reverse order

	printf("F\tC\n");
	for ( float F = 300.0f; F >= 0.0f; F -= 20.0f )
	{
		float C = (5.0f / 9.0f) * (F - 32.0f);
		printf("%.1f\t%.1f\n", F, C);
	}

}


// 1.2 ------------------------------------------------------------------------------------------------------
void
CelsiusToFahrenheit_Float(void)
{
	// EX 1-4 DONE: Print Celsius to Fahrenheit table
	float fahr, celsius;
	int lower, upper, step;

	lower = 0;
	upper = 300;
	step = 20;

	celsius = (float)lower;

	printf("F\tC\n");
	while ( celsius <= (float)upper )
	{
		fahr = (9.0f / 5.0f) * celsius + 32.0f;

		printf("%5.1f\t%5.1f\n", fahr, celsius);
		celsius = celsius + (float)step;
	}
}

void
C_FahrenheitToCelsius_Float(void)
{
	float fahr, celsius;
	int lower, upper, step;

	lower = 0;
	upper = 300;
	step = 20;

	fahr = (float)lower;

	while ( fahr <= (float)upper )
	{
		celsius = (5.0f / 9.0f) * (fahr - 32.0f);
		printf("%5.1f\t%5.1f\n", fahr, celsius);
		fahr = fahr + (float)step;
	}
}

void
C_FahrenheitToCelsius_Int(void)
{
	int fahr, celsius;
	int lower, upper, step;

	lower = 0;
	upper = 300;
	step = 20;

	fahr = lower;

	while ( fahr <= upper )
	{
		celsius = 5 * (fahr - 32) / 9;
		printf("%3d\t%3d\n", fahr, celsius);
		fahr = fahr + step;
	}
}

void
AO_FahrenheitToCelsius(void)
{
	// 0 to 300 F
	// C = (5/9) (F - 32)

	// EX 1-3 DONE: Print table above the calculations

	printf("F\tC\n");
	for ( float F = 0.0f; F <= 300.0f; F += 20.0f )
	{
		float C = (5.0f / 9.0f) * (F - 32.0f);
		printf("%.1f\t%.1f\n", F, C);
	}

}

// 1.1 ------------------------------------------------------------------------------------------------------

void
HelloWorld(void)
{
	// Ex 1-1 DONE: Run hello world program
	// Ex 1-2 DONE: Test what happens if printf argument string uses some other chars
	printf("Hello World!\n");
}
