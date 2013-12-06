#include "c_dec.h"
#include <stdlib.h>

String *AllocTable () {
	String *tbl;
	tbl = malloc (TABLESIZE * sizeof(String));
	return tbl;
}

/* Inicijalizacija tabele */
String *InitTable (String *tbl, Index *size) {
	Index i;
	for (i=0; i<TABLESIZE; i++)	{
		tbl[i].left = tbl[i].right = tbl[i].prefix = tbl[i].tree = -1;
		tbl[i].byte = (i < 256) ? i : -1; /* mozda promeniti ovo -1 u nesto drugo, npr 0 */
	}
	*size = 256;
	return tbl;
}

String *DeleteTable (String *tbl) {
	if (tbl != NULL) free(tbl);
	return NULL;
}

int SearchTable (String *tbl, Index *idx, Index *cur, int *prev, unsigned char chr) {
	Index next;
	
	*prev = 0;
	if (tbl[*cur].tree == -1) return 0;
	else {
		next = tbl[*cur].tree;
		while (next != -1) {
			if (tbl[next].byte < chr) {
				*cur = next;
				next = tbl[next].right;
				*prev = RIGHT;
			} else if (tbl[next].byte > chr) {
				*cur = next;
				next = tbl[next].left;
				*prev = LEFT;
			} else {
				*idx = next;	/* idx uzima poziciju elementa koji predstavlja poslednji pronadjen string */
				return 1;
			}
		}
	}
	return 0;
}

/* Funkcija za ubacivanje u tabelu pri kompresiji */
void TableAddCompress (String *tbl, Index idx, Index cur, int dir, Index *size, unsigned char chr) {
	switch (dir) {
		case 0: tbl[cur].tree = *size; break;
		case RIGHT: tbl[cur].right = *size; break;
		case LEFT: tbl[cur].left = *size; break;
	}
	tbl[*size].prefix = idx;
	tbl[*size].byte = chr;
	(*size)++;
}


/* Funkcija za ubacivanje u tabelu pri dekompresiji */
void TableAddDecompress (String *tbl, Index *size, Index oldcode, unsigned char chr) {
	tbl[*size].prefix = oldcode;
	tbl[*size].byte = chr;
	(*size)++;
}