#include "stdafx.h"
int get_type(char *argv[], int* type, int n)
{
	if (argv[n] == NULL)
	{
		return 0;
	}
	int er = 0;
	*type = parse_number(argv[n], &er);

	if (er != 0)
	{
		return INCORECT_TYPE;
	}

	return 0;
}
int get_file(char *argv[], FILE **F, int n)
{
	if (argv[n] == NULL)
	{
		return 0;
	}
	(*F) = fopen(argv[n], "r");
	if ((*F) == NULL)
	{
		return ERROR;
	}
	return 0;
}
int get_title(char *argv[], char** T, int n)
{
	if (argv[n] == NULL)
	{
		return 0;
	}
	(*T) = (char*)malloc((strlen(argv[n]) + 1)*sizeof(char));
	if (NULL == T)
	{
		return NO_MEMORY;
	}
	int i = 0, k = 0;
	for (i = 0; i < strlen(argv[n]); i++)
	{
		(*T)[k] = argv[n][i];
		k++;
	}
	(*T)[k] = '\0';
	return 0;
}
int get_but(char *argv[], button** but, int *bn, int n)
{
	if (argv[n] == NULL)
	{
		return 0;
	}
	if (argv[n + 1] == NULL)
	{
		return 0;
	}
	(*bn)++;
	if (NULL == *but)
	{
		(*but) = (button*)malloc((*bn)*sizeof(button));
		if (NULL == *but)
		{
			return NO_MEMORY;
		}
	}
	else
	{
		(*but) = (button*)realloc((*but), (*bn)*sizeof(button));
		if (NULL == (*but))
		{
			return NO_MEMORY;
		}
	}
	(*but)[*bn - 1].text = NULL;
	if (strlen(argv[n]) > sizebut)
	{
		return BUTTON_TEXT_TOO_LONG;
	}
	if (NULL == (*but)[*bn - 1].text)
	{
		(*but)[*bn - 1].text = (char*)malloc((strlen(argv[n]) + 1)*sizeof(char));
		if (NULL == (*but)[*bn - 1].text)
		{
			return NO_MEMORY;
		}
	}
	else
	{
		(*but)[*bn - 1].text = (char*)realloc((*but)[*bn - 1].text, (strlen(argv[n]) + 1)*sizeof(char));
		if (NULL == (*but)[*bn - 1].text)
		{
			return NO_MEMORY;
		}
	}
	int i, k = 0;
	for (i = 0; i < strlen(argv[n]); i++)
	{
		(*but)[*bn - 1].text[k] = argv[n][i];
		k++;
	}
	(*but)[*bn - 1].text[k] = '\0';
	int e = 0;
	(*but)[*bn - 1].ret = parse_number(argv[n + 1], &e);
	if (e != 0)
	{
		return INCORECT_RET;
	}
	return 0;
}
int get_text(char *argv[], char** txt, int n)
{
	if (argv[n] == NULL)
	{
		return 0;
	}
	if (NULL == (*txt))
	{
		(*txt) = (char*)malloc((strlen(argv[n]) + 1)*sizeof(char));
		if (NULL == (*txt))
		{
			return NO_MEMORY;
		}
	}
	else
	{
		(*txt) = (char*)realloc((*txt), (strlen(argv[n]) + 1)*sizeof(char));
		if (NULL == (*txt))
		{
			return NO_MEMORY;
		}
	}
	int k = 0, i;
	for (i = 0; i < strlen(argv[n]); i++)
	{
		(*txt)[k] = argv[n][i];
		k++;
	}
	(*txt)[k] = '\0';
	return 0;
}
int get_arg(char** T, char** txt, FILE **F, button** but, int *bn, int *type, int argc, char *argv[])
{
	int i = 1;
	int er;
	while (i < argc)
	{
		if (NULL == argv[i])
		{
			i++;
			continue;
		}
		if ((string_key(argv[i], "-text")) || (string_key(argv[i], "-longtext")) || (string_key(argv[i], "-button")) || (string_key(argv[i], "-type")) || (string_key(argv[i], "-title")))
		{

			if (string_key(argv[i], "-type"))
			{
				i++;
				if (i > argc)break;

				er = get_type(argv, type, i);

				if (er != 0)
				{
					return er;
				}
				i++;
				if (i > argc)break;
			}

			if (string_key(argv[i], "-longtext"))
			{
				i++;
				if (i > argc)break;

				er = get_file(argv, F, i);
				if (er != 0)
				{
					return er;
				}
				i++;
				if (i > argc)break;

			}
			if (string_key(argv[i], "-title"))
			{
				i++;
				if (i > argc)break;
				er = get_title(argv, T, i);
				if (er != 0)
				{
					return er;
				}
				i++;
				if (i > argc)break;

			}
			if (string_key(argv[i], "-button"))
			{
				i++;
				if (i > argc)break;
				er = get_but(argv, but, bn, i);
				if (er != 0)
				{
					return er;
				}
				i += 2;
				if (i > argc)break;

			}
			if (string_key(argv[i], "-text"))
			{
				i++;
				if (i > argc)break;

				er = get_text(argv, txt, i);
				if (er != 0)
				{
					return er;
				}

				i++;
				if (i > argc)break;
			}
		}
		else
		{
			i++;
		}

	}
	return 0;
}