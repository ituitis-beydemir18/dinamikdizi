#ifndef DIZIISLEMLERI_H
#define DIZIISLEMLERI_H
#include <stdio.h>
#include "kayit.h"

/*=======Gerek Kalmadý=======
#define MAXKAYIT 100
*/
struct Dizi{
	int boyut; //yeni boyut deðiþkeni
	void boyutartir(); // yeni boyutartir fonksiyonu
	char *dosyaadi;
	FILE *teldefteri;
	int *indis; //Dinamik diziler için iþaretçiler tanýmlandý. - Alfabetik sýra için...
	Tel_Kayit *k; //Dinamik diziler için iþaretçiler tanýmlandý.
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