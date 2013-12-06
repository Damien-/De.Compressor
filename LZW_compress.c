#include "c_dec.h"
#include <stdlib.h>

void LZW_compress (Chunk chunk, lzwArray *lzw_array) {
	int dir, i;
	unsigned char chr;
	Index idx, size, cur;
	String *table;

	table = AllocTable ();
	table = InitTable (table, &size);
	lzw_array->size = 0;
	idx = chr = chunk.c[0];
	for (i=1; i<chunk.size; i++) {
		chr = chunk.c[i];
		cur = idx;
		if (!SearchTable (table, &idx, &cur, &dir, chr)) { 
			TableAddCompress (table, idx, cur, dir, &size, chr);
			lzw_array->idx[lzw_array->size++] = idx;
			idx = chr; 
		}
	}
	lzw_array->idx[lzw_array->size++] = idx;
	free(table); table = NULL;
}