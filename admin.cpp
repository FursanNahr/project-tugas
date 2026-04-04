#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
using namespace std;

struct LaguAdmin {
    string judul;
    string penyanyi;
};

LaguAdmin daftar_lagu_admin[100];
int jumlah_lagu_admin = 0;

void tambah() {
    string judul, penyanyi;

    cout << "\n--- TAMBAH LAGU ---" << endl;
    cout << "Judul         : ";
    cin.ignore();
    getline(cin, judul);

    cout << "Penyanyi      : ";
    getline(cin, penyanyi);
    ofstream file("data_lagu.txt", ios::app);
    if (file.is_open()) {
        file << judul << "|" << penyanyi << endl;
        file.close();
    } else {
        cout << "Gagal membuka file!" << endl;
        cout << "Tekan Enter untuk lanjut...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        return;
    }

    cout << "Lagu berhasil ditambahkan!" << endl;
    cout << "Tekan Enter untuk lanjut...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

#include <sstream>

void hapus() {
    int input_user;
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
        cout << "File data_lagu.txt tidak ditemukan!" << endl;
        cout << "Tekan Enter untuk lanjut...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        return;
    }

    cout << "\n--- HAPUS LAGU ---" << endl;
    cout << "Daftar Lagu:" << endl;
    for (int i = 0; i < jumlah_lagu_admin; i++) {
        cout << i + 1 << ". " << daftar_lagu_admin[i].judul << " - " << daftar_lagu_admin[i].penyanyi << endl;
    }
    cout << "Masukkan nomor lagu yang ingin dihapus : ";
    cin.ignore();
    cin >> input_user;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Input harus angka! \n";
        return;
    }

    int ketemu = 0;
    if (input_user >= 1 && input_user <= jumlah_lagu_admin) {
        ketemu = input_user - 1;

        for (int j = ketemu; j < jumlah_lagu_admin - 1; j++) {
            daftar_lagu_admin[j] = daftar_lagu_admin[j + 1];
        }

        jumlah_lagu_admin--;

        ofstream file_out("data_lagu.txt");
        for (int k = 0; k < jumlah_lagu_admin; k++) {
            file_out << daftar_lagu_admin[k].judul << "|" << daftar_lagu_admin[k].penyanyi << endl;
        }
        file_out.close();

        cout << "Lagu berhasil dihapus!" << endl;
    } else {
        cout << "Nomor lagu tidak ditemukan atau tidak valid!" << endl;
    }
    cout << "Tekan Enter untuk lanjut...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

int menu_admin(string username) {
    int pilihan;

    do {
        system("cls");

        cout << "============================" << endl;
        cout << "     SELAMAT DATANG " << username << endl;
        cout << "============================" << endl;
        cout << "0. Logout" << endl;
        cout << "1. Tambah Lagu" << endl;
        cout << "2. Hapus Lagu" << endl;
        cout << "Pilih menu: ";
        cin >> pilihan;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input harus angka! \n";
            continue;
        }

        if (pilihan == 1) {
            tambah();
        } else if (pilihan == 2) {
            hapus();
        } else if (pilihan == 0) {
            cout << "\nSampai jumpa!" << endl;
        } else {
            cout << "Pilihan tidak valid!" << endl;
        }

    } while (pilihan != 0);

    return 0;
}