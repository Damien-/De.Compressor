#ifndef _Lists_h_
#define _Lists_h_

void FAM(Pcvor *bgh);
void FAHead(Pcvor *bgh);
void RefreshTabE(Pcvor tab,Pcvor ljevi, Pcvor *POS,COORD *cur, Pcvor *POS2, int oo);
void RefreshTab(Pcvor tab, Pcvor POS);
void Extract(Pcvor *tab,Pcvor *tek);
void RePrintRight(Pcvor desni);
void RePrint(Pcvor levi);
void GetAllFiles(Pcvor *bgh,COORD *cur, Pcvor *posffs);
BOOL Enter_Dir(COORD cursor,Pcvor bgh);
int RefreshTabDown(Pcvor tek,COORD cursor);
int RefreshTabUp(Pcvor tek,COORD cursor);
void RefreshMain(Pcvor tab, Pcvor POS);

#endif