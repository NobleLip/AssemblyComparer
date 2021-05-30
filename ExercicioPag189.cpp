#include "stdio.h"
#include "conio.h"
#include <stdlib.h> 
#include "string.h"
#include <time.h>
#include <malloc.h>

#ifdef _WIN32
#include <intrin.h>
#else
#include <x86intrin.h>
#endif

#define Tamanho 1000000

extern "C" { //indicate that we have an external function
	void binarize(unsigned char, unsigned char*, int);
}

void Graf(unsigned __int64 Grafico[], int Max) {
	for (int z = 0; z < 50; z++) {
		if ((Max - z * 40000) / (1000000) >= 1 || (Max - z * 40000) / (1000000) == 2 && (Max - z * 40000) / (1000000) <= 2) {
			printf("\n%d |", Max - z * 40000);
		}
		else if (((Max - z * 40000) / (100000) >= 1 && (Max - z * 40000) / (100000) <= 9)) {
			printf("\n%d  |", Max - z * 40000);
		}
		else {
			printf("\n%d   |", Max - z * 40000);
		}

		for (int i = 0; i < 100; i++) {
			if (Grafico[i] / (Max - (z * 40000)) >= 1) {
				printf("#");
			}
			else {
				printf(" ");
			}
		}
	}
	printf("\n\n\n");
}

int main(int argc, char* argv[])
{

	unsigned char Limite = 56;
	unsigned char* ArrayChar;
	ArrayChar = (unsigned char*)malloc(Tamanho);
	unsigned char* ArrayChar1;
	ArrayChar1 = (unsigned char*)malloc(Tamanho);


	unsigned __int64 ArrayTempos[100];
	unsigned __int64 Grafico[100];

	unsigned __int64 initial_counter, final_counter, initial_counter1, final_counter1;
	for (int z = 0; z < 100; z++) {
		for (int i = 0; i < Tamanho; i++) {
			ArrayChar[i] = i;
		}
		initial_counter = __rdtsc();
		binarize(Limite, ArrayChar, Tamanho);
		final_counter = __rdtsc();
		ArrayTempos[z] = (final_counter - initial_counter);
	}
	int Soma = 0;
	int Minimo = ArrayTempos[0];
	int Maximo = ArrayTempos[0];
	
	for (int i = 0; i < 100; i++) {
		Grafico[i] = ArrayTempos[i];
	}

	Graf(Grafico, 2000000);

	for (int i = 0; i < 100; i++) {
		if (i % 10 == 0 && i !=0 ) {
			printf("\n");
		}
		printf("%I64d     ", ArrayTempos[i]);
		Soma += ArrayTempos[i];
		if (Minimo > ArrayTempos[i]) {
			Minimo = ArrayTempos[i];
		}
		if (Maximo < ArrayTempos[i]) {
			Maximo = ArrayTempos[i];
		}
	}

	unsigned __int64 temp;
	for (int i = 0; i < 100; i++) {
		for (int j = i + 1; j < 100; j++) {
			if (ArrayTempos[i] > ArrayTempos[j]) {
				temp = ArrayTempos[i];
				ArrayTempos[i] = ArrayTempos[j];
				ArrayTempos[j] = temp;
			}
		}
	}

	printf("\n\nMedia Ciclos de Clock = %d\nMaximo de Clocks = %d\nMinimo de Clocks = %d\nMediana d Clocks = %d\n\n\n", Soma/100, Maximo, Minimo, (ArrayTempos[49]+ ArrayTempos[50])/2);

	unsigned __int64 ArrayTempos1[100];
	unsigned __int64 Grafico1[100];

	for (int z = 0; z < 100; z++) {

		for (int i = 0; i < Tamanho; i++) {
			ArrayChar1[i] = i;
		}

		initial_counter1 = __rdtsc();
		for (int i = 0; i < Tamanho; i++) {
			if (ArrayChar1[i] < Limite) {
				ArrayChar1[i] = 0;
			}
			else {
				ArrayChar1[i] = 255;
			}
		}
		final_counter1 = __rdtsc();
		ArrayTempos1[z] =  (final_counter1 - initial_counter1);
	}

	Soma = 0;
	Minimo = ArrayTempos1[0];
	Maximo = ArrayTempos1[0];

	for (int i = 0; i < 100; i++) {
		Grafico1[i] = ArrayTempos1[i];
	}


	Graf(Grafico1, 5000000);

	for (int i = 0; i < 100; i++) {
		if (i % 10 == 0 && i != 0) {
			printf("\n");
		}
		printf("%I64d     ", ArrayTempos1[i]);
		Soma += ArrayTempos1[i];
		if (Minimo > ArrayTempos1[i]) {
			Minimo = ArrayTempos1[i];
		}
		if (Maximo < ArrayTempos1[i]) {
			Maximo = ArrayTempos1[i];
		}
	}

	for (int i = 0; i < 100; i++) {
		for (int j = i + 1; j < 100; j++) {
			if (ArrayTempos1[i] > ArrayTempos1[j]) {
				temp = ArrayTempos1[i];
				ArrayTempos1[i] = ArrayTempos1[j];
				ArrayTempos1[j] = temp;
			}
		}
	}

	printf("\n\nMedia Ciclos de Clock = %d\nMaximo de Clocks = %d\nMinimo de Clocks = %d\nMediana d Clocks = %d\n\n\n", Soma / 100, Maximo, Minimo, (ArrayTempos1[49] + ArrayTempos1[50]) / 2);
}

