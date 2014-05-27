#include"stdafx.h"
#pragma once

void get_size_window(Dialog* D, winsize* ws);
void Draw_window(Dialog* D);
int draw_title(Dialog* D);
int draw_text(Dialog* D, int y_s);
int draw_longtext(Dialog* D, int y_s);
void draw_string(Dialog* D, int y);
int print_string(Dialog* D, int y, int key);
int draw_but(Dialog* D, int y_s);
int do_Dialog(Dialog* D);
void put_string(Dialog *D);
void main(int argc, char *argv[]);