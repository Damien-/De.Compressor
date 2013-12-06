#ifndef SHDECODER
#define SHDECODER

#include <stdio.h>
#include <stdlib.h>

typedef struct znak{
	unsigned char character;
	double frequency;
	char *code;
}Znak;

typedef struct node 
{
	Znak znak;
	struct node *left, *right;
} Node;

Node * Tree(char * file);
void UbaciUStablo(Znak zn, Node * koren);
void DeleteTree (Node *koren);

#endif