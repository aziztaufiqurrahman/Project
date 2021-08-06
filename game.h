/**
 * Kelompok 6
 * 
 * Anggota:
 * 201524003 - Diana Fauziah
 * 201524011 - Ihsan Fauzan Hanif
 * 201524014 - Muhammad Aziz Taufiqurrahman
 * 
 * game.h
 * Struktur data yang merepresentasikan sistem Game yang
 * dikhususkan untuk permainan Tower of Hanoi.
 */
#ifndef __GAME
#define __GAME

#include <stdbool.h>
#include <pthread.h>
#include "all.h"

#define MAX_LEVEL 5
#define MAX_SAVED_GAME 10
#define MAX_SAVED_SCORE 10

// Kondisi game
typedef enum _GameState {
    NONE,
    WIN,
    LOSE
} GameState;

// Tipe game yang dipilih
typedef enum _GameMode {
    ORIGINAL,
    PRACTICE
} GameMode;

// Sistem Game
typedef struct _Game {
    Tower right;
    Tower middle;
    Tower left;
    int index;
    int moveCount;
    int towerLevel;
    int maxDisk;
    int score;
    int timeLeft;
    bool isLevelMax;
    bool isPaused;
    GameMode mode;
    GameState state;
    char playerName[50];
} Game;

typedef struct _Runner {
    Game** game;
    pthread_t* threadGame;
    pthread_t* threadTimer;
} Runner;

/**
 * Inisialisasi sistem Game, bertujuan untuk mengatur agar semua
 * informasi terkait dengan Game bernilai kosong
 * @author Diana Fauziah
 */
void createGame(Game *game);
/**
 * Inisialisasi sistem game dan threading
 * @author Ihsan Fauzan Hanif
 */
void createRunner(Runner *runner);
/**
 * Mendapatkan disk maksimal yang bisa dimasukkan berdasarkan level dari tower 
 * @author M Aziz Tafiqurrahman
 */
int getMaxDisk(int towerLevel);
/**
 * Mendapatkan waktu maksimal yang bisa digunakan untuk bermain berdasarkan level dari tower
 * @author M Aziz Taufiqurrahman
 */
int getMaxTime(int towerLevel);
/**
 * Mendapatkan pergerakan minimal yang bisa dilakukan untuk menyelesaikan permainan
 * @author Ihsan Fauzan Hanif
 */
int getMinMoves(int maxDisk);
/**
 * Menampilkan taktik bermain Tower of hanoi
 * @author 
 * Diana Fauziah
 * 07/22/21
 */
void showStep(Game *game, int choose);
/**
 * Menyimpan game dengan posisi penyimpanan berdasarkan index
 * @author Ihsan Fauzan Hanif
 */
bool saveGame(Game *game, int index);
/**
 * Memuat seluruh data permainan tersimpan
 * @author Ihsan Fauzan Hanif
 */
void loadAllSaveGame(char* result, int memorySize);
/**
 * Memuat game yang terdapat pada save game berdasarkan index
 * @author Ihsan Fauzan Hanif
 */
Game loadGame(int index);
/**
 * Menghapus data game yang telah tersimpan
 * @author Ihsan Fauzan Hanif
 */
bool deleteGame(int index);
/**
 * Menampilkan daftar permainan tersimpan
 * @author Ihsan Fauzan Hanif
 */
int printSaveGame();
/**
 * Titik masuk dari permainan
 * @author Ihsan Fauzan Hanif
 */
int gameEntry(Game *game);
/**
 * Menampilkan output isi dari tower berdasarkan string.
 * @author Ihsan Fauzan Hanif
 */
void printTowerStr(char *str, int width);/**
 * Menampilkan tampilan dari tower
 * @author Ihsan Fauzan Hanif
 */
void printTower(Game* g);
/**
 * Menjalankan lojik dari permainan
 * @author Ihsan Fauzan Hanif
 */
void *gameRun(void *argsData);
/**
 * Menjalankan timer dari permainan
 * @author Ihsan Fauzan Hanif
 */
void *gameTimer(void *argsData);
/**
 * Inisialisasi pengaturan sistem pada game
 * @author Ihsan Fauzan Hanif
 */
void initializeGameSystem(Game* game);
#endif
