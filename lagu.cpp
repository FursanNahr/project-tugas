// clang-format off
#include <windows.h>
#include <mmsystem.h>
// clang-format on

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
        string judul, penyanyi, mood, genre, midi;

        getline(ss, judul, '|');
        getline(ss, penyanyi, '|');
        getline(ss, mood, '|');
        getline(ss, genre, '|');
        getline(ss, midi);

        daftar_lagu[jumlah_lagu].judul = judul;
        daftar_lagu[jumlah_lagu].penyanyi = penyanyi;
        daftar_lagu[jumlah_lagu].mood = mood;
        daftar_lagu[jumlah_lagu].genre = genre;
        daftar_lagu[jumlah_lagu].midi = midi;

        jumlah_lagu++;
    }

    file.close();
}

void aksi_lagu(int indeks) {
    int pilihan_lagu;

    while (true) {
        system("cls");

        cout << "\n 🎧 Kamu memilih: " << daftar_lagu[indeks].judul << " - " << daftar_lagu[indeks].penyanyi << endl;
        cout << "    [" << daftar_lagu[indeks].genre << " | " << daftar_lagu[indeks].mood << "]\n"
             << endl;

        cout << "🎵 ════════ OPSI LAGU ════════ 🎵" << endl;
        cout << "  [1] ➕ Masukkan ke Antrean" << endl;
        cout << "  [2] ▶️  Putar Sekarang" << endl;
        cout << "  ──────────────────────────────" << endl;
        cout << "  [0] 🔙 Kembali" << endl;
        cout << "================================" << endl;
        cout << "👉 Pilih aksi (0-2): ";

        pilihan_lagu = ambil_input_angka();

        if (pilihan_lagu == 1) {
            tambah_antrean(daftar_lagu[indeks].judul, daftar_lagu[indeks].penyanyi);
            cout << "✅ Dimasukkan ke antrean!" << endl;
            pause();
            return;
        } else if (pilihan_lagu == 2) {
            putar_sekarang(daftar_lagu[indeks].judul, daftar_lagu[indeks].penyanyi);

            cout << "▶️ Sedang diputar!" << endl;
            pause();
            return;
        } else if (pilihan_lagu == 0) {
            return;
        } else {
            cout << "❌ Pilihan tidak valid!" << endl;
            pause();
        }
    }
}

void tampilkan_lagu() {
    int pilihan;
    while (true) {
        system("cls");

        cout << "\n🎵 ═══════════════ DAFTAR LAGU LEORA ═══════════════ 🎵\n"
             << endl;

        if (jumlah_lagu == 0) {
            cout << "  📭 Belum ada lagu di dalam sistem." << endl;
            cout << "=======================================" << endl;
            cout << "  [0] 🔙 Kembali\n";
        } else {
            cout << "  Total lagu : " << jumlah_lagu << " lagu\n";
            cout << "  ┌────┬────────────────────────┬─────────────────┬──────────────┬────────────┐" << endl;
            cout << "  │ No │ Judul                  │ Penyanyi        │ Genre        │ Mood       │" << endl;
            cout << "  ├────┼────────────────────────┼─────────────────┼──────────────┼────────────┤" << endl;

            // Lambda function untuk padding tabel yang rapi
            auto pad = [](string s, int w) -> string {
                if ((int)s.size() > w) s = s.substr(0, w - 1) + "~";
                return s + string(w - s.size(), ' ');
            };

            for (int i = 0; i < jumlah_lagu; i++) {
                cout << "  │ " << pad(to_string(i + 1), 2)
                     << " │ " << pad(daftar_lagu[i].judul, 22)
                     << " │ " << pad(daftar_lagu[i].penyanyi, 15)
                     << " │ " << pad(daftar_lagu[i].genre, 12)
                     << " │ " << pad(daftar_lagu[i].mood, 10)
                     << " │" << endl;
            }
            cout << "  └────┴────────────────────────┴─────────────────┴──────────────┴────────────┘" << endl;
            cout << "  [0] 🔙 Kembali\n";
        }

        cout << "\n👉 Pilih nomor lagu (1-" << jumlah_lagu << "): ";
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