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
	D->stxt.w = 10;
	
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
		return NO_MEMORY;
	}
	for (e = 0; e < D->stxt.h;e++)
	{
		D->text[e] = (char*)malloc((D->stxt.w)*sizeof(char));
		if (NULL == D->text[e])
		{
			return NO_MEMORY;
		}
	}
	
	int i = 0, j = 0, k = 0;
	
	do
	{
		if (j > D->stxt.h-1)																
		{
			D->stxt.h++;
			D->text = (char**)realloc(D->text, (D->stxt.h)*sizeof(char*));
			if (NULL == D->text)
			{
				return NO_MEMORY;
			}
			for (e; e < D->stxt.h;e++)
			{
				D->text[e] = (char*)malloc((D->stxt.w)*sizeof(char));
				if (NULL == D->text[e])
				{
					return NO_MEMORY;
				}
			}
			/*if (D->text == NULL)
			{
				return NO_MEMORY;
			}*/
		}
		/*int o = 1;
		while (str[k + D->stxt.w - o] != ' ')
		{
			o++;
		}										*///чтобы разделения были по целым словам
		for (i = 0; i < D->stxt.w - 1; i++)
		{
			if (str[k] == '\n' || str[k] == '\r')
			{
				k++;
				break;
			}
			if (str[k] == '\0') 
			{
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
	if (NULL==D->but)
	{
		D->but = (button*)malloc((D->numb + 1)*sizeof(button));
	}
	else
	{
		D->but = (button*)realloc(D->but,(D->numb + 1)*sizeof(button));
	}
	if (NULL == D->but)
	{
		return NO_MEMORY;								
	}
	//for (int t = 0; t < D->numb; t++)
	//{
	//	if (D->but[D->numb].ret == reture) return INCORECT_RET; // возращаемое значение уже существует
	//}
	D->but[D->numb].ret = retur;
	int len = strlen(txt);
	if (sizebut < len)
	{
		return BUTTON_TEXT_TOO_LONG;							
	}
	D->but[D->numb].text= (char*)malloc((len+1)*sizeof(char));
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
			D->slong.h = D->stxt.h;	//-1 
			D->slong.w = D->stxt.w;
			
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
			}
			for (int i = 0; i < D->stxt.h; i++)
			{
				free(D->text[i]);
				
			}
			D->stxt.h = 0;
			D->stxt.w = 0;
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
		for (int i = 0; i < D->numb; i++)
		{
			free(D->but[i].text);
		}
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

