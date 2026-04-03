#include <cstdlib>
#include <fstream>
#include <iostream>
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

        jumlah_lagu++;
    }

    file.close();
}

void aksi_lagu(int indeks) {
    int pilihan_lagu;

    while (true) {
        cout << "0. Kembali" << endl;
        cout << "1. Masukkan ke Antrean" << endl;
        cout << "2. Putar Sekarang" << endl;

        cout << "Pilih: ";
        cin >> pilihan_lagu;

        if (pilihan_lagu == 0) {
            break;
        } else if (pilihan_lagu == 1) {
            tambah_antrean(daftar_lagu[indeks].judul, daftar_lagu[indeks].penyanyi);
            return;
        } else if (pilihan_lagu == 2) {
            putar_sekarang(daftar_lagu[indeks].judul, daftar_lagu[indeks].penyanyi);
            return;
        } else {
            cout << "Silakan masukkan pilihan yang valid";
        }
    }
}

// buat bikin fungsi lowercase buat ngebandingin dengan database sementara aja
string lowercase(string teks) {
    for (int i = 0; i < teks.length(); i++) {
        teks[i] = tolower(teks[i]);
    }
    return teks;
}

void cari_lagu() {
    cin.ignore(1000, '\n');
    while (true) {
        string input_user;
        cout << "Lagu yang ingin dicari (ketik '0' untuk kembali) : ";
        getline(cin, input_user);
        if (input_user == "0") return;

        bool ketemu = false;
        for (int i = 0; i < jumlah_lagu; i++) {
            if (lowercase(input_user) == lowercase(daftar_lagu[i].judul)) {
                cout << "Lagu berhasil ditemukan!" << endl;
                cout << daftar_lagu[i].judul << " - " << daftar_lagu[i].penyanyi << endl;
                ketemu = true;
                aksi_lagu(i);
                cin.ignore(1000, '\n');
                break;
            }
        }
        if (ketemu == false) {
            cout << "Lagu tidak ditemukan! " << endl;
        }
    }
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
            cout << "\n \n Kamu memilih: " << daftar_lagu[pilihan - 1].judul << " - " << daftar_lagu[pilihan - 1].penyanyi << endl;
            aksi_lagu(pilihan - 1);
        } else {
            cout << "Pilihan tidak valid";
        }
    }
}