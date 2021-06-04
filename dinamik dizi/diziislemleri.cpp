#include "diziislemleri.h"
#include <iostream>
#include <stdlib.h>
//#include <cstdlib.h>
#include <stdio.h>
#include <string.h>
#include <iomanip>


using namespace std;


void Dizi::ekle(Tel_Kayit *ykptr){
	if(kayitsayisi >= boyut){ /*Yeni Eklenen boyutartir fonksiyonunu çaðýran kontrol*/
		boyutartir();
	}
	int tmp1,tmp2;
	int sayac = 0;
	strcpy(k[kayitsayisi].ad,ykptr->ad);
    strcpy(k[kayitsayisi].telno,ykptr->telno);
	kayitsayisi++;
    for(int m=0;m<kayitsayisi;m++)
	  {
		  
	      if((strcmp(ykptr->ad, k[m].ad)>0))
		  {  
				sayac++;
		  
		  }
		  

	  }
   tmp1 = indis[sayac];
   indis[sayac]=kayitsayisi-1;
   sayac++;
   while(sayac<=kayitsayisi){
			tmp2 = indis[sayac];
			indis[sayac] = tmp1;
			tmp1 = tmp2;
			sayac++;
		}

     for(int i=0;i<kayitsayisi;i++)
      
	 cout<<i+1<<"="<<k[indis[i]].ad<<endl;





}
/*BOYUT ARTIRMA FONKSIYONU*/
void Dizi::boyutartir(){
	Tel_Kayit *yeniBoyut;
	yeniBoyut = new Tel_Kayit[boyut*2];
	for(int i=0;i<boyut;i++){
		strcpy((yeniBoyut+i)->ad,k[i].ad);
		strcpy((yeniBoyut+i)->telno,k[i].telno);
	}
	delete []k;
	k = yeniBoyut;
	boyut = boyut * 2;
}
     
	

void Dizi::diziolustur(){
	Tel_Kayit k1,k2;
    int sayac;
	fseek(teldefteri, 0, SEEK_SET);
	while(!feof(teldefteri)){
		
		fseek(teldefteri, kayitsayisi*sizeof (Tel_Kayit), SEEK_SET);
		fread( &k[kayitsayisi], sizeof (Tel_Kayit), 1, teldefteri);		
		if(feof(teldefteri)) break;
		kayitsayisi++;
		sayac = 0;
	}


  for(int i=0;i<kayitsayisi;i++)
			cout<< i+1 <<"-"<<k[i].ad<<"\t"<< k[i].telno<<endl;


  for(int j=0;j<kayitsayisi;j++)
  {  
	  sayac=0;
      k1= k[j];
	  for(int m=0;m<kayitsayisi;m++)
	  {
		  k2=k[m];
	      if((strcmp(k1.ad, k2.ad)>0))
		  {  
				sayac++;
		  
		  }
		  
	  }
	  indis[sayac]=j;
			
  }
    
   
}


void Dizi::olustur(){    /*Oluþtur Fonksiyonununda yeni dinamik diziler*/ 
	boyut = 1; //boyut deðiþkeni initialize ediliyor
	indis = new int[boyut];
	k = new (nothrow) Tel_Kayit[boyut];
	dosyaadi="teldefteri.txt";
	teldefteri = fopen( dosyaadi, "r+" );
	if(!teldefteri){
		teldefteri = fopen( dosyaadi, "w" );
		fclose(teldefteri);
		teldefteri = fopen( dosyaadi, "r+" );
		if(!teldefteri){
			cerr << "Dosya acilamadi" << endl;
			exit(1);
		}
	}
	kayitsayisi=0;
	//indis[0]=0;
	diziolustur();
}

void Dizi::kapat(){
	dosyayakayit();
	fclose(teldefteri);
}


int Dizi::ara(char aranacak[]){
	
	int sayac=0;
	bool tumu=false;
	int bulunan,flag=0;
	if(strcmp(aranacak,"*")==0)
		tumu=true;

	for(int i=0;i<kayitsayisi;i++){
		    if(strcmp(k[indis[i]].ad,aranacak)==0)
			{ 
		      cout<<i+1<<". "<<k[indis[i]].ad<<endl;
			  bulunan=indis[i];
			  flag=1;
			}
		
	}	
	return flag;
}


void Dizi::guncelle(int kayitno, Tel_Kayit *ykptr){
	strcpy(k[indis[kayitno-1]].ad,ykptr->ad);
    strcpy(k[indis[kayitno-1]].telno,ykptr->telno);
	
}

void Dizi::sil(int kayitno){
	
	Tel_Kayit temp;
    int indisno,temp1;
    indisno=indis[kayitno-1];
	for(int m=indisno;m<kayitsayisi-1;m++)
	{
     temp=k[m];
	 k[m]=k[m+1];
	 k[m+1]=temp;
	}

	for(int i=kayitno-1;i<kayitsayisi-1;i++)
	{
    temp1=indis[i+1];
	indis[i]=indis[i+1]-1;
    indis[i+1]=temp1-1;
	}
			
 	kayitsayisi--;


}
void Dizi::dosyayakayit(){
   for(int i=0;i<kayitsayisi;i++)
{
   fseek(teldefteri, i*sizeof (Tel_Kayit), SEEK_SET);
   fwrite(&k[i], sizeof (Tel_Kayit), 1, teldefteri);
}
}


int Dizi::dosyabakim(){
	char *gecicidosyaadi = "geciciteldefteri.txt";
	FILE *geciciteldefteri;
	Tel_Kayit k1;
	int sayac = 0;
	geciciteldefteri = fopen( gecicidosyaadi, "w+" );
	if(!geciciteldefteri){

			cerr << "Bakim icin gecici dosya acilamadi" << endl;
			exit(1);
	}
	fseek(teldefteri, 0, SEEK_SET);
	while(!feof(teldefteri)){		
		fread( &k1, sizeof (Tel_Kayit), 1, teldefteri);		
		if(feof(teldefteri)) break;
		if((strcmp(k1.ad,"")==0))
			sayac ++;
		else
			fwrite(&k1, sizeof (Tel_Kayit), 1, geciciteldefteri);

	}
	if(sayac > 0){
		fclose(teldefteri);
		fclose(geciciteldefteri);
		char komut[500]="copy ";   //Linux'ta kopyalama islemi icin cp komutunu kullaniniz.
		strcat(komut,gecicidosyaadi);
		strcat(komut," ");
		strcat(komut,dosyaadi);
		system(komut);

		olustur();				
	}	
	return sayac;

}

void Dizi::listele(){
for(int i=0;i<kayitsayisi;i++)
cout<<i+1<<". "<<k[indis[i]].ad<<"    \t"<<k[indis[i]].telno<<endl;


}
