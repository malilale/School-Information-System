#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>
				//��RENC� DERS KAYIT UYGULAMASI		Muhammed Ali LALE 20011045
typedef struct ogrenci{ //ogrenci bilgilerinin tutuldu�u structure
	int no;
	char isim[50];
	char soyad[50];
	int kredi;
	int ders_sayisi;
	struct ogrenci *next;
	struct ogrenci *prev;
	struct ders **ders; // her ��rencinin ald��� dersleri dinamik pointer dizisi �eklinde saklad�m 
}OGRENCI;

typedef struct ders{ //ogrenci bilgilerinin tutuldu�u structure
	char ders_kodu[10];
	char ders_adi[50];
	int kapasite;
	int kredi;
	struct ders *next;
	int mevcut;
	OGRENCI **ogr;	// her derse kay�tl� olan ��rencileri dinamik pointer dizisi �eklinde saklad�m 
}DERS;

typedef struct derskayit{ //Ders kay�t i�lemlerinin tutuldu�u struct
	int ID;
	char ders_kodu[10];
	int no;
	char tarih[15];
	char durum[20];
	struct derskayit *next;
}KAYIT;

void MENU(DERS* head,OGRENCI* bas,KAYIT* holder,int* max_kredi,int* max_ders);
DERS* ders_oku(char File_Name[20],char delimiter[2]); //dersler.txt dosyas�n� okur
void Split_DERS(DERS* holder,char buff[255],char delimiter[2]); //dosyadaki sat�rlardaki verileri virg�llere g�re ay�r�r
OGRENCI* ogrenci_oku(char File_Name[20],char delimiter[2]); //��renciler.txt dosyas�n� okur
void Split_OGRENCI(OGRENCI* holder,char buff[255],char delimiter[2]); //dosyadaki sat�rlardaki verileri virg�llere g�re ay�r�r
void dersekle(DERS** head);
void ders_sil (DERS** head,OGRENCI* bas,KAYIT* holder);
void ders_isleri(DERS* head, OGRENCI* bas,KAYIT* holder,int* max_kredi,int* max_ders);//derslerle ilgili i�lemler i�in alt men�
void ogrenci_isleri(DERS* head, OGRENCI* bas,KAYIT* holder,int* max_kredi,int* max_ders);//��rencilerle ilgili i�lemler i�in alt men�
void ogrenciekle(OGRENCI** head);
void ogrenci_sil (OGRENCI** head,DERS* bas, KAYIT* holder);
void ogrenci_kayit (DERS** head, OGRENCI**, KAYIT** holder,int* max_kredi,int* max_ders);//��rencileri derslere kay�t eden fonksiyon
void listele(DERS* head, OGRENCI* bas); //derslerin s�n�f listelerini g�r�nt�leyen fonksiyon
void ogrenci_kayit_sil (DERS** head, OGRENCI** bas,KAYIT* holder); //��rencinin kayd�n� silme
void dosyaya_kaydet(DERS* head, OGRENCI* bas,KAYIT* holder);	//yap�lan t�m de�i�iklikleri dosyaya yazd�rma komutu
void Split_KAYIT(KAYIT* holder,char buff[255],char delimiter[2]); //OgrenciDersKay�t.txt dosyas�n� okur
KAYIT* kayit_oku(char File_Name[20],char delimiter[2]); //dosyadaki sat�rlardaki verileri virg�llere g�re ay�r�r
void DersKayit(DERS* head, OGRENCI* bas, KAYIT* holder); //OgrenciDersKay�t dosyas�na g�re kay�tl� olan ��renci-ders e�le�tirmelerine g�re haf�zay� d�zenler

int main() {
	setlocale(LC_ALL,"Turkish");
	int max_kredi,max_ders;
	printf("\n\t\t\t\t\t��RENC� DERS KAYIT UYGULAMASI");
	printf("\n\n\n\t\t\t��rencilerin alabilece�i maksimum ders say�s�n� giriniz: ");
	scanf("%d",&max_ders);
	printf("\n\n\n\t\t\t��rencilerin alabilece�i maksimum kredi say�s�n� giriniz: ");
	scanf("%d",&max_kredi);
			DERS* ders;
			OGRENCI* ogr;
			KAYIT* kayit;
			ders=ders_oku("dersler.txt",",\0"); //sat�rlar� virg�llere g�re ay�rarak dosyay� okur ve DERS struct�na yerle�tirir
			ogr=ogrenci_oku("ogrenciler.txt",",\0"); //sat�rlar� virg�llere g�re ay�rarak dosyay� okur ve OGRENCI struct�na yerle�tirir
			kayit=kayit_oku("OgrenciDersKayit.txt",",\0"); //sat�rlar� virg�llere g�re ay�rarak dosyay� okur ve KAYIT struct�na yerle�tirir
			DersKayit(ders,ogr,kayit); //Ders kay�t durumuna g�re bilgileri structlara yerle�tir
	MENU(ders,ogr,kayit,&max_kredi,&max_ders); //ANA MENU
	
	return 0;
}

void MENU(DERS* ders,OGRENCI* ogr,KAYIT* kayit,int* max_kredi,int* max_ders){
		system("CLS"); //Ekran� temizle
	printf("\n\n\n\n\n ----- MENU -----\n\n");
	printf(" 1. Ders ��lemleri\n");
	printf(" 2. ��renci ��lemleri\n");
	printf(" 3. Kay�t durumunu g�r�nt�le\n");
	printf(" 4. Dosyaya Kaydet\n\n");
	printf(" 5. CIKIS\n\n");
	printf(" Lutfen seciminizi yapiniz <1-5> : ");
	char secim;	
	do {
		scanf("%d", &secim);
		if (secim < 1 || secim >5)
		printf("\nL�tfen 1-5 aral���nda se�iminizi yap�n�z : ");
	}while(secim < 1 || secim >5);
	switch(secim){

		case 1:
			ders_isleri(ders,ogr,kayit,max_kredi,max_ders); //Ders ekleme-silme ve listeleme i�levlerinin bulundu�u alt men�
			break;
		case 2:
			ogrenci_isleri(ders,ogr,kayit,max_kredi,max_ders); //��renci ekleme-silme,kay�t etme-silme i�levlerinin buludnu�u alt men�
			break;
		case 3:
			listele(ders,ogr); //Derslerin S�n�f listelerini g�r�nt�le (DERSKODU.txt gibi) 
			printf("\n\n Ge�mek i�in bir tu�a ogr�n�z...");
			getch();
			MENU(ders,ogr,kayit,max_kredi,max_ders); //men�ye geri d�n
			break;
		case 4:
			dosyaya_kaydet(ders,ogr,kayit); //yap�lan de�i�iklikleri dosyalara yaz
			printf("\n Kaydetme i�lemi ba�ar�l�. ");
			printf("\n\n Ge�mek i�in bir tu�a bas�n�z...");
			getch(); 
			MENU(ders,ogr,kayit,max_kredi,max_ders);
			break;		
		case 5:
			printf("\n  ��k�� Yap�l�yor...\n");
			exit(0);
			break;
	}	
}

DERS* ders_oku(char File_Name[20],char delimiter[2]){ //dersler.txt oku
	FILE *fp=fopen(File_Name,"r");
	if(fp==NULL){
		printf("dosya a��lamad�");
		exit(1);
	}
	char buf[255]; //sat�rlar� buraya yazaca��z
	DERS* head=(DERS*)malloc(sizeof(DERS));
	DERS* current;
	DERS* prev;
	if(fgets(buf,255,fp)!=NULL){ //ilk sat�r� okuyup split'e g�nder
		Split_DERS(head,buf,delimiter);		//virg�le g�re par�alar
	}
	else{
		head=NULL; //dosya bo�sa head d�nd�r
		return head;
	}
	prev=head;
	while(fgets(buf,255,fp)!=NULL){	//sonraki sat�rlar� tek tek okuyp split'e g�nder
		current=(DERS*)malloc(sizeof(DERS));
		prev->next=current;
		Split_DERS(current,buf,delimiter); //virg�le g�re par�alay�p par�alar� struct elemanlar�na atar
		prev=current;
	}
	prev->next=NULL; 
	fclose(fp);
	return head;
}


void Split_DERS(DERS* holder,char buff[255],char delimiter[2]){ //dosyalardaki sat�rlar� virg�le g�re par�alay�p atar
	//s�rayla her par�ay� DERS struct elemanlar�na atama
	char *token;
	token=strtok(buff,delimiter); 
	strcpy(holder->ders_kodu,token);
	
	token=strtok(NULL,delimiter);
	strcpy(holder->ders_adi,token);
	
	token=strtok(NULL,delimiter);
	holder->kredi=atoi(token);	
	
	token=strtok(NULL,delimiter);
	holder->kapasite=atoi(token);
	
	holder->mevcut =0; //s�n�fta kay�tl� ��renci say�s�n� ba�lang��ta 0 olarak tutuyorum
}

OGRENCI* ogrenci_oku(char File_Name[20],char delimiter[2]){ //dersler.txt oku
	FILE *fp=fopen(File_Name,"r");
	char buf[255];
	
	OGRENCI* head=(OGRENCI*)malloc(sizeof(OGRENCI));
	OGRENCI* current;
	OGRENCI* prev;
	if(fgets(buf,255,fp)!=NULL){ //ilk sat�r� okuyup split'e g�nder
		Split_OGRENCI(head,buf,delimiter);	//virg�le g�re par�alar	
	}
	else{
		head=NULL; 	//dosya bo�sa head d�nd�r
		return head;
	}
	prev=head;
	while(fgets(buf,255,fp)!=NULL){	//sonraki sat�rlar� tek tek okuyp split'e g�nder
		current=(OGRENCI*)malloc(sizeof(OGRENCI));
		prev->next=current;
		Split_OGRENCI(current,buf,delimiter);	//virg�le g�re par�alay�p par�alar� struct elemanlar�na atar
		prev=current;
	}
	prev->next=NULL;
	fclose(fp);
	return head;
}

void Split_OGRENCI(OGRENCI* holder,char buff[255],char delimiter[2]){ //dosyalardaki sat�rlar� virg�le g�re par�alay�p atar
	//s�rayla her par�ay� OGRENCI struct elemanlar�na atama
	char *token;
	token=strtok(buff,delimiter);
	holder->no=atoi(token);
	
	token=strtok(NULL,delimiter);
	strcpy(holder->isim,token);
	token=strtok(NULL,delimiter);
	
	strcpy(holder->soyad,token);
	holder->kredi=atoi(token);
	
	holder->kredi=0; 		//kredi ve ders say�s� dosyadan da okunabilir ancak ba�ta 0 verip OgrenciDersKay�t.txt'deki 
	holder->ders_sayisi=0;	//bilgilere g�re kredi ve ders say�s�n� g�ncellemek daha d�zenli oldu
}

void dersekle(DERS** head){
	DERS *p;
	DERS *d;
	DERS *temp;
	char kod[10];
	printf(" Eklemek istedi�iniz dersin kodunu giriniz: ");
	scanf("%s",kod);

	for(temp=*head;  temp!=NULL && strcmp(temp->ders_kodu,kod)!=0; temp=temp->next); //yaz�lan kodu structta ara
	if(temp!=NULL){ //NULLa e�it de�ilse sona gelinmemi�tir yani ders mevcuttur. bulunmu�tur.
		printf(" Bu kodda bir ders zaten var!!!");
		return;
	}
		d = (DERS*)malloc(sizeof(DERS));
	if (d == NULL){	
		printf(" Ders eklenemedi! \n");
		return;
	}	
	if(*head==NULL){	//head NULLsa yani dosya bo�sa
		*head=d;		//heade eklenir yani ilk eleman olur.
	}
	else{				//aksi takdirde
		for(p=*head; p->next!=NULL; p=p->next); //son eleman bulunur
	p->next=d;	//son elemandan sonraki NULL k�sma yeni ders eklenir
	}
	
//DERS B�LG�LER�N� KULLANICIDAN ALIP KAYDETME	
	strcpy(d->ders_kodu,kod);
	printf(" Dersin Ad�n� giriniz: ");
	scanf ("%s",d->ders_adi);
	printf(" Dersin Kapasitesini giriniz: ");
	scanf("%d", &d->kapasite);
	printf(" Dersin Kredisini giriniz: ");
	scanf("%d", &d->kredi);
		d->next = NULL;	//sonraki node
	return;
}

void ders_sil (DERS** d_head,OGRENCI* o_head,KAYIT* k_head){	//var olan bir dersi kald�rma
	DERS *temp;
	DERS *temp2;
	char kod[10];
	int i,j,k,m,n;
	OGRENCI *temp0;
	printf("Silmek istedi�iniz dersin kodunu giriniz: ");
	scanf("%s",kod);
	KAYIT *hold;
	
	//DERS KAYIT B�L�M�NDE DERS KAPANDI�INA DA�R D�ZENLEME	
	for(hold=k_head; hold->next!=NULL; hold=hold->next){ //DersKay�t'ta bu derse dair bilgi var m� kontrol edilir.
		if(strcmp(kod,hold->ders_kodu)==0){ //bulunmasa bir �ey yap�lmaz ��k�l�r.
			time_t t;
		    t = time(NULL);	
		    struct tm tm = *localtime(&t);
		    char date[15];
		    sprintf(date,"%.2d.%.2d.%d", tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900); //tarih yazma
			strcpy(hold->durum,"ders kapand�"); //silinen dersle ilgili kay�tlar� "ders kapand�" olarak g�ncelleme
			strcpy(hold->tarih,date); //tarih g�ncelleme
		}
	}
		temp=*d_head;
	//Ders silinince dersi alan ��rencilerin program�ndan da silinmesi
	//Ders head'deyse (ilk elemansa)
	if(strcmp(temp->ders_kodu,kod)==0){	//silinen dersi bulma
		n=temp->mevcut;
		for(i=0; i<n; i++){
		temp0=temp->ogr[i];				//dersi alan ��renci listesine eri�im
		printf("%s",temp0);
		for(;o_head==temp0;o_head=o_head->next);
			m=temp0->ders_sayisi;
		for(j=0;temp0->ders[j]!=temp;j++); //��renci program�nda dersi bul
		for(k=j;k<m-1;k++){
			temp0->ders[j]=temp0->ders[j+1];	//dersi kald�r
		}
			temp0->ders_sayisi--;
			temp0->kredi-=temp->kredi;
	}
		temp=temp->next;
		free(*d_head);
		*d_head=temp;
		printf("\t%s dersi kald�r�ld�. ",kod);
		return;
	}
	//Ders mevuct mu kontrol
	for(temp=*d_head;  temp->next!=NULL && strcmp(temp->next->ders_kodu,kod)!=0; temp=temp->next);
		if(temp->next==NULL){
		printf("B�yle bir ders yok");	
		return;
	}
	//Ders head d���nda bir elemansa ayn� i�lemler
	n=temp->mevcut;
	for(i=0; i<n; i++){	
		temp0=temp->ogr[i];
		for(;o_head==temp0;o_head=o_head->next);
			m=temp0->ders_sayisi;
		for(j=0;temp0->ders[j]!=temp;j++);
		for(k=j;k<m-1;k++){
			temp0->ders[j]=temp0->ders[j+1];
		}
			temp0->ders_sayisi--;
			temp0->kredi-=temp->kredi;
	}
		temp2=temp->next->next;
		free(temp->next);
		temp->next=temp2;
		printf("\t%s dersi kald�r�ld�. ",kod);
return;	
}

void ders_isleri(DERS* d_head, OGRENCI* o_head,KAYIT* k_head,int* max_kredi,int* max_ders){//alt men�
	system("CLS");
	DERS *temp;
	temp=d_head;
	printf("\n\n\n\n\n  Ders ��LEMLER�  \n\n");
	printf(" 1. Ders Ekle\n");
	printf(" 2. Ders Sil\n");
	printf(" 3. Ders Listesi G�r�nt�le\n");
	printf(" 4. Ana Men�ye D�n\n");
	printf("\n Hangi i�lemi yapmak istedi�ini se�iniz <1-4> : ");
	int secim;
		do {
		scanf("%d", &secim);
		if (secim < 1 || secim >4)
			printf("\nL�tfen 1-4 aral���nda se�iminizi yap�n�z : ");
		}while (secim < 1 || secim >4);
	switch (secim){
		case 1:
			dersekle(&d_head);
			printf("\n\n Ge�mek i�in bir tu�a bas�n�z...");
			getch();
			ders_isleri(d_head,o_head,k_head,max_kredi,max_ders);	
			break;
		case 2:
			ders_sil(&d_head,o_head,k_head);
			printf("\n\n Ge�mek i�in bir tu�a bas�n�z...");
			getch();
			ders_isleri(d_head,o_head,k_head,max_kredi,max_ders);
			break;
		case 3: //ders listele
			while(temp!=NULL){
				printf("%s,%s,%d,%d\n",temp->ders_kodu,temp->ders_adi,temp->kredi,temp->kapasite);
				temp=temp->next;
			}
			printf("\n\n Ge�mek i�in bir tu�a bas�n�z...");
			getch();
			ders_isleri(d_head,o_head,k_head,max_kredi,max_ders);	
			break;
		case 4:
			system("CLS");
			MENU(d_head,o_head,k_head,max_kredi,max_ders);
			break;
	}	
}
	
void ogrenci_isleri(DERS* d_head, OGRENCI* o_head,KAYIT* k_head,int* max_kredi,int* max_ders){
	system("CLS");
	OGRENCI *temp;
	temp=o_head;
	int maxders, maxkredi;
	int check;
	int n=0;
	printf("\n\n\n\n\n  ��RENC� ��LEMLER�  \n\n");
	printf(" 1. ��renci Ekle\n");
	printf(" 2. ��renci Sil\n");
	printf(" 3. ��renciyi Derse Kaydet\n");
	printf(" 4. ��rencinin Ders Kayd�n� Sil\n");
	printf(" 5. ��renci Bilgilerini G�r�nt�le\n");
	printf(" 6. Ana Men�ye D�n\n");
	printf("\n Hangi i�lemi yapmak istedi�ini se�iniz <1-6> : ");
	int secim;
		do {
		scanf("%d", &secim);
		if (secim < 1 || secim >6)
			printf("\nL�tfen 1-6 aral���nda se�iminizi yap�n�z : ");
		}while(secim < 1 || secim >6);
	switch (secim){
		case 1:
			ogrenciekle(&o_head);
			printf("\n\n Ge�mek i�in bir tu�a bas�n�z...");
			getch();
			ogrenci_isleri(d_head,o_head,k_head,max_kredi,max_ders);
			
		case 2:
			ogrenci_sil(&o_head,d_head,k_head);
			printf("\n\n Ge�mek i�in bir tu�a bas�n�z...");
			getch();
			ogrenci_isleri(d_head,o_head,k_head,max_kredi,max_ders);
			break;
		case 3:
			ogrenci_kayit(&d_head,&o_head,&k_head,max_kredi,max_ders);
			printf("\n\n Ge�mek i�in bir tu�a bas�n�z...");
			getch();
			ogrenci_isleri(d_head,o_head,k_head,max_kredi,max_ders);
			break;
		case 4:
			ogrenci_kayit_sil(&d_head,&o_head,k_head);
			printf("\n\n Ge�mek i�in bir tu�a bas�n�z...");
			getch();
			ogrenci_isleri(d_head,o_head,k_head,max_kredi,max_ders);
			break;
		case 5:
			while(temp!=NULL){
				printf("NO: %d, �sim: %s, Soyisim: %s, Kredisi: %d, Ald��� ders say�s�: %d\n",temp->no,temp->isim,temp->soyad,temp->kredi,temp->ders_sayisi);
				temp=temp->next;	
			}
			printf("\n\n Ge�mek i�in bir tu�a bas�n�z...");
			getch();
			ogrenci_isleri(d_head,o_head,k_head,max_kredi,max_ders);
			break;
		case 6:
			system("CLS");
			MENU(d_head,o_head,k_head,max_kredi,max_ders);
			break;
	}
}	

void ogrenciekle(OGRENCI** head){
	OGRENCI *p;
	OGRENCI *std;
	OGRENCI *temp;
	int NO;
	printf(" Eklemek istedi�iniz ��rencinin numaras�n� giriniz: ");
	scanf("%d",&NO);
	for(temp=*head;  temp!=NULL && temp->no!=NO; temp=temp->next); //listeden ��renciyi bulma
	if(temp!=NULL){
		printf(" Bu numaral� bir ��renci zaten var!!!");
		return;
	}
	
	std = (OGRENCI*)malloc(sizeof(OGRENCI));
	if (std == NULL){
		printf(" ��renci eklenemedi! \n");
		return;
	}

	if(*head == NULL){
		*head = std;
	}
	else{
	for(p=*head; p->next!=NULL; p=p->next); //son eleman� bulup bir sonraki b�l�me yeni ��renciyi yerle�tirme
	p->next = std;
}	//Bilgilerin al�m�
	std->no = NO;
	printf(" ��rencinin Ad�n� giriniz: ");
	scanf ("%s",std->isim);
	printf(" ��rencinin Soyad�n� giriniz: ");
	scanf("%s", std->soyad);
	std->kredi=0;
	std->ders_sayisi=0;
		std->next = NULL;	
	return;
}

void ogrenci_sil (OGRENCI** d_head,DERS* o_head, KAYIT* k_head){
	OGRENCI *temp;
	OGRENCI *temp2;
	int i,j,k,m,n;
	DERS *temp0;
	int No;
	printf("Silmek istedi�iniz ��rencinin numaras�n� giriniz: ");
	scanf("%d",&No);
	temp=*d_head;
	KAYIT *hold;	
	//S�L�NEN ��RENC�Y� KAYIT DEFTER�NDE G�NCELLEME
	for(hold=k_head; hold!=NULL; hold=hold->next){ //t�m ast�rlar� dola�
		if(hold->no==No){	//silinen numaral� i�lemleri bul
			time_t t;
		    t = time(NULL);
		    struct tm tm = *localtime(&t);
		    char date[15];
		    sprintf(date,"%.2d.%.2d.%d", tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900);//tarih
			strcpy(hold->durum,"��renci silindi"); //durum bilgisi g�ncelleme
			strcpy(hold->tarih,date); //tarih g�ncelleme
		}
	}
	//S�L�NEN ��RENC� L�STE BA�INDAYSA HEAD G�NCELEN�R
	if(temp->no==No){	
		n=temp->ders_sayisi;
		for(i=0; i<n; i++){		//��renciyi kay�tl� oldu�u ders listelerinden de silme
			temp0=temp->ders[i];
			for(;o_head==temp0;o_head=o_head->next);
				m=temp0->mevcut;
			for(j=0;temp0->ogr[j]!=temp;j++);
			for(k=j;k<m-1;k++){
				temp0->ogr[j]=temp0->ogr[j+1];
			}
				temp0->mevcut--;
		}	
		temp=temp->next;
		free(*d_head);
		*d_head=temp;
		printf("\t%d numaral� ��renci kald�r�ld�. ",No);
		return;
	}
	for(temp=*d_head;  temp->next!=NULL && temp->next->no!=No; temp=temp->next);//ilk eleman de�ilse
		if(temp->next==NULL){
		printf("B�yle bir ��renci yok");
		return;
	}
	n=temp->ders_sayisi;
	for(i=0; i<n; i++){
		temp0=temp->ders[i];
		for(;o_head==temp0;o_head=o_head->next);
			m=temp0->mevcut;
		for(j=0;temp0->ogr[j]!=temp;j++);
		for(k=j;k<m-1;k++){
			temp0->ogr[j]=temp0->ogr[j+1];
		}
			temp0->mevcut--;
	}
		temp2=temp->next->next;
		free(temp->next);
		temp->next=temp2;
		printf("\t%d numaral� ��renci kald�r�ld�. ",No);
return;	
}

void ogrenci_kayit (DERS** d_head, OGRENCI** o_head, KAYIT** k_head,int* max_kredi,int* max_ders){
	//DERSE KAYIT | ��RENC� VE DERS E�LE�T�RMES� YAPMA
	OGRENCI *temp,*tmp;
	DERS *temp2,*tmp2;
	KAYIT *hold;
	int No;
	char kod[10];
	printf("Kayd�n� yapmak istedi�iniz ��rencinin numaras�n� giriniz: ");
	scanf("%d",&No);
	DERS *p;
	
	for(temp=*o_head;  temp!=NULL && temp->no!=No; temp=temp->next); //listeden ��renciyi bul
		if(temp==NULL){
		printf("B�yle bir ��renci yok");
		return;
	}
	printf("Kay�t yapt�rmak istedi�iniz dersin kodunu giriniz: ");
	scanf("%s", kod);
		for(temp2=*d_head;  temp2!=NULL && strcmp(temp2->ders_kodu,kod)!=0; temp2=temp2->next);	//dersi bul
		if(temp2==NULL){
			printf("B�yle bir ders yok");
			return;
		}

	if(temp2->mevcut+1>temp2->kapasite){		//kontenjan kontrol�
		printf("Dersin kontenjan� dolmu�tur! ");
		return;
	}
	if(temp->kredi+temp2->kredi>*max_kredi){	//kredi limiti kontrol�
		printf("��rencinin kredisi bitmi�tir! ");
		return;
	}	
	if(temp->ders_sayisi+1>*max_ders){			//ders say�s� kontrol�
		printf("��renci alabilece�i maksimum ders sayisina ula�m��! ");
		return;
	}
	int i,j,n;
	n=temp2->mevcut;
	for(i=0; i<n && temp2->ogr[i]->no!=No;i++); //��rencinin ders listesind eolup olmad���n�n kontrol�
		if(i!=n){
			printf("Bu ��renci zaten bu derse kay�tl�! ");
			return;
		}
	for(hold=*k_head; hold->next!=NULL; hold=hold->next); //Kay�t defterine kay�tl� bilgisi giri�i
	KAYIT *k;
		if (k == NULL){
		printf(" Kay�t Yap�lamad�! \n");
		return;
	}	
	k=(KAYIT*)malloc(sizeof(KAYIT));
	hold->next=k;
	k->ID=hold->ID+1;
	strcpy(k->ders_kodu,temp2->ders_kodu);
	k->no=temp->no;
	    time_t t;
    t = time(NULL);
    struct tm tm = *localtime(&t);
    char date[15];
    sprintf(date,"%.2d.%.2d.%d", tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900);
	strcpy(k->tarih,date);
	strcpy(k->durum,"kayitli");
		k->next=NULL;
	//D�NAM�K D�Z� �LE ��RENC� B�LG�LER�N�N DERSTE TUTULMASI	
		//Bellek ay�r�m�
		temp2->mevcut++;
		n++;
		if(n==1){//ilk kez
			temp2->ogr =malloc(sizeof(OGRENCI*)+n*sizeof(OGRENCI));
			temp2->ogr[n-1] =malloc(n*sizeof(OGRENCI));
		}
		else{//geni�letme
			temp2->ogr =realloc(temp2->ogr,sizeof(OGRENCI*)+n*sizeof(OGRENCI));
			temp2->ogr[n-1] =malloc(n*sizeof(OGRENCI));
		}
	temp2->ogr[n-1]=temp;
	//Kay�t
	for(i=0;i<n-1;i++){
		for(j=i+1;j<n;j++){
			if(temp2->ogr[i]>temp2->ogr[j]){
				tmp=temp2->ogr[i];
				temp2->ogr[i]=temp2->ogr[j];
				temp2->ogr[j]=tmp;
			}
		}
	}
	temp->ders_sayisi++;
	temp->kredi+=temp2->kredi;
	//D�NAM�K D�Z� �LE DERS B�LG�LER�N�N ��RENC� PROGRAMINDA TUTULMASI
		//Bellek ay�r�m�	
		int m=temp->ders_sayisi;
		if(m==1){
			temp->ders =malloc(sizeof(DERS*)+m*sizeof(DERS));
			temp->ders[m-1] =malloc(m*sizeof(DERS));
		}
		else{
			temp->ders =realloc(temp->ders,sizeof(DERS*)+m*sizeof(DERS));
			temp->ders[m-1] =malloc(m*sizeof(DERS));
		}
	temp->ders[m-1]=temp2;
	//Kay�t Listesi s�ralama
		for(i=0;i<m-1;i++){
		for(j=i+1;j<n;j++){
			if(temp->ders[i]>temp->ders[j]){
				tmp2=temp->ders[i];
				temp->ders[i]=temp->ders[j];
				temp->ders[j]=tmp2;
			}
		}
	}
	return;
}

void ogrenci_kayit_sil (DERS** d_head, OGRENCI** o_head,KAYIT* k_head){
	OGRENCI *temp,*tmp;
	DERS *temp2;
	int No;
	char kod[10];
	printf("Kayd�n� silmek istedi�iniz ��rencinin numaras�n� giriniz: ");
	scanf("%d",&No);
	DERS *p;
	
	for(temp=*o_head;  temp!=NULL && temp->no!=No; temp=temp->next);	//��renciyi listeden bulma
		if(temp==NULL){
		printf("B�yle bir ��renci yok");
		return;
	}
	printf("Kayd� silmek istedi�iniz dersin kodunu giriniz: ");
	scanf("%s", kod);
		for(temp2=*d_head;  temp2!=NULL && strcmp(temp2->ders_kodu,kod)!=0; temp2=temp2->next); //dersi bul
		if(temp2==NULL){
			printf("B�yle bir ders yok");
			return;
		}
	int i,j,n;
	n=temp2->mevcut;
	for(i=0; i<n && temp2->ogr[i]->no!=No;i++); //dersin s�m�f listesinde ��renciyi ara
		if(i==n){
			printf("Bu ��renci Bu derse kay�tl� de�il!");
			return;
		}
		//KAYIT DEFTER� G�NCELLEMES�
	KAYIT *hold;	
	for(hold=k_head; hold->next!=NULL; hold=hold->next){
		if(strcmp(temp2->ders_kodu,hold->ders_kodu)==0){
			if(temp->no==hold->no){
				time_t t;
			    t = time(NULL);
			    struct tm tm = *localtime(&t);
			    char date[15];
			    sprintf(date,"%.2d.%.2d.%d", tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900);
				strcpy(hold->durum,"sildi"); //��RENC� DERS� S�LD�
				strcpy(hold->tarih,date);
			}
		}
	}
		//Ders s�n�f listesinden kald�rma
	for(j=i;j<n-1;j++){
		temp2->ogr[j]=temp2->ogr[j+1];
	}
	temp2->mevcut--;
	temp->kredi-=temp2->kredi;
	temp->ders_sayisi--;	
}

void listele(DERS* d_head, OGRENCI* o_head){
	//(DERKODU.txt DOSYASI B�LG�LER�) DERS L�STELER�N� PROGRAM ���NDE G�R�NT�LEME
	int n;
	DERS *temp;
	DERS p;
	char kod[10];
	printf("Listesini g�r�nt�lemek istedi�iniz dersin kodunu giriniz: ");
	scanf("%s", kod);
			for(temp=d_head;  temp!=NULL && strcmp(temp->ders_kodu,kod)!=0; temp=temp->next);
		if(temp==NULL){
			printf("B�yle bir ders yok");
			return;
		}
	n=temp->mevcut;
	int i;
	for(i=0;i<n;i++){
		printf("NO: %d, �sim: %s, Soyisim: %s, Ald��� ders say�s�: %d, Kredisi: %d\n",temp->ogr[i]->no,temp->ogr[i]->isim,temp->ogr[i]->soyad,temp->ogr[i]->ders_sayisi,temp->ogr[i]->kredi);
	}
	return;	
	}

void dosyaya_kaydet(DERS* d_head, OGRENCI* o_head,KAYIT* k_head){ //T�M B�LG�LER� TXT OLARAK YAZDIRIR
	FILE *p_dersler=fopen("dersler.txt","w");
	DERS *temp=d_head;
	OGRENCI *temp2=o_head;
	while(temp!=NULL){
		fprintf(p_dersler,"%s,%s,%d,%d\n",temp->ders_kodu,temp->ders_adi,temp->kredi,temp->kapasite);	
		temp=temp->next;	
	}
	fclose(p_dersler);
	
	FILE *p_ogrenciler=fopen("ogrenciler.txt","w");
	while(temp2!=NULL){
		fprintf(p_ogrenciler,"%d,%s,%s,%d,%d\n",temp2->no,temp2->isim,temp2->soyad,temp2->kredi,temp2->ders_sayisi);	
		temp2=temp2->next;	
	}
	fclose(p_ogrenciler);	
	
	temp=d_head;
	char name[20];
	FILE *p_ders;
	int n,i,j=0;
	while(temp!=NULL){
	n=temp->mevcut;
		sprintf(name,"%s.txt",temp->ders_kodu); //DERSKODU.TXT
		p_ders=fopen(name,"w");
		for(i=0;i<n;i++){
			fprintf(p_ders,"%d,%s,%s,%d,%d\n",temp->ogr[i]->no,temp->ogr[i]->isim,temp->ogr[i]->soyad,temp->ogr[i]->kredi,temp->ogr[i]->ders_sayisi);	
		}
		fclose(p_ders);	
				temp=temp->next;
	}
	
	temp2=o_head;
	FILE *p_ogr;
	j=0;
	while(temp2!=NULL){
	n=temp2->ders_sayisi;
		sprintf(name,"%d_DERSPROGRAMI.txt",temp2->no); //OGRENCINO_DERSPROGRAMI.TXT
		p_ogr=fopen(name,"w");
		for(i=0;i<n;i++){
			fprintf(p_ogr,"%s,%s,%d,%d\n",temp2->ders[i]->ders_kodu,temp2->ders[i]->ders_adi,temp2->ders[i]->kredi,temp2->ders[i]->kapasite);	
		}
		fclose(p_ogr);	
				temp2=temp2->next;
	}
	
	KAYIT *hold;
	hold=k_head;
	FILE *p_kayit=fopen("OgrenciDersKayit.txt","w");
	while(hold!=NULL){
		fprintf(p_kayit,"%d,%s,%d,%s,%s\n",hold->ID,hold->ders_kodu,hold->no,hold->tarih,hold->durum);	
		hold=hold->next;	
	}
	fclose(p_kayit);
	return;
	}

KAYIT* kayit_oku(char File_Name[20],char delimiter[2]){ //OgrenciDersKay�t.txt dosyas�n� okuyup structurea verileri kaydetme
	FILE *fp=fopen(File_Name,"r");
	char buf[255];
	
	KAYIT* head=(KAYIT*)malloc(sizeof(KAYIT));
	KAYIT* current;
	KAYIT* prev;
	if(fgets(buf,255,fp)!=NULL){ //ilk sat�r� oku
		Split_KAYIT(head,buf,delimiter);		
	}
	else{
		head=NULL;
		return head;
	}
	prev=head;
	while(fgets(buf,255,fp)!=NULL){ //her sat�r� tek tek oku
		current=(KAYIT*)malloc(sizeof(KAYIT));
		prev->next=current;
		Split_KAYIT(current,buf,delimiter); //virg�le g�re par�alay�p kaydet
		prev=current;
	}
	prev->next=NULL;
	fclose(fp);
	return head;
}

void Split_KAYIT(KAYIT* holder,char buff[255],char delimiter[2]){
	//dosyadaki bilgileri parametre(virg�le)e g�re par�alay�p kaydetme
	char *token;
	token=strtok(buff,delimiter);
	holder->ID=atoi(token);
	
	token=strtok(NULL,delimiter);
	strcpy(holder->ders_kodu,token);
	
	token=strtok(NULL,delimiter);
	holder->no=atoi(token);
	
	token=strtok(NULL,delimiter);
	strcpy(holder->tarih,token);
	
	token=strtok(NULL,delimiter);
	token[strlen(token)-1]='\0';
	strcpy(holder->durum,token);
}

void DersKayit(DERS* d_head, OGRENCI* o_head, KAYIT* k_head){	//okunan kay�t bilgilerini di�er structlara ekleme
	int i,j,n,m;
	KAYIT *hold;
	DERS *td_head;
	OGRENCI *to_head;
	for(hold=k_head; hold!=NULL; hold=hold->next){
		if(strcmp(hold->durum,"kayitli")==0){ //kay�tl� bilgileri ders ve ��renci listelerinde g�ncelle
		//DERS L�STES�NDE
			for(td_head=d_head;strcmp(td_head->ders_kodu,hold->ders_kodu)!=0;td_head=td_head->next);
			for(to_head=o_head;to_head->no!=hold->no; to_head=to_head->next);
			n=++td_head->mevcut;
				if(n==1){ //ilk elemansa
			td_head->ogr =malloc(sizeof(OGRENCI*)+n*sizeof(OGRENCI));
			td_head->ogr[n-1] =malloc(n*sizeof(OGRENCI));
		}
		else{ //bellek g�ncelleme
			td_head->ogr =realloc(td_head->ogr,sizeof(OGRENCI*)+n*sizeof(OGRENCI));
			td_head->ogr[n-1] =malloc(n*sizeof(OGRENCI));
		}
		m=++to_head->ders_sayisi;
		//��RENC� L�STES�NDE
		if(m==1){
			to_head->ders =malloc(sizeof(DERS*)+m*sizeof(DERS));
			to_head->ders[m-1] =malloc(m*sizeof(DERS));
		}
		else{
			to_head->ders =realloc(to_head->ders,sizeof(DERS*)+m*sizeof(DERS));
			to_head->ders[m-1] =malloc(m*sizeof(DERS));
		}
			td_head->ogr[n-1]=to_head;
				to_head->ders[m-1]=td_head;
			to_head->kredi+=td_head->kredi;
		}
	}
		return;	
}
