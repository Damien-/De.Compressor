#include "c_dec.h"
#include <stdlib.h>
#include <string.h>
#include <windows.h>
/* ova funkcija ce postojati, ali bice dosta izmenjena, */
/* jer je ova sluzila samo da proveri ispravnost funkcije UnpackData (...) */

void Decompress (InFile bek, char root_dir[]) {   
	CompressChunk compress_chunk;
	lzwArray lzw_array;
	Chunk chunk;
	char dir[MAX_PATH], newDir[MAX_PATH];
	int bit1=8*BITPACKAGE, idx=0, len, i, j, kraj, compress_type;
	InFile file;
	unsigned char s[3];
	FILE *in, *out;

	file.name = NULL;

	compress_chunk.pack = calloc(OUTSIZE, sizeof(BitPackage));
	compress_chunk.size = 0;
	lzw_array.idx = malloc(CHUNKSIZE * sizeof(Index));
	lzw_array.size = 0;
	chunk.c = malloc(CHUNKSIZE * sizeof(char));
	chunk.size = 0;

	in = fopen (bek.name[0], "rb");
	GetCurrentDirectory(MAX_PATH,dir);
	strcat(dir,"\\"); bek.name[0][strlen(bek.name[0])-4] = '\0';
	strcat(dir,bek.name[0]);
	CreateDirectory (dir, NULL);
	SetCurrentDirectory(dir);

	fread(s, sizeof(char), 3, in);
	if (s[0] == 'L' && s[1] == 'M' && s[2] == 'D') {

		compress_chunk.size = fread(compress_chunk.pack, BITPACKAGE, OUTSIZE, in);
		UnpackData (in, &file.size, 8, &compress_chunk, &idx, &bit1);
		file.name = malloc (file.size * sizeof(char *));
		for (i=0; i<file.size; i++) {
			UnpackData (in, &len, 9, &compress_chunk, &idx, &bit1);
			file.name[i] = malloc ((len+1) * sizeof(char));
			for (j=0; j<len; j++) UnpackData (in, &file.name[i][j], 8, &compress_chunk, &idx, &bit1);
			file.name[i][j] = '\0';
		}

		for (i=0; i<file.size; i++) {
			SetCurrentDirectory (dir);
			out = fopen (file.name[i], "wb");

			kraj = 0;
			while (!kraj) {
				UnpackData (in, &compress_type, 2, &compress_chunk, &idx, &bit1);
				switch (compress_type) {
					case 0: DecompressUncompressed (in, out, &chunk, &compress_chunk, &idx, &bit1); break;
					case 1: DecompressStaticHuffman (in, out, &chunk, &compress_chunk, &idx, &bit1, root_dir); break;
					case 2: DHuffmanDecompress (in, &compress_chunk, &idx, &bit1, &lzw_array); 
							LZW_decompress (out, lzw_array, &chunk); 
							break;
					case 3: UnpackData (in, &lzw_array.size, NUMBIT, &compress_chunk, &idx, &bit1);
							for (j=0; j<lzw_array.size; j++) 
								UnpackData (in, &lzw_array.idx[j], NUMBIT, &compress_chunk, &idx, &bit1);
							LZW_decompress (out, lzw_array, &chunk);
							break;
				}
				UnpackData (in, &kraj, 1, &compress_chunk, &idx, &bit1);
			}
			fclose(out);
		}
		//for (i=0; i<file.size; i++) free (file.name[i]);
		//free (file.name);
		/* Potrebno je dealocirati alociranu memoriju */
	}
	fclose(in);
	//free (compress_chunk.pack);
	//free (lzw_array.idx);
	//free (chunk.c);
}

/* Vraca 0 ako je kraj fajla */
int UnpackData (FILE *in, BitPackage *num, int bit, CompressChunk *compress_chunk, int *idx, int *bit1) {
	int q=1;

	if (*bit1 < bit) {
		*num = compress_chunk->pack[(*idx)++] >> 8*BITPACKAGE-*bit1;
		bit -= *bit1;
		if (*idx == compress_chunk->size) {
			q = compress_chunk->size = fread(compress_chunk->pack, BITPACKAGE, OUTSIZE, in);
			*idx = 0;
		}
		if (q) {
			*num <<= bit;
			*bit1 = 8 * BITPACKAGE;
			*num |= compress_chunk->pack[*idx] >> *bit1-bit;
			compress_chunk->pack[*idx] <<= bit;
			*bit1 -= bit;
		}
	} else {
		*num = compress_chunk->pack[*idx] >> 8*BITPACKAGE-bit;
		compress_chunk->pack[*idx] <<= bit;
		*bit1 -= bit;
	}
	return q;
}