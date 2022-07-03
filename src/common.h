#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define TRUE 1
#define FALSE 0

// Debug strings
void AO_DEBUG_Print_Tab_Stops(int tabLength, int tabStopCount);
void AO_DEBUG_Print_Visualized_WhiteSpace(char str[], int tab_stop_length);

// Strings
int AO_Find_Word_Length(char str[], int index);
int C_getline(char line[], int maxline);
void C_copy(char to[], char from[]);

// Files
char *AO_Read_Entire_File(char *file_name, size_t *size);

// Console
void Exit_Console(void);
