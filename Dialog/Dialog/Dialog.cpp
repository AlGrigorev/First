#include "stdafx.h"
#include "console.h"
#include "support.h"

int put_text(Dialog* D,char* str)
{
	if (NULL == D)
	{
		return ERROR;
	}
	int e = 0,len=strlen(str);
	D->stxt.h = 1;
	
	if (len > 60)
	{
		D->stxt.w = sizestring;
		}
	if (len<= 60 && len> 30)
	{
		D->stxt.w = 60;
	
	}
	if (len <= 30 && len > 10)
	{
		D->stxt.w = 30;
		}

	D->text = (char**)malloc((D->stxt.h)*sizeof(char*));
	if (NULL == D->text)
	{
		return 1;
	}
	for (e = 0; e < D->stxt.h;e++)
	{
		D->text[e] = (char*)malloc((D->stxt.w)*sizeof(char));
		if (NULL == D->text[e])
		{
			return 1;
		}
	}
	
	int i = 0, j = 0, k = 0;
	
	do
	{
		if (j == D->stxt.h-1)
		{
			D->stxt.h++;
			D->text = (char**)realloc(D->text, (D->stxt.h)*sizeof(char*));
			for (e; e < D->stxt.h;e++)
			{
				D->text[e] = (char*)malloc((D->stxt.w)*sizeof(char));
				if (NULL == D->text[e])
				{
					return NO_MEMORY;
				}
			}
			if (D->text == NULL)
			{
				return NO_MEMORY;
			}
		}
		int o = 1;
		/*while (str[k + D->stxt.w - o] != ' ')
		{
			o++;
		}										*///чтобы разделения были по целым словам
		for (i = 0; i < D->stxt.w - 1; i++)
		{
			if (str[k] == '\n' || str[k] == '\0')
			{
				k++;
				break;
			}
			if (i >= D->stxt.w - 11 && str[k] == ' ')
			{
				k++;
				break;
			}
			D->text[j][i] = str[k];
			k++;
		}

			D->text[j][i] = '\0';
		j++;
	} while (str[k] != '\0');
	return 0;
}
int put_title(Dialog* D, char* str)
{
	if (NULL == D)
	{
		return ERROR;
	}
	int l = strlen(str)+1;
	if (l > sizetitle)
	{
		return TOO_LONG_TITLE;  // слишком большой заголовок
	}
	D->title = (char*)malloc(l*sizeof(char));
	if (NULL == D->title)
	{
		return NO_MEMORY;
	}
	int i;
	for ( i = 0; i < l; i++)
	{
		D->title[i] = str[i];
	}
	//D->title[i] = '\0';
	return 0;   
}
int put_longtext(Dialog* D, FILE* f)
{
	if (NULL == D)
	{
		return ERROR;
	}
	char c;
	int i = 0, j = 0, e = 0;
	D->slong.h = 1;
	D->slong.w = sizestring;
	D->longtext = (char**)malloc((D->slong.h)*sizeof(char*));
	if (NULL == D->longtext)
	{
		return NO_MEMORY;
	}
	for (e = 0; e < D->slong.h; e++)
	{
		D->longtext[e] = (char*)malloc((D->slong.w)*sizeof(char));
		if (NULL == D->longtext[e])
		{
			return NO_MEMORY;
		}
	}
	int fs = 0, qe = file_size(f);
	while (fs < qe)
	{
		char* str = (char*)malloc(D->slong.w*sizeof(char));
		if (NULL == str)return 1;
		int n = 0;
		for (n = 0; n < D->slong.w - 1; n++)
		{
			c = fgetc(f);
			fs++;
			if (c == EOF || (c == '\n')|| (fs >= qe) || (c == '\r') )break;
			if (n >= (D->slong.w - 10) && c == ' ')
			{
				str[n] = c;
				break;
			}						//чтобы был перенос слов
			str[n] = c;
		}
		str[n] = '\0';

		if (j >= D->slong.h)
		{
			D->slong.h ++;
			D->longtext = (char**)realloc(D->longtext, (D->slong.h)*sizeof(char*));
			if (D->longtext == NULL)
			{
				return NO_MEMORY;
			}
			for (e; e < D->slong.h; e++)
			{
				D->longtext[e] = (char*)malloc((D->slong.w)*sizeof(char));
				if (NULL == D->longtext[e])
				{
					return NO_MEMORY;
				}
			}
		}
		i = 0;
		while (str[i] != '\0')
		{

			D->longtext[j][i] = str[i];
			i++;
		}
		D->longtext[j][i] = '\0';
		j++;
	}

	return 0;
}
int add_but(Dialog* D, int retur, char* txt)
{
	if (NULL == D)
	{
		return ERROR;
	}
	if (retur == EXIT)
	{
		return INCORECT_RET;
	}
	if (0 == D->numb)
	{
		D->but = (button*)malloc((D->numb + 1)*sizeof(button));
	}
	else
	{
		D->but = (button*)realloc(D->but,(D->numb + 1)*sizeof(button));
	}
	if (NULL == D->but)
	{
		return NO_MEMORY;								//если возращает 1 то не хватило места
	}
	//for (int t = 0; t < D->numb; t++)
	//{
	//	if (D->but[D->numb].ret == reture) return 5; // возращаемое значение уже существует
	//}
	D->but[D->numb].ret = retur;
	//D->but[D->numb].text= txt;   // или посимвольно?
	int len = strlen(txt);
	if (sizebut < len)
	{
		return BUTTON_TEXT_TOO_LONG;								// слишком длинный текст кнопки
	}
	D->but[D->numb].text= (char*)malloc(len*sizeof(char));
	if (NULL == D->but[D->numb].text)
	{
		return NO_MEMORY;
	}
	int i = 0;
	for (i = 0; i < len; i++)
	{
		D->but[D->numb].text[i] = txt[i];
	}
	D->but[D->numb].text[i] = '\0';
	D->numb++;
	return 0;
}
int correct_text(Dialog* D)
{
	if (NULL == D)
	{
		return ERROR;
	}
	if (NULL == D->text )
	{
		return 0;
	}
	if (D->stxt.h > sizetext)
	{
		if (NULL == D->longtext)
		{
			D->slong.h = D->stxt.h-1;
			D->slong.w = D->stxt.w;
			D->stxt.h = 0;
			D->stxt.w = 0;
			D->longtext = (char**)malloc(D->slong.h*sizeof(char*));
			if (NULL == D->longtext)
			{
				return NO_MEMORY;					//не хватило памяти
			}
			for (int i = 0; i < D->slong.h; i++)
			{
				D->longtext[i] = (char*)malloc(D->slong.w*sizeof(char));
				if (D->longtext[i] == NULL)
				{
					return NO_MEMORY;
				}
				for (int j = 0; j < D->slong.w; j++)
				{
					D->longtext[i][j] = D->text[i][j];
				}
				free(D->text[i]);
			}
			free(D->text);
		}
		else if (NULL != D->longtext)
		{
			for (int j = 0; j < D->stxt.h; j++)
			{
				free(D->text[j]);
			}
			D->stxt.h = 0;
			D->stxt.w = 0;
			free(D->text);
			return TOO_LONG_TEXT;						//размер текста слишком большой, при том "длинный текст " уже существует (текст удален) 
		}
	}
	return 0;
}
int create_Dialog(Dialog *D,int t, char* T, char* txt, FILE* lt)
{
	if (NULL == D)
	{
		return ERROR;
	}
	D->string.cursor = 0;
	D->string.s = NULL;
	if (t > 1 || t < 0)
	{
		return INCORECT_TYPE;		//некоректный тип
	}
	D->type = t;
	int ret=0;
	if (NULL != T)
	{

		ret = put_title(D, T);
		if (0 != ret) return ret;
	}
	if (NULL != txt)
	{

		ret = put_text(D, txt);
		if (0 != ret) return ret;
	}
	if (NULL != lt)
	{

		ret = put_longtext(D, lt);
		if (ret != 0)return ret;
	}
	ret = correct_text(D);
	return ret;
}
void del_Dialog(Dialog *D)
{
	if (NULL != D->but)
	{
		free(D->but);
	}
	
	if (NULL != D->text)
	{

		for (int i = 0; i < D->stxt.h; i++)
		{
			if (NULL != D->text[i])
			{
				free(D->text[i]);
			}
		}
		free(D->text);
	}
	if (NULL != D->longtext)
	{

		for (int i = 0; i < D->slong.h; i++)
		{
			if (NULL != D->longtext[i])
			{
				free(D->longtext[i]);
			}
		}
		free(D->longtext);
	}
	if (NULL != D->title)
	{
		free(D->title);
	}
	if (NULL != D->string.s)
	{
		free(D->string.s);
	}
	D->slong.h = 0;
	D->slong.w = 0;
	D->stxt.h = 0;
	D->stxt.w = 0;
	D->string.cursor = 0;
	D->nbut = 1;
	D->numb = 0;
	D->type = 0;
}

int get_type(char *argv[], int* type, int n)
{
	int er = 0;
	*type = parse_number(argv[n], &er);

	if (er != 0)
	{
		return INCORECT_TYPE;
	}

	return 0;
}
int get_file(char *argv[], FILE *F, int n)
{
	F = fopen("argv[n]", "r");
	if (F == NULL)
	{
		return ERROR;
	}
	return 0;
}
int get_title(char *argv[], char* T, int n)
{
	T = (char*)malloc(strlen(argv[n])*sizeof(char));
	if (NULL == T)
	{
		return NO_MEMORY;
	}
	int i = 0, k = 0;
	for (i = 0; i < strlen(argv[n]); i++)
	{
		T[k] = argv[n][i];
	}
	return 0;
}
int get_but(char *argv[], button* but, int *bn, int n)
{
	*bn++;
	if (NULL == but)
	{
		but = (button*)malloc(*bn*sizeof(but));
		if (NULL == but)
		{
			return NO_MEMORY;
		}
	}
	else
	{
		but = (button*)realloc(but, *bn*sizeof(but));
		if (NULL == but)
		{
			return NO_MEMORY;
		}
	}
	but[*bn - 1].text = (char*)malloc(sizebut*sizeof(char));
	if (NULL == but[*bn - 1].text)
	{
		return NO_MEMORY;
	}
	if (strlen(argv[n]) > sizebut)
	{
		return BUTTON_TEXT_TOO_LONG;
	}
	for (int i = 0; i < strlen(argv[n]); i++)
	{
		but[*bn - 1].text[i] = argv[n][i];
	}
	int e = 0;
	but[*bn - 1].ret = parse_number(argv[n + 1], &e);
	if (e != 0)
	{
		return INCORECT_RET;
	}
	return 0;
}
int get_text(char *argv[], char* txt, int n)
	{
		
		txt = (char*)malloc(strlen(argv[n])*sizeof(char));
		if (NULL == txt)
		{
			return NO_MEMORY;
		}

		for (int i = 0; i < strlen(argv[n]); i++)
		{
			txt[i] = argv[n][i];
		}
		return 0;
	}
// C:\Users\Alexei>dialog.exe -text "he  llo" -longtext a.txt -button "OK" 0 -button "Cancel" 1 -title "title" 
int get_arg(char* T, char* txt, FILE *F, button* but, int *bn, int *type, int argc, char *argv[])
{
	int i = 1;
	int er;
	while (i < argc)
	{
		if ((strcmp(argv[i], "-text") == 0) || (strcmp(argv[i], "-longtext") == 0) || (strcmp(argv[i], "-button") == 0) || (strcmp(argv[i], "-type") == 0) || (strcmp(argv[i], "-title") == 0))
		{
		
			if (strcmp(argv[i], "-type") == 0)
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

			if (strcmp(argv[i], "-longtext") == 0)
			{
				i++;
				if (i > argc)break;

				er = get_file(argv,F, i);
				if (er != 0)
				{
					return er;
				} 
				i++;
				if (i > argc)break;
			
			}
			if (strcmp(argv[i], "-title") == 0)
			{
				i++;
				if (i > argc)break;
				er=get_title(argv, T, i);
				if (er != 0)
				{
					return er;
				}
				i++;
				if (i > argc)break;
									
			}
			if (strcmp(argv[i], "-button") == 0)
			{
	
				i++;
				if (i > argc)break;
				er = get_but(argv, but,bn, i);
				if (er != 0)
				{
					return er;
				}
				i += 2;
				if (i > argc)break;
				
			}
			if (strcmp(argv[i], "-text") == 0)
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