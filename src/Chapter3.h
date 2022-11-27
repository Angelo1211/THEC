#pragma once

#include "common.h"

// Chapter 3 - Control Flow
// ----------------------------------------------------------------------------------------------------------

// C_ stands for functions from the C Book
// AO_ stands for functions I (Angel Ortiz) wrote

// 3.4
void AO_Test_escape();
void AO_chars_to_escape(char d[], char s[]);
void AO_escape_to_chars(char d[], char s[]);

// 3.3
void AO_Test_binsearch();
s64 AO_binsearch(s64 x, s64 v[], s64 n);
s64 C_binsearch(s64 x, s64 v[], s64 n);
