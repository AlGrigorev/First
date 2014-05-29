#include "stdafx.h"
#define SOUND 0

void get_size_window(Dialog* D, winsize* ws)
{
	ws->w = 30;
	ws->h = 4;
	if (D->text != NULL)
	{

		if (D->stxt.w > ws->w - 4)
		{
			ws->w = D->stxt.w + 4;
		}

		for (int ij = 0; ij < D->stxt.h; ij++)
		{
			if (D->text[ij] != NULL)
			{
				ws->h++;
			}
		}
	}
	if (NULL != D->longtext)
	{
		ws->h += LONG_SIZE_h + 2;
		ws->w = sizestring + 4;

	}
	ws->h += D->numb;
	if (D->type == 1)
	{
		ws->h = ws->h + 3;
		ws->w = sizestring + 4;
	}
}
void Draw_window(Dialog* D)
{

	winsize ws;
	int x, y, max_x, max_y;
	get_size_window(D, &ws);
	if (ws.h > 50)return;
	con_init();
	con_hideCursor();
	con_initPair(7, CON_COLOR_BLUE, CON_COLOR_WHITE);	//окно
	con_initPair(9, CON_COLOR_BLACK, CON_COLOR_WHITE);	//кнопки
	con_initPair(11, CON_COLOR_WHITE, CON_COLOR_BLUE);	//строка
	con_getMaxXY(&max_x, &max_y);
	while (max_x < ws.w || max_y < ws.h)
	{
		con_clearScr();
		con_gotoXY(max_x / 2 - 20, max_y / 2);
		con_setColor(7);
		con_outTxt("Please extend consoles window and press ENTER\n");
		con_getMaxXY(&max_x, &max_y);
		if (con_getKey() == '\r')
		{
			con_clearScr();
			con_getMaxXY(&max_x, &max_y);
		}
		//con_clearScr();
	}
	//con_clearScr;
	for (x = (max_x - ws.w) / 2; x <= (max_x + ws.w) / 2; x++)
	{
		for (y = (max_y - ws.h) / 2; y <= (max_y + ws.h) / 2; y++)
		{
			if (x == (max_x - ws.w) / 2 || x == (max_x + ws.w) / 2)
			{
				con_setColor(7);
				con_gotoXY(x, y);
				con_outTxt("\xB3");//|
			}
			else if (y == (max_y - ws.h) / 2 || y == (max_y + ws.h) / 2)
			{
				con_setColor(7);
				con_gotoXY(x, y);
				con_outTxt("\xC4");//-
			}
			else if (x != (max_x - ws.w) / 2 || x != (max_x + ws.w) / 2 || y != (max_y - ws.h) / 2 || y != (max_y + ws.h) / 2)
			{
				con_setColor(7);
				con_gotoXY(x, y);
				con_outTxt(" ");
			}
			if (x == (max_x - ws.w) / 2 && y == (max_y - ws.h) / 2)
			{
				con_setColor(7);
				con_gotoXY(x, y);
				con_outTxt("\xDA");
			}
			if (x == (max_x + ws.w) / 2 && y == (max_y - ws.h) / 2)
			{
				con_setColor(7);
				con_gotoXY(x, y);
				con_outTxt("\xBF");
			}
			if (x == (max_x - ws.w) / 2 && y == (max_y + ws.h) / 2)
			{
				con_setColor(7);
				con_gotoXY(x, y);
				con_outTxt("\xC0");
			}
			if (x == (max_x + ws.w) / 2 && y == (max_y + ws.h) / 2)
			{
				con_setColor(7);
				con_gotoXY(x, y);
				con_outTxt("\xD9");
			}
		}
	}//рисует окно
}
int draw_title(Dialog* D)
{
	winsize ws;
	get_size_window(D, &ws);
	if (ws.h > 50)return ERROR;

	int max_x, max_y, x, y;
	con_getMaxXY(&max_x, &max_y);

	y = (max_y - ws.h) / 2 + 1;

	if (NULL != D->title)
	{
		int len = strlen(D->title);
		x = (max_x - len) / 2;

		con_setColor(7);
		con_gotoXY(x, y);
		con_outTxt("%s", D->title);
		y++;
	}
	return y;
}
int draw_text(Dialog* D, int y_s)
{
	winsize ws;
	get_size_window(D, &ws);
	if (ws.h > 50)return ERROR;
	int max_x, max_y, x, y = y_s;
	con_getMaxXY(&max_x, &max_y);

	if (NULL != D->text)
	{
		int i;
		x = (max_x - ws.w) / 2 + 2;
		for (i = 0; i < D->stxt.h; i++)
		{
			if (D->text[i] == NULL)
			{
				break;
			}
			con_setColor(7);
			con_gotoXY(x, y);
			con_outTxt("%s", D->text[i]);
			y++;
		}
	}
	return y;
}
int draw_longtext(Dialog* D, int y_s)
{
	winsize ws;
	get_size_window(D, &ws);
	if (ws.h > 50)return ERROR;
	int max_x, max_y, x, y = y_s;
	con_getMaxXY(&max_x, &max_y);

	if (NULL != D->longtext)
	{
		int count = 0;
		int y_1 = y, y_2 = y + LONG_SIZE_h;
		for (y = y_1; y <= y_2; y++)
		{
			for (x = (max_x - ws.w) / 2 + 1; x <= (max_x + ws.w) / 2 - 1; x++)
			{
				con_setColor(7);
				con_gotoXY(x, y);
				con_outTxt(" ");

			}
		}
		y = y_1;

		while (y <= y_2)
		{
			if (y == y_1 || y == y_2)
			{
				for (x = (max_x - ws.w) / 2 + 1; x <= (max_x + ws.w) / 2 - 1; x++)
				{
					con_setColor(7);
					con_gotoXY(x, y);
					con_outTxt("\xC4");//-
				}
				y++;
			}
			else
			{
				if (NULL == D->longtext[count])break;
				if (count >= D->slong.h - D->numblong)
				{
					y++;
					continue;
				}
				x = (max_x - ws.w) / 2 + 1;
				con_setColor(7);
				con_gotoXY(x, y);
				con_outTxt("%s", D->longtext[D->numblong + count]);

				count++;
				y++;
			}
		}
	}
	return y;
}
void draw_string(Dialog* D, int y)
{
	winsize ws;
	get_size_window(D, &ws);
	if (ws.h > 50)return;
	int max_x, x, max_y;
	con_getMaxXY(&max_x, &max_y);
	for (x = (max_x - ws.w) / 2 + 2; x <= (max_x + ws.w) / 2 - 2; x++)
	{
		con_setColor(11);
		con_gotoXY(x, y);
		con_outTxt(" ");
	}
}
int print_string(Dialog* D, int y, int key)
{
	int n = 1, i = 0, k = 0;

	if (NULL == D->string.s)
	{
		D->string.s = (char*)malloc((sizestring + 1)*(sizeof(char)));
		if (NULL == D->string.s)
		{
			return NO_MEMORY;
		}
	}
	winsize ws;
	get_size_window(D, &ws);
	if (ws.h > 50)return ERROR;
	int max_x, max_y, x;
	con_getMaxXY(&max_x, &max_y);
	x = (max_x - ws.w) / 2 + 3;
	if (key != CON_KEY_BACKSPACE)
	{
		if (D->string.cursor > sizestring)
		{
			n = (D->string.cursor / sizestring) + 1;
		}
		if (D->string.cursor >= n*sizestring - 1)
		{
			n++;
			D->string.s = (char*)realloc(D->string.s, (n*sizestring + 10)*(sizeof(char)));
		}
		D->string.s[D->string.cursor] = key;
		D->string.cursor++;
		D->string.s[D->string.cursor] = '\0';
		if (D->string.cursor - sizestring > 0)
		{
			i = D->string.cursor - sizestring;
		}
		else
		{
			i = 0;
		}
		k = 0;
		for (i; i < D->string.cursor; i++)
		{
			con_setColor(11);
			con_gotoXY(x + k, y);
			con_outTxt("%c", D->string.s[i]);
			k++;
		}
	}
	else
	{
		if (D->string.cursor < n*sizestring / 4)
		{
			n--;
			if (n>0)
			{
				D->string.s = (char*)realloc(D->string.s, (n*sizestring + 1)*(sizeof(char)));
			}
			if (n < 1)
			{
				n = 1;
			}
		}
		if (D->string.cursor>0)
		{
			D->string.cursor--;
			D->string.s[D->string.cursor] = '\0';
			if (D->string.cursor - sizestring > 0)
			{
				i = D->string.cursor - sizestring;
			}
			else
			{
				i = 0;

			}
			k = 0;
			for (i; i < D->string.cursor; i++)
			{
				con_setColor(11);
				con_gotoXY(x + k, y);
				con_outTxt("%c", D->string.s[i]);
				k++;
			}
			if (D->string.cursor < sizestring)
			{
				con_setColor(11);
				con_gotoXY(x + D->string.cursor, y);
				con_outTxt(" ");
			}
		}
	}

	return 0;
}
int draw_but(Dialog* D, int y_s)
{
	winsize ws;
	get_size_window(D, &ws);
	if (ws.h > 50)return ERROR;
	int max_x, max_y, y = y_s;
	con_getMaxXY(&max_x, &max_y);

	if (D->numb != 0)
	{
		int but_len;
		int l = 0;
		while (l < D->numb)
		{
			if (l == D->nbut - 1)
			{
				con_setColor(7);
			}
			else
			{
				con_setColor(9);
			}
			but_len = strlen(D->but[l].text);
			con_gotoXY((max_x - but_len) / 2, y);
			con_outTxt("%s", D->but[l].text);
			y++;
			l++;
		}
	}
	return y;
}
int do_Dialog(Dialog* D)
{
	if (NULL == D)
	{
		return ERROR;
	}
	if (D->but == NULL && D->text == NULL && D->longtext == NULL && D->title == NULL && D->type != 1)
	{
		return 0;
	}
	con_clearScr();
	int key;
	int y_t, y_lt, y_s, y_b, u, o = 0;
	Draw_window(D);
	y_t = draw_title(D) + 1;
	y_lt = draw_text(D, y_t) + 1;
	if (D->type == 1)
	{
		o = 3;
	}
	y_b = draw_longtext(D, y_lt) + o;
	if (D->type == 1)
	{
		y_s = y_b - o / 2 - 1;
		draw_string(D, y_s);
	}
	u = draw_but(D, y_b);
	while (1)
	{
		key = con_getKey();
		if (key == CON_KEY_ESCAPE)
		{
			con_clearScr();
			return EXIT;
		}
		if (key == CON_KEY_UP)
		{
			if (D->nbut > 1)
			{
				D->nbut--;
				draw_but(D, y_b);
			}
			else if (D->nbut == 1)
			{
				D->nbut = D->numb;
				draw_but(D, y_b);
			}
			if (SOUND == 1)
			{
				printf(" \a ");
			}
		}
		if (key == CON_KEY_DOWN)
		{
			if (D->nbut < D->numb)
			{
				D->nbut++;
				draw_but(D, y_b);
			}
			else if (D->nbut == D->numb)
			{
				D->nbut = 1;
				draw_but(D, y_b);
			}
			if (SOUND == 1)
			{
				printf(" \a ");
			}
		}
		if (key == CON_KEY_ENTER)
		{
			if (D->numb == 0)
			{
				con_clearScr();
				return EXIT;
			}
			con_clearScr();
			return D->but[D->nbut - 1].ret;
		}
		if (key == CON_KEY_PAGEDOWN)
		{
			if (D->slong.h > D->numblong + LONG_SIZE_h)
			{
				D->numblong += LONG_SIZE_h - 3;
				draw_longtext(D, y_lt);
			}
		}
		if (key == CON_KEY_PAGEUP)
		{
			if (D->numblong > 1)
			{
				D->numblong -= LONG_SIZE_h - 3;
				draw_longtext(D, y_lt);
			}
		}
		if (((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z') || (key >= '0' && key <= '9') || key == CON_KEY_BACKSPACE || key == ' ') && D->type == 1)
		{
			int er = print_string(D, y_s, key);
			if (er != 0)break;
		}
	}
}
void put_string(Dialog *D)
{
	if (NULL == D->string.s)return;
	FILE *out;
	out = fopen("out.txt", "w");
	if (NULL == out) return;
	fputs(D->string.s, out);
	fclose(out);
	/*for (int i = 0; i < D->string.cursor; i++)
	{
	fputc(D->string.s[i], out);
	}*/

}
//int print_string(Dialog* D, int y, int key)
//{
//
//	if (NULL == D->string.s)
//	{
//		D->string.s = (char*)malloc((sizestring + 1)*(sizeof(char)));
//		if (NULL == D->string.s)
//		{
//			return NO_MEMORY;
//		}
//	}
//	winsize ws;
//	get_size_window(D, &ws);
//	if (ws.h > 50)return ERROR;
//	int max_x, max_y, x;
//	con_getMaxXY(&max_x, &max_y);
//	x = (max_x - ws.w) / 2 + 3;
//	if (key != CON_KEY_BACKSPACE)
//	{
//		if (D->string.cursor < sizestring)
//		{
//
//			D->string.s[D->string.cursor] = key;
//			D->string.cursor++;
//			D->string.s[D->string.cursor] = '\0';
//
//			con_setColor(11);
//			con_gotoXY(x + D->string.cursor - 1, y);
//			con_outTxt("%c", D->string.s[D->string.cursor - 1]);
//		}
//	}
//	else
//	{
//		if (D->string.cursor > 0)
//			D->string.cursor--;
//		D->string.s[D->string.cursor] = '\0';
//
//		con_setColor(11);
//		con_gotoXY(x + D->string.cursor, y);
//		con_outTxt(" ");
//	}
//
//	return 0;
//} //строка в 70 символов