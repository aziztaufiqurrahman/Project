#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#include "include/all.h"

/**
 * Menu untuk memulai permainan baru
 * @author M Aziz Taufiqurrahman
 */
void menuPlayGame(Game *game)
{
	cls();
	createGame(game);
	printSaveGame(); 
	printf("[0]. Kembali\n\n");
	printf("Masukkan posisi yang akan digunakan untuk menyimpan permainan: "); 
	scanf("%d", &game->index); 

	// set index atau posisi dari permainan pada data save game
	// (hitungan dimulai dari 0)
	if (game->index <= 0 || game->index > MAX_SAVED_GAME) return;
	game->index--; 

	game->towerLevel = 1;
	fflush(stdin);
	printf ("Silakan, masukan nama anda : ");
	scanf("%[^\n]s", game->playerName); 
	fflush(stdin);
	saveGame(game, game->index);
	menuLobby(game);
}
/**
 * Menu untuk memuat permainan lama (yang telah tersimpan)
 * @author M Aziz Taufiqurrahman
 */
void menuLoadGame(Game *game) {
	int pilihan;
	cls();
	int count = printSaveGame();
	printf("[0]. Kembali\n\n");
	printf("Masukkan posisi dari game yang ingin dilanjutkan : ");  
	scanf ("%d", &pilihan); 
	fflush(stdin);
	if (pilihan <= 0 || pilihan > MAX_SAVED_GAME) return;
	// ambil data permainan berdasarkan index/pilihan (hitungan
	// dimulai dari 0)
	*game = loadGame(--pilihan);
	if (game->index == 0 && strlen(game->playerName) == 0) return;
	menuLobby(game);
}
/**
 * Menu untuk membuat permainan yang dikustomisasi oleh pemain
 * @author
 * Diana Fauziah
 * 07/21/21
 */
void menuPracticeGame(Game *game)
{
	while(true){
	cls();
	createGame(game);
	printf("-----------------MENU PRACTICE GAME---------------\n\n");
	printf("Masukan Banyaknya disk pada permainan : ");
	scanf("%d", &game->maxDisk);
	fflush(stdin);
		if(game->maxDisk == 1 || game->maxDisk== 2 || game->maxDisk == 3 ||game->maxDisk == 4 || game->maxDisk == 5){
			game->mode = PRACTICE;
			menuLobby(game);
			return;
		}	
	}
}
/**
 * Menu untuk menampilkan top 10 pemain dengan skor tertinggi
 * @author M Aziz Taufiqurrahman
 */
void menuHighScore(Game *game)
{
	char pilihan;
	cls();
	printf ("Berikut ini merupakan daftar 10 pemain dengan skor tertinggi : \n");
	int count = printAllHighScore();
	if (count > 0)
	{
		printf ("Hapus High Score? [Y/N] ");
		scanf ("%c", &pilihan);
		fflush(stdin);
		switch (pilihan) {
			case 'Y' :
			case 'y' :
				deleteAllHighScore();
				return menuHighScore(game);
				break;
			case 'N' :
			case 'n' :
				break;
			default : printf ("Anda memasukkan nilai yang salah :( ");
		}
	}
	system("pause");
}
/**
 * Menu untuk menampilkan informasi mengenai game dan/atau developer
 * @author
 * Diana Fauziah
 * 07/21/21
 */
void menuCredits(Game *game)
{
	cls();
	printf("***********************************************************************************\n");
	printf("\t\t TOWER OF HANOI\n");
	printf("***********************************************************************************\n\n");
	printf("Permainan yang bertujuan untuk melatih kemampuan\n");
	printf("Matematis anda dalam memperhitungkan langkah untuk\n");
	printf("menyelesaikan permasalahan yang dilakukan dengan cara\n");
	printf("memindahkan seluruh disk pada tower yang ada di ujung\n");
	printf("===================================================================================\n\n");
	printf("--------------------------------------------------------\n");
	printf("|Tower of Hanoi dibuat oleh :							|\n");
	printf("|Diana Fauziah - Tunjukkan Versi Terbaik Anda!!!!   	|\n");
	printf("|Ihsan Fauzan Hanif - Orang yang menyukai pemrograman  	|\n");
	printf("|M Aziz Taufiqurrahman                                 	|\n");
	printf("--------------------------------------------------------\n");
	system("pause");
}
/**
 * Menu untuk keluar dari program
 * @author
 * Diana Fauziah
 * 07/21/21
 */
void menuExit(Game *game)
{
    char ch;
	cls();
    printf("-------------------------------------------------\n");
    printf("|Apakah Anda yakin ingin meninggalkan permainan? |\n");
    printf("|Tekan [ESC] untuk keluar                        |\n");
    printf("=================================================\n");
    do {
		// jika tombol yang ditekan itu ESC, hentikan program
        ch = getch();
        if(ch == ESC){
        	exit(0);
        }
		else break;
    } while(ch != ESC);
}
/**
 * Menu sebagai tempat berhenti sesaat sebelum permainan dimulai
 * @author M Aziz Taufiqurrahman
 */
void menuLobby(Game *game) {
	int pilihan;
	cls();
	printf ("1. Mulai Permainan\n");
	printf ("2. Menu Utama\n");
	printf ("Masukkan pilihan Anda : ");
	scanf ("%d", &pilihan);
	fflush(stdin);
	switch (pilihan) {
		case 1 : menuExec(game); break;
		case 2 : menuMain(game); break;
		default : printf ("Mohon maaf Anda salah dalam input nilai :( ");
	}
}
/**
 * Menu utama dalam permainan
 * @author Ihsan Fauzan Hanif
 */
void menuMain(Game *game)
{
	bool showInvalidMsg = false;

	// pointer ke fungsi menu yang digunakan pada program
	void (*menuSelect[6])(Game*) = {
		menuPlayGame,
		menuLoadGame,
		menuPracticeGame,
		menuHighScore,
		menuCredits,
		menuExit
	};
	while (true)
	{
		cls();
		printf("--------------------------------------------------------\n");
		printf("\t\tTower of Hanoi\n");
		printf("--------------------------------------------------------\n");
		printf("\n[1]. Permainan Baru\n");
		printf("[2]. Lanjutkan Permainan\n");
		printf("[3]. Permainan Kustom\n");
		printf("[4]. Skor Tertinggi\n");
		printf("[5]. Tentang Permainan\n");
		printf("[6]. Keluar\n");

		// tampilkan pesan jika input tidak valid
		if (showInvalidMsg)
		{
			printf("\nInput tidak valid!\n");
			showInvalidMsg = false;
		}
		printf("\nInput: ");
		int input = 0;
		scanf("%d", &input);
		fflush(stdin);
		input--;
		if (input < 0 || input > 5) showInvalidMsg = true;
		else
		{
			// panggil fungsi via pointer
			menuSelect[input](game);
		}
	}
}
/**
 * Menu untuk mengeksekusi permainan
 * @author Ihsan Fauzan Hanif
 */
void menuExec(Game *game)
{
	int state = gameEntry(game);
	switch (state)
	{
	case WIN: menuGameWin(game); break;
	case LOSE: menuGameLose(game); break;
	default: menuGameResolve(game, game->state? true : false); break;
	}
	return menuMain(game);
}
/**
 * Menu ketika pemain menang pada mode ORIGINAL
 * @author Ihsan Fauzan Hanif
 */
void menuGameWin(Game* game)
{
	// update skor jika menang
	// perhitungan skor:
	// skor = skor + (level * 10) + sisa waktu tersisa - jumlah langkah
	if (game->towerLevel == 5) game->score += 500;
	else game->score += (game->towerLevel * 10) + game->timeLeft - game->moveCount;
	printf("Skor Anda: %d\n", game->score);
	if (game->towerLevel < 5)
	{
		game->towerLevel++;
		saveGame(game, game->index);
		printf("Anda telah naik level! Lanjutkan sekarang? [Y/N] ");
		char input = (char)0;
		scanf("%c", &input);
		fflush(stdin);
		if (input == 'Y' || input == 'y') return menuLobby(game);
	}
	else
	{
		// hanya simpan skor dan data bahwa level sudah max kalau sudah mencapai
		// level 5
		game->isLevelMax = true;
		saveGame(game, game->index);
		printf("Selamat! Anda telah menyelesaikan semua level.\n");
		printf("Untuk mendapatkan skor lagi, anda bisa mengulangi level ini.\n\n");
		printf("Tekan tombol apapun untuk melanjutkan");
		getch();
		fflush(stdin);
	}
}
/**
 * Menu ketika pemain kalah pada mode ORIGINAL
 * @author Ihsan Fauzan Hanif
 */
void menuGameLose(Game* game)
{
	// simpan skor hasil permainan jika kalah dalam permainan, juga hapus data
	// permainannya karena dilarang untuk mengulangi permainan ketika sudah kalah
	saveHighScore(*game);
	deleteGame(game->index);
	printf("Skor Anda: %d\n", game->score);
	printf("Permainan tidak dapat diulangi.\n");
	printf("Tekan tombol apapun untuk melanjutkan");
	getch();
	fflush(stdin);
}
/**
 * Menu ketika pemain menang ataupun kalah pada mode PRACTICE
 * @author Ihsan Fauzan Hanif
 */
void menuGameResolve(Game* game, bool isWin)
{
	printf("Ulangi permainan? [Y/N] ");
	char input = (char)0;
	scanf("%c", &input);
	fflush(stdin);

	if (input == 'Y' || input == 'y')
	{
		game->moveCount = 0;
		return menuLobby(game);
	}
}
