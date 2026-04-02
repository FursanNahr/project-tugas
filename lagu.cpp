#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

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
    cout << "---------- DAFTAR LAGU ----------" << endl;

    if (jumlah_lagu == 0) {
        cout << "belum ada lagu." << endl;
        return;
    }

    for (int i = 0; i < jumlah_lagu; i++) {
        cout << i + 1 << ". " << daftar_lagu[i].judul << " - " << daftar_lagu[i].penyanyi << endl;
        
    }
}