#pragma once

#include "common.h"

// C_ stands for functions from the C Book
// AO_ stands for functions I (Angel Ortiz) wrote

// 2.11
int AO_lower_compact(int c);

// 2.10
int AO_bitcount(u32 bits);

// 2.9
u32 AO_rightrot(u32 bits, int n);
u32 AO_invert(u32 bits, int p, int n);
u32 AO_setbits(u32 bits, int p, int n, u32 y);
u32 C_getbits(u32 bits, int p, int n);

// 2.8
int AO_any(char s1[], char s2[]);
void AO_squeeze(char s1[], char s2[]);

// 2.7
bool AO_htoi(char value_as_hex_string[], u32 *value_as_int);
int AO_lower(int c);
int C_atoi(char s[]);
bool AO_atoi(char value_as_string[], int *value_as_int);

// 2.6 
void AO_New_For(void);

// 2.3
int C_strlen(char s[]);

// 2.2
void AO_Find_Type_Numerical_Limits(void);
