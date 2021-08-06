    /**
 * Kelompok 6
 * 
 * Anggota:
 * 201524003 - Diana Fauziah
 * 201524011 - Ihsan Fauzan Hanif
 * 201524014 - Muhammad Aziz Taufiqurrahman
 * 
 * menu.h
 * Klasifikasi modul yang digunakan sebagai menu pada program
 */
#ifndef __MENU
#define __MENU

#include "all.h"

/**
 * Menu untuk memulai permainan baru
 * @author M Aziz Taufiqurrahman
 */
void menuPlayGame(Game *game);
/**
 * Menu untuk memuat permainan lama (yang telah tersimpan)
 * @author M Aziz Taufiqurrahman
 */
void menuLoadGame(Game *game);
/**
 * Menu untuk membuat permainan yang dikustomisasi oleh pemain
 * @author Diana Fauziah
 */
void menuPracticeGame(Game *game);
/**
 * Menu untuk menampilkan top 10 pemain dengan skor tertinggi
 * @author M Aziz Taufiqurrahman
 */
void menuHighScore(Game *game);
/**
 * Menu untuk menampilkan informasi mengenai game dan/atau developer
 * @author Diana Fauziah
 */
void menuCredits(Game *game);
/**
 * Menu untuk keluar dari program
 * @author Diana Fauziah
 */
void menuExit(Game *game);
/**
 * Menu sebagai tempat berhenti sesaat sebelum permainan dimulai
 * @author M Aziz Taufiqurrahman
 */
void menuLobby(Game *game);
/**
 * Menu utama dalam permainan
 * @author Ihsan Fauzan Hanif
 */
void menuMain(Game *game);
/**
 * Menu untuk mengeksekusi permainan
 * @author Ihsan Fauzan Hanif
 */
void menuExec(Game *game);
/**
 * Menu ketika pemain menang pada mode ORIGINAL
 * @author Ihsan Fauzan Hanif
 */
void menuGameWin(Game* game);
/**
 * Menu ketika pemain kalah pada mode ORIGINAL
 * @author Ihsan Fauzan Hanif
 */
void menuGameLose(Game* game);
/**
 * Menu ketika pemain menang ataupun kalah pada mode PRACTICE
 * @author Ihsan Fauzan Hanif
 */
void menuGameResolve(Game* game, bool isWin);

#endif
