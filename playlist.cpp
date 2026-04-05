#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
using namespace std;
#include "header/lagu.h"
#include "header/queue.h"
struct Playlist {
    string judul_playlist;
    string pemilik;
    int isi_lagu[1000];
    int jumlah_lagu;
};

Playlist semua_playlist[100];
int total_playlist = 0;

void pause() {
    cout << "Tekan Enter untuk lanjut...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void buat_playlist(string username) {
    string input;
    cout << "Masukkan nama playlist : ";
    cin.ignore();
    getline(cin, input);
    semua_playlist[total_playlist].judul_playlist = input;
    semua_playlist[total_playlist].jumlah_lagu = 0;
    semua_playlist[total_playlist].pemilik = username;
    total_playlist++;
    cout << "✅ Playlist berhasil dibuat!" << endl;
    pause();
}

void hapus_lagu(int id_pl) {
    int pilihan_hapus;
    cout << "Pilih nomor lagu yang ingin dihapus : ";
    cin >> pilihan_hapus;
    if (pilihan_hapus >= 1 && pilihan_hapus <= semua_playlist[id_pl].jumlah_lagu) {
        // Geser data
        for (int i = pilihan_hapus - 1; i < semua_playlist[id_pl].jumlah_lagu - 1; i++) {
            semua_playlist[id_pl].isi_lagu[i] = semua_playlist[id_pl].isi_lagu[i + 1];
        }
        semua_playlist[id_pl].jumlah_lagu--;
        cout << "✅ Lagu berhasil dihapus!" << endl;
    } else {
        cout << "❌ Nomor lagu tidak ditemukan!" << endl;
    }
    pause();
}

void tambah_lagu(int id_pl) {
    system("cls");
    cout << "=== List Lagu Tersedia ===" << endl;
    for (int i = 0; i < jumlah_lagu; i++) {
        cout << i + 1 << ". " << daftar_lagu[i].judul << " - " << daftar_lagu[i].penyanyi << endl;
    }
    cout << "Pilih nomor lagu: ";
    int input_nomor;
    cin >> input_nomor;

    if (input_nomor > 0 && input_nomor <= jumlah_lagu) {
        int slot = semua_playlist[id_pl].jumlah_lagu;
        semua_playlist[id_pl].isi_lagu[slot] = input_nomor - 1;
        semua_playlist[id_pl].jumlah_lagu++;
        cout << "✅ Lagu berhasil ditambahkan!" << endl;
    } else {
        cout << "❌ Nomor tidak valid!" << endl;
    }
    pause();
}

void putar_playlist(int id_pl) {
    if (semua_playlist[id_pl].jumlah_lagu == 0) {
        cout << "❌ Playlist kosong!" << endl;
    } else {
        for (int i = 0; i < semua_playlist[id_pl].jumlah_lagu; i++) {
            int idx = semua_playlist[id_pl].isi_lagu[i];
            if (i == 0)
                putar_sekarang(daftar_lagu[idx].judul, daftar_lagu[idx].penyanyi);
            else
                tambah_antrean(daftar_lagu[idx].judul, daftar_lagu[idx].penyanyi);
        }
        cout << "▶️ Playlist sedang diputar!" << endl;
    }
    pause();
}

void kelola_playlist(int pilih_pl) {
    int id_pl = pilih_pl - 1;

    while (true) {
        system("cls");
        cout << "\n🎶 ═══════════ ISI PLAYLIST ═══════════ 🎶" << endl;
        cout << "  📁 Nama Playlist : " << semua_playlist[id_pl].judul_playlist << endl;
        cout << "──────────────────────────────────────────" << endl;

        if (semua_playlist[id_pl].jumlah_lagu == 0) {
            cout << "  📭 Playlist ini masih kosong." << endl;
        } else {
            for (int i = 0; i < semua_playlist[id_pl].jumlah_lagu; i++) {
                int index_lagu_asli = semua_playlist[id_pl].isi_lagu[i];
                cout << "  [" << i + 1 << "] 🎵 " << daftar_lagu[index_lagu_asli].judul
                     << " - " << daftar_lagu[index_lagu_asli].penyanyi << endl;
            }
        }
        cout << "\n🎶 ════════════════════════════════════ 🎶" << endl;
        cout << "  Menu Playlist:" << endl;
        cout << "  [1] ➕ Tambah Lagu" << endl;
        cout << "  [2] 🗑️  Hapus Lagu" << endl;
        cout << "  [3] ▶️  Putar Playlist" << endl;
        cout << "  ────────────────────────────────────────" << endl;
        cout << "  [0] 🔙 Kembali" << endl;
        cout << "==========================================" << endl;
        cout << "👉 Pilih Opsi (0-3): ";

        int sub_menu;
        cin >> sub_menu;

        if (sub_menu == 0) {
            break;
        } else if (sub_menu == 1) {
            tambah_lagu(id_pl);
        } else if (sub_menu == 2) {
            hapus_lagu(id_pl);
        } else if (sub_menu == 3) {
            putar_playlist(id_pl);
        }
    }
}

void playlist(string username) {
    while (true) {
        system("cls");
        cout << "\n💽 ═════════ PLAYLIST KAMU ═════════ 💽" << endl;
        if (total_playlist == 0) {
            cout << "  📭 Belum ada playlist yang dibuat." << endl;
            cout << "     (Yuk, bikin playlist pertama kamu!)" << endl;
        } else {
            for (int i = 0; i < total_playlist; i++) {
                cout << "  [" << i + 1 << "] 📁 " << semua_playlist[i].judul_playlist << endl;
            }
        }
        cout << "💽 ══════════════════════════════════ 💽" << endl;
        cout << "  Aksi:" << endl;
        cout << "  [1] ➕ Buat Playlist Baru" << endl;
        cout << "  [2] 💿 Pilih Playlist" << endl;
        cout << "  ──────────────────────────────────" << endl;
        cout << "  [0] 🔙 Kembali" << endl;
        cout << "======================================" << endl;
        cout << "👉 Pilihan kamu (0-2): ";
        int input_user;
        cin >> input_user;

        if (input_user == 0) {
            return;

        } else if (input_user == 1) {
            buat_playlist(username);
        } else if (input_user == 2) {
            int pilih_pl;
            cout << "Pilih Playlist : ";
            cin >> pilih_pl;

            if (pilih_pl >= 1 && pilih_pl <= total_playlist) {
                kelola_playlist(pilih_pl);
            } else {
                cout << "❌ Playlist tidak ditemukan!" << endl;
                pause();
            }
        } else {
            cout << "❌ Pilihan tidak valid!" << endl;
            pause();
        }
    }
}