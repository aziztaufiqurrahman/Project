/**
 * Kelompok 6
 * 
 * Anggota:
 * 201524003 - Diana Fauziah
 * 201524011 - Ihsan Fauzan Hanif
 * 201524014 - Muhammad Aziz Taufiqurrahman
 * 
 * tower.c
 * Implementasi kode program dari struktur data pada file tower.h
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "include/all.h"

/**
 * Inisialisasi tower, bertujuan untuk mengeset agar isi dari tower kosong
 * @author M Aziz Taufiqurrahman
 */
void createTower(Tower *tower){
	(*tower).top = NULL;
}
/**
 * Inisialisasi disk, bertujuan untuk mengatur agar disk memiliki isi (panjang) sesuai
 * dengan width
 * @author Diana Fauziah
 */
void createDisk(Address disk, int width)
{
	disk->width = width;
	disk->next = NULL;
}
/**
 * Membuat disk baru dengan panjang disk yang telah ditentukan
 * @author M Aziz Taufiqurrahman
 * Dimodifikasi oleh : Ihsan Fauzan Hanif
 */
Address allocate(int width) {
	Address x = malloc(sizeof(Disk));
	if (x)
		{
  		x->width = width;
  		x->next = NULL;
	}
	return x;
}
/**
 * Membebaskan memori yang dipesan oleh pointer pada disk
 * @author Ihsan Fauzan Hanif
 */
void deallocate(Address disk)
{
    if (disk) free(disk);
}
/**
 * Mengecek apakah tower memiliki disk atau tidak
 * @author Diana Fauziah
 */
bool isEmpty(Tower tower)
{
	if(tower.top == NULL){
		return true;
	}else {
		return false;
	}
}
/**
 * Memasukkan disk pada tower, dengan panjang disk yang diminta oleh width
 * @author Diana Fauziah
 */
void push(Tower *tower, int width)
{
	Address p;
	
	p = allocate(width);
	if (isEmpty(*tower)){	//tower kosong
		tower->top = p;
	}else{					//tower ada isi
		p->next = tower->top;
		tower->top = p;
	}
	
}
/**
 * Menghapus disk pada tower, dengan panjang disk yang ditampung oleh width
 * @author M Aziz Taufiqurrahman
 */
void pop(Tower *tower, int* width)
{
	if ((*tower).top != NULL) {
		Disk *del = (*tower).top;
		
		if (!del->next) {
		(*tower).top = NULL;
		}
		else {
			(*tower).top = (*tower).top -> next;
		}
		*width = del->width;
		deallocate(del);
		} 
		else {
			printf ("Disk udah kosong");
		}
}
/**
 * Mendapatkan jumlah disk yang berada pada satu tower
 * @author Ihsan Fauzan Hanif
 */
int getDiskCount(Tower* tower)
{
	Address ptr = tower->top;
	int count = 0;
	while(ptr)
	{
		count++;
		ptr = ptr->next;
	}
	return count;
}
