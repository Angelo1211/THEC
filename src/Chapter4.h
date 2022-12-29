#pragma once

#include "common.h"

// C_ stands for functions from the C Book
// AO_ stands for functions I (Angel Ortiz) wrote

// Chapter 4 - Functions and Program Structure
// ----------------------------------------------------------------------------------------------------------
// 4.3 - External Variables
int getch(void);
void ungetch(int);
int getop(char s[]);
void push(double f);
double pop(void);
void C_calculator(void);

// 4.2 - Functions Returning Non-Integers
double AO_atof(char s[]);
double C_atof(char s[]);

// 4.1 - Basics of Functions
int AO_strrindex(char s[], char t[]);
int C_minigrep(char pattern[]);
int C_strindex(char s[], char t[]);
int C_getline_4(char s[], int lim);