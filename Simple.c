#include "Simple.h"
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <conio.h>
#define BGColor 2
#define FGColor 7
#define SelLen 37
#define BH 220
#define itemNum 13
void CmpPrnt()
{
	int i,j,y;
	SetColorAndBackground(FGColor, BGColor);
	for(i=10;i<13;i++) 
	{
		gotoXY(21,i);
		printf("                                        ");
	}
	gotoXY(20,9);
	putchar(201);for(i=0;i<38;i++)putchar(205); putchar(187);
	for(i=10;i<11;i++) {gotoXY(20,i); putchar(186);gotoXY(59,i); putchar(186);}
	gotoXY(20,i); putchar(204); for(i=0;i<38;i++)putchar(205); putchar(188);
	i++;
	gotoXY(20,11); putchar(204); for(i=0;i<38;i++) putchar(205); putchar(185);
	gotoXY(20,12); putchar(186); gotoXY(59,12);  putchar(186); 
	gotoXY(20,13); putchar(200); for(i=0;i<38;i++) putchar(205); putchar(188);
	

	gotoXY(22,10);
		printf("Compressing, please wait...");
	//gotoXY(22,12);
	//	printf("\t\tPlease wait...");
	SetColorAndBackground(FGColor, BGColor);
	for(i=0;i<38;i++)
	{
		gotoXY(21,12);
		for(j=0;j<i;j++) putchar(32);
		if(i>2 && i <35) {putchar(BH);putchar(BH);putchar(BH);}
		if(i==2) {putchar(BH);putchar(BH);}
		if(i==1) putchar(BH);
		if(i==35){putchar(BH);putchar(BH);}
		if(i==36) putchar(BH);
		Sleep(60);
	}

}
void OnePrintZ()
{
	int i,j;

	for(i=9;i<14;i++) 
	{
		gotoXY(20,i);
		printf("                                          ");
		gotoXY(39,i); putchar(186);
	}
}
void GetStringWindow(char newDir[MAX_PATH])
{

	int i,j,y;
	int LJEVO=15;
	int DJESNO=64;
	SetColorAndBackground(FGColor, BGColor);
	for(i=10;i<13;i++) 
	{
		gotoXY(LJEVO+1,i);
		printf("                                                 ");
	}
	SetColorAndBackground(FGColor, BGColor);
	gotoXY(LJEVO,9);

	putchar(201);for(i=0;i<DJESNO-LJEVO-1;i++)putchar(205); putchar(187);
	for(i=10;i<11;i++) {gotoXY(LJEVO,i); putchar(186); gotoXY(DJESNO,i); putchar(186);}
	gotoXY(LJEVO,i); putchar(204); for(i=0;i<DJESNO-LJEVO-1;i++)putchar(205); putchar(185);
	gotoXY(LJEVO,12); putchar(186); gotoXY(DJESNO,12);  putchar(186); 
	gotoXY(LJEVO,13); putchar(200); for(i=0;i<DJESNO-LJEVO-1;i++) putchar(205); putchar(188);
	SetColorAndBackground(FGColor, BGColor);

	gotoXY(LJEVO+1,10);
		printf(" Enter name of new archive:");
	gotoXY(LJEVO+1,12); ShowTheCursor();
	scanf("%s",newDir); HideTheCursor();
	Sleep(400);
	for(i=9;i<20;i++) 
	{
		gotoXY(LJEVO,i);
		printf("                                                    ");
		gotoXY(39,i); putchar(186);
	}
}
void About()
{
	int i;
	SetColorAndBackground(FGColor, BGColor);
	for(i=6;i<19;i++) 
	{
		gotoXY(21,i);
		printf("                                      ");
	}
	gotoXY(20,5);
	putchar(201);for(i=0;i<38;i++)putchar(205); putchar(187);
	for(i=6;i<19;i++) {gotoXY(20,i); putchar(186);gotoXY(59,i); putchar(186);}
	gotoXY(20,i); putchar(200); for(i=0;i<38;i++)putchar(205); putchar(188);


	gotoXY(22,6);
		printf("Project PP2 <DRC> v1.0 - 2011");
	gotoXY(22,8);
		printf("Compressing and decompressing tools");
	gotoXY(22,10);
		printf("Liljana Rajicic");
	gotoXY(22,11);
		printf("Matija Prekajski");
	gotoXY(22,12);
		printf("Damnjan Nikolic");
	gotoXY(22,14);
		printf("With great thanks to mentoring team!");
	gotoXY(22,17);
		printf("University of Electrical Engineering");
	gotoXY(22,18);
		printf("in Belgrade");
	fflush(stdin);
	getch();
	for(i=5;i<20;i++) 
	{
		gotoXY(20,i);
		printf("                                         ");
		gotoXY(39,i); putchar(186);
	}

}
void Help()
{
	int i;
	SetColorAndBackground(FGColor, BGColor);
	for(i=6;i<19;i++) 
	{
		gotoXY(21,i);
		printf("                                      ");
	}
	gotoXY(20,5);
	putchar(201);for(i=0;i<38;i++)putchar(205); putchar(187);
	for(i=6;i<19;i++) {gotoXY(20,i); putchar(186);gotoXY(59,i); putchar(186);}
	gotoXY(20,i); putchar(200); for(i=0;i<38;i++)putchar(205); putchar(188);


	gotoXY(22,6);
		printf("-Space is used to open folders and");
	gotoXY(22,7); printf("select or deselect files");
	gotoXY(22,9);
		printf("-Folders are not supposed to be added");
	gotoXY(22,11);
		printf("-De\\Compression is supposed to be"); 
	gotoXY(22,12);
		printf("done only from main window (left one)"); 
	gotoXY(22,14);
		printf("-To navigate from one tab to the ");
	gotoXY(22,15);
		printf("other one, press TAB key");
	getch();
	fflush(stdin);
	for(i=5;i<20;i++) 
	{
		gotoXY(20,i);
		printf("                                         ");
		gotoXY(39,i); putchar(186);
	}

}
void Exiting()
{
	int i,j,y;
	for(i=9;i<13;i++) 
	{
		gotoXY(21,i);
		printf("                                        ");
	}
	SetColorAndBackground(FGColor, BGColor);
	gotoXY(20,8);
	putchar(201);for(i=0;i<38;i++)putchar(205); putchar(187);
	for(i=9;i<11;i++) {gotoXY(20,i); putchar(186);gotoXY(59,i); putchar(186);}
	gotoXY(20,i); putchar(204); for(i=0;i<38;i++)putchar(205); putchar(188);
	i++;
	gotoXY(20,11); putchar(204); for(i=0;i<38;i++) putchar(205); putchar(185);
	gotoXY(20,12); putchar(186); gotoXY(59,12);  putchar(186); 
	gotoXY(20,13); putchar(200); for(i=0;i<38;i++) putchar(205); putchar(188);
	

	gotoXY(22,9);
		printf("\t  Program is shutting down...");
	gotoXY(22,10);
		printf("\t\tPlease wait...");
	for(y=0;y<1;y++)
		for(i=0;i<38;i++)
		{
			gotoXY(21,12);
			for(j=0;j<i;j++) putchar(32);
			if(i>2 && i <35) {putchar(BH);putchar(BH);putchar(BH);}
			if(i==2) {putchar(BH);putchar(BH);}
			if(i==1) putchar(BH);
			if(i==35){putchar(BH);putchar(BH);}
			if(i==36) putchar(BH);
			Sleep(60);
		}
	Sleep(200);
}
int Initial(void)
{	int i;
	TCHAR failname[25];	
	char mydirectory[MAX_PATH] = {""};
	_tcscpy_s(failname, _countof( failname ), _T("StarterScreen.exe") );
	SetConsoleTitle(failname);
    ClearConsoleToColors(FGColor,BGColor);
    ClearConsole();
    gotoXY(0,0);
	putchar(201);for(i=0;i<78;i++)putchar(205); putchar(187);
	gotoXY(0,1);
	putchar(186); printf("Path:"); gotoXY(79,1); putchar(186); 
	gotoXY(0,2);
	putchar(204); for(i=0;i<38;i++)putchar(205);putchar(203);for(i=0;i<39;i++)putchar(205); putchar(185);
	putchar(186);printf(" Current folder:"); gotoXY(39,3); putchar(186);printf(" Archive:"); gotoXY(79,3);putchar(186);
	gotoXY(0,4);
	putchar(204); for(i=0;i<38;i++)putchar(205);putchar(206);for(i=0;i<39;i++)putchar(205); putchar(185);
	for(i=5;i<20;i++) {gotoXY(39,i); putchar(186);gotoXY(79,i); putchar(186);gotoXY(0,i); putchar(186);}
	gotoXY(0,20);
	putchar(204); for(i=0;i<38;i++)putchar(205);putchar(202);for(i=0;i<39;i++)putchar(205); putchar(185);
	SetColor(8  | FOREGROUND_INTENSITY); 
	printf("  Space - add/remove  ||   Tab - switch tab   ||                      \n  F1 - about          ||   F5 - compress      ||   F6  - decompress \n  F9 - help           ||   F10 - exit         ||");
	SetColor(FGColor);
	for(i=0;i<4;i++){gotoXY(0,i+20); putchar(186);gotoXY(79,i+20); putchar(186);}
	putchar(200);for(i=0;i<78;i++)putchar(205); putchar(188); gotoXY(0,0);
	if (GetCurrentDirectory(MAX_PATH, (LPWSTR)mydirectory) == 0)
      exit(1);
	//GetCurrentDirectory(MAX_PATH,mydirectory);
	gotoXY(6,1);
	puts(mydirectory);
	gotoXY(2,5);
	printf("...");

	return 1;
}
int Select(COORD cursor)
{
	int i;
	char CharBuf[SelLen+1];
	DWORD num_read;
	ReadConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), (LPTSTR) CharBuf, (DWORD) SelLen, cursor, (LPDWORD) &num_read);
 	SetColorAndBackground(BGColor,FGColor);
	if(CharBuf[0]!=' ' || CharBuf[1]!=' '){
	gotoXY(cursor.X,cursor.Y);
	for(i=0;i<SelLen;i++)
		printf("%c",CharBuf[i]);
	return 1;
	}
    return 0;
}
void Deselect(COORD cursor)
{
	int i;
	char CharBuf[SelLen+1];
	DWORD num_read;
	ReadConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), (LPTSTR) CharBuf, (DWORD) SelLen, cursor, (LPDWORD) &num_read);
 	SetColorAndBackground(FGColor,BGColor);
	gotoXY(cursor.X,cursor.Y);
	for(i=0;i<SelLen;i++)
		printf("%c",CharBuf[i]);
	FlushConsoleInputBuffer(GetStdHandle(STD_OUTPUT_HANDLE));
	fflush(stdin);
    return;
}
void ClearConsoleToColors(int ForgC, int BackC)
{
     WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     COORD coord = {0, 0};
     DWORD count;
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     SetConsoleTextAttribute(hStdOut, wColor);
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          FillConsoleOutputCharacter(hStdOut, (TCHAR) 32, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);         
          FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &count );
          SetConsoleCursorPosition(hStdOut, coord);
     }
     return;
}
void ClearConsole()
{
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     COORD coord = {0, 0};
     DWORD count;
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          FillConsoleOutputCharacter(hStdOut, (TCHAR) 32, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
          FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &count );
          SetConsoleCursorPosition(hStdOut, coord);
     }
     return;
}
void gotoXY(int x, int y)
{
     COORD coord = {x, y};
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
     return;
}
void SetColor(int ForgC)
{
     WORD wColor; 
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);     
     }
     return;
}
void SetColorAndBackground(int ForgC, int BackC)
{
     WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);; 
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);     
     return;
}
void ConPrint(char *CharBuffer, int len)
{
    DWORD count;
     WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), CharBuffer, len, &count, NULL);
     return;
}
void ConPrintAt(int x, int y, char *CharBuffer, int len)
{
     DWORD count;
     COORD coord = {x, y}; 
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     SetConsoleCursorPosition(hStdOut, coord); 
     WriteConsole(hStdOut, CharBuffer, len, &count, NULL);
     return;
}
void HideTheCursor()
{
     CONSOLE_CURSOR_INFO cciCursor;
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     
     
     if(GetConsoleCursorInfo(hStdOut, &cciCursor))
     {
          cciCursor.bVisible=FALSE;
		  SetConsoleCursorInfo(hStdOut,&cciCursor);
     }
	 
     return;
}
void ShowTheCursor()
{
     CONSOLE_CURSOR_INFO cciCursor;
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     
     
     if(GetConsoleCursorInfo(hStdOut, &cciCursor))
     {
          cciCursor.bVisible=TRUE;
		  SetConsoleCursorInfo(hStdOut,&cciCursor);
     }
	 
     return;
}