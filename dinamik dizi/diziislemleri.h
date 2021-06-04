#ifndef DIZIISLEMLERI_H
#define DIZIISLEMLERI_H
#include <stdio.h>
#include "kayit.h"

/*=======Gerek Kalmad�=======
#define MAXKAYIT 100
*/
struct Dizi{
	int boyut; //yeni boyut de�i�keni
	void boyutartir(); // yeni boyutartir fonksiyonu
	char *dosyaadi;
	FILE *teldefteri;
	int *indis; //Dinamik diziler i�in i�aret�iler tan�mland�. - Alfabetik s�ra i�in...
	Tel_Kayit *k; //Dinamik diziler i�in i�aret�iler tan�mland�.
	void olustur();						
    void kapat();
	void ekle(Tel_Kayit *);
	int ara(char []);
    void sil(int kayitno);
    void guncelle(int kayitno, Tel_Kayit *);
	int dosyabakim();
    void diziolustur();
	void dosyayakayit();
	void listele();
	int kayitsayisi;
};
#endif