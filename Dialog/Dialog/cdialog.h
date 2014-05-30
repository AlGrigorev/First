#include "stdafx.h"
#pragma once
#define NO_MEMORY 1						//код ошибки
#define TOO_LONG_TITLE 2
#define TOO_LONG_TEXT 3
#define BUTTON_TEXT_TOO_LONG 4
#define INCORECT_TYPE 5
#define INCORECT_RET 101
#define ERROR 999 //некоректный ввод данных

#define LONG_SIZE_h 10 //параметры рисования 
#define enter_string 2
#define EXIT 101

#define sizebut 30
#define sizestring 70
#define sizetitle 70
#define sizetext 20

/*typedef struct txt
{
sizetxt s;
char** text;
}txt;*/

typedef struct sizetxt
{
	int w, h;
}sizetxt;
typedef struct button
{
	int ret;
	char* text;
}button;
typedef struct str
{
	int cursor=0;
	char* s;
}str;
typedef struct Dialog
{
	int type;
	button* but = NULL;
	int numb = 0;	// кол-во кнопок
	int nbut=1;
	char *title = NULL;
	char **text = NULL;	//массив строк
	sizetxt stxt;   // параметры текста
	char **longtext = NULL;
	sizetxt slong;
	int numblong=0;	//указывает на начало отображаемого фрагмента
	str string ;
}Dialog;
typedef struct winsize
{
	int h, w;
}winsize;


int put_text(Dialog* D, char* str);
int put_title(Dialog* D, char* str);
int correct_text(Dialog* D);
int add_but(Dialog* D, int retur, char* txt);
int put_longtext(Dialog* D, FILE* f);
int create_Dialog(Dialog *D, int t, char* T, char* txt, FILE* lt);
void del_Dialog(Dialog *D);

