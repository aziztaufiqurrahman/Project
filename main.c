/**
 * Kelompok 6
 * 
 * Anggota:
 * 201524003 - Diana Fauziah
 * 201524011 - Ihsan Fauzan Hanif
 * 201524014 - Muhammad Aziz Taufiqurrahman
 * 
 * main.c
 * Kode Permainan Tower of Hanoi
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include "include/all.h"

int main()
{
	// inisialisasi sistem permainan
	Game game;
	initializeGameSystem(&game);

	// memanggil menu utama
	menuMain(&game);
	
	return 0;
}
