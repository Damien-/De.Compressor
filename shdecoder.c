#include "shdecoder.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Node * Tree(char *file)
{
	FILE *f = fopen(file, "r");
	int i;
	char ch, s[257];
	Node * koren = (Node*)malloc(sizeof(Node));
	Znak  znak;
	koren->left=koren->right=NULL;
	for(i=0;i<256;i++)
	{
		fscanf(f,"%u %lf %s%c",&(znak.character),&(znak.frequency), s, &ch);
		znak.code = (char *) malloc ((strlen(s)+1) * sizeof (char));
		strcpy (znak.code, s);
		UbaciUStablo(znak,koren);
	}
	fclose (f);
	return koren;
}

void UbaciUStablo(Znak zn, Node * koren)
{
	Node *tek =koren;
	char *string=zn.code;
	int i;
	
	for(i=0;i<strlen(string);i++)
	{
		if(string[i]=='1')
		{
			if(tek->right==NULL)
			{
				tek->right=(Node*)malloc(sizeof(Node));	
				tek->right->left=tek->right->right=NULL;
			}
			tek=tek->right;
		}
		else
		{
			if(tek->left==NULL)
			{
				tek->left=(Node*)malloc(sizeof(Node));
				tek->left->left=tek->left->right=NULL;
			}
			tek=tek->left;				
		}
	}
	tek->znak=zn;
}

void DeleteTree (Node *koren) {
	if (koren != NULL) 
	{
		DeleteTree (koren->left);
		DeleteTree (koren->right);
		free(koren); koren = NULL;
	}
}