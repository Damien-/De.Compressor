#include "c_dec.h"
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include "dh.h"

void Compress (InFile file, char name[MAX_PATH], char root_dir[]) {   /* name -> ime kompresovanog fajla */
	Chunk chunk;
	CompressChunk compress_chunk;
	lzwArray lzw_array;

	int i, j, bit1=8*BITPACKAGE, compress_type, huff;
	char huff_tbl[10];
	char magic_code[] = {'L', 'M', 'D'};
	unsigned short name_len;
	FILE *in, *out;           /* in -> pokazivac na ulazne datoteke; out -> pokazivac na kompresovanu arhivu */


	compress_chunk.pack = calloc (OUTSIZE, sizeof(BitPackage));
	compress_chunk.size = 0;
	chunk.c = malloc (CHUNKSIZE * sizeof(char));
	chunk.size = 0;
	lzw_array.idx = malloc (CHUNKSIZE * sizeof(Index));
	lzw_array.size = 0;

	if (file.size > 0) {
		out = fopen (name, "wb");
		fwrite (magic_code, sizeof(char), 3, out);   /* magic_code -> da se zna da se radi o arhivi kompresovanoj ovim kompresorom */

		PackData (out, (BitPackage) file.size, 8, &compress_chunk, &bit1);  /* maximalni broj fajlova je 256! */
		for (i=0; i<file.size; i++) {
			name_len = strlen (file.name[i]);
			PackData (out, (BitPackage) name_len, 9, &compress_chunk, &bit1); /* maximalno ime fajla je 512! */
			for (j=0; j<name_len; j++) PackData (out, (BitPackage) file.name[i][j], 8, &compress_chunk, &bit1);
		}  /* imena fajlova se stavljaju na pocetak kompresovanog fajla */

		for (i=0; i<file.size; i++) {
			SetCurrentDirectory (file.path[i]);
			in = fopen (file.name[i], "rb");
			/* Ovde ubaciti proveru postojanja fajla */

			chunk.size = fread (chunk.c, sizeof(char), CHUNKSIZE, in);
			while (1) {
				if (chunk.size == 0) break;
				/* ... compression ... */
				
				LZW_compress (chunk, &lzw_array);

				compress_type = Decide (chunk, lzw_array.size, file.size, &huff_tbl, &huff, root_dir);
				switch (compress_type) {
					case 0: Uncompressed (out, chunk, &compress_chunk, &bit1); break;
					case 1: CompressStaticHuffman (out, chunk, &compress_chunk, &bit1, huff_tbl, huff, root_dir); break;
					case 2: DHuffman (lzw_array, out, &compress_chunk, &bit1); break;
					case 3: PackData (out, 3, 2, &compress_chunk, &bit1);
							PackData (out, lzw_array.size, NUMBIT, &compress_chunk, &bit1);
							for (j=0; j<lzw_array.size; j++) 
								PackData (out, lzw_array.idx[j], NUMBIT, &compress_chunk, &bit1);
							break;
				}
				chunk.size = fread (chunk.c, sizeof(char), CHUNKSIZE, in);
				if (chunk.size > 0) PackData (out, 0, 1, &compress_chunk, &bit1);  /* kraj prethodnog chunk_a, ali ne i file_a */
			}
			PackData (out, 1, 1, &compress_chunk, &bit1);
			fclose (in);
		}
		compress_chunk.pack[compress_chunk.size] <<= bit1;
		fwrite (compress_chunk.pack, sizeof(BitPackage), compress_chunk.size+1, out);
		fclose (out);
	}
	free(compress_chunk.pack); compress_chunk.pack = NULL;
	free(chunk.c);			   chunk.c = NULL;   
	free(lzw_array.idx);	   lzw_array.idx = NULL;
}

 
/* PackData se poziva sa parametrima: kompresovani fajl, broj (bit, bajt, ...) koji treba kompresovati, */
/* u koliko bita kompresovati num, niz u koji se stavlja kompresovani deo, ...						    */

void PackData (FILE *out, BitPackage num, int bit, CompressChunk *compress_chunk, int *bit1) {
	if (*bit1 < bit) {
		compress_chunk->pack[compress_chunk->size] <<= *bit1;
		compress_chunk->pack[compress_chunk->size++] |= num >> bit-*bit1;
		if (compress_chunk->size == OUTSIZE) {
			fwrite(compress_chunk->pack, BITPACKAGE, compress_chunk->size, out);
			compress_chunk->size = 0;
		}
		compress_chunk->pack[compress_chunk->size] = num % (1 << bit-*bit1);
		*bit1 = 8 * BITPACKAGE - (bit-*bit1);
	} else {
		compress_chunk->pack[compress_chunk->size] <<= bit;
		*bit1 -= bit;
		compress_chunk->pack[compress_chunk->size] |= num;
	}
}
