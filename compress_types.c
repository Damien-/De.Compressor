#include "c_dec.h"
#include "shdecoder.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

void Sort (Znak1 *niz) {
	int i, j;
	Znak1 tmp;

	for (i=0; i<255; i++)
		for (j=i+1; j<256; j++)
			if (niz[i].freq < niz[j].freq) {
				tmp = niz[i];
				niz[i] = niz[j];
				niz[j] = tmp;
			}
}

/* Funkcija odlucivanja */
int Decide (Chunk chunk, int lzw_size, int number_files, const char *huff_tbl[], int *huff, char root_dir[]) {
	const char tabela[10][10] = {"h0.tbl", "h1.tbl", "h2.tbl", "h3.tbl", "h4.tbl", "h5.tbl", "h6.tbl", "h7.tbl", "h8.tbl", "h9.tbl"};
	Znak1 niz[260];
	double x, tek, huffman, lzw, unc;
	char code[257];
	FILE *in;
	int i, j, a[260], ch;

	if (number_files == 1 && chunk.size < 1000) return 2;
	if (number_files == 2 && chunk.size < 500) return 2;
	if (chunk.size < 300) return 2;
	lzw = (double)(lzw_size * (NUMBIT-1));

	for (i=0; i<256; i++) niz[i].num = 0;
	for (i=0; i<chunk.size; i++) niz[chunk.c[i]].num++;
	for (i=0; i<256; i++) niz[i].freq = (double)niz[i].num/(double)chunk.size;
	Sort (niz);

	SetCurrentDirectory (root_dir);
	huffman = 12; 
	for (i=0; i<10; i++) {
		tek = 0;
		in = fopen (tabela[i], "r");
		for (j=0; j<256; j++) {
			fscanf (in, "%u%lf%s", &ch, &x, code);
			a[j] = strlen(code);
			tek += (double)a[j]*niz[j].freq;
		}
		if (tek < huffman) {
			huffman = tek;
			strcpy (huff_tbl, tabela[i]);
			*huff = i;
		}
		fclose (in);
	}
	huffman *= (double)chunk.size;
	unc = (double)(9 * chunk.size);
	if (huffman < unc) {
		if (huffman < lzw) return 1;
		else return 3;
	} else {
		if (unc < lzw) return 0;
		else return 3;
	}
}

void Uncompressed (FILE *out, Chunk chunk, CompressChunk *compress_chunk, int *bit1) {
	int i;

	PackData (out, 0, 2, compress_chunk, bit1);
	PackData (out, chunk.size, NUMBIT, compress_chunk, bit1);
	for (i=0; i<chunk.size; i++) 
		PackData (out, chunk.c[i], 8, compress_chunk, bit1);
}

void CompressStaticHuffman (FILE *out, Chunk chunk, CompressChunk *compress_chunk, int *bit1, const char *huff_tbl, int huff, char root_dir[]) {
	FILE *tmp;
	unsigned char s[256][257], kod[257], karakter;
	unsigned int ch, i, j;
	double f;

	PackData (out, 1, 2, compress_chunk, bit1);
	PackData (out, huff, 4, compress_chunk, bit1);
	PackData (out, chunk.size, NUMBIT, compress_chunk, bit1);
 
	//SetCurrentDirectory (root_dir);
	tmp = fopen (huff_tbl, "r");
	for (i=0; i<256; i++) {
		fscanf (tmp, "%u %lf %s%c", &ch, &f, kod, &karakter);
		strcpy (s[ch], kod);
	}
	fclose(tmp);
	for (i=0; i<chunk.size; i++) {
		for (j=0; j<strlen(s[chunk.c[i]]); j++)	
			PackData (out, (s[chunk.c[i]][j] - '0'), 1, compress_chunk, bit1);
	}
}

void DecompressUncompressed (FILE *in, FILE *out, Chunk *chunk, CompressChunk *compress_chunk, int *idx, int *bit1) {
	int i;

	UnpackData (in, &chunk->size, NUMBIT, compress_chunk, idx, bit1);
	for (i=0; i<chunk->size; i++)
		UnpackData (in, &chunk->c[i], 8, compress_chunk, idx, bit1);
	fwrite (chunk->c, sizeof(char), chunk->size, out);
}

void DecompressStaticHuffman (FILE *in, FILE *out, Chunk *chunk, CompressChunk *compress_chunk, int *idx, int *bit1, char root_dir[]) {
	const char tabela[10][10] = {"h0.tbl", "h1.tbl", "h2.tbl", "h3.tbl", "h4.tbl", "h5.tbl", "h6.tbl", "h7.tbl", "h8.tbl", "h9.tbl"};
	Node *root, *tek;
	int dr, size, i=0, huff;
	char *huff_tbl;

	UnpackData (in, &huff, 4, compress_chunk, idx, bit1);
	huff_tbl = tabela[huff];
	UnpackData (in, &size, NUMBIT, compress_chunk, idx, bit1); 
	

	SetCurrentDirectory (root_dir);
	chunk->size = size;
	root = Tree (huff_tbl);
	tek = root;
	for (i=0; i<chunk->size; i++) {
		while (tek->left != NULL || tek->right != NULL) {
			UnpackData (in, &dr, 1, compress_chunk, idx, bit1);
			if (dr == 1) tek = tek->right;
			else tek = tek->left;
		}
		chunk->c[i] = tek->znak.character;
		tek = root;
	}
	fwrite (chunk->c, sizeof(char), chunk->size, out);
	DeleteTree (root);
}