#include "Chapter1.h"

// 1.8 - Character Arrays
// ----------------------------------------------------------------------------------------------------------
#define MAXLINE 1000

int getline_c(char line[], int maxline);
void copy_c(char to[], char from[]);

// Print longest line
void
print_longest_line_theirs(void)
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
	while ( (len = getline(line, MAXLINE)) > 0 )
	{
		if ( len > max )
		{
			max = len;
			copy(longest, line);
		}
	}

	if ( max > 0 )
	{
		printf("%s", longest);
	}
}

int
getline_c(char s[], int lim)
{
	int c, i;

	// While you haven't hit the limit 
	// Or you have not seen an EOF
	// Or your character is not an endline
	// put the line into the line string
	for ( i = 0;
		  i < lim - 1 && (c = getchar()) != EOF && c != '\n';
		  ++i )
	{
		s[i] = c;
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
copy_c(char to[], char from[])
{
	int i;

	i = 0;
	while ( (to[i] = from[i]) != '\0' )
		++i;
}

#undef MAXLINE

#define MAX_CHAR_ARRAY_SIZE 1<<12
void
print_longest_line_mine(void)
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
pow_byval_c(int base, int n)
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
pow_c(int base, int n)
{
	int i, p;
	p = 1;
	for ( i = 1; i <= n; ++i )
		p = p * base;

	return p;
}

void
pow_test_thec(void)
{
	int i;
	for ( i = 0; i < 10; ++i )
		printf("%d %d %d\n", i, pow_c(2, i), pow_c(-3, i));
}

void
pow_example_mine(void)
{
	int base = 2;
	int exp = 32;
	printf("%d^%d = %d\n", base, exp, pow_mine(base, exp));
}

int
pow_mine(int base, int exponent)
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
Number_Of_Ocurrences_TheC(void)
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
Number_Of_Ocurrences_Mine(void)
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
Word_Count_TheC(void)
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
Word_Count_Mine(void)
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
Line_Count_TheC(void)
{
	int c, nl;
	nl = 0;

	while ( (c = getchar()) != EOF )
		if ( c == '\n' )
			nl++;

	printf("%d\n", nl);
}

void
Line_Count_mine(void)
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
Char_Count_Theirs(void)
{
	double count;

	for ( count = 0; getchar() != EOF; ++count )
		; // Null statement (for loop needs something to happen

	printf("%.2f\n", count);
}

void
Char_Count_Mine(void)
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
FileCopy_Theirs(void)
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
FahrenheitToCelsius_Mine_SymConstants(void)
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
FahrenheitToCelsius_Mine_Reverse(void)
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
FahrenheitToCelsius_Float_Theirs(void)
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
FahrenheitToCelsius_Int_Theirs(void)
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
FahrenheitToCelsius_Mine(void)
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

