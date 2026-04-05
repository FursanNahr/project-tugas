#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>

using namespace std;

#include "header/admin.h"
#include "header/lagu.h"
#include "header/playlist.h"
#include "header/queue.h"

Lagu daftar_lagu[100];
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
        system("cls");

        cout << "\n Kamu memilih " << daftar_lagu[indeks].judul << " - " << daftar_lagu[indeks].penyanyi << endl;

        cout << "\n🎵 ════════ OPSI LAGU ════════ 🎵" << endl;
        cout << "  [1] ➕ Masukkan ke Antrean" << endl;
        cout << "  [2] ▶️  Putar Sekarang" << endl;
        cout << "  ──────────────────────────────" << endl;
        cout << "  [0] 🔙 Kembali" << endl;
        cout << "================================" << endl;
        cout << "👉 Pilih Aksi (0-2): ";
        cin >> pilihan_lagu;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "❌ Error: Input harus berupa angka! Coba lagi ya." << endl;
            pause();
            continue;
        }

        if (pilihan_lagu == 0) {
            break;

        } else if (pilihan_lagu == 1) {
            tambah_antrean(daftar_lagu[indeks].judul, daftar_lagu[indeks].penyanyi);
            cout << "✅ Lagu berhasil dimasukkan ke antrean!" << endl;
            pause();
            return;
        } else if (pilihan_lagu == 2) {
            putar_sekarang(daftar_lagu[indeks].judul, daftar_lagu[indeks].penyanyi);
            cout << "▶️ Lagu sedang diputar!" << endl;
            pause();
            return;
        } else {
            cout << "❌ Pilihan tidak valid!" << endl;
            pause();
        }
    }
}

string lowercase(string teks) {
    for (int i = 0; i < teks.length(); i++) {
        teks[i] = tolower(teks[i]);
    }
    return teks;
}

void cari_lagu() {
    while (true) {
        string input_user;
        cout << "========== CARI LAGU ==========" << endl;
        cout << "Lagu yang ingin dicari (ketik '0' untuk kembali) : ";
        getline(cin, input_user);
        if (input_user == "0")
            return;

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

        cout << "\n🎵 ══════════ DAFTAR LAGU ══════════ 🎵" << endl;

        cout << "0. Kembali" << endl;

        if (jumlah_lagu == 0) {
            cout << "  📭 Belum ada lagu di dalam sistem." << endl;
            cout << "=======================================" << endl;
            return;
        }

        for (int i = 0; i < jumlah_lagu; i++) {
            cout << i + 1 << ". " << daftar_lagu[i].judul << " - " << daftar_lagu[i].penyanyi << endl;
        }
        cout << "  ─────────────────────────────────────" << endl;
        cout << "  [0] 🔙 Kembali" << endl;
        cout << "=======================================" << endl;
        cout << "👉 Pilih nomor lagu (1-" << jumlah_lagu << "): ";

        pilihan = ambil_input_angka();

        if (pilihan == 0) {
            return;
        } else if (pilihan >= 1 && pilihan <= jumlah_lagu) {
            aksi_lagu(pilihan - 1);
        } else {
            cout << "❌ Pilihan tidak valid! Pilih nomor yang ada di daftar." << endl;
            pause();
        }
    }
}