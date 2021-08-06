#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/all.h"

/**
 * Menyimpan skor dari permainan
 * @author Ihsan Fauzan Hanif
 */
void saveHighScore(Game game)
{
	// alokasi blok memori untuk menyimpan seluruh data highscore
    int maxSize = sizeof(game) * MAX_SAVED_SCORE;
    Game HSdata[MAX_SAVED_SCORE];
    memset(&HSdata, 0, sizeof(HSdata));
    
    FILE *file = fopen("score.dat", "rb");
    if (file) fread(HSdata, maxSize, 1, file);
    fclose(file);

    // ambil data highscore yang dulu, kemudian data baru dimasukkan ke dalam highscore
	// apabila record terakhir pada highscore lebih dari data baru, kemudian sortir isinya
	if (game.score < HSdata[MAX_SAVED_SCORE - 1].score) return;
    memset(&HSdata[MAX_SAVED_SCORE - 1], 0, sizeof(HSdata[MAX_SAVED_SCORE - 1]));
    memcpy(&HSdata[MAX_SAVED_SCORE - 1], &game, sizeof(game));
    sortHighScore(HSdata);

	// simpan kembali ke file save highscore
    file = fopen("score.dat", "wb");
    if (!file) return;
    int code = fwrite(HSdata, sizeof(HSdata), 1, file);
    fclose(file);
}
/**
 * Menyortir isi dari file highscore
 * @author Ihsan Fauzan Hanif
 */
void sortHighScore(Game *game)
{
    Game temp;
    int i, j;
    for (i = 0; i < MAX_SAVED_SCORE; i++)
    {
        for (j = MAX_SAVED_SCORE - 1; j > i; j--)
        {
            if (game[j].score > game[j - 1].score)
            {
                memset(&temp, 0, sizeof(Game));
                memcpy(&temp, &game[j], sizeof(Game));

                memset(&game[j], 0, sizeof(Game));
                memcpy(&game[j], &game[j - 1], sizeof(Game));
                
                memset(&game[j - 1], 0, sizeof(Game));
                memcpy(&game[j - 1], &temp, sizeof(Game));
            }
        }
    }
}
/**
 * Menghapus semua skor yang tersimpan
 * @author Ihsan Fauzan Hanif
 */
bool deleteAllHighScore()
{
    return remove("score.dat") == 0? true : false;
}
/**
 * Menampilkan seluruh daftar high score
 * @author Ihsan Fauzan Hanif
 */
int printAllHighScore()
{
	int maxSize = sizeof(Game) * MAX_SAVED_SCORE;
    Game HSdata[MAX_SAVED_SCORE] = {0};
	Game game;

    int count = 0;

	// baca semua isi file dan masukkan pada array highscore
    FILE *file = fopen("score.dat", "rb");
    if (file) fread(HSdata, maxSize, 1, file);
    fclose(file);
    printf("\n%-4s %-20s %-7s %-15s %s", "No", "Nama Pemain", "Level", "Total Langkah", "Skor");
    printf("\n--------------------------------------------------------");
	int i;
	for (i = 0; i < MAX_SAVED_SCORE; i++)
	{
		game = HSdata[i];
        printf("\n");
		if (game.index == 0 && strlen(game.playerName) == 0) printf("%-4s %-20s %-7s %-15s %s", "-", "-", "-", "-", "-");
		else
        {
            char num[4] = {0};
            char playerName[20] = {0};
            char level[7] = {0};
            char moveCount[15] = {0};
            char score[10] = {0};
            int len = strlen(game.playerName);

            itoa(i + 1, num, 10);
            memcpy(playerName, game.playerName, len >= 20? 16 : len);
            if (len >= 20) memcpy(playerName + len, "...", 3);
            itoa(game.towerLevel, level, 10);
            itoa(game.moveCount, moveCount, 10);
            itoa(game.score, score, 10);
            printf("%-4s %-20s %-7s %-15s %s", num, playerName, level, moveCount, score);
            count++;
        }
	}
    printf("\n--------------------------------------------------------\n\n");
    return count;
}
