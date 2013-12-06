#include "Simple.h"
#include "Move.h"
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <conio.h>
#include <strsafe.h>
#include <Shlwapi.h>

#define globLen 30
#define FGColor 7
#define BGColor 2
#define SelLen 37


int RefreshTabDown(Pcvor tek,COORD cursor)  //ret val
{

	int i, y;
	Pcvor novi,zmz=NULL;
	SetColorAndBackground(BGColor,FGColor);
	if(cursor.Y==18)
		//if(tek->num>13)
		{
			novi=tek->next; 
			Deselect(cursor);
			for(i=5;i<20;i++)
			{
				gotoXY(cursor.X,i); 
				printf("                                     ");
			}
			gotoXY(cursor.X,5); printf("---up---"); i=6;
			while(i<19 && novi!=NULL)
			{
				gotoXY(cursor.X,i);
				if(strlen(novi->file)>SelLen-2)
				{
					for(y=0;y<SelLen-5;y++)
						putchar(novi->file[y]);
					printf("...");
				}
				else
				printf("%s",novi->file);
				if(!novi->next) zmz=novi;
				novi=novi->next;
				if(novi) zmz=novi;
				i++;
			}
			if(zmz->next) if(i==19) {gotoXY(cursor.X,i); printf("---down---");}
			return 1;
		}
	return 0;
}
int RefreshTabUp(Pcvor tek,COORD cursor)  //ret val
{

	int i, y,k;
	Pcvor novi;
  	SetColorAndBackground(BGColor,FGColor);
	if(cursor.X==2) k=12; if (cursor.X==42) k=13;
	if(cursor.Y==6 && tek->num>k)
		{
			novi=tek->former; 
			Deselect(cursor);
			for(i=5;i<20;i++)
			{
				gotoXY(cursor.X,i); 
				printf("                                     ");
			}
			gotoXY(cursor.X,19); printf("---down---"); i=18;
			while(i>5 && novi!=NULL)
			{
				gotoXY(cursor.X,i);
				if(strlen(novi->file)>SelLen-2)
				{
					for(y=0;y<SelLen-5;y++)
						putchar(novi->file[y]);
					printf("...");
				}
				else
				printf("%s",novi->file);
				if(!novi->former) break;
				novi=novi->former;
				i--;
			}
			gotoXY(cursor.X,i);
			if(i==5)
				if(tek->num>26) {gotoXY(cursor.X,i); printf("---up---");}
				else 
					if(cursor.X==2){ gotoXY(2,i);  printf("              "); gotoXY(2,i);printf("...");}
					else {gotoXY(cursor.X,i); printf("%s",novi->file);}
			return 1;
		}
	return 0;
}
BOOL Enter_Dir(COORD cursor,Pcvor bgh)
{
	int i;
	char CharBuf[SelLen+1], curDir[MAX_PATH];
	DWORD num_read;
	ReadConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), (LPTSTR) CharBuf, (DWORD) SelLen, cursor, (LPDWORD) &num_read);
	i=SelLen;
	GetCurrentDirectory(MAX_PATH, curDir);
	while(CharBuf[i-1]==' ')
		i--;
	CharBuf[i]='\0';
	if(strlen(curDir)+3+i>=MAX_PATH)
		return FALSE;
	if(strlen(curDir)!=3)
		strcat(curDir,"\\");
	strcat(curDir,CharBuf);
	if(PathIsDirectory((LPTSTR)curDir)){
		SetColorAndBackground(FGColor, BGColor);
		SetCurrentDirectory(curDir);
		return TRUE;
	}
	return FALSE;
	//*/
}
void FAM(Pcvor *bgh)
{
	Pcvor tek;
	tek= *bgh;
	while(*bgh){
		tek=*bgh;
		*bgh=(*bgh)->next;
		tek->next=NULL;
		free(tek);
	}
}
void Extract(Pcvor *tab,Pcvor *tek)
{
	int i=0;
	Pcvor help;
	help=*tek;
	if(*tek==*tab){
		help=*tab;
		*tab=(*tab)->next;
		*tek=*tab;
		free(help);	
		if(*tab==NULL) return;
		(*tab)->former=NULL;
		help=*tab;
		while(help)
		{
			help->num=i;
			i++;
			help=help->next;
		}
		return;
	}
	(*tek)->former->next=(*tek)->next;
	if((*tek)->next!=NULL){
		(*tek)->next->former=(*tek)->former;
		(*tek)=(*tek)->next;
	}
	else{
		(*tek)->former->next=NULL;
		(*tek)=(*tek)->former;
	}
	free(help);	
	help=*tab;
	i=0;
	while(help)
	{
		help->num=i;
		i++;
		help=help->next;
	}
}
void FAHead(Pcvor *bgh)
{
	Pcvor tek,pret;
	tek= (*bgh)->next;
	(*bgh)->next=NULL;
	while(tek){
		pret=tek;
		tek=tek->next;
		free(pret);
	}
}
void GetAllFiles(Pcvor *bgh,COORD *cur, Pcvor *posffs)
{ 
	WIN32_FIND_DATA ds;
	HANDLE hDir;
	int i,y,k,j;
	char dir[MAX_PATH], nextDir[MAX_PATH];
	Pcvor novi,last=*bgh;
	SetColorAndBackground(FGColor, BGColor);
	GetCurrentDirectory(MAX_PATH,dir);
	gotoXY(6,1);
	printf("                                                                         ");
	gotoXY(6,1);
	puts(dir);
	if(strlen(dir)+3>=MAX_PATH)
		return;
	else strcat(dir,"\\*");
	hDir=FindFirstFile(dir,&ds);
	SetColorAndBackground(FGColor, BGColor);
	(*bgh)->len=1;
	(*bgh)->num=0;
	if(hDir==INVALID_HANDLE_VALUE){
		GetCurrentDirectory(MAX_PATH,dir);
		k=strlen(dir);
		while(dir[k]!='\\')
		k--;
		for(j=0;j<k;j++)
		nextDir[j]=dir[j];
		if(nextDir[j-1]==':')
		{
			nextDir[j]='\\'; j++;
			nextDir[j]='\0';
		}
		else
		nextDir[j]='\0';
		SetCurrentDirectory(nextDir);
		SetColorAndBackground(FGColor, BGColor);
		for(j=strlen(dir);j>strlen(nextDir);j--){
			gotoXY(j+5,1);
			putchar(32);
		}
		SetColorAndBackground(FGColor, BGColor);
		gotoXY(6,1);
		puts(nextDir);


		gotoXY(cur->X,cur->Y);
		printf("--- Access denied! ---");
		SetColorAndBackground(FGColor, BGColor);
		Sleep(400);
		gotoXY(cur->X,cur->Y);
		printf("--- Access denied! ---");
		SetColorAndBackground(BGColor,FGColor);
		Sleep(400);
		gotoXY(cur->X,cur->Y);
		printf("--- Access denied! ---");
		SetColorAndBackground(FGColor, BGColor);
		Sleep(400);
		gotoXY(cur->X,cur->Y);
		printf("--- Access denied! ---");
		SetColorAndBackground(BGColor,FGColor);
		Sleep(700);
		gotoXY(cur->X,cur->Y);
		printf("                                     ");
		gotoXY(cur->X,cur->Y);
		printf("%s",(*posffs)->file);
		SetColorAndBackground(BGColor,FGColor);
		Select(*cur);
		//PRINT CAN'T ACCESS, NO PRIVILEGES
		return;
	}
	gotoXY(2,5); printf("...      ");
	if(strcmp(dir,"C:")==0) strcat(dir,"\\*");

	FAHead(bgh);
	for(i=6;i<20;i++)
	{
		gotoXY(2,i); 
		printf("                                     ");
	}
	FindNextFile(hDir,&ds);
	FindNextFile(hDir,&ds);
	i=0;
	do	
	{
		dir[strlen(dir)]='\0';
		novi=(Scvor*)malloc(sizeof(Scvor));
		strcpy(novi->folder,dir);
		novi->len=1;
		strcpy(novi->file,ds.cFileName);
		novi->page=i/13+1;
		novi->num=(*bgh)->len;
		(*bgh)->len++;
		/*if(ds.dwFileAttributes == FILE_ATTRIBUTE_NORMAL)
//		{ gotoXY(32,i); printf("Norm "); } // Normal
		if(ds.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE)
		{gotoXY(32,i); printf("Arc "); } // Archive
		if(ds.dwFileAttributes & FILE_ATTRIBUTE_COMPRESSED)
		{ gotoXY(32,i);printf("Cmp "); } // Compressed
		if(ds.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			novi->type=FOLDER;
		else
			novi->type=FILE;
		//{ gotoXY(32,i);	printf("<DIR> "); } // Directory
		/*
		if(ds.dwFileAttributes & FILE_ATTRIBUTE_OFFLINE)
		{ gotoXY(32,i);printf("Off "); } // Offline
		if(ds.dwFileAttributes & FILE_ATTRIBUTE_READONLY)
		{ gotoXY(32,i);printf("RO "); } //Read Only
		if(ds.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM)
		{ gotoXY(32,i);printf("Sys "); } // System
		if(ds.dwFileAttributes & FILE_ATTRIBUTE_TEMPORARY)
		{ gotoXY(32,i);printf("Tmp "); } // Temporary*/
		last->next=novi; 
		last->next->former=last;
		last=novi;
		last->next=NULL;
		i++;
	}
	while(FindNextFile(hDir,&ds)==TRUE);
	novi=(*bgh)->next; i=6;
	while(i<19 && novi!=NULL)
	{
		gotoXY(2,i);
		if(strlen(novi->file)>SelLen-2)
		{
			for(y=0;y<SelLen-5;y++)
				putchar(novi->file[y]);
			printf("...");
		}
		else
		printf("%s",novi->file);
		novi=novi->next; i++;
	
	}
	if(i==19){gotoXY(2,i); printf("---down---");}
	FindClose(hDir); 
	*posffs=*bgh;
	cur->Y=5;
	Select(*cur);
	return; 
	
}
void RePrint(Pcvor levi)
{
	int i, y;
	Pcvor novi;
	novi=levi; i=5;
	while(i<19 && novi!=NULL)
	{
		gotoXY(2,i);
		if(strlen(novi->file)>SelLen-2)
		{
			for(y=0;y<SelLen-5;y++)
				putchar(novi->file[y]);
			printf("...");
		}
		else
		printf("%s",novi->file);
		novi=novi->next;
		i++;
	
	}
	if(i==19){gotoXY(2,i); printf("---down---");}
}
void RePrintRight(Pcvor desni)
{
	int i, y;
	Pcvor novi;
	novi=desni; i=5;
	while(i<19 && novi!=NULL)
	{
		gotoXY(42,i);
		if(strlen(novi->file)>SelLen-2)
		{
			for(y=0;y<SelLen-5;y++)
				putchar(novi->file[y]);
			printf("...");
		}
		else
		printf("%s",novi->file);
		novi=novi->next; i++;
	
	}
	if(i==19){gotoXY(2,i); printf("---down---");}
}
void RefreshTab(Pcvor tab, Pcvor POS)
{
	Pcvor tek=POS;
	int y,k,i=0;
	if(!tab) return;
	if(tab->len>13 && POS->num>13)
	{
	tek=POS; 
	while((tek->num-1)%13)
		tek=tek->former;}
	SetColorAndBackground(FGColor, BGColor);
	for(i=5;i<20;i++)
	{
		gotoXY(42,i); 
		printf("                                     ");
	}
	if(tek->num<=13)
	{tek=tab; i=5;}
	else
	{
		gotoXY(42,5); printf("---up---");
		i=6;
	}
	while(i<19 && tek!=NULL){
		gotoXY(42,i); 
		if(strlen(tek->file)>SelLen-2)
		{
			for(y=0;y<SelLen-5;y++)
				putchar(tek->file[y]);
			printf("...");
		}
		else
		printf("%s",tek->file);
		/*if(!tek->next)
			zmz=tek;*/
		tek=tek->next;
		i++;
	}
	
	gotoXY(42,19); 
			printf("          ");
	

	if(tab)
	{
		//if(tab->len>13 && (tek->num<tab->len) && tek && !(tek->num+1)%14 ) 
		if(tek) if(i==19)
		{
			gotoXY(42,19); 
			printf("---down---");
		}
	}

}
void RefreshTabE(Pcvor tab,Pcvor ljevi, Pcvor *POS,COORD *cur, Pcvor *POS2, int oo)//Y Y Y Y 
{  
	Pcvor tek=NULL;
	int y,i=0;
	COORD pom;
	SetColorAndBackground(FGColor, BGColor);
	if(oo){
		
		if (i=RefreshTabUpL(*POS,*cur))
		{
			cur->Y=18; 
			Select(*cur);
			return;
		}
		else{		
			pom.Y=cur->Y;
			*cur=GoingUp(*cur); 
			SetColorAndBackground(FGColor, BGColor);
			if(pom.Y==cur->Y){
				*cur=Switch_TAB(*cur);
				*POS2=*POS; *POS=ljevi; 
				SetColorAndBackground(FGColor, BGColor);
				gotoXY(42,cur->Y); printf("                                     ");
				return;
			}
			gotoXY(42,pom.Y); printf("                                     ");
			return;
		}
	}
	/*i=5;
	if(cur.X==42)
		if(POS->num>13)
		{	tek=POS;
			gotoXY(42,5); printf("---up---"); i++;
			while(tek->num%13+1!=1)
				tek=tek->former; }
		else tek=tab;
	*/
		RefreshTab(tab,*POS);
		Select(*cur);
}
int RefreshTabUpL(Pcvor tek,COORD cursor)  //ret val
{

	int i, y;
	Pcvor novi;
	SetColorAndBackground(BGColor,FGColor);
	if(cursor.Y==6 && (!tek->num+1%14) && tek->num>2)
		{
			novi=tek; 
			Deselect(cursor);
			for(i=5;i<20;i++)
			{
				gotoXY(cursor.X,i); 
				printf("                                     ");
			}
			i=18;

			while(i>=5 && novi!=NULL)
			{
				gotoXY(cursor.X,i);
				if(strlen(novi->file)>SelLen-2)
				{
					for(y=0;y<SelLen-5;y++)
						putchar(novi->file[y]);
					printf("...");
				}
				else
				printf("%s",novi->file);
				//if(!novi->former) break;
				novi=novi->former;
				i--;
			}
			if(tek->num>13) gotoXY(42,5); printf("---up---");
			/*SetColorAndBackground(BGColor,FGColor);
			gotoXY(cursor.X,19);  printf("              "); */
			return 1;
		}
	return 0;
}
void RefreshMain(Pcvor tab, Pcvor POS)
{
	Pcvor tek=POS;
	int y,i=0;
	if(tab->len>12 && POS->num>12)
	{
	tek=POS; 
	while((tek->num-1)%13)
		tek=tek->former;
	}
	SetColorAndBackground(FGColor, BGColor);
	for(i=5;i<20;i++)
	{
		gotoXY(2,i); 
		printf("                                     ");
	}
	if(tek->num<=12)
	{tek=tab; i=5;}
	else
	{
		gotoXY(2,5); printf("---up---");
		i=6;
	}
	while(i<19 && tek!=NULL){
		gotoXY(2,i); 
		if(strlen(tek->file)>SelLen-2)
		{
			for(y=0;y<SelLen-5;y++)
				putchar(tek->file[y]);
			printf("...");
		}
		else
		printf("%s",tek->file);
		/*if(!tek->next)
			zmz=tek;*/
		tek=tek->next;
		i++;
	}
	
	gotoXY(2,19); 
			printf("          ");
	

	if(tab)
	{
		//if(tab->len>13 && (tek->num<tab->len) && tek && !(tek->num+1)%14 ) 
		if(tek) if(i==19)
		{
			gotoXY(2,19); 
			printf("---down---");
		}
	}

}