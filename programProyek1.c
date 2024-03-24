/*

Documentation:
Group 13:
1. Arsinta Kirana Nisa (23606215980)
2. Putri Kiara Salsabila Arief (2306250743)

Class: PROGLAN02 (Dr. Ir. Dodi Sudiana M.Eng.)
Date: 18/03/2024
Version Number: 1.5

"Advanced Programming Practicum"
Mid Project - "TallyFunds: Program Pencatat Uang Pengeluaran dan Pendapatan"

Program purpose: The program is designed to record the user's income and expenses. 
The user can add, view, search, and sort transactions. The program will store the transactions in a file called "pendataan.txt".
There are 5 main features in this program:1
1. Help: Display the help menu. 
2. Add Transaction: Add a new transaction to the file.
3. View Transaction: Display all transactions that have been entered.
4. Search Transaction: Search for transactions based on their type.
5. Sort Transaction: Sort transactions based on their amount.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h> // Tambahkan library ini untuk menggunakan clrscr()

#define SIZE 100 // Ukuran maksimum array transaksi

// Prototipe fungsi-fungsi
void displayMenu();
void displayHelp();
void tambahTransaksi();
void lihatTransaksi();
void searchTransaksi();
void urutkanTransaksi();
int compare(const void *a, const void *b);
void cariTransaksi(char jenisCari[20], FILE *file);
void displayJenisPengeluaran();

// Struktur untuk menyimpan data transaksi
typedef struct Transaksi {
    char jenis[50];
    float jumlah;
} Transaksi;

// Definisikan fungsi compare
int compare(const void *a, const void *b) {
    const Transaksi *transaksiA = (const Transaksi *)a;
    const Transaksi *transaksiB = (const Transaksi *)b;
    
    if (transaksiA->jumlah < transaksiB->jumlah) return -1;
    else if (transaksiA->jumlah > transaksiB->jumlah) return 1;
    else return 0;
}

// Definisikan fungsi displayMenu
void displayMenu() {
    printf("\n=== Selamat Datang di TallyFunds! ===\n");
    printf("1. Help\n");
    printf("2. Tambah Transaksi\n");
    printf("3. Lihat Transaksi\n");
    printf("4. Cari Transaksi\n");
    printf("5. Urutkan Transaksi\n");
    printf("6. Exit\n");
}

int main() {
    int pilihan;
    do {
        displayMenu(); // Menampilkan menu
        printf("\nPilihan Anda: ");
        scanf("%d", &pilihan);
        switch (pilihan) {
            case 1:
                displayHelp();
                break;
            case 2:
                tambahTransaksi();
                break;
            case 3:
                lihatTransaksi();
                break;      
            case 4:
                searchTransaksi();
                break;
            case 5: 
                urutkanTransaksi();
                break;
            case 6:
                printf("Terima kasih telah menggunakan program ini.\n");
                break;      
            default:    
                printf("Pilihan tidak valid.\n");
        }   
    } while (pilihan != 6);
    return 0;
}

// Fungsi untuk menampilkan bantuan
void displayHelp() {
    system("cls"); // Membersihkan layar
    printf("\n=== Bantuan ===\n");
    printf("Program Pencatat Uang Pengeluaran dan Pendapatan\n");
    printf("1. Pilih opsi 'Tambah Transaksi' untuk menambahkan transaksi baru.\n");
    printf("2. Pilih opsi 'Lihat Transaksi' untuk melihat semua transaksi yang telah dimasukkan.\n");
    printf("3. Pilih opsi 'Cari Transaksi' untuk mencari transaksi berdasarkan jenisnya.\n");
    printf("4. Pilih opsi 'Urutkan Transaksi' untuk mengurutkan transaksi berdasarkan jumlahnya.\n");
    printf("5. Pilih opsi 'Exit' untuk keluar dari program.\n");
    printf("Selamat menggunakan!\n");
}

// Fungsi untuk menambahkan transaksi
void tambahTransaksi() {
    system("cls"); // Membersihkan layar
    struct Transaksi t;
    FILE *file;
    file = fopen("pendataan.txt", "a"); // Membuka file untuk menambahkan data
    
    printf("\nTambah Transaksi\n");
    
    int pilihanJenis;
    printf("Pilih Jenis (1. Pengeluaran, 2. Pendapatan): ");
    scanf("%d", &pilihanJenis);
    
    if (pilihanJenis == 1) {
        displayJenisPengeluaran();
        printf("Pilih Kategori Pengeluaran: ");
        int pilihanKategori;
        scanf("%d", &pilihanKategori);
        
        switch (pilihanKategori) {
            case 1:
                strcpy(t.jenis, "Makan");
                break;
            case 2:
                strcpy(t.jenis, "Transportasi");
                break;
            case 3:
                strcpy(t.jenis, "Kebutuhan Kuliah");
                break;
            case 4:
                strcpy(t.jenis, "Biaya Kesehatan");
                break;
            case 5:
                strcpy(t.jenis, "Hiburan");
                break;
            case 6:
                strcpy(t.jenis, "Komunikasi");
                break;
            default:
                printf("Pilihan tidak valid.\n");
                return;
        }
    } else if (pilihanJenis == 2) {
        strcpy(t.jenis, "Pendapatan");
    } else {
        printf("Pilihan tidak valid.\n");
        return;
    }
    
    printf("Jumlah: ");
    scanf("%f", &t.jumlah);
    
    // Menulis data ke file
    fprintf(file, "%s %.2f\n", t.jenis, t.jumlah);
    
    fclose(file); // Menutup file
    printf("Transaksi berhasil ditambahkan.\n");
}

// Fungsi untuk melihat transaksi
void lihatTransaksi() {
    system("cls"); // Membersihkan layar
    printf("\nLihat Transaksi\n");
    struct Transaksi t;
    FILE *file;
    file = fopen("pendataan.txt", "r"); // Membuka file untuk membaca data
    
    if (file == NULL) {
        printf("Belum ada transaksi yang dimasukkan.\n");
        return;
    }
    
    printf("Jenis\t\tJumlah\n");
    while (fscanf(file, "%s %f", t.jenis, &t.jumlah) != EOF) {
        printf("%-15s %.2f\n", t.jenis, t.jumlah);
    }
    
    fclose(file); // Menutup file
}

// Fungsi rekursif untuk mencari transaksi berdasarkan jenisnya
void cariTransaksi(char jenisCari[20], FILE *file) {
    struct Transaksi t;
    if (fscanf(file, "%s %f", t.jenis, &t.jumlah) == EOF)
    return;
    
    if (strcasecmp(t.jenis, jenisCari) == 0)
        printf("%s\t%.2f\n", t.jenis, t.jumlah);
    
    cariTransaksi(jenisCari, file);
}

// Fungsi untuk mencari transaksi
void searchTransaksi() {
    system("cls"); // Membersihkan layar
    printf("\nCari Transaksi\n");
    char jenisCari[20];
    printf("Masukkan jenis transaksi yang ingin dicari: ");
    scanf("%s", jenisCari);
    
    // Membersihkan input buffer
    fflush(stdin);
    
    FILE *file;
    file = fopen("pendataan.txt", "r"); // Membuka file untuk membaca data
    
    if (file == NULL) {
        printf("Belum ada transaksi yang dimasukkan.\n");
        return;
    }
    
    printf("Jenis\t\tJumlah\n");
    cariTransaksi(jenisCari, file);
    
    fclose(file); // Menutup file
}

// Fungsi untuk menampilkan jenis pengeluaran
void displayJenisPengeluaran() {
    printf("\n=== Jenis Pengeluaran ===\n");
    printf("1. Makan\n");
    printf("2. Transportasi\n");
    printf("3. Kebutuhan Kuliah\n");
    printf("4. Biaya Kesehatan\n");
    printf("5. Hiburan\n");
    printf("6. Komunikasi\n");
}

// Fungsi untuk mengurutkan transaksi
void urutkanTransaksi() {
    system("cls"); // Membersihkan layar
    printf("\nUrutkan Transaksi\n");
    
    struct Transaksi *transaksi;
    int jumlahTransaksi = 0;
    FILE *file;
    file = fopen("pendataan.txt", "r"); // Membuka file untuk membaca data
    
    if (file == NULL) {
        printf("Belum ada transaksi yang dimasukkan.\n");
        return;
    }
    
    // Menghitung jumlah transaksi
    while (!feof(file)) {
        char c = fgetc(file);
        if (c == '\n')
            jumlahTransaksi++;
    }
    fseek(file, 0, SEEK_SET); // Mengembalikan pointer file ke awal
    
    // Mengalokasikan memori untuk array transaksi
    transaksi = (struct Transaksi *)malloc(jumlahTransaksi * sizeof(struct Transaksi));
    
    // Membaca data transaksi ke dalam array
    int i = 0;
    while (fscanf(file, "%s %f", transaksi[i].jenis, &transaksi[i].jumlah) != EOF) {
        i++;
    }
    fclose(file); // Menutup file
    
    // Mengurutkan transaksi
    qsort(transaksi, jumlahTransaksi, sizeof(struct Transaksi), compare);
    
    // Menampilkan transaksi yang sudah diurutkan
    printf("Jenis\t\tJumlah\n");
    for (i = 0; i < jumlahTransaksi; i++) {
        printf("%-15s %.2f\n", transaksi[i].jenis, transaksi[i].jumlah);
    }
    
    free(transaksi); // Mendealokasikan memori
}
