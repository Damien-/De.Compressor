#ifndef DynamicH
#define DynamicH

#include <stdio.h>
#include "c_dec.h"


typedef struct node
{
	Index number;
	int weight;
	int id;
	struct node *left,*right;
	struct node *parent;
} Node;


void DHuffman(lzwArray numbers,FILE *fout, CompressChunk *cc, int *bit1);
void InsertNYT(Node **tree,Node **NYT);
Node * Find(Node *tree, Index next);
void TransmitCode(FILE *fout,Node* tree,Node* current,CompressChunk *cc, int *bit1);
void TransmitSymbol(FILE *fout,Index next,CompressChunk *cc, int *bit1);
void SpawnNode(Node **tree,Node *NYT,Index next);
void UpdateTree(Node **tree,Index next,Node *current, Node *NYT,int *numOfNodes);
void UpdateIDs(Node *tree,Index num);
Node * FindMaxInBlock(Node *tree, Node* current,int num);
void Swap(Node *tree, Node* max, Node* current);
int Ancestor(Node *node,Node * current);
void Dealocate(Node * tree);
void DHuffmanDecompress(FILE *fin, CompressChunk *compress_chunk, int *idx, int *bit1, lzwArray *numbers);
#endif
