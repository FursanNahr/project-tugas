#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

#include "header/lagu.h"
#include "header/playlist.h"
#include "header/user.h"
using namespace std;

struct LaguAdmin {
    string judul;
    string penyanyi;
};

LaguAdmin daftar_lagu_admin[100];
int jumlah_lagu_admin = 0;

int ambil_input_angka() {
    int angka;
    while (true) {
        cin >> angka;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "❌ Error: Input harus valid! : ";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return angka;
        }
    }
}

void tambah() {
    string judul, penyanyi;
    system("cls");  // Bersihin layar biar fokus nambah lagu
    cout << "\n➕ ═════════ TAMBAH LAGU ═════════ ➕" << endl;
    cout << "   (Pastikan data diisi dengan benar)" << endl;
    cout << "───────────────────────────────────────" << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    while (true) {
        cout << "  🎵 Judul Lagu : ";
        getline(cin, judul);

        if (judul.empty() || judul.find_first_not_of(' ') == string::npos) {
            cout << "  ❌ Error: Judul lagu tidak boleh kosong!\n";
        } else {
            break;
        }
    }

    while (true) {
        cout << "  🎤 Penyanyi   : ";
        getline(cin, penyanyi);

        if (penyanyi.empty() || penyanyi.find_first_not_of(' ') == string::npos) {
            cout << "  ❌ Error: Nama penyanyi tidak boleh kosong!\n";
        } else {
            break;
        }
    }
    cout << "=======================================" << endl;

    ofstream file("data_lagu.txt", ios::app);
    if (file.is_open()) {
        file << judul << "|" << penyanyi << endl;
        file.close();
        cout << "✅ BERHASIL: Lagu '" << judul << " - " << penyanyi << "' ditambahkan ke database!" << endl;
    } else {
        cout << "❌ CRITICAL ERROR: Gagal membuka file 'data_lagu.txt'!" << endl;
    }
    load_lagu();

    pause();
}

#include <sstream>

void hapus() {
    system("cls");
    cout << "\n🗑️  ══════════ HAPUS LAGU ══════════ 🗑️" << endl;

    ifstream file_in("data_lagu.txt");
    string line;
    jumlah_lagu_admin = 0;

    if (file_in.is_open()) {
        while (getline(file_in, line)) {
            stringstream ss(line);
            string judul, penyanyi;
            getline(ss, judul, '|');
            getline(ss, penyanyi);

            daftar_lagu_admin[jumlah_lagu_admin].judul = judul;
            daftar_lagu_admin[jumlah_lagu_admin].penyanyi = penyanyi;
            jumlah_lagu_admin++;
        }
        file_in.close();
    } else {
        cout << "  ❌ ERROR: File data_lagu.txt tidak ditemukan!" << endl;
        pause();
        return;
    }

    if (jumlah_lagu_admin == 0) {
        cout << "  📭 Belum ada lagu di dalam sistem." << endl;
        cout << "========================================" << endl;
        pause();
        return;
    }

    for (int i = 0; i < jumlah_lagu_admin; i++) {
        cout << "  [" << i + 1 << "] 🎶 " << daftar_lagu_admin[i].judul << " - " << daftar_lagu_admin[i].penyanyi << endl;
    }

    cout << "  ──────────────────────────────────────" << endl;
    cout << "  [0] 🔙 Batal / Kembali" << endl;
    cout << "========================================" << endl;
    cout << "👉 Masukkan nomor lagu yang ingin dihapus : ";

    int input_user = ambil_input_angka();

    if (input_user == 0) {
        return;

    } else if (input_user >= 1 && input_user <= jumlah_lagu_admin) {
        int index_hapus = input_user - 1;

        string lagu_dihapus = daftar_lagu_admin[index_hapus].judul;

        for (int j = index_hapus; j < jumlah_lagu_admin - 1; j++) {
            daftar_lagu_admin[j] = daftar_lagu_admin[j + 1];
        }

        jumlah_lagu_admin--;

        ofstream file_out("data_lagu.txt");
        for (int k = 0; k < jumlah_lagu_admin; k++) {
            file_out << daftar_lagu_admin[k].judul << "|" << daftar_lagu_admin[k].penyanyi << endl;
        }
        file_out.close();

        cout << "✅ BERHASIL: Lagu '" << lagu_dihapus << "' telah dihapus dari database!" << endl;
        load_lagu();
        pause();

    } else {
        cout << "❌ ERROR: Nomor lagu tidak ditemukan atau tidak valid!" << endl;
        pause();
    }
}

int menu_admin(string username) {
    int pilihan;
    do {
        system("cls");

        cout << "\n👑 ══════════ MENU ADMIN ══════════ 👑" << endl;
        cout << "     SELAMAT DATANG, " << username << endl;
        cout << "──────────────────────────────────────" << endl;
        cout << "  [1] ➕ Tambah Lagu" << endl;
        cout << "  [2] 🗑️  Hapus Lagu" << endl;
        cout << "  ────────────────────────────────────" << endl;
        cout << "  [0] 🚪 Logout" << endl;
        cout << "======================================" << endl;
        cout << "👉 Pilih menu (0-2): ";
        pilihan = ambil_input_angka();

        if (pilihan == 1) {
            tambah();
        } else if (pilihan == 2) {
            hapus();
        } else if (pilihan == 0) {
            cout << "\n👋 Sampai jumpa, Admin " << username << "! Selamat istirahat." << endl;
            pause();
        } else {
            cout << "❌ Pilihan tidak valid! Silakan pilih 0, 1, atau 2." << endl;
            pause();
        }

    } while (pilihan != 0);

    return 0;
}