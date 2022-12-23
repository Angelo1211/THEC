#pragma once

#include "common.h"

// C_ stands for functions from the C Book
// AO_ stands for functions I (Angel Ortiz) wrote

// Chapter 3 - Control Flow
// ----------------------------------------------------------------------------------------------------------

// 3.6
void AO_itob(int n, char s[], int b);
void AO_itoa(int n, char s[]);
void C_itoa(int n, char s[]);

// 3.5
void AO_Test_expand();
void AO_expand(char s1[], char s2[]);
void C_reverse(char s[]);
void AO_reverse_ip(char s[]);
void AO_Print_IntArray(int v[], int n, int highlight_a, int highlight_b);
void AO_Test_shellsort();
void C_shellsort(int v[], int n);

// 3.4
void AO_Test_escape();
void AO_chars_to_escape(char d[], char s[]);
void AO_escape_to_chars(char d[], char s[]);

// 3.3
void AO_Test_binsearch();
s64 AO_binsearch(s64 x, s64 v[], s64 n);
s64 C_binsearch(s64 x, s64 v[], s64 n);
