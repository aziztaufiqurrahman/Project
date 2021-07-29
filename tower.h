/**
 * Kelompok 6
 * 
 * Anggota:
 * 201524003 - Diana Fauziah
 * 201524011 - Ihsan Fauzan Hanif
 * 201524014 - Muhammad Aziz Taufiqurrahman
 * 
 * tower.h
 * Struktur data yang merepresentasikan unit Stack yang
 * dikhususkan untuk permainan Tower of Hanoi.
 */

#ifndef __TOWER
#define __TOWER

#include <stdbool.h>
#include "all.h"

// Pointer pada disk/cakram
typedef struct _Disk* Address;

// Disk pada menara
typedef struct _Disk {
    int width;
    Address next;
} Disk;

// Tower
typedef struct _Tower {
    Address top;
} Tower;

/**
 * Inisialisasi tower, bertujuan untuk mengeset agar isi dari tower kosong
 * @author M Aziz Taufiqurrahman
 */
void createTower(Tower *tower);
/**
 * Inisialisasi disk, bertujuan untuk mengatur agar disk memiliki isi (panjang) sesuai
 * dengan width
 * @author Diana Fauziah
 */
void createDisk(Address disk, int width);
/**
 * Membuat disk baru dengan panjang disk yang telah ditentukan
 * @author M Aziz Taufiqurrahman
 */
Address allocate(int width);
/**
 * Membebaskan memori yang dipesan oleh pointer pada disk
 * @author Ihsan Fauzan Hanif
 */
void deallocate(Address disk);
/**
 * Mengecek apakah tower memiliki disk atau tidak
 * @author Diana Fauziah
 */
bool isEmpty(Tower tower);
/**
 * Memasukkan disk pada tower, dengan panjang disk yang diminta oleh width
 * @author Diana Fauziah
 */
void push(Tower *tower, int width);
/**
 * Menghapus disk pada tower, dengan panjang disk yang ditampung oleh width
 * @author M Aziz Taufiqurrahman
 */
void pop(Tower *tower, int* width);
/**
 * Mendapatkan jumlah disk yang berada pada satu tower
 * @author Ihsan Fauzan Hanif
 */
int getDiskCount(Tower* tower);

#endif
