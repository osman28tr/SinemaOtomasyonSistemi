#include <stdio.h>
#include <stdlib.h>

void Anamenu();
void Salonlar();
void SalonSecimIslemleri(int salonno);
void LoginIslem();
void LoginEkran();
void HasilatDosyaYaz();
void HasilatShow();
void salonmatinebilgidosyayaz();
void salonmatineshow();

struct Red {
	int** pointerredkoltuk[100][100];
} red;
enum matinered {
	matine1 = 1, matine2, matine3, matine4, matine5
};
struct Green {
	int** pointergreenkoltuk[100][100];
} green;
enum matinegreen {
	matine6 = 1, matine7, matine8, matine9, matine10
};
struct Blue {
	int** pointerbluekoltuk[100][100];
}blue;
enum matineblue {
	matine11 = 1, matine12, matine13, matine14, matine15
};

void greenmatinefonk(enum matinegreen mg);
void redmatinefonk(enum matinered mr);
void bluematinefonk(enum matineblue mb);

int koltukkontrol, sec, sayac = 0, toplam = 0, koltuksec, loginsayac = 0, SalonSecim, anamenusecim, matineno, ogrsecim, Hasilatlar[100];
char KullaniciAdi[30], line[1024], Film[50], validationusername[30], Sifre[50], validationpassword[50];
int main(void) {
don:
	Anamenu();
	if (anamenusecim == 1) {
		Salonlar();
		printf("Lutfen Sinema Salonunu Seciniz...");
		scanf("%d", &SalonSecim);
		if (SalonSecim == 1) {
			SalonSecimIslemleri(1);
		}
		else if (SalonSecim == 2) {
			SalonSecimIslemleri(2);
		}
		else {
			SalonSecimIslemleri(3);
		}
	}
	else {
		LoginIslem();
	}
	return 0;
}
void Anamenu() {
	printf("------->....Merhaba Hosgeldiniz....<-------\n");
	printf("Lutfen secim yapiniz\n");
	printf("1-Anamenu\n");
	printf("2-Login Ekrani\n");
	scanf("%d", &anamenusecim);
}
void Salonlar() {
	printf("1-Green\n");
	printf("2-Red\n");
	printf("3-Blue\n");
}
void SalonSecimIslemleri(int salonno) {
	printf("matine numarasini giriniz(1-5)\n");
	scanf("%d", &matineno);
	printf("Izleyeceginiz filmi giriniz(Lutfen gireceginiz filmin isminde bosluk karakteri varsa bosluk yerine _ olarak girin)\n");
	scanf("%s", Film);
	printf("Ogrenci misiniz? 1-evet 2-hayir");
	scanf("%d", &ogrsecim);
	if (ogrsecim == 1) {
		Hasilatlar[sayac] = 20;
	}
	else {
		Hasilatlar[sayac] = 30;
	}
	if (salonno == 1) {
		enum matinegreen mgreen;
		mgreen = matineno;
		greenmatinefonk(mgreen);
	}
	else if (salonno == 2) {
		enum matinered mred;
		mred = matineno;
		redmatinefonk(mred);
	}
	else {
		enum matineblue mblue;
		mblue = matineno;
		bluematinefonk(mblue);
	}
}
void LoginIslem() {
	loginsayac++;
	int i, j;
	if (loginsayac == 1) {
		FILE* p, fp;
		LoginEkran();
		p = fopen("sifre.txt", "w+");
		fprintf(p, "%s %s", KullaniciAdi, Sifre);
		printf("KullaniciAdi ve Sifreniz basarili bir sekilde kaydedildi\n");
		fclose(p);
		HasilatDosyaYaz();
		HasilatShow();
		salonmatinebilgidosyayaz();
		salonmatineshow();
		main();
	}
	else {

		FILE* fp;
		fp = fopen("sifre.txt", "r");
		LoginEkran();
	don:
		fscanf(fp, "%s %s", validationusername, validationpassword);

		if (strcmp(validationpassword, Sifre) || strcmp(validationusername, KullaniciAdi)) {
			if (strcmp(validationpassword, Sifre) && strcmp(validationusername, KullaniciAdi)) {
				printf("kullanici adi ve sifreniz hatali tekrar deneyiniz...\n");
				LoginEkran();
				goto don;
			}
			else if (strcmp(validationusername, KullaniciAdi)) {
				printf("kullanici adiniz hatali tekrar deneyiniz...\n");
				LoginEkran();
				goto don;
			}
			else {
				printf("sifreniz hatali tekrar deneyiniz...\n");
				printf("sifremi unuttum ekrani icin 1 tusuna tekrar sifre girisi icin 2 tusuna basiniz\n");
				scanf("%d", &sec);
				if (sec == 1) {
					SifremiUnuttum();
				}
				else {
					LoginEkran();
					goto don;
				}
			}
		}
		else {
			HasilatDosyaYaz();
			HasilatShow();
			salonmatinebilgidosyayaz();
			salonmatineshow();
			main();
		}
		fclose(fp);
	}
}
void LoginEkran() {
	printf("Login Ekranina Hosgeldiniz...\n");
	printf("Kullanici adinizi giriniz(Lutfen gireceginiz kullanici adi bosluk iceriyorsa bosluk yerine _ giriniz)\n");
	scanf("%s", KullaniciAdi);
	printf("Sifrenizi giriniz");
	scanf("%s", Sifre);
}
void SifremiUnuttum() {
	FILE* fk;
	fk = fopen("sifre.txt", "r");
	fscanf(fk, "%s", validationusername);
	printf("Sifremi Unuttum Ekranina Hosgeldiniz...\n");
	printf("Lutfen hatirladiginiz kullanici adinizi giriniz(Lutfen gireceginiz kullanici adi bosluk iceriyorsa bosluk yerine _ giriniz)\n");
	scanf("%s", KullaniciAdi);
	if (strcmp(KullaniciAdi, validationusername)) {
		printf("Malesef Kullanici Adini Yanlis Girdiniz...\n");
		printf("Simdi yeni bir kullanici olusturalim\n");
		loginsayac = 0;
		fclose(fk);
		LoginIslem();
	}
	else {
		printf("Kullanici Adiniz Dogrulandi...\n");
		printf("Simdi yeni bir sifre olusturalim\n");
		printf("Lutfen yeni sifrenizi giriniz...\n");
		scanf("%s", Sifre);
		fk = fopen("sifre.txt", "w+");
		fprintf(fk, "%s %s", validationusername, Sifre);
		fclose(fk);
		HasilatDosyaYaz();
		HasilatShow();
		salonmatinebilgidosyayaz();
		salonmatineshow();
		main();
	}
}
void HasilatDosyaYaz() {
	printf("Hasilatlar dosyaya yaziliyor...\n");
	FILE* hp;
	int i, toplamhasilat = 0;
	hp = fopen("hasilat.txt", "w+");
	for (i = 0;i < sayac;i++) {
		toplamhasilat = toplamhasilat + Hasilatlar[i];
	}
	fprintf(hp, "%d", toplamhasilat);
	fclose(hp);
}
void HasilatShow() {
	printf("Hasilatlar gosteriliyor...\n");
	FILE* fpp;
	int hasilat;
	fpp = fopen("hasilat.txt", "r");
	fscanf(fpp, "%d", &hasilat);
	printf("Hasilat Bilgisi: %dTL dir.\n", hasilat);
	fclose(fpp);
}
void salonmatinebilgidosyayaz() {
	int i, j, k, say = 0;
	FILE* fpf;
	fpf = fopen("salonmatinebilgi.txt", "w+");
	for (i = 0;i < 3;i++) {
		if (i == 0) {
			for (j = 0;j < 5;j++) {
				for (k = 0;k < 50;k++) {
					if (green.pointergreenkoltuk[j][k] == 1) {
						say++;
					}
				}
				fprintf(fpf, "%d %s %d %s %d %s", i + 1, "nolusalonda", j + 1, "nolumatineyi", say, "kisiizliyor\n");
				say = 0;
			}
		}
		else if (i == 1) {
			for (j = 0;j < 5;j++) {
				for (k = 0;k < 50;k++) {
					if (red.pointerredkoltuk[j][k] == 1) {
						say++;
					}
				}
				fprintf(fpf, "%d %s %d %s %d %s", i + 1, "nolusalonda", j + 1, "nolumatineyi", say, "kisiizliyor\n");
				say = 0;
			}
		}
		else {
			for (j = 0;j < 5;j++) {
				for (k = 0;k < 50;k++) {
					if (blue.pointerbluekoltuk[j][k] == 1) {
						say++;
					}
				}
				fprintf(fpf, "%d %s %d %s %d %s", i + 1, "nolusalonda", j + 1, "nolumatineyi", say, "kisiizliyor\n");
				say = 0;
			}
		}
	}
	printf("Salonmatine bilgileri basarili bir sekilde dosyaya yaziliyor...\n");
	fclose(fpf);
}
void salonmatineshow() {
	printf("salon matine bilgileri gosteriliyor...\n");
	FILE* fs;
	int i, s1, s2, s3;
	char k1[20], k2[20], k3[20];
	fs = fopen("salonmatinebilgi.txt", "r");
	for (i = 0;i < 15;i++) {
		fscanf(fs, "%d %s %d %s %d %s", &s1, k1, &s2, k2, &s3, k3);
		printf("%d nolu salonda %d nolu matineyi %d kisi izliyor\n", s1, s2, s3);
	}
	fclose(fs);
}
void greenmatinefonk(enum matinegreen mg) {
	if (mg > 5) {
		printf("Lutfen 1-5 arasinda bir matine numarasi giriniz...");
	}
	else {
	koltuk:
		printf("Lutfen izleyeceginiz koltuk numarasini giriniz(1-50)");
		scanf("%d", &koltuksec);

		if (green.pointergreenkoltuk[mg - 1][koltuksec - 1] == 0) {
			green.pointergreenkoltuk[mg - 1][koltuksec - 1] = 1;
			printf("koltuk numaraniz basariyla olusturulmustur.\n");
			sayac++;
			main();
		}
		else {
			printf("koltuk dolu\n");
			goto koltuk;
		}
	}
}
void redmatinefonk(enum matinered mr) {
	if (mr > 5) {
		printf("Lutfen 1-5 arasinda bir matine numarasi giriniz...");
	}
	else {
	koltuk:
		printf("Lutfen izleyeceginiz koltuk numarasini giriniz");
		scanf("%d", &koltuksec);
		if (red.pointerredkoltuk[mr - 1][koltuksec - 1] == 0) {
			red.pointerredkoltuk[mr - 1][koltuksec - 1] = 1;
			printf("koltuk numaraniz basariyla olusturulmustur.\n");
			sayac++;
			main();
		}
		else {
			printf("koltuk dolu\n");
			goto koltuk;
		}
	}
}
void bluematinefonk(enum matineblue mb) {
	if (mb > 5) {
		printf("Lutfen 1-5 arasinda bir matine numarasi giriniz...");
	}
	else {
	koltuk:
		printf("Lutfen izleyeceginiz koltuk numarasini giriniz");
		scanf("%d", &koltuksec);
		if (blue.pointerbluekoltuk[mb - 1][koltuksec - 1] == 0) {
			blue.pointerbluekoltuk[mb - 1][koltuksec - 1] = 1;
			printf("koltuk numaraniz basariyla olusturulmustur.\n");
			sayac++;
			main();
		}
		else {
			printf("koltuk dolu\n");
			goto koltuk;
		}
	}
}
