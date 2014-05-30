#include "stdafx.h"
#pragma once
#define NO_MEMORY 1						//��� ������
#define TOO_LONG_TITLE 2
#define TOO_LONG_TEXT 3
#define BUTTON_TEXT_TOO_LONG 4
#define INCORECT_TYPE 5
#define INCORECT_RET 101
#define ERROR 999 //����������� ���� ������

#define LONG_SIZE_h 10 //��������� ��������� 
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
	int numb = 0;	// ���-�� ������
	int nbut=1;
	char *title = NULL;
	char **text = NULL;	//������ �����
	sizetxt stxt;   // ��������� ������
	char **longtext = NULL;
	sizetxt slong;
	int numblong=0;	//��������� �� ������ ������������� ���������
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

