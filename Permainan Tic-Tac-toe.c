/*Program	: Aplikasi Permainan Tic-Tac-toe.c
Deskripsi 	: Aplikasi permainan tic tac toe dengan pilihan papan 3x3,5x5, dan 7x7. Mode permainan pada aplikasi ini bisa dengan komputer.
			: Pada mode komputer, disisipkan kecerdasan dengan metode minimax. 
Author		: Muhammad Aziz Taufiqurrahman - 201524014
			: Hafiz Maulana Azhar - 201524009
Compiler	: Dev-C++
*/ 

#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>


/*VARIABEL GLOBAL*/
int Generate=1; 
int game; 
int menang = 0 , seri = 0, kalah = 0;

struct SaveScore{
		char NamaPemain[50];
		int skor;
	}; 


/*INISIALISASI MODUL*/
void AboutUs();
void board3(int b[10]);
void board5(int b[26]);
void board7(int b[50]);
void CaraBermain();
int CekMenang(const int board[10]);
int CekMenang5(const int board[26]);
int CekMenang7(const int board[50]);
void DisplayPemain3(int board[10]);
void DisplayPemain5(int board[26]);
void DisplayPemain7(int board[50]);
void fullscreen();
void GetLevel(int GiliranMain);
void gotoxy(int x, int y);
char gridChar(int i);
void GuntingKertasBatu();
void HitungSkor();
void Judul();
void LangkahKomputerMudah3(int board[10]);
void LangkahKomputerMudah5(int board[26]);
void LangkahKomputerMudah7(int board[50]);
void LangkahKomputerSulit3(int board[10]);
void LangkahKomputerSulit5(int board[26]);
void LangkahKomputerSulit7(int board[50]);
void LangkahPemain3(int board[10]);
void LangkahPemain5(int board[26]);
void LangkahPemain7(int board[50]);
void loading();
int main();
void Menengah3(int GiliranMain);
void Menengah5(int GiliranMain);
void Menengah7(int GiliranMain);
void MenuUtama();
int minimax(int board[10], int player);
int minimax5(int board[26], int player);
int minimax7(int board[50], int player);
void Mudah3(int GiliranMain);
void Mudah5(int GiliranMain);
void Mudah7(int GiliranMain);
void PilihPapan();
void PilihLevel();
void SimpanSkor(int skor);
void showScore();
void SortScore();
void Sulit3();
void Sulit5();
void Sulit7();
void timer(float persentase);
void setcolor(unsigned short color);

/*===========================================================================================================================================
===========================================================================================================================================*/
void timer(float persentase) {

	clock_t endwait;
	endwait=clock()+persentase*CLOCKS_PER_SEC;
	while(clock()<endwait){};	
}

void fullscreen(){

	keybd_event(VK_MENU,0x38,0,0);
	keybd_event(VK_RETURN,0x1c,0,0);
	keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);
	keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);
}


void gotoxy(int x, int y){
	
	HANDLE hConsoleOutput;  
	COORD dwCursorPosition;  
	dwCursorPosition.X = x;  
	dwCursorPosition.Y = y;  
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);  
	SetConsoleCursorPosition(hConsoleOutput,dwCursorPosition);   
}


void Judul(){

/*BEGIN PROCEDURE_JUDUL*/
		
	/*baris 1*/
	gotoxy(58,5); printf("ÛÛÛÛÛÛÛÛÛÛÛÛÛ\n");
	gotoxy(76,5); printf("ÛÛÛÛÛÛÛÛÛÛÛÛÛ\n");
	gotoxy(94,5); printf("ÛÛÛÛÛÛÛÛÛÛÛÛÛ\n");
	
	/*baris 2*/
	gotoxy(58,6); printf("ÛÛÛÛÛÛÛÛÛÛÛÛÛ\n");
	gotoxy(76,6); printf("ÛÛÛÛÛÛÛÛÛÛÛÛÛ\n");
	gotoxy(94,6); printf("ÛÛÛÛÛÛÛÛÛÛÛÛÛ\n");
	
	/*baris 3*/
	gotoxy(62,7); printf("ÛÛÛÛÛ\n");
	gotoxy(80,7); printf("ÛÛÛÛÛ\n");
	gotoxy(98,7); printf("ÛÛÛÛÛ\n");
	
	/*baris 4*/
	gotoxy(62,8); printf("ÛÛÛÛÛ\n");
	gotoxy(80,8); printf("ÛÛÛÛÛ\n");
	gotoxy(98,8); printf("ÛÛÛÛÛ\n");
	
	/*baris 5*/
	gotoxy(62,9); printf("ÛÛÛÛÛ\n");
	gotoxy(80,9); printf("ÛÛÛÛÛ\n");
	gotoxy(98,9); printf("ÛÛÛÛÛ\n");
	
	/*baris 6*/
	gotoxy(62,10); printf("ÛÛÛÛÛ\n");
	gotoxy(80,10); printf("ÛÛÛÛÛ\n");
	gotoxy(98,10); printf("ÛÛÛÛÛ\n");
		
	/*baris 7*/
	gotoxy(62,11); printf("ÛÛÛÛÛ\n");
	gotoxy(80,11); printf("ÛÛÛÛÛ\n");
	gotoxy(98,11); printf("ÛÛÛÛÛ\n");
	
	/*baris 8*/
	gotoxy(62,12); printf("ÛÛÛÛÛ\n");
	gotoxy(80,12); printf("ÛÛÛÛÛ\n");
	gotoxy(98,12); printf("ÛÛÛÛÛ\n");


	gotoxy(76,14);printf("TIC-TAC-TOE");
	gotoxy(67,16);printf("S E L A M A T    D A T A N G !");
	gotoxy(67,18);printf("MULAI PERMAINAN DARI MANA NIH?");
	
/*END PROCEDURE_JUDUL*/
}


void PilihLevel(){

	int pilihlevel; //variabel lokal bertipe int yang berfungsi sebagai pilihan dari case menu yang tersedia
		
	system("CLS");
	
	gotoxy(70,18);printf("PILIH LEVEL");
	gotoxy(70,20);printf("[1] MUDAH\n");
	gotoxy(70,21);printf("[2] SEDANG\n");
	gotoxy(70,22);printf("[3] SULIT\n");
	gotoxy(70,23);printf("[0] Menu Utama\n");
	gotoxy(70,25);printf("Masukkan Pilihan :\n");
	gotoxy(90,25);scanf("%d",&pilihlevel);
	menang = 0;
	seri = 0;
	kalah = 0;
	Generate = 1;
	
	switch(pilihlevel){
		case 1:
			system("CLS");
			Generate=Generate*1;
			PilihPapan();
			break;
			
		case 2:
			system("CLS");
			Generate=Generate*2;
			PilihPapan();
			break;
			
		case 3:
			system("CLS");
			Generate=Generate*3;
			PilihPapan();
			break;
			
		case 0: 
			system("CLS");
			MenuUtama();
			break;
		
		default: 
			PilihLevel();
		break;
	}
}


void PilihPapan(){

	int pilihpapan; 

	system("CLS");
		
	gotoxy(70,18);printf("PILIH PAPAN");
	gotoxy(70,20);printf("[1] PAPAN 3x3\n");
	gotoxy(70,21);printf("[2] PAPAN 5x5\n");
	gotoxy(70,22);printf("[3] PAPAN 7x7\n");
	gotoxy(70,23);printf("[9] Kembali\n");
	gotoxy(70,24);printf("[0] Menu Utama\n");
	gotoxy(70,26);printf("Masukkan Pilihan :\n");
	gotoxy(90,26);scanf("%d",&pilihpapan);
	
	switch(pilihpapan){
		case 1:
			system("CLS");
			Generate=Generate*3;
			loading();
			GuntingKertasBatu();
			break;
		
		case 2:
			system("CLS");
			Generate=Generate*5;
			loading();
			GuntingKertasBatu();
			break;
		
		case 3:
			system("CLS");
			Generate=Generate*7;
			loading();
			GuntingKertasBatu();
			break;
		
		case 9:
			system("CLS");
			PilihLevel();
			break;
			
		case 0:
			system("CLS");
			MenuUtama();
			break;
		
		default: 
			PilihPapan();
		break;
	}
}


void GuntingKertasBatu(){
//author	: http://deriyuliansyah.blogspot.com/2014/04/game-gunting-batu-dan-kertas-bahasa-c.html

    srand(time(NULL)); 
    int pemain; 
    int musuh; 
    int GiliranMain;
    system("CLS"); //berfungsi untuk clear screen atau membersihkan layar(mengosongkan layar)

        musuh = rand()%3; //inisialisasi dari pilihan musuh yang acak dari 0 hingga 2
        gotoxy(70,18);printf("MAU PILIH YANG MANA ? \n");
        gotoxy(70,20);printf("[1] Gunting\n");
        gotoxy(70,21);printf("[2] Batu\n");
        gotoxy(70,22);printf("[3] Kertas\n");
        gotoxy(70,23);printf("Masukkan Pilihan : ");
        gotoxy(90,23);scanf("%d",&pemain); 
        
		if(pemain>0 && pemain<4){
			if(musuh==0) //jika hasil acak = 0 berinisialiasi bahwa pilihan musuh adalah gunting
	        {
	            if(pemain==1) //jika pemain menginput 1 maka inisialiasinya pemain gunting
	            {
	                gotoxy(70,25);printf("Gunting Lawan Gunting (Seri)\n\n");
	                gotoxy(70,29);system("pause");
	                GuntingKertasBatu();
	            }
	            else if(pemain==2) //jika pemain menginput 2 maka inisialiasinya pemain batu
	            {
	                gotoxy(70,25);printf("Gunting Lawan Batu (Menang)\n\n");
	                gotoxy(70,27);printf("Kamu Main Pertama\n");
	                gotoxy(70,29);system("pause");
	                
	                GetLevel(1);	
	            }
	            else if(pemain==3) //jika pemain menginput 3 maka inisialiasinya pemain kertas
	            {
	                gotoxy(70,25);printf("Gunting Lawan Kertas (Kalah)\n\n");
	                gotoxy(70,27);printf("Kamu Main Kedua\n");	                
	                gotoxy(70,29);system("pause");
					
					GetLevel(2);
	            }
	        }
	        else if(musuh==1)
	        {
	            if(pemain==1) //jika pemain menginput 1 maka inisialiasinya pemain gunting
	            {
	               	gotoxy(70,25);printf("Batu Lawan Gunting (Kalah)\n\n");
	                gotoxy(70,27);printf("Kamu Main Kedua\n");
	                gotoxy(70,29);system("pause");
	               
					GetLevel(2);	                
	            }
	            else if(pemain==2) //jika pemain menginput 1 maka inisialiasinya pemain batu
	            {
	                gotoxy(70,25);printf("Batu Lawan Batu (Seri)\n\n");
	                gotoxy(70,29);system("pause");
	                GuntingKertasBatu();
	            }
	            else if(pemain==3) //jika pemain menginput 1 maka inisialiasinya pemain kertas
	            {
	                gotoxy(70,25);printf("Batu Lawan Kertas (Menang)\n\n");
					gotoxy(70,27);printf("Kamu Main Pertama\n");
	                gotoxy(70,29);system("pause");
					
					GetLevel(1);
	            }
	        }
	        if(musuh==2)
	        {
	            if(pemain==1) //jika pemain menginput 1 maka inisialiasinya pemain gunting
	            {
	                gotoxy(70,25);printf("Kertas Lawan Gunting (Menang)\n\n");
	                gotoxy(70,27);printf("Kamu Main Pertama\n");
	                gotoxy(70,29);system("pause");
	                
	                GetLevel(1);
	            }
	            else if(pemain==2) //jika pemain menginput 1 maka inisialiasinya pemain batu
	            {
	                gotoxy(70,25);printf("Kertas Lawan Batu (Kalah)\n\n");
	                gotoxy(70,27);printf("Kamu Main Kedua\n");
	                gotoxy(70,29);system("pause");
	                
            		GetLevel(2);
	            }
	            else if(pemain==3) //jika pemain menginput 1 maka inisialiasinya pemain kertas
	            {
	                gotoxy(70,25);printf("Kertas Lawan Kertas (Seri)\n\n");
	                gotoxy(70,29);system("pause");
	                GuntingKertasBatu();
	            }
	        }
		}else{
			gotoxy(65,24);printf("Angka yang Anda Masukkan Tidak Valid\n");
			getch();
			GuntingKertasBatu();
		}
}


void GetLevel(int GiliranMain){

	switch(Generate){
		case 3: 
			game = 1;
			do{
				Mudah3(GiliranMain);
				gotoxy(45,29);system("pause");
				game++;
			}while (game < 5);
			break;
		case 5:
			game = 1;
			do{
				Mudah5(GiliranMain);
				gotoxy(45,34);system("pause");
				game++;
			}while (game < 5);
			break;
		case 7: 
			game = 1; 
			do{
				Mudah7(GiliranMain);
				gotoxy(45,39);system("pause");
				game++;
			}while (game<5);
			break;
		case 6:
			game = 1;
			do{
				Menengah3(GiliranMain);
				gotoxy(45,29);system("pause");
				game++;
			}while (game < 5);	
			break;
		case 10:
			game = 1;
			do{
				Menengah5(GiliranMain);
				gotoxy(45,34);system("pause");
				game++;
			}while (game < 5);	
			break;
		case 14: 
			game = 1;
			do{
				Menengah7(GiliranMain);
				gotoxy(45,39);system("pause");
				game++;
			}while (game<5);
			break;
		case 9:
			game = 1;
			do{
				Sulit3(GiliranMain);
				gotoxy(45,29);system("pause");
				game++;
			}while (game < 5);	
			break;
		case 15:
			game = 1;
			do{
				Sulit5(GiliranMain);
				gotoxy(45,34);system("pause");
				game++;
			}while (game < 5);	
			break;
		case 21: 
			game = 1;
			do{
				Sulit7(GiliranMain);
				gotoxy(45,39);system("pause");
				game++;
			}while (game < 5);
			break;
	}
}


int CekMenang(const int board[10]){

	/*Deklarasi*/
	unsigned wins[8][3]={{1,2,3},{4,5,6},{7,8,9},{1,4,7},{2,5,8},{3,6,9},{1,5,9},{3,5,7}};
	int i;
	
	/*Proses*/
	for(i = 0; i < 8; ++i){
		if (board[wins[i][0]] != 0 &&
           board[wins[i][0]] == board[wins[i][1]] &&
           board[wins[i][0]] == board[wins[i][2]])
			return board[wins[i][2]];
	}
	return 0;
}


int CekMenang5(const int board[26]){

	/*Deklarasi*/
	unsigned wins[12][5] = {{1,2,3,4,5},{6,7,8,9,10},{11,12,13,14,15},{16,17,18,19,20},{21,22,23,24,25},{1,6,11,16,21},{2,7,12,17,22},
	{3,8,13,18,23},{4,9,14,19,24},{5,10,15,20,25},{1,7,13,19,25},{5,9,13,17,21}};
	int i;
	
	/*Proses*/
	for(i = 0; i < 12; ++i){
		if (board[wins[i][0]] != 0 &&
           board[wins[i][0]] == board[wins[i][1]] &&
           board[wins[i][0]] == board[wins[i][2]] &&
           board[wins[i][0]] == board[wins[i][3]] &&
           board[wins[i][0]] == board[wins[i][4]])
			return board[wins[i][4]];
	}
	return 0;
}

int CekMenang7 (const int board [50]) {
	/*Deklarasi*/ 
	unsigned wins [16][7] = {{1,2,3,4,5,6,7},{8,9,10,11,12,13,14},{15,16,17,18,19,20,21},{22,23,24,25,26,27,28},{29,30,31,32,33,34,35},
	{36,37,38,39,40,41,42},{43,44,45,46,47,48,49},{1,9,17,25,33,41,49},{7,13,19,25,31,37,43},{1,8,15,22,29,36,43},{2,9,16,23,30,37,44},
	{3,10,17,24,31,38,45},{4,11,18,25,32,39,46},{5,12,19,26,33,40,47},{6,13,20,27,34,41,48},{7,14,21,28,35,42,49}};
	int i;
	/*Proses*/ 
	for (i=0;i<16;++i){
		if (board[wins[i][0]] != 0 && 
		board [wins[i][0]] == board [wins[i][1]] && 
		board [wins[i][0]] == board [wins[i][2]] && 
		board [wins[i][0]] == board [wins[i][3]] && 
		board [wins[i][0]] == board [wins[i][4]] && 
		board [wins[i][0]] == board [wins[i][5]] && 
		board [wins[i][0]] == board [wins[i][6]])
		 return board[wins[i][6]];
	}
	return 0;
} 

int minimax(int board[10], int player) {

    int winner = CekMenang(board);
    if(winner != 0) return winner*player;

    int move = -1;
    int score = -2;
    int i;
    for(i = 1; i < 10; ++i) {
        if(board[i] == 0) {
            board[i] = player;
            int thisScore = -minimax(board, player*-1);
            if(thisScore > score) {
                score = thisScore;
                move = i;
            }
            board[i] = 0;
        }
    }
    if(move == -1) return 0;
    return score;
}


int minimax5(int board[26], int player) {

    int winner = CekMenang5(board);
    if(winner != 0) return winner*player;

    int move = -1;
    int score = -2;
    int i;
    for(i = 1; i < 26; ++i) {
        if(board[i] == 0) {
            board[i] = player;
            int thisScore = -minimax5(board, player*-1);
            if(thisScore > score) {
                score = thisScore;
                move = i;
            }
            board[i] = 0;
        }
    }
    if(move == -1) return 0;
    return score;
}

int minimax7(int board[50], int player) {

    int winner = CekMenang7(board);
    if(winner != 0) return winner*player;

    int move = -1;
    int score = -2;
    int i;
    for(i = 1; i < 50; ++i) {
        if(board[i] == 0) {
            board[i] = player;
            int thisScore = -minimax7(board, player*-1);
            if(thisScore > score) {
                score = thisScore;
                move = i;
            }
            board[i] = 0;
        }
    }
    if(move == -1) return 0;
    return score;
} 

void LangkahKomputerMudah3(int board[10]) {

	/*Deklarasi*/
	int i;
	int move;

	/*Proses*/
	reset:
	move = 1 + rand()% 9; // 1 adalah range angka terkecil yg akan di random, dan 9 adalah angka terbesar yang akan dirandom
		
	if(board[move] != 0){
		goto reset;
	}
	else{
		board[move] = 1;
	}
}


void LangkahKomputerMudah5(int board[26]){
    
	/*Deklarasi*/
	int i;
	int move;

	/*Proses*/
	reset:
	move = 1 + rand()% 25; // 1 adalah range angka terkecil yg akan di random, dan 25 adalah angka terbesar yang akan dirandom
		
	if(board[move] != 0){
		goto reset;
	}
	else{
		board[move] = 1;
	}
}

void LangkahKomputerMudah7(int board[50]){
    
	int i;
	int move;

	reset:
	move = 1 + rand()% 49; // 1 adalah range angka terkecil yg akan di random, dan 49 adalah angka terbesar yang akan dirandom
		
	if(board[move] != 0){
		goto reset;
	}
	else{
		board[move] = 1;
	}
} 

void LangkahKomputerSulit3(int board[10]){

	/*Deklarasi*/
	int move = -1;
	int score = -2;
	int i;

	/*Proses*/
	for(i=1; i < 10; ++i) {
		
		if(board[i] == 0){
			board[i] = 1;
			int tempScore = -minimax(board, -1);
			board[i] = 0;
			if (tempScore > score) {
				score = tempScore;
				move = i;	
			}
		}
	}
	
	board[move] = 1;
}


void LangkahKomputerSulit5(int board[26]){

	/*Deklarasi*/
	int move = -1;
	int score = -2;
	int i;

	/*Proses*/
	for(i=1; i < 26; ++i) {
		
		if(board[i] == 0){
			board[i] = 1;
			int tempScore = -minimax5(board, -1);
			board[i] = 0;
			if (tempScore > score) {
				score = tempScore;
				move = i;	
			}
		}
	}
	
	board[move] = 1;
}

void LangkahKomputerSulit7(int board[50]){

	int move = -1;
	int score = -2;
	int i;

	/*Proses*/
	for(i=1; i < 50; ++i) {
		
		if(board[i] == 0){
			board[i] = 1;
			int tempScore = -minimax7(board, -1);
			board[i] = 0;
			if (tempScore > score) {
				score = tempScore;
				move = i;	
			}
		}
	}
	
	board[move] = 1;
} 

void DisplayPemain3(int board[10]){
	
	/*Deklarasi*/
	int y; //variabel untuk menentukan koordinat y
	
	/*Process*/
	switch(CekMenang(board)){
		case -1:
			++menang;
			break;

		case 1:
			++kalah;
			break;
	}
	
	/*TAMPILAN SAAT PERMAINAN MULAI*/
	board3(board);
	gotoxy(15,2);printf("ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»");
	gotoxy(39,3);printf("º");
	gotoxy(15,3);printf("º Ronde Ke :\t %d",game);
	gotoxy(15,4);printf("ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼");
	gotoxy(43,10);printf("Pemain ( X )        Komputer ( O )\n");
	gotoxy(145,10);printf("Map");
	gotoxy(143,25);printf("Status");
	gotoxy(135,27);printf("Menang	: %d", menang);
	gotoxy(135,29);printf("Seri	: %d", seri);
	gotoxy(135,31);printf("Kalah	: %d", kalah);
	
	for(y = 0; y < 48; y++){
		gotoxy(125,y);printf("º");
	}
}


void DisplayPemain5(int board[26]){
	
	/*Deklarasi*/
	int y; //variabel untuk menentukan koordinat y
	
	/*Process*/
	switch(CekMenang5(board)){
		case -1:
			++menang;
			break;
		case 1:
			++kalah;
			break;
	}
	
	/*TAMPILAN SAAT PERMAINANA MULAI*/
	board5(board);
	gotoxy(15,2);printf("ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»");
	gotoxy(39,3);printf("º");
	gotoxy(15,3);printf("º Ronde Ke :\t %d",game);
	gotoxy(15,4);printf("ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼");
	gotoxy(43,10);printf("Pemain ( X )        Komputer ( O )\n");
	gotoxy(145,10);printf("Map");
	gotoxy(143,31);printf("Status");
	gotoxy(135,33);printf("Menang	: %d", menang);
	gotoxy(135,35);printf("Seri	: %d", seri);
	gotoxy(135,37);printf("Kalah	: %d", kalah);
	
	for(y = 0; y < 48; y++){
		gotoxy(125,y);printf("º");
	}
}

void DisplayPemain7(int board[50]){
	
	int y;
	
	/*Process*/
	switch(CekMenang7(board)){
		case -1:
			++menang;
			break;
		case 1:
			++kalah;
			break;
	}
	
	/*TAMPILAN SAAT PERMAINANA MULAI*/
	board7(board);
	gotoxy(15,2);printf("ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»");
	gotoxy(39,3);printf("º");
	gotoxy(15,3);printf("º Ronde Ke :\t %d",game);
	gotoxy(15,4);printf("ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼");
	gotoxy(43,10);printf("Pemain ( X )        Komputer ( O )\n");
	gotoxy(145,10);printf("Map");
	gotoxy(143,37);printf("Status");
	gotoxy(135,39);printf("Menang	: %d", menang);
	gotoxy(135,41);printf("Seri	: %d", seri);
	gotoxy(135,43);printf("Kalah	: %d", kalah);
	
	for(y = 0; y < 48; y++){
		gotoxy(125,y);printf("º");
	}
} 

void LangkahPemain3(int board[10]) {

	/*Deklarsi*/
	int move = 0;
		
	/*Proses*/
	do{
		begin:
		
			DisplayPemain3(board);
		
			gotoxy(45,28);printf("Masukkan Pilihan (1 - 9):");
			gotoxy(72,28);scanf("%d", &move);

			if (board[move] != 0){
				gotoxy(45, 32);printf("Langkah Tidak Valid!\n");
				gotoxy(65, 32);getch();
				goto begin;
				printf("\n");
			}
				
	}while( move >= 10 || move < 1 && board[move] == 0);
	
	board[move] = -1;
}


void LangkahPemain5(int board[26]) {

	/*Deklarsi*/
	int move = 0;
		
	/*Proses*/
	do{
		begin:
		
			DisplayPemain5(board);
		
			gotoxy(45,33);printf("Masukkan Pilihan (1 - 25):");
			gotoxy(72,33);scanf("%d", &move);
			
			if (board[move] != 0){
				gotoxy(45, 37);printf("Langkah Tidak Valid!\n");
				gotoxy(65, 37);getch();
				goto begin;
				printf("\n");
			}
	}while( move >= 26 || move < 1 && board[move] == 0);
	
	board[move] = -1;
}

void LangkahPemain7(int board[50]) {

	int move = 0;
		
	/*Proses*/
	do{
		begin:
		
			DisplayPemain7(board);
		
			gotoxy(45,38);printf("Masukkan Pilihan (1 - 49):");
			gotoxy(72,38);scanf("%d", &move);
			
			if (board[move] != 0){
				gotoxy(45, 42);printf("Langkah Tidak Valid!\n");
				gotoxy(65, 42);getch();
				goto begin;
				printf("\n");
			}
	}while( move >= 50 || move < 1 && board[move] == 0);
	
	board[move] = -1;
} 

void Mudah3(int GiliranMain){

	/*Deklarasi*/
	int board[10] = {0,0,0,0,0,0,0,0,0,0};
	
	unsigned turn;
	
	int pilihan;
	
	/*Proses*/		
	for(turn = 0; turn < 9 && CekMenang(board) == 0; ++turn){
				
		if((turn + GiliranMain) % 2 == 0) {
			LangkahKomputerMudah3(board);
		}
		else {
			LangkahPemain3(board);
		}
	}
	
	switch(CekMenang(board)) {
		case 0:
			++seri;
			DisplayPemain3(board);
			gotoxy(55,27);printf("Permainan Imbang!\n");
			if (game == 4){
				gotoxy(45,29);system("pause");
				system("CLS");
				HitungSkor();
				MenuUtama();
			}
			break;
		
		case 1:
			DisplayPemain3(board);
			gotoxy(55,27);printf("Kamu Kalah :(\n");
			if (game == 4){
				gotoxy(45,29);system("pause");
				system("CLS");
				HitungSkor();
				MenuUtama();
			}
			break;
			
		case -1:
			DisplayPemain3(board);
			gotoxy(55,27);printf("Kamu Menang!!\n");
			if (game == 4){
				gotoxy(45,29);system("pause");
				system("CLS");
				HitungSkor();
				MenuUtama();
			}
			break;
	}
}


void Mudah5(int GiliranMain){

	/*Deklarasi*/
	int board[26] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	
	unsigned turn;
	
	int pilihan;
	
	/*Proses*/		
	for(turn = 0; turn < 25 && CekMenang5(board) == 0; ++turn){

				
		if((turn + GiliranMain) % 2 == 0) {
			LangkahKomputerMudah5(board);
		}
		else {
			LangkahPemain5(board);
		}
	}
	
	switch(CekMenang5(board)) {
		case 0:
			++seri;
			DisplayPemain5(board);
			gotoxy(55,32);printf("Permainan Imbang!\n");
			if (game == 4){
				gotoxy(45,34);system("pause");
				system("CLS");
				HitungSkor();
				MenuUtama();
			}
			break;
		
		case 1:
			DisplayPemain5(board);
			gotoxy(55,32);printf("Kamu Kalah :(\n");
			if (game == 4){
				gotoxy(45,34);system("pause");
				system("CLS");
				HitungSkor();
				MenuUtama();
			}
			break;
			
		case -1:
			DisplayPemain5(board);
			gotoxy(55,32);printf("Kamu Menang!!\n");
			if (game == 4){
				gotoxy(45,34);system("pause");
				system("CLS");
				HitungSkor();
				MenuUtama();
			}
			break;
	}
}

void Mudah7(int GiliranMain){

	/*Deklarasi*/
	int board[50] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
					 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	unsigned turn;
	
	int pilihan;
	
	/*Proses*/		
	for(turn = 0; turn < 50 && CekMenang7(board) == 0; ++turn){

				
		if((turn + GiliranMain) % 2 == 0) {
			LangkahKomputerMudah7(board);
		}
		else {
			LangkahPemain7(board);
		}
	}
	
	switch(CekMenang7(board)) {
		case 0:
			++seri;
			DisplayPemain7(board);
			gotoxy(55,37);printf("Permainan Imbang!\n");
			if (game == 4){
				gotoxy(45,39);system("pause");
				system("CLS");
				HitungSkor();
				MenuUtama();
			}
			break;
		
		case 1:
			DisplayPemain7(board);
			gotoxy(55,37);printf("Kamu Kalah :(\n");
			if (game == 4){
				gotoxy(45,39);system("pause");
				system("CLS");
				HitungSkor();
				MenuUtama();
			}
			break;
			
		case -1:
			DisplayPemain7(board);
			gotoxy(55,37);printf("Kamu Menang!!\n");
			if (game == 4){
				gotoxy(45,39);system("pause");
				system("CLS");
				HitungSkor();
				MenuUtama();
			}
			break;
	}
} 

void Menengah3(int GiliranMain){

	/*Deklarasi*/
	int board[10] = {0,0,0,0,0,0,0,0,0,0};
	
	unsigned turn;
	
	int pilihan;
	
	/*Proses*/
	for(turn = 0; turn < 9 && CekMenang(board) == 0; ++turn){

		if((turn + GiliranMain) % 2 == 0) {
			if(turn < 6) {
				LangkahKomputerSulit3(board);
			}
			else{
				LangkahKomputerMudah3(board);
			}
		}
		else {
			LangkahPemain3(board);
		}
	}
	
	switch(CekMenang(board)) {
		case 0:
			++seri;
			DisplayPemain3(board);
			gotoxy(55,27);printf("Permainan Imbang!\n");
			if (game == 4){
				gotoxy(45,29);system("pause");
				system("CLS");
				HitungSkor();
				MenuUtama();
			}
			break;
		
		case 1:
			DisplayPemain3(board);
			gotoxy(55,27);printf("Kamu Kalah :(\n");
			if (game == 4){
				gotoxy(45,29);system("pause");
				system("CLS");
				HitungSkor();
				MenuUtama();
			}
			break;
			
		case -1:
			DisplayPemain3(board);
			gotoxy(55,27);printf("Kamu Menang!!\n");
			if (game == 4){
				gotoxy(45,29);system("pause");
				system("CLS");
				HitungSkor();
				MenuUtama();
			}
			break;
	}
}


void Menengah5(int GiliranMain){

	/*Deklarasi*/
	int board[26] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	
	unsigned turn;
	
	int pilihan;
	
	/*Proses*/		
	for(turn = 0; turn < 25 && CekMenang5(board) == 0; ++turn){

		if((turn + GiliranMain) % 2 == 0) {
			LangkahKomputerMudah5(board);
		}
		else {
			LangkahPemain5(board);
		}
	}
	
	switch(CekMenang5(board)) {
		case 0:
			++seri;
			DisplayPemain5(board);
			gotoxy(55,32);printf("Permainan Imbang!\n");
			if (game == 4){
				gotoxy(45,34);system("pause");
				system("CLS");
				HitungSkor();
				MenuUtama();
			}
			break;
		
		case 1:
			DisplayPemain5(board);
			gotoxy(55,32);printf("Kamu Kalah :(\n");
			if (game == 4){
				gotoxy(45,34);system("pause");
				system("CLS");
				HitungSkor();
				MenuUtama();
			}
			break;
			
		case -1:
			DisplayPemain5(board);
			gotoxy(55,32);printf("Kamu Menang!!\n");
			if (game == 4){
				gotoxy(45,34);system("pause");
				system("CLS");
				HitungSkor();
				MenuUtama();
			}
			break;
	}	
}

void Menengah7(int GiliranMain){

	int board[50] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 
					 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	
	unsigned turn;
	
	int pilihan;
	
	/*Proses*/		
	for(turn = 0; turn < 49 && CekMenang7(board) == 0; ++turn){

		if((turn + GiliranMain) % 2 == 0) {
			LangkahKomputerMudah7(board);
		}
		else {
			LangkahPemain7(board);
		}
	}
	
	switch(CekMenang7(board)) {
		case 0:
			++seri;
			DisplayPemain7(board);
			gotoxy(55,37);printf("Permainan Imbang!\n");
			if (game == 4){
				gotoxy(45,39);system("pause");
				system("CLS");
				HitungSkor();
				MenuUtama();
			}
			break;
		
		case 1:
			DisplayPemain5(board);
			gotoxy(55,37);printf("Kamu Kalah :(\n");
			if (game == 4){
				gotoxy(45,39);system("pause");
				system("CLS");
				HitungSkor();
				MenuUtama();
			}
			break;
			
		case -1:
			DisplayPemain5(board);
			gotoxy(55,37);printf("Kamu Menang!!\n");
			if (game == 4){
				gotoxy(45,39);system("pause");
				system("CLS");
				HitungSkor();
				MenuUtama();
			}
			break;
	}	
} 

void Sulit3(int GiliranMain){

	/*Deklarasi*/
	int board[10] = {0,0,0,0,0,0,0,0,0,0};
	
	unsigned turn;
	
	int pilihan;
	
	/*Proses*/
	for(turn = 0; turn < 9 && CekMenang(board) == 0; ++turn){

		
		if((turn + GiliranMain) % 2 == 0) {
			LangkahKomputerSulit3(board);
		}
		else {
			LangkahPemain3(board);
		}
	}
	
	switch(CekMenang(board)) {
		case 0:
			++seri;
			DisplayPemain3(board);
			gotoxy(45,27);printf("Permainan Imbang!\n");
			if (game == 4){
				gotoxy(45,29);system("pause");
				system("CLS");
				HitungSkor();
				MenuUtama();
				
			}
			break;
		
		case 1:
			DisplayPemain3(board);
			gotoxy(45,27);printf("Kamu Kalah :(\n");
			if (game == 4){
				gotoxy(45,29);system("pause");
				system("CLS");
				HitungSkor();
				MenuUtama();
			}
			break;
			
		case -1:
			DisplayPemain3(board);
			gotoxy(45,27);printf("Kamu Menang!!\n");
			if (game == 4){
				gotoxy(45,29);system("pause");
				system("CLS");
				HitungSkor();
				MenuUtama();
			}
			break;
	}
}


void Sulit5(int GiliranMain){

	/*Deklarasi*/
	int board[26] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	
	unsigned turn;
	
	int pilihan;
	
	/*Proses*/		
	for(turn = 0; turn < 25 && CekMenang5(board) == 0; ++turn){

		if((turn + GiliranMain) % 2 == 0) {
			LangkahKomputerSulit5(board);
		}
		else {
			LangkahPemain5(board);
		}
	}
	
	switch(CekMenang5(board)) {
		case 0:
			++seri;
			DisplayPemain5(board);
			gotoxy(55,32);printf("Permainan Imbang!\n");
			if (game == 4){
				gotoxy(45,34);system("pause");
				system("CLS");
				HitungSkor();
				MenuUtama();
			}
			break;
		
		case 1:
			DisplayPemain5(board);
			gotoxy(55,32);printf("Kamu Kalah :(\n");
			if (game == 4){
				gotoxy(45,34);system("pause");
				system("CLS");
				HitungSkor();
				MenuUtama();
			}
			break;
			
		case -1:
			DisplayPemain5(board);
			gotoxy(55,32);printf("Kamu Menang!!\n");
			if (game == 4){
				gotoxy(45,34);system("pause");
				system("CLS");
				HitungSkor();
				MenuUtama();
			}
			break;
	}
}

void Sulit7(int GiliranMain){

	int board[50] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	
	unsigned turn;
	
	int pilihan;
	
	/*Proses*/
	for(turn = 0; turn < 49 && CekMenang(board) == 0; ++turn){

		
		if((turn + GiliranMain) % 2 == 0) {
			LangkahKomputerSulit7(board);
		}
		else {
			LangkahPemain7(board);
		}
	}
	
	switch(CekMenang(board)) {
		case 0:
			++seri;
			DisplayPemain7(board);
			gotoxy(65,37);printf("Permainan Imbang!\n");
			if (game == 4){
				gotoxy(45,39);system("pause");
				system("CLS");
				HitungSkor();
				MenuUtama();
				
			}
			break;
		
		case 1:
			DisplayPemain7(board);
			gotoxy(65,37);printf("Kamu Kalah :(\n");
			if (game == 4){
				gotoxy(45,39);system("pause");
				system("CLS");
				HitungSkor();
				MenuUtama();
			}
			break;
			
		case -1:
			DisplayPemain7(board);
			gotoxy(65,37);printf("Kamu Menang!!\n");
			if (game == 4){
				gotoxy(45,39);system("pause");
				system("CLS");
				HitungSkor();
				MenuUtama();
			}
			break;
	}
} 

void HitungSkor(){

	int SkorTotal, SkorMenang, SkorSeri;
	
	switch(Generate){
		case 3:
			SkorMenang = menang*1000;
			SkorSeri = seri*500;
			SkorTotal = SkorMenang + SkorSeri;
			break;
		case 5:
			SkorMenang = menang*2000;
			SkorSeri = seri*1000;
			SkorTotal = SkorMenang + SkorSeri;
			break;
		case 7:
			SkorMenang = menang*3000;
			SkorSeri = seri*1500;
			SkorTotal = SkorMenang + SkorSeri;
			break;
		case 6:
			SkorMenang = menang*4000;
			SkorSeri = seri*2000;
			SkorTotal = SkorMenang + SkorSeri;
			break;
		case 10:
			SkorMenang = menang*5000;
			SkorSeri = seri*2500;
			SkorTotal = SkorMenang + SkorSeri;
			break; 
		case 14:
			SkorMenang = menang*6000;
			SkorSeri = seri*3000;
			SkorTotal = SkorMenang + SkorSeri;
			break;
		case 9:
			SkorMenang = menang*7000;
			SkorSeri = seri*3500;
			SkorTotal = SkorMenang + SkorSeri;
			break;
		case 15:
			SkorMenang = menang*8000;
			SkorSeri = seri*4000;
			SkorTotal = SkorMenang + SkorSeri;
			break;
		case 21:
			SkorMenang = menang*9000;
			SkorSeri = seri*4500;
			SkorTotal = SkorMenang + SkorSeri;
			break;
	}
	
	SimpanSkor(SkorTotal);
}


void SimpanSkor(int skor){

	struct SaveScore data; 
	FILE *DataSkor;
	int pilihan;
	
	DataSkor = fopen("KumpulanSkor.txt", "ab");
	gotoxy(70,22);printf("Skor kamu : %d", skor);
	data.skor = skor;

	gotoxy(65,24);printf("Masukkan nama kamu : ");
	gotoxy(86,24);scanf("%s", &data.NamaPemain);
	
	fprintf(DataSkor, "%s - %d\n", data.NamaPemain, data.skor);
	fclose(DataSkor);	
}


void SortScore(){

	FILE *arrange;
	struct SaveScore leaderboard[100];
	struct SaveScore temp;
	int n, i, j;
	
	arrange = fopen("KumpulanSkor.txt", "rb");
	n = 0;
	while(!feof(arrange)){
		fscanf(arrange, "%s - %d\n", &leaderboard[n].NamaPemain, &leaderboard[n].skor);
		n++;
	}
	fclose(arrange);
	
	for(i=0; i<n-1; i++){
		for(j=0; j<n-1; j++){
			if(leaderboard[j].skor < leaderboard[j+1].skor){
				temp = leaderboard[j];
				leaderboard[j] = leaderboard[j+1];
				leaderboard[j+1] = temp;
			}
		}
	}
	
	arrange = fopen("KumpulanSkor.txt", "wb");
	
	for(i=0; i<n; i++){
		fprintf(arrange, "%s - %d\n", leaderboard[i].NamaPemain, leaderboard[i].skor);
		};
	fclose(arrange);
}


void showScore(){

	SortScore();
   
    FILE *tampil;
    struct SaveScore data;
    int y = 5;
    
    tampil = fopen("KumpulanSkor.txt", "rb");
    
    while (!feof(tampil)) {
        fscanf(tampil, "%s - %d\n", &data.NamaPemain, &data.skor);
        gotoxy(70,2);printf("Papan Peringkat\n");
        gotoxy(70,y);printf("%s - %d\n\n", data.NamaPemain, data.skor);
    	y++;
	}
    
	gotoxy(65,y+3);system("pause");
    MenuUtama();
}


char gridChar(int i){
	
	switch(i){
		case -1:
			return 'X';
			
		case 0:
			return ' ';
		
		case 1:
			return 'O';
	}	
}


void board3(int b[10]) {
	
	int x = 50;
	system("CLS");
	
	/*TAMPILAN PAPAN YANG AKAN DIISI INPUT PLAYER*/
	gotoxy(x,15);printf("     |     |\n");
	gotoxy(x,16);printf("  %c  |  %c  |  %c\n", gridChar(b[1]), gridChar(b[2]), gridChar(b[3]));
	gotoxy(x,17);printf("_____|_____|_____\n");
	gotoxy(x,18);printf("     |     |\n");
	gotoxy(x,19);printf("  %c  |  %c  |  %c\n",gridChar(b[4]), gridChar(b[5]), gridChar(b[6]));	
	gotoxy(x,20);printf("_____|_____|_____\n");
	gotoxy(x,21);printf("     |     |\n");
	gotoxy(x,22);printf("  %c  |  %c  |  %c\n",gridChar(b[7]), gridChar(b[8]), gridChar(b[9]));
	gotoxy(x,23);printf("     |     |\n");
	/*END TAMPILAN PAPAN YANG AKAN DIISI INPUT PLAYER*/
	
		
	/*TAMPILAN PAPAN MAP*/
	gotoxy(143,12);printf("|     |\n");
	gotoxy(138,13);printf("  1  |  2  |  3\n");
	gotoxy(138,14);printf("_____|_____|_____\n");
	gotoxy(143,15);printf("|     |\n");
	gotoxy(138,16);printf("  4  |  5  |  6\n");	
	gotoxy(138,17);printf("_____|_____|_____\n");
	gotoxy(143,18);printf("|     |\n");
	gotoxy(138,19);printf("  7  |  8  |  9\n");
	gotoxy(138,20);printf("     |     |\n");
	/*END TAMPILAN PAPAN MAP*/
}


void board5(int b[26]) {
	
	system("CLS");
	/*TAMPILAN PAPAN*//*TAMPILAN PAPAN YANG AKAN DIISI INPUT PLAYER*/
	gotoxy(50,15);printf("|     |     |     |\n");
	gotoxy(45,16);printf("  %c  |  %c  |  %c  |  %c  |  %c  \n", gridChar(b[1]), gridChar(b[2]), gridChar(b[3]), gridChar(b[4]), gridChar(b[5])); //tempat penyimpanan bidak 1-5
	gotoxy(45,17);printf("_____|_____|_____|_____|_____\n");
	gotoxy(50,18);printf("|     |     |     |\n");
	gotoxy(45,19);printf("  %c  |  %c  |  %c  |  %c  |  %c  \n", gridChar(b[6]), gridChar(b[7]), gridChar(b[8]), gridChar(b[9]), gridChar(b[10]));//tempat penyimpanan bidak 6-10
	gotoxy(45,20);printf("_____|_____|_____|_____|_____\n");
	gotoxy(50,21);printf("|     |     |     |\n");
	gotoxy(45,22);printf("  %c  |  %c  |  %c  |  %c  |  %c  \n", gridChar(b[11]), gridChar(b[12]), gridChar(b[13]), gridChar(b[14]), gridChar(b[15])); //tempat penyimpanan bidak 11-15
	gotoxy(45,23);printf("_____|_____|_____|_____|_____\n");
	gotoxy(50,24);printf("|     |     |     |\n");
	gotoxy(45,25);printf("  %c  |  %c  |  %c  |  %c  |  %c  \n", gridChar(b[16]), gridChar(b[17]), gridChar(b[18]), gridChar(b[19]), gridChar(b[20])); //tempat penyimpanan bidak 16-20
	gotoxy(45,26);printf("_____|_____|_____|_____|_____\n");
	gotoxy(50,27);printf("|     |     |     |\n");
	gotoxy(45,28);printf("  %c  |  %c  |  %c  |  %c  |  %c  \n", gridChar(b[21]), gridChar(b[22]), gridChar(b[23]), gridChar(b[24]), gridChar(b[25])); //tempat penyimpanan bidak 21-25
	gotoxy(50,29);printf("|     |     |     |\n");
	/*END TAMPILAN PAPAN YANG AKAN DIISI INPUT PLAYER*/
	
	/*TAMPILAN PAPAN MAP*/
	gotoxy(137,12);printf("|     |     |     |\n");
	gotoxy(132,13);printf("  1  |  2  |  3  |  4  |  5  \n"); //tempat penyimpanan bidak 1-5
	gotoxy(132,14);printf("_____|_____|_____|_____|_____\n");
	gotoxy(137,15);printf("|     |     |     |\n");
	gotoxy(132,16);printf("  6  |  7  |  8  |  9  |  10  \n");//tempat penyimpanan bidak 6-10
	gotoxy(132,17);printf("_____|_____|_____|_____|_____\n");
	gotoxy(137,18);printf("|     |     |     |\n");
	gotoxy(132,19);printf("  11 |  12 |  13 |  14 |  15 \n"); //tempat penyimpanan bidak 11-15
	gotoxy(132,20);printf("_____|_____|_____|_____|_____\n");
	gotoxy(137,21);printf("|     |     |     |\n");
	gotoxy(132,22);printf("  16 |  17 |  18 |  19 |  20 \n"); //tempat penyimpanan bidak 16-20
	gotoxy(132,23);printf("_____|_____|_____|_____|_____\n");
	gotoxy(137,24);printf("|     |     |     |\n");
	gotoxy(132,25);printf("  21 |  22 |  23 |  24 |  25 \n"); //tempat penyimpanan bidak 21-25
	gotoxy(137,26);printf("|     |     |     |\n");	
	/*END TAMPILAN PAPAN MAP*/
}

void board7(int b[50]) {
	
	system("CLS");
	
	/*TAMPILAN PAPAN YANG AKAN DIISI INPUT PLAYER*/
	gotoxy (50,15); printf("|     |     |     |     |     |\n"); 
	gotoxy (45,16); printf("  %c  |  %c  |  %c  |  %c  |  %c  |  %c  |  %c  \n",gridChar(b[1]), gridChar(b[2]), gridChar(b[3]), gridChar(b[4]), gridChar(b[5]),gridChar(b[6]), gridChar(b[7]));
	gotoxy (45,17); printf("_____|_____|_____|_____|_____|_____|_____\n");
	gotoxy (50,18); printf("|     |     |     |     |     |\n"); 
	gotoxy (45,19); printf("  %c  |  %c  |  %c  |  %c  |  %c  |  %c  |  %c  \n",gridChar(b[8]), gridChar(b[9]), gridChar(b[10]), gridChar(b[11]), gridChar(b[12]),gridChar(b[13]), gridChar(b[14]));
	gotoxy (45,20); printf("_____|_____|_____|_____|_____|_____|_____\n"); 
	gotoxy (50,21); printf("|     |     |     |     |     |\n"); 
	gotoxy (45,22); printf("  %c  |  %c  |  %c  |  %c  |  %c  |  %c  |  %c  \n",gridChar(b[15]), gridChar(b[16]), gridChar(b[17]), gridChar(b[18]), gridChar(b[19]),gridChar(b[20]), gridChar(b[21]));
	gotoxy (45,23); printf("_____|_____|_____|_____|_____|_____|_____\n"); 
	gotoxy (50,24); printf("|     |     |     |     |     |\n"); 
	gotoxy (45,25); printf("  %c  |  %c  |  %c  |  %c  |  %c  |  %c  |  %c  \n",gridChar(b[22]), gridChar(b[23]), gridChar(b[24]), gridChar(b[25]), gridChar(b[26]),gridChar(b[27]), gridChar(b[28]));
	gotoxy (45,26); printf("_____|_____|_____|_____|_____|_____|_____\n"); 
	gotoxy (50,27); printf("|     |     |     |     |     |\n"); 
	gotoxy (45,28); printf("  %c  |  %c  |  %c  |  %c  |  %c  |  %c  |  %c  \n",gridChar(b[29]), gridChar(b[30]), gridChar(b[31]), gridChar(b[32]), gridChar(b[33]),gridChar(b[34]), gridChar(b[35]));
	gotoxy (45,29); printf("_____|_____|_____|_____|_____|_____|_____\n"); 
	gotoxy (50,30); printf("|     |     |     |     |     |\n"); 
	gotoxy (45,31); printf("  %c  |  %c  |  %c  |  %c  |  %c  |  %c  |  %c  \n",gridChar(b[36]), gridChar(b[37]), gridChar(b[38]), gridChar(b[39]), gridChar(b[40]),gridChar(b[41]), gridChar(b[42]));
	gotoxy (45,32); printf("_____|_____|_____|_____|_____|_____|_____\n"); 
	gotoxy (50,33); printf("|     |     |     |     |     |\n");
	gotoxy (45,34); printf("  %c  |  %c  |  %c  |  %c  |  %c  |  %c  |  %c  \n",gridChar(b[43]), gridChar(b[44]), gridChar(b[45]), gridChar(b[46]), gridChar(b[47]),gridChar(b[48]), gridChar(b[49])); 
	gotoxy (50,35); printf("|     |     |     |     |     |\n"); 
	
	gotoxy (131,12); printf("|     |     |     |     |     |\n"); 
	gotoxy (126,13); printf("  1  |  2  |  3  |  4  |  5  |  6  |  7  \n");
	gotoxy (126,14); printf("_____|_____|_____|_____|_____|_____|_____\n");
	gotoxy (131,15);printf("|     |     |     |     |     |\n"); 
	gotoxy (126,16); printf("  8  |  9  |  10 |  11 |  12 |  13 |  14  \n");
	gotoxy (126,17); printf("_____|_____|_____|_____|_____|_____|_____\n"); 
	gotoxy (131,18); printf("|     |     |     |     |     |\n"); 
	gotoxy (126,19); printf("  15 |  16 |  17 |  18 |  19 |  20 |  21  \n");
	gotoxy (126,20); printf("_____|_____|_____|_____|_____|_____|_____\n"); 
	gotoxy (131,21); printf("|     |     |     |     |     |\n"); 
	gotoxy (126,22); printf("  22 |  23 |  24 |  25 |  26 |  27 |  28  \n");
	gotoxy (126,23); printf("_____|_____|_____|_____|_____|_____|_____\n"); 
	gotoxy (131,24); printf("|     |     |     |     |     |\n"); 
	gotoxy (126,25); printf("  29 |  30 |  31 |  32 |  33 |  34 |  35  \n");
	gotoxy (126,26); printf("_____|_____|_____|_____|_____|_____|_____\n"); 
	gotoxy (131,27); printf("|     |     |     |     |     |\n"); 
	gotoxy (126,28); printf("  36 |  37 |  38 |  39 |  40 |  41 |  42  \n");
	gotoxy (126,29); printf("_____|_____|_____|_____|_____|_____|_____\n"); 
	gotoxy (131,30); printf("|     |     |     |     |     |\n");
	gotoxy (126,31); printf("  43 |  44 |  45 |  46 |  47 |  48 |  49  \n"); 
	gotoxy (131,32); printf("|     |     |     |     |     |\n"); 
}

void CaraBermain() {

	FILE*file;
	char length[6000];//variabel length adalah variabel lokal bertipe array of char untuk memberi batas char dari file yang dibuka
	
	file=fopen("CaraBermain.txt","r");
	
	while(fgets(length,6000,file)!=NULL){
		printf("%s", length);
	}
	
	fclose(file);
	gotoxy(65,47);printf("Tekan Tombol Untuk Kembali...\n");getch();
	//KEMBALI KE MENU UTAMA
	system("CLS");
	MenuUtama();
	
/*END PROCEDURE CARA_BERMAIN*/
}


void AboutUs() {

/*BEGIN PROCEDUR ABOUTUS*/
	FILE *file;
	char length[6000];//variabel length adalah variabel lokal bertipe array of char untuk memberi batas char dari file yang dibuka
	
	file=fopen("TentangPermainan.txt","r");
	
	while (fgets(length,6000,file)!=NULL){
		printf("%s", length);
	}
	
	fclose(file);
	
	gotoxy(65,30);printf("Tekan Tombol Untuk Melanjutkan...\n");getch();
	//KEMBALI KE MENU UTAMA
	system("CLS");
	MenuUtama();
/*END PROCEDURE ABOUTUS*/
}

void loading() {
 
 /*BEGIN PROCEDURE LOADING*/
	int x;
	gotoxy(74,19); printf ("Yakin Sudah Siap?");
	gotoxy(75,20); printf("Mohon Bersabar..");

	for(x=65;x<=67;x++){
		gotoxy(x,22);printf("Û\n");
		timer(0.5);
	}
	
	for(x=68;x<=75;x++){
		gotoxy(x,22);printf("Û\n");
		timer(0.1);
	}
	
	for(x=76;x<=86;x++){
		gotoxy(x,22);printf("Û\n");
		timer(0.02);
	}
	
	for(x=87;x<=97;x++){
		gotoxy(x,22);printf("Û\n");
		timer(0.1);
	}
	
/*END PROCEDURE LOADING*/
}


void MenuUtama() {
	
	int pilihmenu;	//PilihMenu adalah variabel lokal bertipe int yang berfungsi sebagai pilihan dari case menu	yang tersedia
	
	
	system("CLS");
	Judul();
	
	gotoxy(70,20);printf("[1] PERMAINAN BARU\n");
	gotoxy(70,21);printf("[2] CARA BERMAIN\n");
	gotoxy(70,22);printf("[3] HIGH SCORE\n");
	gotoxy(70,23);printf("[4] TENTANG PERMAINAN\n");
	gotoxy(70,24);printf("[0] KELUAR\n");
	gotoxy(70,26);printf("Masukkan Pilihan : \n");
	gotoxy(90,26);scanf("%d",&pilihmenu);

	switch(pilihmenu){
		case 1: 
			PilihLevel();
		break;
		
		case 2: 
			system("CLS");
			CaraBermain();
		break;
		
		case 3: 
			system("CLS");
			showScore();
		break;
		
		case 4: 
			system("CLS");
			AboutUs();
		break;
		
		case 0: 
			exit(1);
		break;
		
		default: 
			MenuUtama();
		break;
	}
} 

void setcolor(unsigned short color)
{
HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);

SetConsoleTextAttribute(hCon,color);
}

int main() {
	system ("COLOR 4F");
	fullscreen();
	MenuUtama();
}

