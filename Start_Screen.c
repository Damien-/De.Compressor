//Guide to whom ever it may bravely dare to modify code below.
//At first, it was not meant to include certain lists which were added later so it might seem a bit pilled up, but it works. Works I said. 
//That's good enough.
//
//Once you are done trying to modify
//current code, please, increment the
//number below.
//
//Hours wasted:0
//
//Getch(); used to fetch the pressed keyboard, seems the most simple way to do it, so please do not bother with struct types of EVENT and similar.
//Some of the headers may not seem logical but they work. Due to some dependancies it does matter which header goes in front of which although they
//are secured with #ifndef #endif.
//
//ASCII code used mostly when prinint out interface, google it out.
//Screen counts from top left corner as (0,0) and goes on X axsys normally and inverted on Y axsys. Meaning, value incremented 
// on Y will go down whilst X will go to the right.

#include "Simple.h"
#include "c_dec.h"
#include "Move.h"
#include "Lists.h"
#include "shdecoder.h"
#include "Structs.h"
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <conio.h>
#include <strsafe.h>
#include <Shlwapi.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#pragma comment (lib, "Shlwapi.lib")

#define BH 220

#include<sys/stat.h>
#include<sys/types.h>

#define globLen 30 //huh?
#define FGColor 7
#define BGColor 2
#define SelLen 37 //CharBug

#define itemNum 13


//#define FOLDER_type 1
//#define FILE_type2

void DisplayErrorBox(LPTSTR lpszFunction) 
{ 
    // Retrieve the system error message for the last-error code

    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
    DWORD dw = GetLastError(); 

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL );

    // Display the error message and clean up

    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, 
        (lstrlen((LPCTSTR)lpMsgBuf)+lstrlen((LPCTSTR)lpszFunction)+40)*sizeof(TCHAR)); 
    StringCchPrintf((LPTSTR)lpDisplayBuf, 
        LocalSize(lpDisplayBuf) / sizeof(TCHAR),
        TEXT("%s failed with error %d: %s"), 
        lpszFunction, dw, lpMsgBuf); 
    MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK); 

    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
}
/*void List_Dir(void)
{
	WIN32_FIND_DATA ffd;
	LARGE_INTEGER filesize;
	TCHAR szDir[MAX_PATH];
	HANDLE hFind = INVALID_HANDLE_VALUE;
	DWORD dwError=0;
	int k,j,i;
	char dir[MAX_PATH],nextDir[MAX_PATH];

	GetCurrentDirectory(MAX_PATH,dir);
					k=strlen(dir);
					while(dir[k]!='\\')
						k--;
					for(j=0;j<k;j++)
						nextDir[j]=dir[j];
					szDir[j]='\0';

	
	hFind = FindFirstFile(szDir, &ffd);
	if (INVALID_HANDLE_VALUE == hFind) 
    {
      DisplayErrorBox(TEXT("FindFirstFile"));
      return;
    } 
	do
    {
      if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
      {
         _tprintf(TEXT("  %s   <DIR>\n"), ffd.cFileName);
      }
      else
      {
         filesize.LowPart = ffd.nFileSizeLow;
         filesize.HighPart = ffd.nFileSizeHigh;
         _tprintf(TEXT("  %s   %ld bytes\n"), ffd.cFileName, filesize.QuadPart);
      }
    }
    while (FindNextFile(hFind, &ffd) != 0);
	dwError = GetLastError();
   if (dwError != ERROR_NO_MORE_FILES) 
   {
      DisplayErrorBox(TEXT("FindFirstFile"));
   }

   FindClose(hFind);
   return;
}*/


int Event(COORD cur,COORD tab)

{
	char root_dir[MAX_PATH];
	InFile file,bek;
	BOOL IsDir=FALSE;
	COORD pom,cur2;
	int curpos, cpi, pomeraj;
	Pcvor left, right, twk, last=NULL;
	Pcvor POS,POS2=NULL;
	Pcvor POS1=NULL;

	char dir[MAX_PATH],nextDir[MAX_PATH], newDir[MAX_PATH]={"Extracted"};
	int posDesel=0;
	int *ffs,k,i,j, Y=0;
	BOOL succ=FALSE;
    BOOL Continue = TRUE;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
    int SpecialC;
	FILE *log=fopen("Drc.log","a");
	time_t t1,t2,t3;
	cur2.X=42; cur2.Y=5;
	time(&t1);
	
	if(log==NULL)
		log=fopen("Drc.log","w+");
	//else {fclose(log); log=fopen("Drc.log","a"); }
	fprintf(log,"Started on %s",ctime(&t1));//*/
	right=NULL;
	left=(Scvor*)malloc(sizeof(Scvor));
	GetCurrentDirectory(MAX_PATH,left->folder);
	GetCurrentDirectory(MAX_PATH, root_dir);

	strcpy(left->file,"...");

	left->transitional=0;
	//left->type=DIR_UP;
	left->next=NULL;
	left->former=NULL;
	POS=left;
	POS1=POS;
	cur.X=2; cur.Y=5;
	GetAllFiles(&left,&cur,&POS);


	ffs=malloc(globLen*sizeof(int));
    while (Continue)
    {
        SpecialC=getch();
		//Fzwez
		if(SpecialC==0)
		{
			 SpecialC=getch();
				switch(SpecialC){
					case 59:{
							 Deselect(cur); 
							 About();// Initial();   //enhance please  <---------------- HERE FFS -- fixed
							 RefreshMain(left,POS1);// RePrint(left);
							 RefreshTab(right,POS2);//RePrintRight(right);
							 Select(cur); break;//F1 ABOUT
							}
					case 60:{	
								gotoXY(0,0);	
								printf("%s    %d",POS->file,POS->num); //putch(SpecialC);
								
								
								Select(cur);
												break;}//F2
					case 62:{
								CmpPrnt();
								OnePrintZ();
								RefreshMain(left,POS1);
								RefreshTab(right,POS2);
								Select(cur);
						
						break;}//F4
					case 63:{	
						if(!right) break;
						GetCurrentDirectory(MAX_PATH,dir);
						GetStringWindow(newDir);
						strcat(newDir,".drc");
						ConvertNames(right,&file);
						CmpPrnt();
						time(&t1);
						t2=clock();
						fprintf(log,"%s - compression of %s started.\n",ctime(&t1),newDir);
						Compress(file, newDir, root_dir);
						SetCurrentDirectory(dir);
						t3=clock();
						OnePrintZ();
						fprintf(log,"\tDuration: %lf.",(double)((t3-t2)/1000));
						curpos=POS->num;
						GetAllFiles(&left,&cur,&POS);
						for(cpi=0;cpi<curpos;cpi++)
								POS=POS->next;
						pomeraj=0; twk=POS;
						if(POS->former)
						while((twk->num-1)%13){
								twk=twk->former; pomeraj++; }
						POS1=POS;
						cur.Y=6+pomeraj;
						RefreshMain(left,POS1);
						RefreshTab(right,POS2);
						CNFA (&file);
						Select(cur);
						break;}//F5
					case 64:{
						if(cur.X==2){
							if(strstr(POS->file,".drc")==0) break;
							 ConvertNames(POS,&bek);
							time(&t1);
							t2=clock();
							fprintf(log,"%s - decompression of %s started.\n",ctime(&t1),bek.name[0]);
							Decompress(bek, root_dir);
							t3=clock();
							fprintf(log,"\tDuration: %lf.",(double)(t3-t2));
							SetCurrentDirectory(bek.path[0]);
							curpos=POS->num;
							GetAllFiles(&left,&cur,&POS);
							for(cpi=0;cpi<curpos;cpi++)
									POS=POS->next;
							pomeraj=0; twk=POS;
							while((twk->num-1)%13){
									twk=twk->former; pomeraj++; }
							POS1=POS;
							cur.Y=6+pomeraj;
							RefreshMain(left,POS1);
							RefreshTab(right,POS2);//*/
							Select(cur);
							CNFA (&bek);
							 
							
							 break;//F6
							}
					}
					case 66:{putch(SpecialC); break;}//F8
					case 67:{Deselect(cur); 
							 Help();
							 RefreshMain(left,POS1);
							 RefreshTab(right,POS2);
							 Select(cur); break;}//F9 HELP
					case 68:{Continue=FALSE;	
								SetColorAndBackground(FGColor, BGColor);
								Exiting();	break;}//F10 EXIT
				}
		}
		//SPACE
		if(SpecialC==32){
			if(cur.X==2)
			{
				if(cur.Y==5){
					GetCurrentDirectory(MAX_PATH,(LPWSTR)dir);
					k=strlen(dir);
					/*if(k==3) 
					{
						SetCurrentDirectory("PC");
						GetAllFiles(&left,&cur,&POS);
						gotoXY(6,1);
						SetColorAndBackground(FGColor, BGColor);
						puts("Computer");
						POS=left;
						POS1=POS;
						cur.Y=5;
						Select(cur);
						continue;
					}*/
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
					GetAllFiles(&left,&cur,&POS);
					gotoXY(6,1);
					SetColorAndBackground(FGColor, BGColor);
					puts(nextDir);
				
					POS=left;
					POS1=POS;
					cur.Y=5;
					Select(cur);
					continue;
				}
				if(cur.Y>5){    
				succ=Enter_Dir(cur,left);
				if(succ) {
					Deselect(cur);
					GetAllFiles(&left,&cur,&POS); 
					POS1=POS;
					succ=FALSE;
					/**/ continue;}
				}
				else continue;
				 //ADD
				AddToCList(&right,POS);
				if(POS2==NULL) POS2=right;
				RefreshTab(right,POS2);

			}
			else
				if(cur.X==42)
				{
					if(POS->next) Y=0; else Y=1;
					Extract(&right,&POS);
					RefreshTabE(right,left,&POS,&cur,&POS2,Y);
					POS2=POS;
					if(POS==NULL){
						cur=Switch_TAB(cur);
						POS=left;
					}
						FlushConsoleInputBuffer(GetStdHandle(STD_OUTPUT_HANDLE));
						fflush(stdin);
				}
		}
		//TAB
		if(SpecialC==9)
		{
			pom.X=cur.X; 
			pom.Y=cur.Y; 
			Deselect(cur); 
			cur=Switch_TAB(cur);
			if(pom.X!=cur.X)
				if((pom.X-cur.X)==40)
					{POS2=POS; POS=left; cur2.X=pom.X; cur2.Y=pom.Y;} 
				else {	POS1=POS; cur.X=cur2.X; cur.Y=cur2.Y; POS=POS2;} 
			Select(cur);
		} //printf("TAB"); //SWITCH TAB
		//UP-DOWN
		if(SpecialC==224){
			SpecialC=getch();
			if(SpecialC==72){
				if (i=RefreshTabUp(POS,cur)) {POS=POS->former;	POS1=POS; cur.Y=18; Select(cur);if(cur.X==42) POS2=POS; continue;}
				pom.Y=cur.Y;
				cur=GoingUp(cur); 	//printf("UP");
				if(pom.Y-cur.Y)
					POS=POS->former;
				if(cur.X==2)
					POS1=POS;
				if(cur.X==42)
					POS2=POS;
			}
			if(SpecialC==80){
				if(POS->next) if (i=RefreshTabDown(POS,cur)) {POS=POS->next; cur.Y=6; Select(cur);if(cur.X==42) POS2=POS; continue;}
				pom.Y=cur.Y;
				cur=GoingDown(cur); //printf("DAUN");	//
				if(cur.Y-pom.Y)
					POS=POS->next;
				if(cur.X==42)
					POS2=POS;
				if(cur.X==2)
					POS1=POS;
			}
		FlushConsoleInputBuffer(GetStdHandle(STD_OUTPUT_HANDLE));
		fflush(stdin);
		}
	}
	free(ffs);
	FAM(&left);
	if(right!=NULL)
		FAM(&right);
	time(&t2);
	fprintf(log,"Finished on %s",ctime(&t2));
	fclose(log);
	return 1;
}

int main(int argc, char* argv[])
{	
	FILE *log;
	COORD cur, SelectedP;
	int checkstart;
	SelectedP.X=42;
	SelectedP.Y=5;
	checkstart=Initial();
	if(!checkstart) printf("Failed initialization, press any key to exit...");
	ConPrintAt(2,5,"...",4);
	HideTheCursor();
	cur.X=2; cur.Y=7; 
	Select(cur);
	Event(cur,SelectedP);
    return 0;
}

void PrintDOTz()
{
	gotoXY(2,5);
	printf("...                                  ");
}
// Fix directory up to get back to selecet current that is being exited.
// Function that rewrites up with DOTDOTDOT. --------------------------------------
// compress.c added #include "dh.c"  ----------------------------------------------
// Added pf DOTS in GetAllFiles, also redo as PrintfDOTz.
// Retrun from right to left goes to DOTDOTDOT. Fix needed.

//*/
