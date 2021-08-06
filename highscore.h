    /**
 * Kelompok 6
 * 
 * Anggota:
 * 201524003 - Diana Fauziah
 * 201524011 - Ihsan Fauzan Hanif
 * 201524014 - Muhammad Aziz Taufiqurrahman
 * 
 * highscore.h
 * Klasifikasi modul yang digunakan untuk mengolah data terkait
 * dengan daftar 10 pemain dengan skor tertinggi
 */
#ifndef __HIGHSCORE
#define __HIGHSCORE

#include "all.h"

/**
 * Menyimpan skor dari permainan
 * @author Ihsan Fauzan Hanif
 */
void saveHighScore(Game game);
/**
 * Menyortir isi dari file highscore
 * @author Ihsan Fauzan Hanif
 */
void sortHighScore(Game *game);
/**
 * Menghapus semua skor yang tersimpan
 * @author Ihsan Fauzan Hanif
 */
bool deleteAllHighScore();
/**
 * Menampilkan seluruh daftar high score
 * @author Ihsan Fauzan Hanif
 */
int printAllHighScore();

#endif
