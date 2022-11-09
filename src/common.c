#include "common.h"

char *
AO_Read_Entire_File(char *file_name, size_t *size)
{
	char *result = 0;

	FILE *file = fopen(file_name, "r");
	if ( file )
	{
		// Seek to the end of the file
		fseek(file, 0, SEEK_END);

		// Tell me where that is and store it
		size_t file_size = ftell(file);

		// Seek back to the front of the file
		fseek(file, 0, SEEK_SET);

		// Extra space for the null terminator
		result = malloc(file_size + 1);

		if ( result )
		{
			int read = fread(result, sizeof(char), file_size, file);
			if ( read )
			{
				*size = read;
				result[read] = 0;
			}
		}

		fclose(file);
	}

	return result;
}

int
AO_Find_Word_Length(char str[], int index)
{
	int beginning = index;
	char currentChar;
	while ( (currentChar = str[index]) != '\0' )
	{
		// Traverse the whole string until you find a whitespace char
		if ( (currentChar == ' ') || (currentChar == '\t') || (currentChar == '\n') )
			return index - beginning;

		++index;
	}

	// The word takes the whole array
	return index - beginning;
}

void
AO_DEBUG_Print_Tab_Stops(int tabLength, int tabStopCount)
{
	int numChars = tabStopCount * tabLength + 1;
	int skip = 0;
	// Draw char numbers aligned to tab stops
	// BUG: This will not work properly with tab stop counts that result in total number of chars rendered
	// Larger than 3 digits (it will be off by one column after each tab stop after 100)
	for ( int i = 0; i < numChars; ++i )
	{
		if ( (i % tabLength) == 0 )
		{
			printf("%d", i);

			if ( i > 9 ) skip = 1;

		}
		else
		{
			if ( !skip )
			{
				putchar(' ');
			}
			else
			{
				skip = 0;
			}
		}
	}
	putchar('\n');

	for ( int i = 0; i < numChars; ++i )
	{
		if ( (i % tabLength) != 0 )
		{
			putchar('-');
		}
		else
		{
			putchar('|');
		}
	}
	putchar('\n');
}

void
AO_DEBUG_Print_Visualized_WhiteSpace(char str[], int tab_stop_length)
{
	// String indices
	// We need to keep separate indices for the whitespace visualized index
	// Because the index stops being a one to one match after parsing tabs
	int original_index = 0;
	int WS_visualized_index = 0;

	char currentChar;
	while ( (currentChar = str[original_index++]) != '\0' )
	{
		char outputChar = 0;

		if ( currentChar == '\t' )
		{
			// We need to use a different index here to account for the added string length
			// from explicitely visualizing the tabs
			int tab_Stop_Gap = tab_stop_length - ((WS_visualized_index) % tab_stop_length);

			while ( tab_Stop_Gap-- )
			{
				WS_visualized_index++;
				putchar('+');
			}
			// Skip to the next char since you've already printed the tabs and incremented the index
			continue;
		}
		else if ( currentChar == ' ' )
		{
			outputChar = '-';
		}
		else
		{
			outputChar = currentChar;
		}

		WS_visualized_index++;
		putchar(outputChar);
	}
}

void
Console_Delay_Exit(void)
{
	printf("\nPress any key to exit!...\n");
	getchar();
}
