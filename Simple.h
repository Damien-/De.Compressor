#ifndef _Simple_h_
#define _Simple_h_

#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <conio.h>
void ConPrint(char *CharBuffer, int len);   //prints at current pos <useless>
void ConPrintAt(int x, int y, char *CharBuffer, int len); //print @ (x,-y) <useless>
void gotoXY(int x, int y); //goes to (x,y), x scaled to right, y scaled downward <useful>
void ClearConsole(void); // <useed>
void ClearConsoleToColors(int ForgC, int BackC); // <useed>
void SetColorAndBackground(int ForgC, int BackC);  //background color and collor of simbols
void SetColor(int ForgC); 
void GetStringWindow(char newDir[MAX_PATH]);
void CmpPrnt();
void OnePrintZ();
void Help();
void HideTheCursor(void);
void ShowTheCursor(void);
int Select(COORD cursor);
void Deselect(COORD cursor);
int Initial(void);
void About();
void Exiting();

#endif