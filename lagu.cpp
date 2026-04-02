#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>

using namespace std;

#include "queue.cpp"

struct lagu {
    string judul;
    string penyanyi;
};

lagu daftar_lagu[100];
int jumlah_lagu = 0;

void load_lagu() {
    ifstream file("data_lagu.txt");
    string line;

    jumlah_lagu = 0;

    while (getline(file, line)) {
        stringstream ss(line);
        string judul, penyanyi;

        getline(ss, judul, '|');
        getline(ss, penyanyi, '|');

        daftar_lagu[jumlah_lagu].judul = judul;
        daftar_lagu[jumlah_lagu].penyanyi = penyanyi;

        jumlah_lagu ++;
    }

    file.close();
}

void cari_lagu() {

}

void tampilkan_lagu() {
    int pilihan;
    while (true) {
        system("cls");

        cout << "---------- DAFTAR LAGU ----------" << endl;
    
        cout << "0. Kembali" << endl;
    
        if (jumlah_lagu == 0) {
            cout << "belum ada lagu." << endl;
            return;
        }
    
        for (int i = 0; i < jumlah_lagu; i++) {
            cout << i + 1 << ". " << daftar_lagu[i].judul << " - " << daftar_lagu[i].penyanyi << endl;
        }
    
        cout << "pilih: ";
        cin >> pilihan;
    
        if (pilihan == 0) {
            return;
        } else if (pilihan >= 1 && pilihan <= jumlah_lagu) {
            int indeks = pilihan - 1;
            int pilihan_lagu;

            while (true) {
                cout << "Kamu memilih: " << daftar_lagu[indeks].judul << " - " << daftar_lagu[indeks].penyanyi << endl;
    
                cout << "0. Kembali" << endl;
                cout << "1. Masukkan ke Antrean" << endl;
                cout << "2. Putar Sekarang" << endl;
    
                cout << "Pilih: "; cin >> pilihan_lagu;
    
                if (pilihan_lagu == 0) {
                    return;
                } else if (pilihan_lagu == 1) {
                    tambah_antrean(daftar_lagu[indeks].judul, daftar_lagu[indeks].penyanyi);
                    break;
                } else if (pilihan_lagu == 2) {
                    putar_sekarang(daftar_lagu[indeks].judul, daftar_lagu[indeks].penyanyi);
                    break;
                } else {
                    cout << "Silakan masukkan pilihan yang valid";
                }
            }



        } else {
            cout << "Pilihan tidak valid";
        }
    }
}