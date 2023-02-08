#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>
				//ÖÐRENCÝ DERS KAYIT UYGULAMASI		Muhammed Ali LALE 20011045
typedef struct ogrenci{ //ogrenci bilgilerinin tutulduðu structure
	int no;
	char isim[50];
	char soyad[50];
	int kredi;
	int ders_sayisi;
	struct ogrenci *next;
	struct ogrenci *prev;
	struct ders **ders; // her öðrencinin aldýðý dersleri dinamik pointer dizisi þeklinde sakladým 
}OGRENCI;

typedef struct ders{ //ogrenci bilgilerinin tutulduðu structure
	char ders_kodu[10];
	char ders_adi[50];
	int kapasite;
	int kredi;
	struct ders *next;
	int mevcut;
	OGRENCI **ogr;	// her derse kayýtlý olan öðrencileri dinamik pointer dizisi þeklinde sakladým 
}DERS;

typedef struct derskayit{ //Ders kayýt iþlemlerinin tutulduðu struct
	int ID;
	char ders_kodu[10];
	int no;
	char tarih[15];
	char durum[20];
	struct derskayit *next;
}KAYIT;

void MENU(DERS* head,OGRENCI* bas,KAYIT* holder,int* max_kredi,int* max_ders);
DERS* ders_oku(char File_Name[20],char delimiter[2]); //dersler.txt dosyasýný okur
void Split_DERS(DERS* holder,char buff[255],char delimiter[2]); //dosyadaki satýrlardaki verileri virgüllere göre ayýrýr
OGRENCI* ogrenci_oku(char File_Name[20],char delimiter[2]); //öðrenciler.txt dosyasýný okur
void Split_OGRENCI(OGRENCI* holder,char buff[255],char delimiter[2]); //dosyadaki satýrlardaki verileri virgüllere göre ayýrýr
void dersekle(DERS** head);
void ders_sil (DERS** head,OGRENCI* bas,KAYIT* holder);
void ders_isleri(DERS* head, OGRENCI* bas,KAYIT* holder,int* max_kredi,int* max_ders);//derslerle ilgili iþlemler için alt menü
void ogrenci_isleri(DERS* head, OGRENCI* bas,KAYIT* holder,int* max_kredi,int* max_ders);//öðrencilerle ilgili iþlemler için alt menü
void ogrenciekle(OGRENCI** head);
void ogrenci_sil (OGRENCI** head,DERS* bas, KAYIT* holder);
void ogrenci_kayit (DERS** head, OGRENCI**, KAYIT** holder,int* max_kredi,int* max_ders);//öðrencileri derslere kayýt eden fonksiyon
void listele(DERS* head, OGRENCI* bas); //derslerin sýnýf listelerini görüntüleyen fonksiyon
void ogrenci_kayit_sil (DERS** head, OGRENCI** bas,KAYIT* holder); //öðrencinin kaydýný silme
void dosyaya_kaydet(DERS* head, OGRENCI* bas,KAYIT* holder);	//yapýlan tüm deðiþiklikleri dosyaya yazdýrma komutu
void Split_KAYIT(KAYIT* holder,char buff[255],char delimiter[2]); //OgrenciDersKayýt.txt dosyasýný okur
KAYIT* kayit_oku(char File_Name[20],char delimiter[2]); //dosyadaki satýrlardaki verileri virgüllere göre ayýrýr
void DersKayit(DERS* head, OGRENCI* bas, KAYIT* holder); //OgrenciDersKayýt dosyasýna göre kayýtlý olan öðrenci-ders eþleþtirmelerine göre hafýzayý düzenler

int main() {
	setlocale(LC_ALL,"Turkish");
	int max_kredi,max_ders;
	printf("\n\t\t\t\t\tÖÐRENCÝ DERS KAYIT UYGULAMASI");
	printf("\n\n\n\t\t\tÖðrencilerin alabileceði maksimum ders sayýsýný giriniz: ");
	scanf("%d",&max_ders);
	printf("\n\n\n\t\t\tÖðrencilerin alabileceði maksimum kredi sayýsýný giriniz: ");
	scanf("%d",&max_kredi);
			DERS* ders;
			OGRENCI* ogr;
			KAYIT* kayit;
			ders=ders_oku("dersler.txt",",\0"); //satýrlarý virgüllere göre ayýrarak dosyayý okur ve DERS structýna yerleþtirir
			ogr=ogrenci_oku("ogrenciler.txt",",\0"); //satýrlarý virgüllere göre ayýrarak dosyayý okur ve OGRENCI structýna yerleþtirir
			kayit=kayit_oku("OgrenciDersKayit.txt",",\0"); //satýrlarý virgüllere göre ayýrarak dosyayý okur ve KAYIT structýna yerleþtirir
			DersKayit(ders,ogr,kayit); //Ders kayýt durumuna göre bilgileri structlara yerleþtir
	MENU(ders,ogr,kayit,&max_kredi,&max_ders); //ANA MENU
	
	return 0;
}

void MENU(DERS* ders,OGRENCI* ogr,KAYIT* kayit,int* max_kredi,int* max_ders){
		system("CLS"); //Ekraný temizle
	printf("\n\n\n\n\n ----- MENU -----\n\n");
	printf(" 1. Ders Ýþlemleri\n");
	printf(" 2. Öðrenci Ýþlemleri\n");
	printf(" 3. Kayýt durumunu görüntüle\n");
	printf(" 4. Dosyaya Kaydet\n\n");
	printf(" 5. CIKIS\n\n");
	printf(" Lutfen seciminizi yapiniz <1-5> : ");
	char secim;	
	do {
		scanf("%d", &secim);
		if (secim < 1 || secim >5)
		printf("\nLütfen 1-5 aralýðýnda seçiminizi yapýnýz : ");
	}while(secim < 1 || secim >5);
	switch(secim){

		case 1:
			ders_isleri(ders,ogr,kayit,max_kredi,max_ders); //Ders ekleme-silme ve listeleme iþlevlerinin bulunduðu alt menü
			break;
		case 2:
			ogrenci_isleri(ders,ogr,kayit,max_kredi,max_ders); //Öðrenci ekleme-silme,kayýt etme-silme iþlevlerinin buludnuðu alt menü
			break;
		case 3:
			listele(ders,ogr); //Derslerin Sýnýf listelerini görüntüle (DERSKODU.txt gibi) 
			printf("\n\n Geçmek için bir tuþa ogrýnýz...");
			getch();
			MENU(ders,ogr,kayit,max_kredi,max_ders); //menüye geri dön
			break;
		case 4:
			dosyaya_kaydet(ders,ogr,kayit); //yapýlan deðiþiklikleri dosyalara yaz
			printf("\n Kaydetme iþlemi baþarýlý. ");
			printf("\n\n Geçmek için bir tuþa basýnýz...");
			getch(); 
			MENU(ders,ogr,kayit,max_kredi,max_ders);
			break;		
		case 5:
			printf("\n  Çýkýþ Yapýlýyor...\n");
			exit(0);
			break;
	}	
}

DERS* ders_oku(char File_Name[20],char delimiter[2]){ //dersler.txt oku
	FILE *fp=fopen(File_Name,"r");
	if(fp==NULL){
		printf("dosya açýlamadý");
		exit(1);
	}
	char buf[255]; //satýrlarý buraya yazacaðýz
	DERS* head=(DERS*)malloc(sizeof(DERS));
	DERS* current;
	DERS* prev;
	if(fgets(buf,255,fp)!=NULL){ //ilk satýrý okuyup split'e gönder
		Split_DERS(head,buf,delimiter);		//virgüle göre parçalar
	}
	else{
		head=NULL; //dosya boþsa head döndür
		return head;
	}
	prev=head;
	while(fgets(buf,255,fp)!=NULL){	//sonraki satýrlarý tek tek okuyp split'e gönder
		current=(DERS*)malloc(sizeof(DERS));
		prev->next=current;
		Split_DERS(current,buf,delimiter); //virgüle göre parçalayýp parçalarý struct elemanlarýna atar
		prev=current;
	}
	prev->next=NULL; 
	fclose(fp);
	return head;
}


void Split_DERS(DERS* holder,char buff[255],char delimiter[2]){ //dosyalardaki satýrlarý virgüle göre parçalayýp atar
	//sýrayla her parçayý DERS struct elemanlarýna atama
	char *token;
	token=strtok(buff,delimiter); 
	strcpy(holder->ders_kodu,token);
	
	token=strtok(NULL,delimiter);
	strcpy(holder->ders_adi,token);
	
	token=strtok(NULL,delimiter);
	holder->kredi=atoi(token);	
	
	token=strtok(NULL,delimiter);
	holder->kapasite=atoi(token);
	
	holder->mevcut =0; //sýnýfta kayýtlý öðrenci sayýsýný baþlangýçta 0 olarak tutuyorum
}

OGRENCI* ogrenci_oku(char File_Name[20],char delimiter[2]){ //dersler.txt oku
	FILE *fp=fopen(File_Name,"r");
	char buf[255];
	
	OGRENCI* head=(OGRENCI*)malloc(sizeof(OGRENCI));
	OGRENCI* current;
	OGRENCI* prev;
	if(fgets(buf,255,fp)!=NULL){ //ilk satýrý okuyup split'e gönder
		Split_OGRENCI(head,buf,delimiter);	//virgüle göre parçalar	
	}
	else{
		head=NULL; 	//dosya boþsa head döndür
		return head;
	}
	prev=head;
	while(fgets(buf,255,fp)!=NULL){	//sonraki satýrlarý tek tek okuyp split'e gönder
		current=(OGRENCI*)malloc(sizeof(OGRENCI));
		prev->next=current;
		Split_OGRENCI(current,buf,delimiter);	//virgüle göre parçalayýp parçalarý struct elemanlarýna atar
		prev=current;
	}
	prev->next=NULL;
	fclose(fp);
	return head;
}

void Split_OGRENCI(OGRENCI* holder,char buff[255],char delimiter[2]){ //dosyalardaki satýrlarý virgüle göre parçalayýp atar
	//sýrayla her parçayý OGRENCI struct elemanlarýna atama
	char *token;
	token=strtok(buff,delimiter);
	holder->no=atoi(token);
	
	token=strtok(NULL,delimiter);
	strcpy(holder->isim,token);
	token=strtok(NULL,delimiter);
	
	strcpy(holder->soyad,token);
	holder->kredi=atoi(token);
	
	holder->kredi=0; 		//kredi ve ders sayýsý dosyadan da okunabilir ancak baþta 0 verip OgrenciDersKayýt.txt'deki 
	holder->ders_sayisi=0;	//bilgilere göre kredi ve ders sayýsýný güncellemek daha düzenli oldu
}

void dersekle(DERS** head){
	DERS *p;
	DERS *d;
	DERS *temp;
	char kod[10];
	printf(" Eklemek istediðiniz dersin kodunu giriniz: ");
	scanf("%s",kod);

	for(temp=*head;  temp!=NULL && strcmp(temp->ders_kodu,kod)!=0; temp=temp->next); //yazýlan kodu structta ara
	if(temp!=NULL){ //NULLa eþit deðilse sona gelinmemiþtir yani ders mevcuttur. bulunmuþtur.
		printf(" Bu kodda bir ders zaten var!!!");
		return;
	}
		d = (DERS*)malloc(sizeof(DERS));
	if (d == NULL){	
		printf(" Ders eklenemedi! \n");
		return;
	}	
	if(*head==NULL){	//head NULLsa yani dosya boþsa
		*head=d;		//heade eklenir yani ilk eleman olur.
	}
	else{				//aksi takdirde
		for(p=*head; p->next!=NULL; p=p->next); //son eleman bulunur
	p->next=d;	//son elemandan sonraki NULL kýsma yeni ders eklenir
	}
	
//DERS BÝLGÝLERÝNÝ KULLANICIDAN ALIP KAYDETME	
	strcpy(d->ders_kodu,kod);
	printf(" Dersin Adýný giriniz: ");
	scanf ("%s",d->ders_adi);
	printf(" Dersin Kapasitesini giriniz: ");
	scanf("%d", &d->kapasite);
	printf(" Dersin Kredisini giriniz: ");
	scanf("%d", &d->kredi);
		d->next = NULL;	//sonraki node
	return;
}

void ders_sil (DERS** d_head,OGRENCI* o_head,KAYIT* k_head){	//var olan bir dersi kaldýrma
	DERS *temp;
	DERS *temp2;
	char kod[10];
	int i,j,k,m,n;
	OGRENCI *temp0;
	printf("Silmek istediðiniz dersin kodunu giriniz: ");
	scanf("%s",kod);
	KAYIT *hold;
	
	//DERS KAYIT BÖLÜMÜNDE DERS KAPANDIÐINA DAÝR DÜZENLEME	
	for(hold=k_head; hold->next!=NULL; hold=hold->next){ //DersKayýt'ta bu derse dair bilgi var mý kontrol edilir.
		if(strcmp(kod,hold->ders_kodu)==0){ //bulunmasa bir þey yapýlmaz çýkýlýr.
			time_t t;
		    t = time(NULL);	
		    struct tm tm = *localtime(&t);
		    char date[15];
		    sprintf(date,"%.2d.%.2d.%d", tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900); //tarih yazma
			strcpy(hold->durum,"ders kapandý"); //silinen dersle ilgili kayýtlarý "ders kapandý" olarak güncelleme
			strcpy(hold->tarih,date); //tarih güncelleme
		}
	}
		temp=*d_head;
	//Ders silinince dersi alan öðrencilerin programýndan da silinmesi
	//Ders head'deyse (ilk elemansa)
	if(strcmp(temp->ders_kodu,kod)==0){	//silinen dersi bulma
		n=temp->mevcut;
		for(i=0; i<n; i++){
		temp0=temp->ogr[i];				//dersi alan öðrenci listesine eriþim
		printf("%s",temp0);
		for(;o_head==temp0;o_head=o_head->next);
			m=temp0->ders_sayisi;
		for(j=0;temp0->ders[j]!=temp;j++); //öðrenci programýnda dersi bul
		for(k=j;k<m-1;k++){
			temp0->ders[j]=temp0->ders[j+1];	//dersi kaldýr
		}
			temp0->ders_sayisi--;
			temp0->kredi-=temp->kredi;
	}
		temp=temp->next;
		free(*d_head);
		*d_head=temp;
		printf("\t%s dersi kaldýrýldý. ",kod);
		return;
	}
	//Ders mevuct mu kontrol
	for(temp=*d_head;  temp->next!=NULL && strcmp(temp->next->ders_kodu,kod)!=0; temp=temp->next);
		if(temp->next==NULL){
		printf("Böyle bir ders yok");	
		return;
	}
	//Ders head dýþýnda bir elemansa ayný iþlemler
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
		printf("\t%s dersi kaldýrýldý. ",kod);
return;	
}

void ders_isleri(DERS* d_head, OGRENCI* o_head,KAYIT* k_head,int* max_kredi,int* max_ders){//alt menü
	system("CLS");
	DERS *temp;
	temp=d_head;
	printf("\n\n\n\n\n  Ders ÝÞLEMLERÝ  \n\n");
	printf(" 1. Ders Ekle\n");
	printf(" 2. Ders Sil\n");
	printf(" 3. Ders Listesi Görüntüle\n");
	printf(" 4. Ana Menüye Dön\n");
	printf("\n Hangi iþlemi yapmak istediðini seçiniz <1-4> : ");
	int secim;
		do {
		scanf("%d", &secim);
		if (secim < 1 || secim >4)
			printf("\nLütfen 1-4 aralýðýnda seçiminizi yapýnýz : ");
		}while (secim < 1 || secim >4);
	switch (secim){
		case 1:
			dersekle(&d_head);
			printf("\n\n Geçmek için bir tuþa basýnýz...");
			getch();
			ders_isleri(d_head,o_head,k_head,max_kredi,max_ders);	
			break;
		case 2:
			ders_sil(&d_head,o_head,k_head);
			printf("\n\n Geçmek için bir tuþa basýnýz...");
			getch();
			ders_isleri(d_head,o_head,k_head,max_kredi,max_ders);
			break;
		case 3: //ders listele
			while(temp!=NULL){
				printf("%s,%s,%d,%d\n",temp->ders_kodu,temp->ders_adi,temp->kredi,temp->kapasite);
				temp=temp->next;
			}
			printf("\n\n Geçmek için bir tuþa basýnýz...");
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
	printf("\n\n\n\n\n  ÖÐRENCÝ ÝÞLEMLERÝ  \n\n");
	printf(" 1. Öðrenci Ekle\n");
	printf(" 2. Öðrenci Sil\n");
	printf(" 3. Öðrenciyi Derse Kaydet\n");
	printf(" 4. Öðrencinin Ders Kaydýný Sil\n");
	printf(" 5. Öðrenci Bilgilerini Görüntüle\n");
	printf(" 6. Ana Menüye Dön\n");
	printf("\n Hangi iþlemi yapmak istediðini seçiniz <1-6> : ");
	int secim;
		do {
		scanf("%d", &secim);
		if (secim < 1 || secim >6)
			printf("\nLütfen 1-6 aralýðýnda seçiminizi yapýnýz : ");
		}while(secim < 1 || secim >6);
	switch (secim){
		case 1:
			ogrenciekle(&o_head);
			printf("\n\n Geçmek için bir tuþa basýnýz...");
			getch();
			ogrenci_isleri(d_head,o_head,k_head,max_kredi,max_ders);
			
		case 2:
			ogrenci_sil(&o_head,d_head,k_head);
			printf("\n\n Geçmek için bir tuþa basýnýz...");
			getch();
			ogrenci_isleri(d_head,o_head,k_head,max_kredi,max_ders);
			break;
		case 3:
			ogrenci_kayit(&d_head,&o_head,&k_head,max_kredi,max_ders);
			printf("\n\n Geçmek için bir tuþa basýnýz...");
			getch();
			ogrenci_isleri(d_head,o_head,k_head,max_kredi,max_ders);
			break;
		case 4:
			ogrenci_kayit_sil(&d_head,&o_head,k_head);
			printf("\n\n Geçmek için bir tuþa basýnýz...");
			getch();
			ogrenci_isleri(d_head,o_head,k_head,max_kredi,max_ders);
			break;
		case 5:
			while(temp!=NULL){
				printf("NO: %d, Ýsim: %s, Soyisim: %s, Kredisi: %d, Aldýðý ders sayýsý: %d\n",temp->no,temp->isim,temp->soyad,temp->kredi,temp->ders_sayisi);
				temp=temp->next;	
			}
			printf("\n\n Geçmek için bir tuþa basýnýz...");
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
	printf(" Eklemek istediðiniz Öðrencinin numarasýný giriniz: ");
	scanf("%d",&NO);
	for(temp=*head;  temp!=NULL && temp->no!=NO; temp=temp->next); //listeden öðrenciyi bulma
	if(temp!=NULL){
		printf(" Bu numaralý bir öðrenci zaten var!!!");
		return;
	}
	
	std = (OGRENCI*)malloc(sizeof(OGRENCI));
	if (std == NULL){
		printf(" Öðrenci eklenemedi! \n");
		return;
	}

	if(*head == NULL){
		*head = std;
	}
	else{
	for(p=*head; p->next!=NULL; p=p->next); //son elemaný bulup bir sonraki bölüme yeni öðrenciyi yerleþtirme
	p->next = std;
}	//Bilgilerin alýmý
	std->no = NO;
	printf(" Öðrencinin Adýný giriniz: ");
	scanf ("%s",std->isim);
	printf(" Öðrencinin Soyadýný giriniz: ");
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
	printf("Silmek istediðiniz öðrencinin numarasýný giriniz: ");
	scanf("%d",&No);
	temp=*d_head;
	KAYIT *hold;	
	//SÝLÝNEN ÖÐRENCÝYÝ KAYIT DEFTERÝNDE GÜNCELLEME
	for(hold=k_head; hold!=NULL; hold=hold->next){ //tüm astýrlarý dolaþ
		if(hold->no==No){	//silinen numaralý iþlemleri bul
			time_t t;
		    t = time(NULL);
		    struct tm tm = *localtime(&t);
		    char date[15];
		    sprintf(date,"%.2d.%.2d.%d", tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900);//tarih
			strcpy(hold->durum,"öðrenci silindi"); //durum bilgisi güncelleme
			strcpy(hold->tarih,date); //tarih güncelleme
		}
	}
	//SÝLÝNEN ÖÐRENCÝ LÝSTE BAÞINDAYSA HEAD GÜNCELENÝR
	if(temp->no==No){	
		n=temp->ders_sayisi;
		for(i=0; i<n; i++){		//öðrenciyi kayýtlý olduðu ders listelerinden de silme
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
		printf("\t%d numaralý öðrenci kaldýrýldý. ",No);
		return;
	}
	for(temp=*d_head;  temp->next!=NULL && temp->next->no!=No; temp=temp->next);//ilk eleman deðilse
		if(temp->next==NULL){
		printf("Böyle bir öðrenci yok");
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
		printf("\t%d numaralý öðrenci kaldýrýldý. ",No);
return;	
}

void ogrenci_kayit (DERS** d_head, OGRENCI** o_head, KAYIT** k_head,int* max_kredi,int* max_ders){
	//DERSE KAYIT | ÖÐRENCÝ VE DERS EÞLEÞTÝRMESÝ YAPMA
	OGRENCI *temp,*tmp;
	DERS *temp2,*tmp2;
	KAYIT *hold;
	int No;
	char kod[10];
	printf("Kaydýný yapmak istediðiniz öðrencinin numarasýný giriniz: ");
	scanf("%d",&No);
	DERS *p;
	
	for(temp=*o_head;  temp!=NULL && temp->no!=No; temp=temp->next); //listeden öðrenciyi bul
		if(temp==NULL){
		printf("Böyle bir öðrenci yok");
		return;
	}
	printf("Kayýt yaptýrmak istediðiniz dersin kodunu giriniz: ");
	scanf("%s", kod);
		for(temp2=*d_head;  temp2!=NULL && strcmp(temp2->ders_kodu,kod)!=0; temp2=temp2->next);	//dersi bul
		if(temp2==NULL){
			printf("Böyle bir ders yok");
			return;
		}

	if(temp2->mevcut+1>temp2->kapasite){		//kontenjan kontrolü
		printf("Dersin kontenjaný dolmuþtur! ");
		return;
	}
	if(temp->kredi+temp2->kredi>*max_kredi){	//kredi limiti kontrolü
		printf("Öðrencinin kredisi bitmiþtir! ");
		return;
	}	
	if(temp->ders_sayisi+1>*max_ders){			//ders sayýsý kontrolü
		printf("Öðrenci alabileceði maksimum ders sayisina ulaþmýþ! ");
		return;
	}
	int i,j,n;
	n=temp2->mevcut;
	for(i=0; i<n && temp2->ogr[i]->no!=No;i++); //öðrencinin ders listesind eolup olmadýðýnýn kontrolü
		if(i!=n){
			printf("Bu Öðrenci zaten bu derse kayýtlý! ");
			return;
		}
	for(hold=*k_head; hold->next!=NULL; hold=hold->next); //Kayýt defterine kayýtlý bilgisi giriþi
	KAYIT *k;
		if (k == NULL){
		printf(" Kayýt Yapýlamadý! \n");
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
	//DÝNAMÝK DÝZÝ ÝLE ÖÐRENCÝ BÝLGÝLERÝNÝN DERSTE TUTULMASI	
		//Bellek ayýrýmý
		temp2->mevcut++;
		n++;
		if(n==1){//ilk kez
			temp2->ogr =malloc(sizeof(OGRENCI*)+n*sizeof(OGRENCI));
			temp2->ogr[n-1] =malloc(n*sizeof(OGRENCI));
		}
		else{//geniþletme
			temp2->ogr =realloc(temp2->ogr,sizeof(OGRENCI*)+n*sizeof(OGRENCI));
			temp2->ogr[n-1] =malloc(n*sizeof(OGRENCI));
		}
	temp2->ogr[n-1]=temp;
	//Kayýt
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
	//DÝNAMÝK DÝZÝ ÝLE DERS BÝLGÝLERÝNÝN ÖÐRENCÝ PROGRAMINDA TUTULMASI
		//Bellek ayýrýmý	
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
	//Kayýt Listesi sýralama
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
	printf("Kaydýný silmek istediðiniz öðrencinin numarasýný giriniz: ");
	scanf("%d",&No);
	DERS *p;
	
	for(temp=*o_head;  temp!=NULL && temp->no!=No; temp=temp->next);	//öðrenciyi listeden bulma
		if(temp==NULL){
		printf("Böyle bir öðrenci yok");
		return;
	}
	printf("Kaydý silmek istediðiniz dersin kodunu giriniz: ");
	scanf("%s", kod);
		for(temp2=*d_head;  temp2!=NULL && strcmp(temp2->ders_kodu,kod)!=0; temp2=temp2->next); //dersi bul
		if(temp2==NULL){
			printf("Böyle bir ders yok");
			return;
		}
	int i,j,n;
	n=temp2->mevcut;
	for(i=0; i<n && temp2->ogr[i]->no!=No;i++); //dersin sýmýf listesinde öðrenciyi ara
		if(i==n){
			printf("Bu öðrenci Bu derse kayýtlý deðil!");
			return;
		}
		//KAYIT DEFTERÝ GÜNCELLEMESÝ
	KAYIT *hold;	
	for(hold=k_head; hold->next!=NULL; hold=hold->next){
		if(strcmp(temp2->ders_kodu,hold->ders_kodu)==0){
			if(temp->no==hold->no){
				time_t t;
			    t = time(NULL);
			    struct tm tm = *localtime(&t);
			    char date[15];
			    sprintf(date,"%.2d.%.2d.%d", tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900);
				strcpy(hold->durum,"sildi"); //ÖÐRENCÝ DERSÝ SÝLDÝ
				strcpy(hold->tarih,date);
			}
		}
	}
		//Ders sýnýf listesinden kaldýrma
	for(j=i;j<n-1;j++){
		temp2->ogr[j]=temp2->ogr[j+1];
	}
	temp2->mevcut--;
	temp->kredi-=temp2->kredi;
	temp->ders_sayisi--;	
}

void listele(DERS* d_head, OGRENCI* o_head){
	//(DERKODU.txt DOSYASI BÝLGÝLERÝ) DERS LÝSTELERÝNÝ PROGRAM ÝÇÝNDE GÖRÜNTÜLEME
	int n;
	DERS *temp;
	DERS p;
	char kod[10];
	printf("Listesini görüntülemek istediðiniz dersin kodunu giriniz: ");
	scanf("%s", kod);
			for(temp=d_head;  temp!=NULL && strcmp(temp->ders_kodu,kod)!=0; temp=temp->next);
		if(temp==NULL){
			printf("Böyle bir ders yok");
			return;
		}
	n=temp->mevcut;
	int i;
	for(i=0;i<n;i++){
		printf("NO: %d, Ýsim: %s, Soyisim: %s, Aldýðý ders sayýsý: %d, Kredisi: %d\n",temp->ogr[i]->no,temp->ogr[i]->isim,temp->ogr[i]->soyad,temp->ogr[i]->ders_sayisi,temp->ogr[i]->kredi);
	}
	return;	
	}

void dosyaya_kaydet(DERS* d_head, OGRENCI* o_head,KAYIT* k_head){ //TÜM BÝLGÝLERÝ TXT OLARAK YAZDIRIR
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

KAYIT* kayit_oku(char File_Name[20],char delimiter[2]){ //OgrenciDersKayýt.txt dosyasýný okuyup structurea verileri kaydetme
	FILE *fp=fopen(File_Name,"r");
	char buf[255];
	
	KAYIT* head=(KAYIT*)malloc(sizeof(KAYIT));
	KAYIT* current;
	KAYIT* prev;
	if(fgets(buf,255,fp)!=NULL){ //ilk satýrý oku
		Split_KAYIT(head,buf,delimiter);		
	}
	else{
		head=NULL;
		return head;
	}
	prev=head;
	while(fgets(buf,255,fp)!=NULL){ //her satýrý tek tek oku
		current=(KAYIT*)malloc(sizeof(KAYIT));
		prev->next=current;
		Split_KAYIT(current,buf,delimiter); //virgüle göre parçalayýp kaydet
		prev=current;
	}
	prev->next=NULL;
	fclose(fp);
	return head;
}

void Split_KAYIT(KAYIT* holder,char buff[255],char delimiter[2]){
	//dosyadaki bilgileri parametre(virgüle)e göre parçalayýp kaydetme
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

void DersKayit(DERS* d_head, OGRENCI* o_head, KAYIT* k_head){	//okunan kayýt bilgilerini diðer structlara ekleme
	int i,j,n,m;
	KAYIT *hold;
	DERS *td_head;
	OGRENCI *to_head;
	for(hold=k_head; hold!=NULL; hold=hold->next){
		if(strcmp(hold->durum,"kayitli")==0){ //kayýtlý bilgileri ders ve öðrenci listelerinde güncelle
		//DERS LÝSTESÝNDE
			for(td_head=d_head;strcmp(td_head->ders_kodu,hold->ders_kodu)!=0;td_head=td_head->next);
			for(to_head=o_head;to_head->no!=hold->no; to_head=to_head->next);
			n=++td_head->mevcut;
				if(n==1){ //ilk elemansa
			td_head->ogr =malloc(sizeof(OGRENCI*)+n*sizeof(OGRENCI));
			td_head->ogr[n-1] =malloc(n*sizeof(OGRENCI));
		}
		else{ //bellek güncelleme
			td_head->ogr =realloc(td_head->ogr,sizeof(OGRENCI*)+n*sizeof(OGRENCI));
			td_head->ogr[n-1] =malloc(n*sizeof(OGRENCI));
		}
		m=++to_head->ders_sayisi;
		//ÖÐRENCÝ LÝSTESÝNDE
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
