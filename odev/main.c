#include <stdio.h>
#include <time.h>

// Tarih ve saat bilgilerini saklamak icin yapi (struct)
typedef struct {
    int gun;
    int ay;
    int yil;
    int saat;
    int dakika;
    int saniye;
} TarihSaat;

// Farkli veri turlerini saklamak icin birlik (union)
typedef union {
    TarihSaat tarihSaat;
    time_t epochZamani;
} ZamanBirimleri;

// Kullanicidan tarih ve saat bilgisi al
void kullanicidanTarihSaatAl(TarihSaat *ts) {
    printf("Gun Ay Yil (Orn: 10 02 2025): ");
    scanf("%d %d %d", &ts->gun, &ts->ay, &ts->yil);

    printf("Saat Dakika Saniye (Orn: 14 30 00): ");
    scanf("%d %d %d", &ts->saat, &ts->dakika, &ts->saniye);
}

// Tarih ve saat bilgisini epoch zamanina cevir
time_t epochHesapla(TarihSaat ts) {
    struct tm zamanStruct = {0};

    zamanStruct.tm_mday = ts.gun;
    zamanStruct.tm_mon = ts.ay - 1; // tm struct'inda ay 0'dan baslar
    zamanStruct.tm_year = ts.yil - 1900; // tm struct'inda yil 1900'den baslar
    zamanStruct.tm_hour = ts.saat;
    zamanStruct.tm_min = ts.dakika;
    zamanStruct.tm_sec = ts.saniye;

    return mktime(&zamanStruct); // Epoch zamanini dondur
}

int main() {
    ZamanBirimleri zaman1, zaman2;

    printf("Birinci tarihi giriniz:\n");
    kullanicidanTarihSaatAl(&zaman1.tarihSaat);

    printf("\nIkinci tarihi giriniz:\n");
    kullanicidanTarihSaatAl(&zaman2.tarihSaat);

    // Epoch zamanlarini hesapla
    zaman1.epochZamani = epochHesapla(zaman1.tarihSaat);
    zaman2.epochZamani = epochHesapla(zaman2.tarihSaat);

    // Epoch degerlerini ekrana yazdir
    printf("\nBirinci tarihin epoch zamani: %ld\n", zaman1.epochZamani);
    printf("Ikinci tarihin epoch zamani: %ld\n", zaman2.epochZamani);

    // Zaman farkini hesapla
    double fark = difftime(zaman2.epochZamani, zaman1.epochZamani);
    printf("\nIki tarih arasindaki zaman farki: %.0f saniye (%.2f saat)\n", fark, fark / 3600.0);

    return 0;
}
