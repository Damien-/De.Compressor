#include "c_dec.h"
#include <stdlib.h>

void LZW_decompress (FILE *out, lzwArray lzw_array, Chunk *chunk) {
	Index oldcode, newcode, size;
	unsigned char chr, chr1;
	int i;
	String *table;

	table = AllocTable ();
	table = InitTable (table, &size);

	chunk->size = 0;
	oldcode = lzw_array.idx[0];
	chr = WriteString (chunk, table, oldcode, size);
	for (i=1; i<lzw_array.size; i++) {
		newcode = lzw_array.idx[i];
		if (newcode >= size) {
			chr1 = chr; 
			chr = WriteString (chunk, table, oldcode, size);
			TableAddDecompress (table, &size, oldcode, chr1);
			chunk->c[chunk->size++] = chr1;
		} else {
			chr = WriteString (chunk, table, newcode, size);
			TableAddDecompress (table, &size, oldcode, chr);
		}
		oldcode = newcode;
	}
	fwrite (chunk->c, sizeof(char), chunk->size, out);
	free(table); table = NULL;
}

/* Funkcija za ispisivanje dekodovanog stringa uz pomoc steka */
unsigned char WriteString (Chunk *chunk, String *table, Index code, Index size) {
	unsigned char stack[TABLESIZE], c, ch;
	Index top=0, t=code;
	while (t >= 0 && t < size) {
		stack[top++] = table[t].byte;
		t = table[t].prefix;
	}
	ch = stack[top-1];
	while (top) {
		c = stack[--top];
		chunk->c[chunk->size++] = c;
	}
	return ch;
}