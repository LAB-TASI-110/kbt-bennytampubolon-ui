#include <stdio.h>
#include <string.h>
#include <ctype.h> // Untuk fungsi tolower

// Konstanta
#define MAX_BANGKU 12
#define HARGA_REGULER_PER_300KM 100000
#define KENA_EXECUTIVE_PERCENTAGE 0.60 // 60% lebih mahal
#define MAX_INPUT_LEN 20 // Panjang maksimum untuk input string

// Fungsi untuk membersihkan buffer input
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    int jumlahBangkuDipesan;
    char kotaTujuanStr[MAX_INPUT_LEN];
    char jenisAngkutanStr[MAX_INPUT_LEN];
    long long hargaTotal = 0;
    int jarakTempuhKM = 0;
    int pilihanValid = 0;

    printf("=======================================\n");
    printf("  SISTEM PEMBELIAN TIKET BUS ANTARKOTA\n");
    printf("=======================================\n");

    // Input jumlah bangku yang dipesan
    do {
        printf("Masukkan jumlah bangku yang ingin dipesan (maks %d): ", MAX_BANGKU);
        if (scanf("%d", &jumlahBangkuDipesan) != 1 || jumlahBangkuDipesan <= 0 || jumlahBangkuDipesan > MAX_BANGKU) {
            printf("Input tidak valid. Harap masukkan bilangan bulat positif tidak lebih dari %d.\n", MAX_BANGKU);
            clearInputBuffer(); // Membersihkan buffer input
        } else {
            pilihanValid = 1;
        }
    } while (!pilihanValid);
    pilihanValid = 0; // Reset untuk validasi berikutnya
    clearInputBuffer(); // Membersihkan buffer input setelah scanf %d

    // Input kota tujuan
    do {
        printf("Pilih kota tujuan (Kota A, Kota B, Kota C): ");
        // Menggunakan scanf %s untuk membaca satu kata.
        // Asumsi input kota tujuan adalah satu kata, cth: "Kota" "A", atau "A" saja.
        // Jika ingin mendukung "Kota A", "Kota B" sebagai satu string utuh,
        // maka scanf dengan format khusus atau fungsi kustom yang membaca spasi akan diperlukan.
        // Sesuai contoh prompt: "kota c", jadi satu kata.
        if (scanf("%s", kotaTujuanStr) == 1) {
            clearInputBuffer(); // Membersihkan buffer input setelah scanf %s
            
            // Konversi ke lowercase untuk perbandingan case-insensitive
            char tempKotaTujuan[MAX_INPUT_LEN];
            for (int i = 0; kotaTujuanStr[i]; i++) {
                tempKotaTujuan[i] = tolower(kotaTujuanStr[i]);
            }
            tempKotaTujuan[strlen(kotaTujuanStr)] = '\0';

            // Logika asumsi jarak:
            // Dari titik awal ke A = 300km
            // Dari titik awal ke B = 600km (300km ke A + 300km ke B)
            // Dari titik awal ke C = 900km (300km ke A + 300km ke B + 300km ke C)
            if (strcmp(tempKotaTujuan, "kotaa") == 0 || strcmp(tempKotaTujuan, "a") == 0) {
                jarakTempuhKM = 300; 
                pilihanValid = 1;
            } else if (strcmp(tempKotaTujuan, "kotab") == 0 || strcmp(tempKotaTujuan, "b") == 0) {
                jarakTempuhKM = 600; 
                pilihanValid = 1;
            } else if (strcmp(tempKotaTujuan, "kotac") == 0 || strcmp(tempKotaTujuan, "c") == 0) {
                jarakTempuhKM = 900; 
                pilihanValid = 1;
            } else {
                printf("Input tidak valid. Harap masukkan 'Kota A', 'Kota B', atau 'Kota C'.\n");
            }
        } else {
             printf("Gagal membaca input.\n");
             clearInputBuffer();
        }
    } while (!pilihanValid);
    pilihanValid = 0; // Reset untuk validasi berikutnya

    // Input jenis angkutan
    do {
        printf("Pilih jenis angkutan (Executive/Reguler): ");
        if (scanf("%s", jenisAngkutanStr) == 1) {
            clearInputBuffer(); // Membersihkan buffer input setelah scanf %s
            
            // Konversi ke lowercase untuk perbandingan case-insensitive
            char tempJenisAngkutan[MAX_INPUT_LEN];
            for (int i = 0; jenisAngkutanStr[i]; i++) {
                tempJenisAngkutan[i] = tolower(jenisAngkutanStr[i]);
            }
            tempJenisAngkutan[strlen(jenisAngkutanStr)] = '\0';

            if (strcmp(tempJenisAngkutan, "reguler") == 0 || strcmp(tempJenisAngkutan, "executive") == 0) {
                pilihanValid = 1;
            } else {
                printf("Input tidak valid. Harap masukkan 'Executive' atau 'Reguler'.\n");
            }
        } else {
            printf("Gagal membaca input.\n");
            clearInputBuffer();
        }
    } while (!pilihanValid);
    
    // Hitung harga dasar per bangku berdasarkan jarak
    // Diasumsikan harga 100.000 untuk setiap 300km perjalanan.
    // Jika jaraknya 600km, berarti 2x lipat. Jika 900km, 3x lipat.
    double hargaDasarPerBangku = (double)HARGA_REGULER_PER_300KM * (jarakTempuhKM / 300);

    // Sesuaikan harga jika executive
    char tempJenisAngkutanFinal[MAX_INPUT_LEN];
    for (int i = 0; jenisAngkutanStr[i]; i++) {
        tempJenisAngkutanFinal[i] = tolower(jenisAngkutanStr[i]);
    }
    tempJenisAngkutanFinal[strlen(jenisAngkutanStr)] = '\0';

    if (strcmp(tempJenisAngkutanFinal, "executive") == 0) {
        hargaDasarPerBangku *= (1 + KENA_EXECUTIVE_PERCENTAGE);
    }

    // Hitung harga total
    hargaTotal = (long long)(hargaDasarPerBangku * jumlahBangkuDipesan);

    printf("\n=======================================\n");
    printf("         DETAIL PEMESANAN TIKET\n");
    printf("=======================================\n");
    printf("Jumlah bangku dipesan: %d\n", jumlahBangkuDipesan);
    printf("Kota tujuan          : %s\n", kotaTujuanStr);
    printf("Jarak tempuh         : %d KM\n", jarakTempuhKM);
    printf("Jenis angkutan       : %s\n", jenisAngkutanStr);
    printf("---------------------------------------\n");
    printf("Harga total tiket    : IDR %lld\n", hargaTotal);
    printf("=======================================\n");

    return 0;
}