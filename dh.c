#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "c_dec.h"
#include "dh.h"
#include "queue.h"


void DHuffman(lzwArray numbers, FILE *fout, CompressChunk *compress_chunk, int * bit1)
{
	Index next;
	Node * tree=NULL;
	int numOfNodes;
	int i;
	Node *NYT=NULL;
	Node *current;
	InsertNYT(&tree,&NYT);
	numOfNodes=1;
	//next=numbers.idx[0];
	//next=fgetc(f);
	PackData (fout, 2, 2, compress_chunk, bit1);
	PackData (fout, numbers.size, NUMBIT, compress_chunk, bit1);
	for(i=0; i<numbers.size;i++)
	{
		next = numbers.idx[i];
		current=Find(tree,next);
		if(current)
		{
			
			TransmitCode(fout,tree,current,compress_chunk,bit1);
		}
		else
		{
			TransmitCode(fout,tree,NYT,compress_chunk,bit1);
			TransmitSymbol(fout,next,compress_chunk,bit1);
			
			//SpawnNode(&tree,&NYT,next);
		}
		
		UpdateTree(&tree,next,current,NYT,&numOfNodes);

		//next=fgetc(f);
		
		
	}
	Dealocate(tree);
}

void InsertNYT(Node **tree,Node **NYT)
{
	*tree = (Node*)malloc(sizeof(Node));
	(*tree)->id=0;
	(*tree)->weight=0;
	(*tree)->parent=NULL;
	(*tree)->right=NULL;
	(*tree)->left=NULL;
	*NYT=*tree;
}

Node * Find(Node *tree,Index next)
{


	Node* current,*tmp;
	Queue Q = Init();
	
	Insert(&Q,tree);
	while(!QueueEmpty(Q))
	{
		current=Delete(&Q);
		if(current->number==next)
			break;
		if(current->left!=NULL)
			Insert(&Q,current->left);
		if(current->right!=NULL)
			Insert(&Q,current->right);
	
	}
	while(!QueueEmpty(Q))
		tmp=Delete(&Q);
	if(current->number==next)
		return current;
	return NULL;
}

void TransmitCode(FILE *fout,Node* tree,Node* current,CompressChunk *compress_chunk, int *bit1)
{
	unsigned int string[257];
	int i,j,k=0;
	Node * temp=current;
	
	while(temp->parent!=NULL)
	{
		temp=temp->parent;
		if(temp->left==current)
			string[k++] = 0;
		else
			string[k++] = 1;
			//strcat(string,"1");
		current=current->parent;
	}
	
	for(i=k-1;i>=0;i--) {
		PackData(fout,string[i],1,compress_chunk,bit1);
	}
	//fprintf(fout,"%s",string);
	//printf("%s",string)

}

void TransmitSymbol(FILE *fout,Index next,CompressChunk *compress_chunk, int *bit1)
{

	PackData(fout,(BitPackage)next,NUMBIT,compress_chunk,bit1);
	//fprintf(fout,"%c",next);
	//printf("%c",next);
}

void UpdateTree(Node **tree,Index next,Node *current, Node *NYT,int *num)
{
	Node *max;
	if(current==NULL)
	{
		SpawnNode(tree,NYT,next);
		current=NYT->parent;
		(*num)+=2;
		UpdateIDs(*tree,*num);
	}

	else
	{
		max=FindMaxInBlock(*tree,current,num);
		if(!Ancestor(max,current))
			Swap(*tree,max,current);
		current->weight++;
	}


	while(current!=(*tree))
	{
		current=current->parent;
		max=FindMaxInBlock(*tree,current,num);
		if(!Ancestor(max,current))
			Swap(*tree,max,current);
		current->weight++;
	}
}

void SpawnNode(Node **tree,Node *NYT,Index next)
{
	Node *NYTsParent, *New;
	NYTsParent=(Node*)malloc(sizeof(Node));
	New=(Node*)malloc(sizeof(Node));
	NYTsParent->parent=NYT->parent;
	if(NYT->parent!=NULL)
		NYT->parent->left=NYTsParent;
	NYT->parent=NYTsParent;
	NYTsParent->left=NYT;
	NYTsParent->right=New;
	New->parent=NYTsParent;
	New->left=New->right=NULL;
	New->number=next;
	NYTsParent->weight=New->weight=1;
	if((*tree)==NYT)
		*tree=NYTsParent;
}


void UpdateIDs(Node *tree,int num)
{
	Node * current = tree;
	Queue Q = Init();
	Insert(&Q,current);
	num--;
	while(!QueueEmpty(Q))
	{
		current = Delete(&Q);
		current->id=num;
		num--;

		if(current->right!=NULL)
			Insert(&Q,current->right);
		if(current->left!=NULL)
			Insert(&Q,current->left);
		
	}

}

Node * FindMaxInBlock(Node *tree, Node* current, int num)
{
	Node * tmp= tree;
	Node * max;
	Queue Q = Init();
	
	Insert(&Q,tmp);

	//i=0;
	max=tree;
	while(tmp->id>current->id)
	{
		tmp=Delete(&Q);
		if(tmp->weight==current->weight)
			break;
		if(tmp->right!=NULL)
			Insert(&Q,tmp->right);
		if(tmp->left!=NULL)
			Insert(&Q,tmp->left);
		
	}

	max=tmp;
	while(!QueueEmpty(Q))
		tmp=Delete(&Q);
	return max;
}

int Ancestor(Node *node,Node * current)
{
	while(current!=NULL)
	{
		if(current==node)
			return 1;
		current=current->parent;
	}
	return 0;
}

void Swap(Node *tree, Node* max, Node* current)
{

	Node* tmp = current->parent;
	int id;
	current->parent = max->parent;
	if(max->parent->right == max)
		max->parent->right = current;
	else
		max->parent->left=current;
	max->parent=tmp;
	if(tmp->left==current)
		tmp->left=max;
	else
		tmp->right=max;
	
	id=max->id;
	max->id=current->id;
	current->id=id;
}


void DHuffmanDecompress(FILE *fin, CompressChunk *compress_chunk, int *idx, int *bit1, lzwArray *numbers)
{
     int size;
	 Index next;
	 int bit;
	 int i;
	 Node * tree=NULL;
	 int numOfNodes;
	 Node *NYT=NULL;
	 Node *current;
	 InsertNYT(&tree,&NYT);
	 numOfNodes=1;

     
	 UnpackData(fin,&size,NUMBIT,compress_chunk,idx,bit1);
	 numbers->size=size;
     UnpackData(fin,&next,NUMBIT,compress_chunk,idx,bit1);
	 numbers->idx[0]=next;

	 for(i=1;i<size;i++)
	 {

		 current=Find(tree,next);

		 UpdateTree(&tree,next,current,NYT,&numOfNodes);

		 current=tree;
		 while(current->left!=NULL || current->right!=NULL)
		 {
			 UnpackData(fin,&bit,1,compress_chunk,idx,bit1);
			 if(bit)
				 current=current->right;
			 else
				 current=current->left;
		 }

		 if(current == NYT)
		 {
			 UnpackData(fin,&next,NUMBIT,compress_chunk,idx,bit1);
			 numbers->idx[i]=next;
		 }
		 else
		 {
			 next=current->number;
			 numbers->idx[i]=next;
		 }
	 }
	 Dealocate(tree);
}
			 

void Dealocate(Node *tree)
{
	Node* current;
	Queue Q = Init();
	
	Insert(&Q,tree);
	while(!QueueEmpty(Q))
	{
		current=Delete(&Q);
		if(current->left!=NULL)
			Insert(&Q,current->left);
		if(current->right!=NULL)
			Insert(&Q,current->right);

		free(current);
		current=NULL;
		
	}
	
}