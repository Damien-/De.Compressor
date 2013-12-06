#ifndef _c_dec_h_
#define _c_dec_h_

#include <stdio.h>

#define CODESIZE 13  /* Najveci broj bitova koji je dopusten za smestanje nekog stringa */
#define TABLESIZE (1<<CODESIZE)
#define RIGHT 1
#define LEFT -1

typedef int Index;

/* sturktura koja predstavlja string u LZW tabeli */ 
typedef struct string {                
	int prefix, left, right, tree;
	unsigned char byte;
} String;

typedef struct lzwarray {    /* struktura koja predstavlja izlaz za koder i ulaz za dekoder LZW-a */
	int size;
	Index *idx;
} lzwArray;

#define NUMBIT 13
#define CHUNKSIZE ((1 << (NUMBIT))-1) /* 8KB */
#define OUTSIZE ((CHUNKSIZE+1)/4)     /* 8KB */

typedef unsigned BitPackage;   /* Ovaj podatak nam pokazuje u kakve podatke smestamo dobijene bitove */
#define BITPACKAGE sizeof (BitPackage)

typedef struct infile {       /* struktura koja sadrzi broj fajlova za kompresiju i njihova imena */
	int size;
	char **name;
	char **path;
} InFile;

/* struktura koja sadrzi chunk za kompresiju i njegovu velicinu */
typedef struct chunk {      
	int size;
	unsigned char *c;
} Chunk;

 /* struktura koja sadrzi nizove bitova koji se salju na izlaz */
typedef struct compresschunk {    
	int size;
	BitPackage *pack;
} CompressChunk;

typedef struct znak1 {
	double freq;
	int num;
} Znak1;

void Compress (InFile infile, char *name, char root_dir[]);
void Decompress (InFile bek, char root_dir[]);
void PackData (FILE *out, BitPackage num, int bit, CompressChunk *compress_chunk, int *bit1);
int UnpackData (FILE *in, BitPackage *num, int bit, CompressChunk *compress_chunk, int *idx, int *bit1);
int Decide (Chunk chunk, int lzw_size, int number_files, const char *huff_tbl[], int *huff, char root_dir[]);
void Uncompressed (FILE *out, Chunk chunk, CompressChunk *compress_chunk, int *bit1);
void CompressStaticHuffman (FILE *out, Chunk chunk, CompressChunk *compress_chunk, int *bit1, const char *huff_tbl, int huff, char root_dir);
void DecompressUncompressed (FILE *in, FILE *out, Chunk *chunk, CompressChunk *compress_chunk, int *idx, int *bit1);
void DecompressStaticHuffman (FILE *in, FILE *out, Chunk *chunk, CompressChunk *compress_chunk, int *idx, int *bit1, char root_dir[]);
void Sort (Znak1 *niz);

/* Funkcije za rad sa LZW tabelom */

String *AllocTable ();
String *InitTable (String *tbl, Index *size);
String *DeleteTable (String *tbl);
int SearchTable (String *tbl, Index *idx, Index *cur, int *prev, unsigned char chr);
void TableAddCompress (String *tbl, Index idx, Index cur, int dir, Index *size, unsigned char chr);
void TableAddDecompress (String *table, Index *size, Index oldcode, unsigned char chr);

/* Funkcije koje omogucuju LZW */

void LZW_compress (Chunk chunk, lzwArray *lzw_array);
void LZW_decompress (FILE *out, lzwArray lzw_array, Chunk *chunk);
unsigned char WriteString (Chunk *chunk, String *table, Index code, Index size);

#endif