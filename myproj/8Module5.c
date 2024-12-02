#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct LongNum_s {
	int rar[64];
	int size;
} LongNum;

int main(void){
	FILE* in = fopen("1.in", "rb");
	FILE* out = fopen("output.txt", "wb");
	int N = 0;
	fread(&N, 4, 1, in);
	int filin[1000000] = {-1};
	LongNum* arr;
	arr = (LongNum*)malloc(N * sizeof(LongNum));
	for (int i = 0; i < N; i++) {
		int L = 0;
		fread(&L, 4, 1, in);
		arr[i].size = L;
		for (int y = 0; y < L; y++) {
			int bit = 0;
			fread(&bit, 1, 1, in);
			arr[i].rar[y] = bit;
		}
	}
	int M = 0;
	fread(&M, 4, 1, in);
	int ari[8] = { 1, 2, 4, 8, 16, 32, 64, 128 };
	int o = 0;
	for (int i = 0; i < M; i++) {
		int t = 0;
		fread(&t, 2, 1, in);
		for (int y = 0; y < arr[t].size; y++) {
			filin[o] = arr[t].rar[y];
			o++;
		}
	}
	int cova[1000000] = {0};
	int wera = 0;
	int chislo = 0;
	int count = 0;
	for (int i = 0; i < o; i++) {
		chislo = chislo + (ari[wera]*filin[i]);
		wera++;
		if (wera == 8) {
			wera = 0;
			cova[count] = chislo;
			count++;
			chislo = 0;
		}
	}
	if (chislo != 0) {
		cova[count] = chislo;
		count++;
	}
	for (int i = 0; i < count; i++) {
		fwrite(&cova[i], 1, 1, out);
	}
}