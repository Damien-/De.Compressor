#ifndef _Move_h_
#define _Move_h_
#include "c_dec.h"
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <conio.h>
#include "Simple.h"
#include "Structs.h"

#define BGColor 2
#define FGColor 7
#define SelLen 37
#define flagtag 37
#define globLen 30

COORD GoingUp(COORD cursor);
COORD GoingDown(COORD cursor);
COORD Switch_TAB(COORD cursor);
COORD Add(COORD cursor,COORD stackP,int **p,int *curPos);
void AddToCList(Pcvor *right, Pcvor POS);
COORD Rem(COORD cursor,COORD stackP, int **p,int curPos);
void CNFA(InFile *f);
void ConvertNames(Pcvor tab, InFile *file);

#endif