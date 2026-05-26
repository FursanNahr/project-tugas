#include <iostream>
#include "header/history.h"
using namespace std;

const int ukuran_stack = 10;

struct ItemRiwayat {
    string judul, penyanyi;
};

struct StackRiwayat {
    int top;
    ItemRiwayat isi[ukuran_stack];
} riwayat;

void push_stack(string judul, string penyanyi) {
    if (riwayat.top >= ukuran_stack) {
        for (int i = 0; i < ukuran_stack - 1; i++) {
            riwayat.isi[i] = riwayat.isi[i + 1];
        }
        riwayat.top = ukuran_stack - 1;
    }

    riwayat.isi[riwayat.top].judul = judul;
    riwayat.isi[riwayat.top].penyanyi = penyanyi;
    riwayat.top++;
}

void tampilkan_riwayat() {
    system("cls");

    cout << "\n🕘 ══════ RIWAYAT PEMUTARAN ══════ 🕘" << endl;

    if (riwayat.top == 0) {
        cout << " Belum ada lagu yang pernah diputar." << endl;
    } else {
        int k = 1;
        for (int i = riwayat.top - 1; i >= 0; i--) {
            cout << "   " << k << ".    "
                 << riwayat.isi[i].judul
                 << " - " << riwayat.isi[i].penyanyi << endl;
            k++;
        }
    }

    cout << "  ═════════════════════════════════" << endl;
}