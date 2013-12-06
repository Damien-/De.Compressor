#ifndef _Structs_h_
#define _Structs_h_

#include <windows.h>
#define globLen 30
#define FGColor 7
#define BGColor 2
#define SelLen 37

#define itemNum 13



typedef struct cvor
{
	char folder[MAX_PATH], file[MAX_PATH];
	int type, transitional, num, page,len;
	struct cvor *former,*next;
}Scvor,*Pcvor;

#endif