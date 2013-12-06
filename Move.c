#include "c_dec.h"
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <conio.h>
#include "Simple.h"

#include "Move.h"
#define BGColor 2
#define FGColor 7
#define SelLen 37
#define flagtag 37
#define globLen 30 // array len for rem check

void CNFA(InFile *f)
{
	int i;
	for (i=0;i<f->size; i++) {
		free (f->path[i]);
		f->path[i] = NULL;
		free (f->name[i]); 
		f->name[i] = NULL;
	}
	free (f->name); f->name = NULL;
	free (f->path); f->path = NULL;
}
void ConvertNames(Pcvor tab, InFile *file)
{
	Pcvor tek=tab;
	int i,k,y;
	if(!tab) return;
	file->size=tab->len;
	file->path=malloc(file->size*sizeof(char*));
	file->name=malloc(file->size*sizeof(char*));
	for(i=0;i<file->size;i++)
	{
		k=strlen(tek->folder);
		y=strlen(tek->file);
		file->path[i]=malloc((k+1)*sizeof(char));
		file->name[i]=malloc((y+1)*sizeof(char));
		strcpy(file->path[i],tek->folder);
		file->path[i][k] = '\0';
		strcpy(file->name[i],tek->file);
		file->name[i][y] = '\0';

		while(file->path[i][k]!='\\')
		k--;
		
		if(file->path[i][k-1]==':')
		{
			file->path[i][k]='\\'; k++;
			file->path[i][k]='\0';
		}
		else
		file->path[i][k]='\0';
		
		tek = tek->next;

	}
}
COORD Switch_TAB(COORD cursor)
{
	COORD temp;
	temp.X=cursor.X;
	temp.Y=cursor.Y;
	if(cursor.X==2){
		Deselect(cursor);
		cursor.X=42;
		cursor.Y=5;
		if(!Select(cursor)){
			cursor.X=temp.X;
			cursor.Y=temp.Y;
			Select(cursor);
		}
		Deselect(cursor);
	}
	else
	if(cursor.X=42){
		Deselect(cursor);
		cursor.X=2;
		cursor.Y=5;
		Select(cursor);
	}
	FlushConsoleInputBuffer(GetStdHandle(STD_OUTPUT_HANDLE));
	fflush(stdin);
	return cursor;
}
COORD GoingUp(COORD cursor)
{

	if(cursor.Y-1>4){
		Deselect(cursor);
		cursor.Y-=1;
		if(!Select(cursor)){
			cursor.Y+=1;
			Select(cursor);}
	}
	FlushConsoleInputBuffer(GetStdHandle(STD_OUTPUT_HANDLE));
	fflush(stdin);
	return cursor;
}
COORD GoingDown(COORD cursor)
{
	if(cursor.Y+1<20){
		Deselect(cursor);
		cursor.Y+=1;
		if(!Select(cursor)){
			cursor.Y-=1;
			Select(cursor);}
	}
	FlushConsoleInputBuffer(GetStdHandle(STD_OUTPUT_HANDLE));
	fflush(stdin);
	return cursor;
}
COORD Add(COORD cursor,COORD stackP,int **p,int *curPos)
{

	int i;
	char CharBuf[SelLen+1];
	DWORD num_read;

	ReadConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), (LPTSTR) CharBuf, (DWORD) SelLen, cursor, (LPDWORD) &num_read);
	if(CharBuf[2]!='.')
		if(CharBuf[flagtag-1]!=15)
		{
			CharBuf[flagtag-1]=15;
			(*p)[*curPos]=cursor.Y;
			gotoXY(cursor.X,cursor.Y);
			for(i=0;i<SelLen;i++)
				printf("%c",CharBuf[i]);
			CharBuf[flagtag-1]=32;
			SetColorAndBackground(FGColor, BGColor);
			gotoXY(stackP.X,stackP.Y);
			for(i=0;i<SelLen;i++)
				printf("%c",CharBuf[i]);
			stackP.Y+=1;
			(*curPos)++;
		}
		return stackP;
}
void AddToCList(Pcvor *right, Pcvor tek)
{
	Pcvor novi,last; int i;
	last=*right;
	while(last)
	{
		if(strcmp(last->folder,tek->folder)==0)
			if(strcmp(last->file,tek->file)==0)
				return;
		last=last->next;
	}
	last=*right;
	novi=(Scvor*)malloc(sizeof(Scvor));
	strcpy(novi->file,tek->file);
	strcpy(novi->folder,tek->folder);
	novi->num=tek->num; 
	if(last)
		while(last->next)
			last=last->next;

	if(*right==NULL) {
		*right=novi;
		(*right)->former=NULL;
		(*right)->next=NULL;
		(*right)->len=1;
		(*right)->num=0;
	}
	else {	
		last->next=novi; 
		last->next->former=last;
		(*right)->len+=1;
		last->next->num=last->num+1;
	}
	last=novi;
	last->next=NULL;
}
COORD Rem(COORD cursor,COORD stackP, int **p,int curPos)
{
	int j,k,i=cursor.Y;
	char CharBuf[SelLen+1];
	DWORD num_read;
	k=i;
	if(i>4){
		Deselect(cursor);
		gotoXY(1+flagtag,(*p)[cursor.Y-5]);
		putchar(32);
		for(i=cursor.Y-5;i<curPos-1;i++)
			(*p)[i]=(*p)[i+1]; 
		for(i=cursor.Y;i<stackP.Y;i++)
		{
			gotoXY(cursor.X,cursor.Y);
			cursor.Y+=1;
			ReadConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), (LPTSTR) CharBuf, (DWORD) SelLen, cursor, (LPDWORD) &num_read);
			cursor.Y-=1;
			//	if(CharBuf[flagtag-1]!=15){
			//	CharBuf[flagtag-1]=15;
			gotoXY(cursor.X,cursor.Y);
			SetColorAndBackground(FGColor, BGColor);
			for(j=0;j<SelLen;j++)
				printf("%c",CharBuf[j]);
			cursor.Y+=1;
		}
		cursor.Y-=stackP.Y-k;
	}

	stackP.Y-=1;
	return stackP;
}
