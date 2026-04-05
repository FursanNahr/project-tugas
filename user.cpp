#include <cstdlib>
#include <iostream>
#include <string>

#include "header/lagu.h"
#include "header/playlist.h"
#include "header/queue.h"
using namespace std;

void menu_user(string username) {
    while (true) {
        system("cls");

        cout << "\n🎵 ═════════════════════════════════════════ 🎵" << endl;
        cout << " ✨  Selamat Datang, " << username << " di LEORA!  ✨" << endl;
        cout << "🎵 ═════════════════════════════════════════ 🎵" << endl;
        cout << "  [1] 🎧 Now Playing" << endl;
        cout << "  [2] 📜 Tampilkan Semua Lagu" << endl;
        cout << "  [3] 🔍 Cari Lagu" << endl;
        cout << "  [4] 💽 Playlist Kamu" << endl;
        cout << "  ─────────────────────────────────────────" << endl;
        cout << "  [0] 🚪 Keluar" << endl;
        cout << "===========================================" << endl;

        int input_pilihan;
        cout << "👉 Pilih aksi (0-4): ";
        cin >> input_pilihan;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');

            cout << "❌ Input harus angka! Coba lagi.\n";
            continue;
        }

        switch (input_pilihan) {
            case 1:
                sedang_diputar();
                break;
            case 2:
                tampilkan_lagu();
                break;
            case 3:
                cari_lagu();
                break;
            case 4:
                playlist(username);
                break;
            case 0:
                exit(0);
            default:
                cout << "Pilihan tidak valid.";
        }
    }
}
