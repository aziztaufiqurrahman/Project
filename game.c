/**
 * Kelompok 6
 * 
 * Anggota:
 * 201524003 - Diana Fauziah
 * 201524011 - Ihsan Fauzan Hanif
 * 201524014 - Muhammad Aziz Taufiqurrahman
 * 
 * game.c
 * Implementasi kode program dari struktur data pada file game.h
 */

#include <conio.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <windows.h>
#include <unistd.h>
#include "include/all.h"

/**
 * Inisialisasi sistem Game, bertujuan untuk mengatur agar semua
 * informasi terkait dengan Game bernilai kosong
 * @author
 * Diana Fauziah
 * 07/21/21
 */
void createGame(Game *game)
{	
	//membuat semua game kosong/membentuk game baru
	memset(game, 0, sizeof(Game));
}
/**
 * Inisialisasi sistem game dan threading
 * @author Ihsan Fauzan Hanif
 */
void createRunner(Runner *runner)
{
	// mengisi blok memori yang digunakan Runner dengan nilai 0
	memset(runner, 0, sizeof(*runner));
}
/**
 * Mendapatkan disk maksimal yang bisa dimasukkan berdasarkan level dari tower 
 * @author M Aziz Taufiqurrahman
 */
int getMaxDisk(int towerLevel) {
	switch (towerLevel) {
		case 1 : return 2; break;
		case 2 : return 3; break;
		case 3 : return 4; break;
		case 4 : return 5; break;
		case 5 : return 5; break;
	}
}
/**
 * Mendapatkan waktu maksimal yang bisa digunakan untuk bermain berdasarkan level
 * dari permainan
 * @author M Aziz Taufiqurrahman
 */
int getMaxTime(int towerLevel) {
	// mengembalikan nilai (waktu) yang tersedia untuk satu level dalam hitungan detik
	switch (towerLevel){
		case 1 : return 30; break; 
		case 2 : return 60; break; 
		case 3 : return 100; break; 
		case 4 : return 300; break; 
		case 5 : return 150; break;
	}
}
/**
 * Mendapatkan pergerakan minimal yang bisa dilakukan untuk menyelesaikan permainan
 * @author
 */
int getMinMoves(int maxDisk)
{
	// bit shifting kurangi satu
	// misal untuk 2 tower, seminimalnya ada 3 langkah,
	// satu pada blok memori dishift 2x kemudian dikurangi 1
	// -------------- 8 4 2 1
	// sebelum shift: 0 0 0 1 [1]
	// setelah shift: 0 1 0 0 [4]
	// setelah dikurangi 1: 0 0 1 1 [3]
	return (1 << maxDisk) - 1;
}
/**
 * Menyimpan game dengan posisi penyimpanan berdasarkan index
 * @author Ihsan Fauzan Hanif
 */
bool saveGame(Game *game, int index)
{
    bool retVal = false;
    int maxSize = sizeof(*game) * MAX_SAVED_GAME;

	// alokasi memori dengan ukuran yang bisa menjangkau seluruh data save game
	// kemudian isi memori tersebut dengan data dari save game
    char *gameData = malloc(maxSize);
    memset(gameData, 0, maxSize);
    loadAllSaveGame(gameData, maxSize);
    
	// copy isi game ke save game (dengan posisi sesuai index (index perhitungan
	// data save game))
    memcpy(gameData + (index * sizeof(*game)), game, sizeof(*game));
    FILE *file = fopen("save.dat", "wb");
    if (!file)
    {
        printf("Error: Unable to create the file");
        system("pause");
        exit(EXIT_FAILURE);
    }
	// simpan data tersebut pada file save game
    if (fwrite(gameData, maxSize, 1, file) == 1) retVal = true;
    fclose(file);
    free(gameData);
    return retVal;
}
/**
 * Memuat seluruh data permainan tersimpan
 * @author Ihsan Fauzan Hanif
 */
void loadAllSaveGame(char* result, int memorySize)
{
	// masukkan semua data save game ke result
    FILE *file = fopen("save.dat", "rb");
    if (file) fread(result, memorySize, 1, file);
    fclose(file);
}
/**
 * Memuat game yang terdapat pada save game berdasarkan index
 * @author Ihsan Fauzan Hanif
 */
Game loadGame(int index)
{
    Game retVal;
    memset(&retVal, 0, sizeof(retVal));
    int maxSize = sizeof(retVal) * MAX_SAVED_GAME;
    char *gameData = malloc(maxSize);

	// ambil save game, copy isi save game dengan index yang diminta ke retVal
    loadAllSaveGame(gameData, maxSize);
    memcpy(&retVal, gameData + (index * sizeof(retVal)), sizeof(retVal));
    free(gameData);
    return retVal;
}
/**
 * Menghapus data game yang telah tersimpan
 * @author Ihsan Fauzan Hanif
 */
bool deleteGame(int index)
{
	// set blok memori menjadi nol dan simpan hasil perubahan tersebut
    Game g;
    memset(&g, 0, sizeof(Game));
    return saveGame(&g, index);
}
/**
 * Menampilkan daftar permainan tersimpan
 * @author Ihsan Fauzan Hanif
 */
int printSaveGame()
{
	Game sgData[MAX_SAVED_GAME] = {0};
	Game game;

	int maxSize = sizeof(Game) * MAX_SAVED_GAME;
    char *gameData = malloc(maxSize);
	memset(gameData, 0, maxSize);
	loadAllSaveGame(gameData, maxSize);
	memcpy(sgData, gameData, maxSize);
	free(gameData);

	printf("%-7s %-20s %-7s %s", "No", "Nama Pemain", "Level", "Skor");
	printf("\n--------------------------------------------------------");

	int count = 0;

	int i;
	for (i = 0; i < MAX_SAVED_GAME; i++)
	{
		game = sgData[i];
		char num[7] = {0};
		char playerName[20] = {0};
		char level[7] = {0};
		char score[5] = {0};
		memcpy(num, "[", 1);
		itoa(i + 1, num + 1, 10);
		memcpy(num + strlen(num), "].", 2);
		if (game.index == 0 && strlen(game.playerName) == 0)
		{
			memcpy(playerName, "-", 1);
			memcpy(level, "-", 1);
			memcpy(score, "-", 1);
		}
		else
		{
			int len = strlen(game.playerName);

			memcpy(playerName, game.playerName, len >= 20? 16 : len);
			if (len >= 20) memcpy(playerName + len, "...", 3);
			itoa(game.towerLevel, level, 10);
			itoa(game.score, score, 10);
			count++;
		}
		printf("\n%-7s %-20s %-7s %s", num, playerName, level, score);
	}
	printf("\n--------------------------------------------------------\n");
	return count;
}
/**
 * Titik masuk dari permainan
 * @author Ihsan Fauzan Hanif
 */
int gameEntry(Game *game)
{
    game->isLevelMax = false;
    game->isPaused = false;

	// pengaturan untuk setiap mode permainan
	if (game->mode == ORIGINAL)
	{
		game->maxDisk = getMaxDisk(game->towerLevel);
		game->timeLeft = getMaxTime(game->towerLevel);
	}
	else game->towerLevel = game->maxDisk;

	// isi tower kiri dengan disk (terurut, 3 --> 2 --> 1)
	int i;
	for (i = game->maxDisk; i > 0; i--) push(&game->left, i);

	// sistem multi threading (menjalankan sistem dalam waktu yang bersamaan)
	// pertama sistem ketika permainan itu sendiri dijalankan
	// kedua sistem untuk mengurus waktu dari permainan
    pthread_t thGameRun, thGameTimer;
	Runner runner;
	createRunner(&runner);
	runner.game = &game;
	runner.threadGame = &thGameRun;
	runner.threadTimer = &thGameTimer;
    pthread_create(&thGameRun, NULL, gameRun, &runner);
    pthread_create(&thGameTimer, NULL, gameTimer, &runner);

	// gabungkan thread agar berjalan bersamaan
    pthread_join(thGameRun, NULL);
    pthread_join(thGameTimer, NULL);

	// setelah thread berakhir, hapus semua isi tower, dan masuk ke pengkondisian keadaan
	// dari permainan (menang/kalahnya)
	printf("\n[Permainan Berakhir]\n\n");
	Tower* tempAddr = &game->left;
	int x;
	while (!isEmpty(*tempAddr)) pop(tempAddr, &x);
	tempAddr = &game->middle;
	while (!isEmpty(*tempAddr)) pop(tempAddr, &x);
	tempAddr = &game->right;
	while (!isEmpty(*tempAddr)) pop(tempAddr, &x);
	printf(game->state == WIN? "Anda Menang!\n" : "Anda Kalah!\n");
	
	return game->mode == PRACTICE? NONE : game->state;
}
/**
 * Menampilkan output isi dari tower berdasarkan string.
 * @author Ihsan Fauzan Hanif
 */
void printTowerStr(char *str, int width)
{
	// inisialisasi handler standar output
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO cInfo;

	// dapatkan informasi dari terminal
	GetConsoleScreenBufferInfo(hConsole, &cInfo);
	WORD consoleAttr = cInfo.wAttributes;
	int i, j;
	for (i = 0; i < strlen(str); i++)
	{
		// jika char posisi ke i (atau sama saja dengan str[i]) tidak berisi UI_BLOCK, skip
		if (*(str + i) != -37)
		{
			printf("%c", *(str + i));
			continue;
		}
		
		// jika charnya UI_BLOCK, loop sampai ujung dari char (spasi)
		int diskWidth = 0;
		int lastIndex = 0;
		for (j = i; j < strlen(str); j++)
		{
			diskWidth++;
			if (*(str + j) == ' ') break;
		}

		// kalkulasi panjang UI_BLOCK terhadap width dari disk
		lastIndex = diskWidth;
		diskWidth = (diskWidth - 1) / width / 2;
		int color = consoleAttr;

		// atur warna berdasarkan width dari disk
		switch (diskWidth)
		{
			case 1: color = 12; break; // merah
			case 2: color = 14; break; // kuning
			case 3: color = 10; break; // hijau
			case 4: color = 9; break; // biru
			case 5: color = 13; break; // ungu
		}
		SetConsoleTextAttribute(hConsole, color);
		int k;
		for (k = 0, j = i; k < lastIndex; k++, j++)
		{
			printf("%c", *(str + j));
		}
		SetConsoleTextAttribute(hConsole, consoleAttr);

		// loop kata berikutnya dimulai dengan posisi setelah spasi ditemukan
		i += lastIndex - 1;
	}
	printf("\n");
}
/**
 * Menampilkan tampilan dari tower
 * @author Ihsan Fauzan Hanif
 */
void printTower(Game* g)
{
	// Karakter yang ditampilkan pada terminal (berdasarkan kode ASCII)
	#define UI_BLOCK 219 // kotak
	#define UI_GROUND 196 // garis horizontal panjang
	#define UI_POLE 179 // garis vertikal panjang

	// size kotak yang di-print
	int sizeEach = 2;
	// panjang output: tower + spasi + panjang disk terhadap size kotak
	// (2 = tambahan kiri-kanan, 3 = banyak tower)
	int width = 3 + 3 + (g->maxDisk * (2 * sizeEach) * 3);

	// posisi tengah dari hasil print disk (3 disk):
	// lebar: 1
	// ---|--- ---|--- ---|---
	// 4 - 12 - 20
	// lebar: 2
	// ------|------ ------|------ ------|------
	// 7 - 21 - 35
	// lebar: 3
	// ---------|--------- ---------|--------- ---------|---------
	// 10 - 30 - 50
	// lebar: 4
	// ------------|------------
	// 13 - ? - ?
	// didapat rumus: sizeEach * maxDisk + 1

	// posisi tengah dari satu disk
	int midPos = sizeEach * g->maxDisk + 1;

	// posisi tengah dari disk terhadap tower (sesuai kalkulasi diatas)
	int middlePos[3] = {
		midPos - 1,
		midPos * 3 - 1,
		midPos * 5 - 1
	};

	char* output = malloc(width + 1);
	int height = g->maxDisk + 1;

	int validIndex = g->left.top - 1;
	int* diskLeft = &g->left.width[validIndex < 0? 0 : validIndex];
	validIndex = g->middle.top - 1;
	int* diskMiddle = &g->middle.width[validIndex < 0? 0 : validIndex];
	validIndex = g->right.top - 1;
	int* diskRight = &g->right.width[validIndex < 0? 0 : validIndex];

	int heightDiskLeft = getDiskCount(&(g->left));
	int heightDiskMiddle = getDiskCount(&(g->middle));
	int heightDiskRight = getDiskCount(&(g->right));
	printf("\n");

	// loop setiap baris output
	int i, j;
	for (i = height + 1; i > 0; i--)
	{
		// set blok memori dengan spasi
		*(output + width) = (char)0;
		memset(output, ' ', width);

		// jika i = baris terakhir, set posisi tengah dengan nomor dari tower-nya
		if (i == 0 + 1)
		{
			memset(output, UI_GROUND, width);
			*(output + middlePos[0]) = '1';
			*(output + middlePos[1]) = '2';
			*(output + middlePos[2]) = '3';
		}
		else if (i > 0)
		{
			// nilai tengahnya pasti tiang dari tower
			*(output + middlePos[0]) = *(output + middlePos[1]) = *(output + middlePos[2]) = UI_POLE;

			// loop untuk setiap disk
			for (j = 0; j < 3; j++)
			{
				int **diskPtr = (j == 0)? &diskLeft : (j == 1)? &diskMiddle : &diskRight;
				int *heightDisk = (j == 0)? &heightDiskLeft : (j == 1)? &heightDiskMiddle : &heightDiskRight;

				if (!diskPtr || !*diskPtr) continue;
				if (i - 1 <= *heightDisk)
				{
					// copy nilai UI_BLOCK ke output
					int blockLen = **diskPtr * sizeEach * 2 + 1;
					int pos = middlePos[j] - **diskPtr * sizeEach;
					memset(output + pos, UI_BLOCK, blockLen);

					// mundurkan address pada pointer
					*diskPtr = (&(**diskPtr) - 1);
				}
			}
		}
		// print hasil dari proses pembuatan output menara (per baris)
		printTowerStr(output, sizeEach);
	}
	free(output);

	// lupakan pendefinisian tadi
	#undef UI_BLOCK
	#undef UI_POLE
	#undef UI_GROUND
}
/**
 * Menjalankan lojik dari permainan
 * @author Ihsan Fauzan Hanif
 */
void *gameRun(void *argsData)
{
	bool showInvalidMsg = false;
	Runner* runner = (Runner*)argsData;
	pthread_t* thTimer = runner->threadTimer;
    Game* game = *(runner->game);
	game->state = NONE;
    while (true)
    {
		cls();
		printf("-------------------------------------------------\n");
		printf("\t\tTower of Hanoi\n");
		printf("-------------------------------------------------\n");
        if (game->timeLeft <= 0 && game->mode == ORIGINAL)
		{
			// permainan kalah jika waktu habis pada mode original
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			CONSOLE_SCREEN_BUFFER_INFO csbi = {};
			
			GetConsoleScreenBufferInfo(hConsole, &csbi);
			SetConsoleTextAttribute(hConsole, 12);
			printf("\nWaktu Habis! Tekan apapun untuk melanjutkan\n\n");
			SetConsoleTextAttribute(hConsole, csbi.wAttributes);

			// hentikan timer
			pthread_cancel(*thTimer);
			game->state = LOSE;
		}
		else printf("\n\n");
		printTower(game);
		
		if (game->state != NONE) break;
        if (game->isPaused)
		{
			cls();
			printf("-------------------------------------------------\n");
			printf("\t\tTower of Hanoi\n");
			printf("-------------------------------------------------\n\n\n");
			printTower(game);
			printf("\n[GAME DIJEDA]\n");
			if (game->mode == ORIGINAL) printf("\nWaktu tersisa: %d detik", game->timeLeft);	
			printf("\n[Enter] Lanjutkan Permainan\n[ESC] Menyerah\n\nInput: ");
			while (true)
			{
				// selagi dijeda, jika menerima key input ENTER lanjutkan permainan, jika ESC
				// permainan berakhir (kalah)
				char input = getch();
				fflush(stdin);
				if ((int)input == ENTER)
				{
					game->isPaused = false;
					break;
				}
				else if ((int)input == ESC)
				{
					game->state = LOSE;
					break;
				}
			}
		}
        else
        {
			// terima input dari pemain
			printf("\n[P] Pause Game\n");
			if (game->mode == PRACTICE)
			{
				printf("[H] Show hint\n");
				printf("[Q] Menyerah\n");
			}
			printf("Masukkan nomor menara asal dan tujuan yang dipisahkan spasi untuk memindahkan disk.\n");
			printf("\nTotal langkah: %d\n", game->moveCount);
			if (showInvalidMsg)
			{
				printf("\nInput tidak valid!\n");
				showInvalidMsg = false;
			}
			printf("\nInput: ");
			char input[10] = {'\000'};
			fgets(input, 10, stdin);
			fflush(stdin);

			// pengkondisian input pemain
			input[strlen(input) - 1] = (char)0;
			if (game->mode == PRACTICE)
			{
				if (strcmp(input, "H") == 0 || strcmp(input, "h") == 0)
				{
					cls();
					showStep(game, game->maxDisk);
					printf("\n");
					printf("\nTekan 'Enter' untuk melanjutkan");
					while (true)
					{
						// keluar dari menu ini jika input key-nya ENTER
						char input = getch();
						fflush(stdin);
						if ((int)input == ENTER) break;
					}
					continue;
				}
				if (strcmp(input, "Q") == 0 || strcmp(input, "q") == 0)
				{
					game->state = LOSE;
					continue;
				}
			}
			if (strcmp(input, "P") == 0 || strcmp(input, "p") == 0)
			{
				game->isPaused = true;
				continue;
			}

			// input char array ke angka (input tidak langsung angka karena input bisa
			// berupa char array)
			char *pSrc = strtok(input, " ");
			char *pDest = strtok(NULL, " ");

			int src = atoi(pSrc);
			int dest = atoi(pDest);
			if (src < 1 || src > 3 || dest < 1 || dest > 3)
			{
				showInvalidMsg = true;
				continue;
			}

			Tower *from = src == 1? &game->left : src == 2? &game->middle : &game->right;
			Tower *to = dest == 1? &game->left : dest == 2? &game->middle : &game->right;

			int topSrc = from->top > 0? from->width[from->top - 1] : 0;
			int topDest = to->top > 0? to->width[from->top - 1] : 0;

			// pindahkan disk jika disk asal lebih kecil dari tujuan, atau tujuannya kosong
			// dan juga posisinya harus berbeda
			if (
				(topSrc > 0 && topSrc < topDest) ||
				(topDest == 0 && topSrc != topDest)
			)
			{
				moveDisk(from, to);
				game->moveCount++;
				// jika total disk di tower kanan sama dengan jumlah maksimum maka pemain menang
				if (getDiskCount(&game->right) == game->maxDisk)
				{
					game->state = WIN;
					
					// hentikan timer
					pthread_cancel(*thTimer);
				}
			}
			else showInvalidMsg = true;
        }
    }
    return NULL;
}
/**
 * Menjalankan timer dari permainan
 * @author Ihsan Fauzan Hanif
 */
void *gameTimer(void *argsData)
{
	Runner *runner = (Runner*) argsData;
	Game* game = *(runner->game);

	// toleransi waktu satu detik untuk bermain
	sleep(1);

	// inisialisasi koordinat untuk mengupdate timer
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi = {};
	COORD timerCoord;
	timerCoord.X = 0;
	timerCoord.Y = 4;

    while (game->timeLeft > -1 && game->state == NONE)
    {
        if (!game->isPaused && game->mode == ORIGINAL)
		{
			// jika game tidak dijeda dan modenya original, maka timer setiap satu detik
			// mengupdate tampilan terminal
			GetConsoleScreenBufferInfo(hConsole, &csbi);
			SetConsoleCursorPosition(hConsole, timerCoord);
			printf("                         ");
			SetConsoleCursorPosition(hConsole, timerCoord);

			// warnanya merah ketika timer tinggal 4 detik lagi
			if (game->timeLeft < 5) SetConsoleTextAttribute(hConsole, 12);
			if (game->timeLeft == 0)
			{
				// pemain kalah jika waktu habis
				printf("Waktu Habis! Tekan apapun untuk melanjutkan");
				game->state = LOSE;
			}
			else printf("Waktu Tersisa: %d detik", game->timeLeft);

			// kembali ke koordinat untuk memasukkan input
			SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
			SetConsoleTextAttribute(hConsole, csbi.wAttributes);
			game->timeLeft--;
		}
        sleep(1);
    }
    return NULL;
}
/**
 * Menampilkan taktik bermain Tower of hanoi@author 
 * Diana Fauziah
 * 07/22/21
 */
void showStep(Game *game, int choose){
	cls();
	printf("===============================================================\n");
	printf("\t\tTAKTIK PERMAINAN TOWER OF HANOI\n");
	printf("===============================================================\n\n");
	
	printf("%d Cakram\n", choose);
	printf("-------------------------------------------\n");
	printf("1. Gunakan rumus = 2^banyaknya_disk - 1, untuk menghitung jumlah minimal langkah\n");
	printf("2. untuk kasus ini terdapat %d cakram berarti -> 2^%d - 1 = %d (langkah)\n", choose, choose, getMinMoves(choose));
	if (choose == 1){
		printf("3. disk 1 -> tower 3\n");
	}else if (choose == 2){
		printf("3. disk 1 -> tower 3\n");
		printf("4. disk 2 -> tower 2\n");
		printf("5. disk 1 -> tower 2\n");
	}else if (choose == 3){
		printf("3. disk 1 -> tower 3\n");
		printf("4. disk 2 -> tower 2\n");
		printf("5. disk 1 -> tower 2\n");
		printf("6. disk 3 -> tower 3\n");
		printf("7. disk 1 -> tower 1\n");
		printf("8. disk 2 -> tower 3\n");
		printf("9. disk 1 -> tower 3\n");
	}else if (choose == 4){
		printf("3. disk 1 -> tower 3\n");
		printf("....................\n");
		printf("17. disk 1 -> tower 2\n");
	}else if (choose == 5){
		printf("3. disk 1 -> tower 3\n");
		printf("....................\n");
		printf("34. disk 1 -> tower 2\n");
	}
}
/**
 * Inisialisasi pengaturan sistem pada game
 * @author Ihsan Fauzan Hanif
 */
void initializeGameSystem(Game* game)
{
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL); // set agar pthread bisa dicancel
	createGame(game); // inisialisasi game
}
