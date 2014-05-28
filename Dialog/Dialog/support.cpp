#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>

#define size 100
void retmas(int a[], int siz)   //переворачивает масив
{
	int i, hold;
	for (i = 0; i < (siz / 2); i++){
		hold = a[i];
		a[i] = a[siz - 1 - i];
		a[siz - 1 - i] = hold;
	}
}

int polynom(int x, int a[], int n) 
{
	int i, j;
	float X = x;
	int s = 0;
	for (j = 0; j <= n; j++){
		
		s += a[j] * pow(X, j);
	}
	return s;
}
int parse_number(char *string,int *er)
{
	int len, c = 0, i = 0, a[size], step = 0, k = 0, sign = 1, j = 0;
		
	*er = 0;
	while (isspace(string[i]))
	{
		string++;
	}
	if (string[0] == '+')
	{
		string++;
	}
	if (string[0] == '-')
	{
		sign = -1;
		string++;
	}
	i = 0;
	while (isspace(string[i]))
	{
		string++;
	}
	len = strlen(string);
	for (i = 0; i < len; i++)
	{
		int n;
		if (isspace(string[i])) {
			continue;
		}

		if (isdigit(string[i]))
		{
			n = string[i] - '0';
		}
		if (n >= 10 || n < 0) 
		{
			*er = 1;
			break;
		}
		else 
		{
			a[j] = n;
			step++;
			j++;
		}
	}
	retmas(a, step);
	c = sign*polynom(10, a, (step - 1));
	return c;
}

int file_size(FILE *f)
{
	int n = 0;
	char c;
	while ((c = fgetc(f)) != EOF)
	{
		n++;
	}
	rewind(f);
	return n;
}

int string_key(char* T1, char* T2)
{
	if (T1 == NULL || T2 == NULL)
	{
		return 0;
	}
	int i, len1 = strlen(T1), len2 = strlen(T2);
	if (len1 != len2)
	{
		return 0;
	}
	for (i = 0; i < len1; i++)
	{
		if (T1[i] != T2[i])
		{
			return 0;
		}
	}

	return 1;
}