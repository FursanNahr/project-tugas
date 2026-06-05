#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
using namespace std;
#include "header/admin.h"
#include "header/lagu.h"
#include "header/queue.h"

struct Playlist {
    string judul_playlist;
    string pemilik;
    string isi_lagu[1000];
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
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    while (true) {
        cout << "Masukkan nama playlist : ";
        getline(cin, input);
        if (input.empty() || input.find_first_not_of(' ') == string::npos) {
            cout << "❌ Nama playlist tidak boleh kosong atau hanya spasi! Coba lagi." << endl;
        } else if (input.length() > 25) {
            cout << "❌ Nama Playlist terlalu panjang maksimal 30 karakter" << endl;
        } else {
            bool terpakai = false;

            for (int i = 0; i < total_playlist; i++) {
                if (input == semua_playlist[i].judul_playlist) {
                    terpakai = true;
                    break;
                }
            }
            if (terpakai == true) {
                cout << "❌ Playlist dengan nama '" << input << "' sudah ada sebelumnya!." << endl;
            } else {
                break;
            }
        }
    }

    semua_playlist[total_playlist].judul_playlist = input;
    semua_playlist[total_playlist].jumlah_lagu = 0;
    semua_playlist[total_playlist].pemilik = username;
    total_playlist++;
    cout << "✅ Playlist berhasil dibuat!" << endl;
    pause();
}

void hapus_lagu(int id_pl) {
    cout << "Pilih nomor lagu yang ingin dihapus : ";
    int pilihan_hapus = ambil_input_angka();

    if (pilihan_hapus >= 1 && pilihan_hapus <= semua_playlist[id_pl].jumlah_lagu) {
        for (int i = pilihan_hapus - 1; i < semua_playlist[id_pl].jumlah_lagu - 1; i++) {
            semua_playlist[id_pl].isi_lagu[i] = semua_playlist[id_pl].isi_lagu[i + 1];
        }
        semua_playlist[id_pl].jumlah_lagu--;
        cout << "✅ Lagu berhasil dihapus dari playlist!" << endl;
    } else {
        cout << "❌ Nomor lagu tidak ditemukan!" << endl;
    }
    pause();
}

void hapus_playlist() {
    while (true) {
        system("cls");
        cout << "\n🗑️  ════════ HAPUS PLAYLIST ════════ 🗑️" << endl;
        if (total_playlist == 0) {
            cout << "  📭 Belum ada playlist yang dibuat." << endl;
            cout << "========================================" << endl;
            pause();
            return;
        }
        for (int i = 0; i < total_playlist; i++) {
            cout << "  [" << i + 1 << "] 📁 " << semua_playlist[i].judul_playlist << endl;
        }

        cout << "  ──────────────────────────────────────" << endl;
        cout << "  [0] 🔙 Batal / Kembali" << endl;
        cout << "========================================" << endl;
        cout << "👉 Pilih nomor playlist yang mau dihapus: ";

        int pilihan_hapus = ambil_input_angka();
        if (pilihan_hapus == 0) {
            return;
        } else if (pilihan_hapus >= 1 && pilihan_hapus <= total_playlist) {
            for (int i = pilihan_hapus - 1; i < total_playlist - 1; i++) {
                semua_playlist[i] = semua_playlist[i + 1];
            }
            total_playlist--;
            cout << "✅ Playlist berhasil dihapus permanen!" << endl;
            pause();
        } else {
            cout << "❌ Pilihan tidak valid!" << endl;
            pause();
        }
    }
}

void tambah_lagu(int id_pl) {
    system("cls");
    cout << "\n🎵 ════════ LIST LAGU TERSEDIA ════════ 🎵" << endl;
    for (int i = 0; i < jumlah_lagu; i++) {
        cout << "  [" << i + 1 << "] 🎶 " << daftar_lagu[i].judul << " - " << daftar_lagu[i].penyanyi << endl;
    }
    cout << "  ──────────────────────────────────────" << endl;
    cout << "  [0] 🔙 Batal / Kembali" << endl;
    cout << "========================================" << endl;
    cout << "👉 Pilih nomor lagu: ";
    int input_nomor = ambil_input_angka();

    if (input_nomor > 0 && input_nomor <= jumlah_lagu) {
        int slot = semua_playlist[id_pl].jumlah_lagu;

        semua_playlist[id_pl].isi_lagu[slot] = daftar_lagu[input_nomor - 1].judul;
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
        bool lagu_pertama = true;

        for (int i = 0; i < semua_playlist[id_pl].jumlah_lagu; i++) {
            string judul_cari = semua_playlist[id_pl].isi_lagu[i];
            int idx_ketemu = -1;

            for (int j = 0; j < jumlah_lagu; j++) {
                if (daftar_lagu[j].judul == judul_cari) {
                    idx_ketemu = j;
                    break;
                }
            }

            if (idx_ketemu != -1) {
                if (lagu_pertama) {
                    putar_sekarang(daftar_lagu[idx_ketemu].judul, daftar_lagu[idx_ketemu].penyanyi, daftar_lagu[idx_ketemu].mood, daftar_lagu[idx_ketemu].genre);
                    lagu_pertama = false;
                } else {
                    tambah_antrean(daftar_lagu[idx_ketemu].judul, daftar_lagu[idx_ketemu].penyanyi, daftar_lagu[idx_ketemu].mood, daftar_lagu[idx_ketemu].genre);
                }
            }
        }

        if (lagu_pertama) {
            cout << "❌ Gagal memutar: Semua lagu di playlist ini telah dihapus oleh Admin!" << endl;
        } else {
            cout << "▶️ Playlist sedang diputar!" << endl;
        }
    }
    pause();
}

void kelola_playlist(int pilih_pl) {
    int id_pl = pilih_pl - 1;

    while (true) {
        system("cls");

        int jml = semua_playlist[id_pl].jumlah_lagu;
        int m1 = jml + 1, m2 = jml + 2, m3 = jml + 3;

        cout << "\n🎶 ═══════════ ISI PLAYLIST ═══════════ 🎶" << endl;
        cout << "  📁 Nama Playlist : " << semua_playlist[id_pl].judul_playlist << endl;
        cout << "──────────────────────────────────────────" << endl;
        if (jml == 0) {
            cout << "  📭 Playlist ini masih kosong." << endl;
        } else {
            for (int i = 0; i < jml; i++) {
                string judul_cari = semua_playlist[id_pl].isi_lagu[i];
                bool ketemu = false;

                for (int j = 0; j < jumlah_lagu; j++) {
                    if (daftar_lagu[j].judul == judul_cari) {
                        cout << "  [" << i + 1 << "] 🎵 "
                             << daftar_lagu[j].judul << " - "
                             << daftar_lagu[j].penyanyi << endl;
                        ketemu = true;
                        break;
                    }
                }

                if (!ketemu) {
                    cout << "  [" << i + 1 << "] ❌ " << judul_cari << " [Lagu Tidak Tersedia / Dihapus Admin]" << endl;
                }
            }
        }
        cout << "\n🎶 ════════════════════════════════════ 🎶" << endl;
        cout << "  Menu Playlist:" << endl;
        cout << "  [" << m1 << "] ➕  Tambah Lagu" << endl;
        cout << "  [" << m2 << "] 🗑️  Hapus Lagu" << endl;
        cout << "  [" << m3 << "] ▶️  Putar Playlist" << endl;
        cout << "  ────────────────────────────────────────" << endl;
        cout << "  [0] 🔙 Kembali" << endl;
        cout << "==========================================" << endl;
        cout << "👉 Pilih Opsi (0-" << m3 << "): ";

        int sub_menu = ambil_input_angka();

        if (sub_menu == 0) {
            break;
        } else if (sub_menu >= 1 && sub_menu <= jml) {
            cout << "ℹ️  Kamu memilih lagu ke-" << sub_menu << endl;
            pause();
        } else if (sub_menu == m1) {
            tambah_lagu(id_pl);
        } else if (sub_menu == m2) {
            hapus_lagu(id_pl);
        } else if (sub_menu == m3) {
            putar_playlist(id_pl);
        } else {
            cout << "❌ Pilihan tidak valid!" << endl;
            pause();
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

        // 🌟 PERBAIKAN: Hanya pakai m1 dan m2 (m3 dihapus)
        int m1 = total_playlist + 1;
        int m2 = total_playlist + 2;

        cout << "💽 ══════════════════════════════════ 💽" << endl;
        cout << "  Opsi Lainnya:" << endl;
        cout << "  [" << m1 << "] ➕ Buat Playlist Baru" << endl;
        cout << "  [" << m2 << "] 🗑️  Hapus Playlist" << endl;
        cout << "  ──────────────────────────────────" << endl;
        cout << "  [0] 🔙 Kembali" << endl;
        cout << "======================================" << endl;
        cout << "👉 Pilih nomor playlist ATAU opsi (0-" << m2 << "): ";
        int input_user = ambil_input_angka();

        if (input_user == 0) {
            return;
        }
        // JIKA USER NGETIK NOMOR PLAYLIST, LANGSUNG BUKA!
        else if (input_user >= 1 && input_user <= total_playlist) {
            kelola_playlist(input_user);
        }
        // JIKA USER NGETIK NOMOR BUAT PLAYLIST
        else if (input_user == m1) {
            buat_playlist(username);
        }
        // JIKA USER NGETIK NOMOR HAPUS PLAYLIST
        else if (input_user == m2) {
            hapus_playlist();
        } else {
            cout << "❌ Pilihan tidak valid!" << endl;
            pause();
        }
    }
}