#include <iostream>
using namespace std;
#include "header/lagu.h"
struct Playlist {
    string judul_playlist;
    string pemilik;
    int isi_lagu[1000];
    int jumlah_lagu;
};

Playlist semua_playlist[100];
int total_playlist = 0;

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
            string input;
            cout << "Masukkan nama playlist : ";
            cin.ignore();
            getline(cin, input);
            semua_playlist[total_playlist].judul_playlist = input;
            semua_playlist[total_playlist].jumlah_lagu = 0;
            semua_playlist[total_playlist].pemilik = username;
            total_playlist++;

            cout << "Playlist berhasil dibuat!" << endl;
        } else if (input_user == 2) {
            cout << "Pilih Playlist : ";
            cin >> input_user;

            if (input_user >= 1 && input_user <= total_playlist) {
                cout << "\n🎶 ═══════════ ISI PLAYLIST ═══════════ 🎶" << endl;
                cout << "  📁 Nama Playlist : " << semua_playlist[input_user - 1].judul_playlist << endl;
                cout << "──────────────────────────────────────────" << endl;
                if (semua_playlist[input_user - 1].jumlah_lagu == 0) {
                    cout << "  📭 Playlist ini masih kosong." << endl;
                    cout << "     (Gas tambahin lagu favorit lu di opsi 1!)" << endl;
                } else {
                    for (int i = 0; i < semua_playlist[input_user - 1].jumlah_lagu; i++) {
                        int index_lagu_asli = semua_playlist[input_user - 1].isi_lagu[i];
                        cout << i + 1 << ". " << daftar_lagu[index_lagu_asli].judul << " - " << daftar_lagu[index_lagu_asli].penyanyi << endl;
                    }
                }

                cout << endl;

                cout << "🎶 ════════════════════════════════════ 🎶" << endl;
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
                    return;
                } else if (sub_menu == 1) {
                    cout << "List Lagu-Lagu : " << endl;
                    for (int i = 0; i < jumlah_lagu; i++) {
                        cout << i + 1 << ". " << daftar_lagu[i].judul << " - " << daftar_lagu[i].penyanyi << endl;
                    }
                    cout << "Pilih nomor lagu yang ingin ditambahkan : ";
                    int input_nomor;
                    cin >> input_nomor;

                    int slot_kosong = semua_playlist[input_user - 1].jumlah_lagu;

                    if (input_nomor > 0 && input_nomor <= jumlah_lagu) {
                        semua_playlist[input_user - 1].isi_lagu[slot_kosong] = input_nomor - 1;
                        semua_playlist[input_user - 1].jumlah_lagu++;
                        cout << "Lagu berhasil ditambahkan ke playlist!" << endl;
                    } else {
                        cout << "Input tidak valid!" << endl;
                    }

                } else if (sub_menu == 2) {
                    int pilihan_hapus;
                    cout << "Pilih nomor lagu yang ingin dihapus : ";
                    cin >> pilihan_hapus;
                    if (pilihan_hapus >= 1 && pilihan_hapus <= semua_playlist[input_user - 1].jumlah_lagu) {
                        for (int i = pilihan_hapus - 1; i < semua_playlist[input_user - 1].jumlah_lagu; i++) {
                            semua_playlist[input_user - 1].isi_lagu[i] = semua_playlist[input_user - 1].isi_lagu[i + 1];
                            semua_playlist[input_user].jumlah_lagu--;
                            cout << "✅ Lagu berhasil dihapus dari playlist!" << endl;
                        }
                    } else {
                        cout << "❌ Nomor lagu tidak ditemukan!" << endl;
                    }

                } else if (sub_menu == 3) {
                } else {
                    cout << "Opsi tidak valid!" << endl;
                }
            }  // opsi pilih playlist
        }
    }
}