#include"stdafx.h"

void main(int argc, char *argv[])
{

	Dialog D;
	button * but = NULL;
	char* txt =NULL;
	char* T = NULL;
	FILE *F = NULL;
	int ret;
	int type=0;
	int num = 0;
	/*T = "Dialog";
	txt = "qqq qq  q q q  q q  q q q q q q q q q  q q   q   q q q q q q q q  q q q q q q q  qq  q q q q q q  q q q q q q q  q q q Advanced Features There are several more things that dialog can do.You can create and use a dialogrc file to customize the color and appearance of the dialog boxes.Dialog also supports displays that do not provide color or graphics characters.The details are given in the man page.Dialog is “8 - bit clean”, meaning that that international character sets other than the standard US ASCII are supported.More ApplicationsFor some longer examples of using dialog you can look at the sample scripts included with the dialog source code.Under Slackware Linux, the system configuration scripts can be found in / usr / lib / setup.There are undoubtedly many possible uses for dialog.You could, for example, create a fully menu - driven interface for Linux users not familiar with shell commands.This could even be expanded into a simple bulletin board system that allowed users to read mail and Usenet news, edit files, etc.The example sound driver script could be expanded into a tool for configuring all of the kernel compile options.Incidently, dialog is reasonably portable and should run with minimal changes on any Unix - compatible system that has a curses library.It can also be used from any shell script language.";
	F = fopen("Text.txt","r");*/
	int er=get_arg(&T, &txt, &F, &but, &num, &type, argc, argv);
	if (er != 0)
	{
		printf("1-%d",er);
		return;
	}
	
	int A = create_Dialog(&D, type, T, txt, F);
	if (A != 0)
	{
		printf("2-%d",A);
		return ;
	}
	free(txt);
	free(T);
	if (F != NULL)
	{
		fclose(F);
	}
	if (but != NULL)
	{

		for (int i = 0; i < num; i++)
		{
			A = add_but(&D, but[i].ret, but[i].text);
			free(but[i].text);
			if (A != 0)
			{
				printf("b-%d", A);
				return;
			}
		}
	}
	ret = do_Dialog(&D);
	if (ret == 1)
	{
		put_string(&D);
	}
	del_Dialog(&D);
	con_initPair(1, CON_COLOR_WHITE, CON_COLOR_BLACK);
	con_setColor(1);
	con_showCursor();
	con_gotoXY(1, 1);
	}
/*char *T = "Main menu";
Dialog D;
create_Dialog(&D, 0, T, NULL, NULL);
add_but(&D, 0, "New game");
add_but(&D, 1, "Continue game");
add_but(&D, 1, "Exit");
int ret = do_Dialog(&D);
del_Dialog(&D);
return;
}*/
