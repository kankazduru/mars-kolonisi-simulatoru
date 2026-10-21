#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

// Degerleri 0-100 sinirlarinda tutmak icin yardimci fonksiyon
int sinirla(int deger) {
    if (deger > 100) return 100;
    if (deger < 0) return 0;
    return deger;
}

int main() {
    // Dev-C++ uyumlulugu icin tum degiskenler blok basinda tanimlaniyor
    int saglik = 100, enerji = 100, oksijen = 100;
    int su = 0, yedek_parca = 0, modul_hasari = 0;
    int kilit_muhurlu = 0;
    int gun = 1, tur = 0;
    char zorluk;
    int firtina_turu = 5;
    int zorluk_gecerli = 0;
    char komut;
    int oyun_devam = 1;
    int puan;

    srand(time(NULL));

    printf("--- MARS KOLONISI YASAM DESTEK SIMULATORU ---\n");
    
    // Zorluk Secimi
    do {
        printf("Zorluk seviyesi secin (K: Kolay, N: Normal, Z: Zor): ");
        scanf(" %c", &zorluk);
        zorluk = toupper(zorluk);
        
        switch(zorluk) {
            case 'K':
                su = 15; yedek_parca = 5; firtina_turu = 3;
                zorluk_gecerli = 1; break;
            case 'N':
                su = 10; yedek_parca = 3; firtina_turu = 5;
                zorluk_gecerli = 1; break;
            case 'Z':
                su = 5; yedek_parca = 1; firtina_turu = 7;
                zorluk_gecerli = 1; break;
            default:
                printf("Gecersiz zorluk seviyesi!\n");
        }
    } while (!zorluk_gecerli);

    // Ana Oyun Dongusu
    do {
        int tur_harcandi = 0;

        printf("\n================ KOMUTLAR ================\n");
        printf("G: Kesif      | O: Oksijen Uret | T: Tamir\n");
        printf("D: Durum      | U: Uyu/Dinlen   | K: Kum Firtinasi\n");
        printf("H: Hava Kilidi| Q: Cikis\n");
        printf("==========================================\n");
        printf("[Gun: %d | Tur: %d] Komutunuzu secin: ", gun, tur);
        scanf(" %c", &komut);
        
        switch (komut) {
            case 'g': case 'G': {
                int zar, ihtimal_esigi, bulgu;
                if (enerji < 15 || oksijen < 10) {
                    printf("Yetersiz enerji veya oksijen! Kesif iptal edildi.\n");
                } else {
                    enerji -= 15;
                    oksijen -= 10;
                    tur_harcandi = 1;
                    
                    zar = rand() % 100;
                    printf("Zar: %d\n", zar);
                    
                    if (zar < 10 || modul_hasari > 70) {
                        printf("Kesifte kaza gecirdiniz! Saglik kaybettiniz.\n");
                        saglik -= 15;
                    }
                    
                    ihtimal_esigi = (enerji > 40 && oksijen > 30) ? 60 : 30;
                    bulgu = rand() % 100;
                    if (bulgu < ihtimal_esigi) {
                        printf("Harika! Su buldunuz.\n");
                        su += 3;
                    } else if (bulgu >= ihtimal_esigi && bulgu < ihtimal_esigi + 20) {
                        printf("Sanslisiniz! Yedek parca buldunuz.\n");
                        yedek_parca += 1;
                    } else {
                        printf("Eli bos dondunuz.\n");
                    }
                }
                break;
            }
            case 'o': case 'O': {
                int kullanilacak_su, uretim_sayisi, kalan_su;
                if (enerji < 5 || su < 2) {
                    printf("Yetersiz su (en az 2) veya enerji! Oksijen uretilemiyor.\n");
                } else {
                    kullanilacak_su = su;
                    uretim_sayisi = kullanilacak_su / 2;
                    kalan_su = kullanilacak_su % 2; 
                    
                    oksijen += (uretim_sayisi * 3);
                    enerji -= 5;
                    su = kalan_su;
                    tur_harcandi = 1;
                    printf("%d birim su harcanarak %d birim oksijen uretildi. Kalan su: %d\n", kullanilacak_su - kalan_su, uretim_sayisi * 3, kalan_su);
                }
                break;
            }
            case 't': case 'T': {
                if (yedek_parca <= 0) {
                    printf("Yedek parca yok! Tamir yapilamaz.\n");
                } else if (modul_hasari == 0) {
                    printf("Modul hasari yok, tamire gerek yok.\n");
                } else {
                    tur_harcandi = 1;
                    yedek_parca--;
                    if (modul_hasari <= 30) {
                        modul_hasari -= 10;
                        printf("Hafif hasar onarildi.\n");
                    } else if (modul_hasari <= 70) {
                        modul_hasari -= 20;
                        printf("Orta hasar onarildi.\n");
                    } else {
                        modul_hasari -= 30;
                        printf("Agir hasar onarildi.\n");
                    }
                }
                break;
            }
            case 'd': case 'D': {
                int tehlike = 0;
                printf("\n--- DURUM RAPORU ---\n");
                printf("Saglik: %d, Enerji: %d, Oksijen: %d, Su: %d, Parca: %d, Hasar: %d, Kilit: %s\n", 
                       saglik, enerji, oksijen, su, yedek_parca, modul_hasari, kilit_muhurlu ? "Muhurlu" : "Acik");
                
                if (oksijen < 25) { printf("UYARI: Oksijen kritik seviyede!\n"); tehlike = 1; }
                if (saglik < 30) { printf("UYARI: Saglik kritik seviyede!\n"); tehlike = 1; }
                if (modul_hasari > 70) { printf("UYARI: Modul hasari kritik seviyede!\n"); tehlike = 1; }
                
                if (!tehlike && saglik >= 30 && oksijen >= 25 && modul_hasari <= 70) {
                    printf("TUM SISTEMLER NORMAL.\n");
                }
                break;
            }
            case 'u': case 'U': {
                tur_harcandi = 1;
                enerji += 25;
                if (oksijen < 20) {
                    saglik -= 10;
                    printf("Uyudunuz ancak oksijen yetersizliginden sagliginiz kotulesti!\n");
                } else {
                    saglik += 15;
                    oksijen -= 5;
                    printf("Dinlendiniz. Enerji ve saglik artti.\n");
                }
                break;
            }
            case 'k': case 'K': {
                int i, hasar_katsayisi, olay;
                tur_harcandi = 1;
                printf("\nKUM FIRTINASI BASLADI!\n");
                for (i = 1; i <= firtina_turu; i++) {
                    hasar_katsayisi = (i % 2 == 0) ? 2 : 1; 
                    
                    olay = rand() % 100;
                    if (olay < 30) {
                        saglik -= (5 * hasar_katsayisi);
                        printf("Tur %d: Firtinadan hasar aldiniz!\n", i);
                    } else if (olay < 60) {
                        if (kilit_muhurlu) {
                            printf("Tur %d: Hava kilidi muhurlu, oksijen sizintisi onlendi.\n", i);
                            continue;
                        }
                        oksijen -= (8 * hasar_katsayisi);
                        printf("Tur %d: Oksijen sizintisi yasandi!\n", i);
                    } else if (olay < 80) {
                        modul_hasari += (10 * hasar_katsayisi);
                        printf("Tur %d: Modul hasar gordu!\n", i);
                    } else {
                        printf("Tur %d: Guvendesiniz.\n", i);
                    }
                    
                    if (saglik <= 0 || oksijen <= 0) {
                        printf("Firtina sirasinda kritik degerler sifirlandi!\n");
                        break;
                    }
                }
                printf("Firtina sona erdi.\n");
                break;
            }
            case 'h': case 'H': {
                if (kilit_muhurlu) {
                    printf("Kilit zaten muhurlu.\n");
                } else {
                    char dogru_sifre, girilen_sifre;
                    int deneme = 0;
                    int basarili = 0;
                    
                    tur_harcandi = 1;
                    dogru_sifre = 'A' + (gun % 26);
                    
                    printf("Ipuci: Sifre, alfabede A harfinden bugunun gun sayisi kadar ilerideki harftir.\n");
                    
                    do {
                        printf("Sifreyi giriniz (%d/3 deneme): ", deneme + 1);
                        scanf(" %c", &girilen_sifre);
                        girilen_sifre = toupper(girilen_sifre);
                        deneme++;
                        
                        if (girilen_sifre == dogru_sifre) {
                            basarili = 1;
                        } else {
                            enerji -= 5;
                            if (girilen_sifre < dogru_sifre) printf("Ileri git!\n");
                            else printf("Geri git!\n");
                        }
                    } while (basarili == 0 && deneme < 3);
                    
                    if (basarili) {
                        kilit_muhurlu = 1;
                        printf("Sifre dogru! Kilit muhurlendi.\n");
                    } else {
                        modul_hasari += 20;
                        printf("Basarisiz! Modul hasari artti.\n");
                    }
                }
                break;
            }
            case 'q': case 'Q':
                oyun_devam = 0;
                printf("Simulasyondan cikiliyor...\n");
                break;

            default:
                printf("Gecersiz komut! Tur harcanmadi.\n");
                break;
        }

        // Tur ve Gun Yonetimi
        if (tur_harcandi) {
            tur++;
            if (tur % 3 == 0) {
                gun++;
                oksijen -= 8;
                if (modul_hasari > 70) {
                    saglik -= 5;
                    printf("\nYENI GUN: Yuksek modul hasari nedeniyle saglik azaldi!\n");
                } else {
                    printf("\nYENI GUN BASLADI!\n");
                }
                kilit_muhurlu = 0; 
            }
        }
        
        // Degerleri Sinirlandirma
        saglik = sinirla(saglik);
        enerji = sinirla(enerji);
        oksijen = sinirla(oksijen);
        modul_hasari = sinirla(modul_hasari);

        // Oyun Sonu Kontrolleri
        if (saglik == 0 || oksijen == 0) {
            printf("\n--- OYUN BITTI: Hayatta Kalamadiniz! ---\n");
            oyun_devam = 0;
        } else if (gun > 15) {
            printf("\n--- TEBRIKLER: Kurtarma Ekibi Geldi! (15 Gun Tamamlandi) ---\n");
            oyun_devam = 0;
        }

    } while (oyun_devam);

    // Skor Hesaplama
    puan = (gun * 100) + saglik + oksijen - modul_hasari;
    printf("\n--- OYUN SONU RAPORU ---\n");
    printf("Hayatta Kalinan Gun: %d\n", (gun > 15) ? 15 : gun);
    printf("Toplam Tur: %d\n", tur);
    printf("Son Durum -> Saglik: %d, Oksijen: %d, Modul Hasari: %d\n", saglik, oksijen, modul_hasari);
    printf("Toplam Puaniniz: %d\n", puan);

    return 0;
}
