#pragma once

#include "common.h"

// C_ stands for functions from the C Book
// AO_ stands for functions I (Angel Ortiz) wrote

// 1.10
void AO_Check_For_Errors(void);
char *AO_Remove_Comments(char *fileName);
void AO_Fold_Test(void);
void AO_EnTab_Test(void);
void AO_DeTab_Test(void);

// 1.9
void AO_test_reverse_string(void);
void AO_remove_trailing_ws(void);
void AO_print_longer_than_80(void);
void AO_print_input_length(void);
void C_print_longest_line(void);
void AO_print_longest_line(void);
// 1.8
int C_pow_byval(int base, int n);
// 1.7 
float fToC(float fahrenheit);
int C_pow(int base, int n);
void C_pow_test(void);
void AO_pow_example(void);
int AO_pow(int base, int exponent);
// 1.6 
#define VERTICAL_HISTOGRAM 1
#define HORIZONTAL_HISTOGRAM 0
void Character_Frequency(int plotDirection);
void Length_Of_Words(int plotDirection);
void C_Number_Of_Ocurrences(void);
void AO_Number_Of_Ocurrences(void);
// 1.5
void One_Word_Per_Line(void);
void C_Word_Count(void);
void AO_Word_Count(void);
void Whitespace_Visualizer(void);
void Multiple_Blanks_To_One(void);
void Blank_Tab_Newline_Count(void);
void C_Line_Count(void);
void AO_Line_Count(void);
void C_Char_Count(void);
void AO_Char_Count(void);
void Print_EOF(void);
void C_FileCopy(void);
// 1.4
void AO_FahrenheitToCelsius_SymConstants(void);
// 1.3
void AO_FahrenheitToCelsius_Reverse(void);
// 1.2
void CelsiusToFahrenheit_Float(void);
void C_FahrenheitToCelsius_Float(void);
void C_FahrenheitToCelsius_Int(void);
void AO_FahrenheitToCelsius(void);
// 1.1
void HelloWorld(void);
