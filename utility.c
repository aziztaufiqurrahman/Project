#include <stdio.h>
#include <windows.h>
#include "include/all.h"

/**
 * Membersihkan isi terminal
 * @author Ihsan Fauzan Hanif
 */
void cls()
{
	// hapus isi terminal dan set warna default menjadi bawaan
	// dari terminal (putih biasanya)
	system("cls");
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi = {0};
	GetConsoleScreenBufferInfo(hOutput, &csbi);
	SetConsoleTextAttribute(hOutput, csbi.wAttributes);
}
