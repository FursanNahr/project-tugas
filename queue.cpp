#include <cstdlib>
#include <iostream>
#include <limits>

#include "header/admin.h"
#include "header/history.h"
#include "header/rekomendasi.h"
using namespace std;

const int ukuran_queue = 10;

struct Lagu {
    string judul;
    string penyanyi;
};

struct AntrianLagu {
    int top;
    int current_index;
    Lagu isi[ukuran_queue];
} antrian_lagu;

int isEmpty() {
    if (antrian_lagu.top == 0) return 1;
    else return 0;
}

int isFull() {
    if (antrian_lagu.top >= ukuran_queue) return 1;
    else return 0;
}

void putar_sekarang(string judul, string penyanyi, string mood, string genre) {
    if (isEmpty() == 1) {
        antrian_lagu.isi[antrian_lagu.top].judul = judul;
        antrian_lagu.isi[antrian_lagu.top].penyanyi = penyanyi;
        antrian_lagu.top++;
        antrian_lagu.current_index = 0;
    } else {
        antrian_lagu.isi[antrian_lagu.current_index].judul = judul;
        antrian_lagu.isi[antrian_lagu.current_index].penyanyi = penyanyi;
    }

    push_stack(judul, penyanyi);

    catat_preferensi(mood, genre);
}

void tambah_antrean(string judul, string penyanyi, string mood, string genre) {
    if (isFull() == 1) {
        cout << "Maaf, antrian lagu penuh!" << endl;
        return;
    }

    antrian_lagu.isi[antrian_lagu.top].judul = judul;
    antrian_lagu.isi[antrian_lagu.top].penyanyi = penyanyi;
    antrian_lagu.top++;

    if (antrian_lagu.current_index == -1) {
        antrian_lagu.current_index = 0;
    }

    catat_preferensi(mood, genre);
}

void next_lagu() {
    if (isEmpty() == 1 || antrian_lagu.current_index == -1) {
        cout << "  Antrian kosong." << endl;
        return;
    }

    if (antrian_lagu.current_index >= antrian_lagu.top - 1) {
        cout << "  Tidak ada lagu berikutnya." << endl;
    } else {
        antrian_lagu.current_index++;
        int idx = antrian_lagu.current_index;
        push_stack(antrian_lagu.isi[idx].judul, antrian_lagu.isi[idx].penyanyi);
    }
}

void prev_lagu() {
    if (isEmpty() == 1 || antrian_lagu.current_index == -1) {
        cout << "  Antrian kosong." << endl;
        return;
    }

    if (antrian_lagu.current_index <= 0) {
        cout << "  Tidak ada lagu sebelumnya." << endl;
    } else {
        antrian_lagu.current_index--;
        int idx = antrian_lagu.current_index;
        push_stack(antrian_lagu.isi[idx].judul, antrian_lagu.isi[idx].penyanyi);
    }
}

void sedang_diputar() {
   while (true) {
    system("cls");

    cout << "========== Now Playing ==========" << endl;

    if (isEmpty() == 1 || antrian_lagu.current_index == -1) {
        cout << "  ❌ Belum ada lagu yang diputar nih." << endl;
        cout << "     (Coba play dari menu Cari/Playlist)" << endl;
    } 
    else {
        int idx = antrian_lagu.current_index;
        cout << "  🎶 Judul    : " << antrian_lagu.isi[idx].judul << endl;
        cout << "  🎤 Penyanyi : " << antrian_lagu.isi[idx].penyanyi << endl;
    }

    cout << "\n========== Queue Lagu ==========" << endl;

    if (isEmpty() == 1) {
        cout << "   (antrian kosong)" << endl;
    } else {
        for (int i = 0; i < antrian_lagu.top; i++) {
            if (i == antrian_lagu.current_index) {
                cout << ">> ";
            } else {
                cout << "   ";
            }
            cout << antrian_lagu.isi[i].judul << " - " << antrian_lagu.isi[i].penyanyi << endl;
        }
    }

    cout << "🎧 ═══════════════════════════════════ 🎧" << endl;
    cout << "  Kontrol Musik:" << endl;
    cout << "  [1] ⏭️  Next" << endl;
    cout << "  [2] ⏮️  Previous" << endl;
    cout << "  ───────────────────────────────────" << endl;
    cout << "  [0] 🔙 Kembali" << endl;
    cout << "=======================================" << endl;
    cout << "Pilihan: ";

    int pilihan = ambil_input_angka();

        if (pilihan == 0) {
            break;
        } else if (pilihan == 1) {
            next_lagu();
        } else if (pilihan == 2) {
            prev_lagu();
        }

   }
}
// #include <cstdlib>
// #include <iostream>
// #include <limits>

// #include "header/admin.h"
// using namespace std;

// struct QueueNode {
//     string judul;
//     string penyanyi;
//     QueueNode* next;
//     QueueNode* prev;
// };

// QueueNode* head_antrean = NULL;
// QueueNode* tail_antrean = NULL;
// QueueNode* current_antrean = NULL;

// void putar_sekarang(string judul, string penyanyi) {
//     if (current_antrean == NULL) {
//         QueueNode* baru = new QueueNode();
//         baru->judul = judul;
//         baru->penyanyi = penyanyi;
//         baru->next = NULL;
//         baru->prev = NULL;

//         head_antrean = tail_antrean = current_antrean = baru;
//     } else {
//         current_antrean->judul = judul;
//         current_antrean->penyanyi = penyanyi;
//     }
// }

// void tambah_antrean(string judul, string penyanyi) {
//     QueueNode* baru = new QueueNode();
//     baru->judul = judul;
//     baru->penyanyi = penyanyi;
//     baru->next = NULL;
//     baru->prev = NULL;

//     if (head_antrean == NULL) {
//         head_antrean = tail_antrean = current_antrean = baru;
//     } else {
//         tail_antrean->next = baru;
//         baru->prev = tail_antrean;
//         tail_antrean = baru;
//     }
// }

// void sedang_diputar() {
//     int pilihan;

//     while (true) {
//         system("cls");

//         cout << "========== Now Playing ==========" << endl;

//         if (current_antrean == NULL) {
//             cout << "  ❌ Belum ada lagu yang diputar nih." << endl;
//             cout << "     (Coba play dari menu Cari/Playlist)" << endl;
//         } else {
//             cout << "  🎶 Judul    : " << current_antrean->judul << endl;
//             cout << "  🎤 Penyanyi : " << current_antrean->penyanyi << endl;
//         }

//         cout << "🎧 ═══════════════════════════════════ 🎧" << endl;
//         cout << "  Kontrol Musik:" << endl;
//         cout << "  [1] ⏭️  Next" << endl;
//         cout << "  [2] ⏮️  Previous" << endl;
//         cout << "  ───────────────────────────────────" << endl;
//         cout << "  [0] 🔙 Kembali" << endl;
//         cout << "=======================================" << endl;

//         cout << "-----Antrean-----" << endl;
//         QueueNode* temp = current_antrean;

//         while (temp != NULL && temp->prev != NULL) {
//             temp = temp->prev;
//         }

//         while (temp != NULL) {
//             if (temp == current_antrean) {
//                 cout << ">> ";
//             } else {
//                 cout << "   ";
//             }

//             cout << temp->judul << " - " << temp->penyanyi << endl;
//             temp = temp->next;
//         }

//         cout << "👉 Pilihan kamu (0-2): ";
//         pilihan = ambil_input_angka();
//         if (cin.fail()) {
//             cin.clear();
//             cin.ignore(1000, '\n');

//             cout << "❌ Input harus angka! Coba lagi.\n";
//             continue;
//         }

//         if (pilihan == 1) {
//             if (current_antrean != NULL && current_antrean->next != NULL) {
//                 current_antrean = current_antrean->next;
//             } else {
//                 cout << "Tidak ada lagu berikutnya." << endl;
//             }
//         } else if (pilihan == 2) {
//             if (current_antrean != NULL && current_antrean->prev != NULL) {
//                 current_antrean = current_antrean->prev;
//             } else {
//                 cout << "Tidak ada lagu sebelumnya." << endl;
//             }
//         } else if (pilihan == 0) {
//             break;
//         } else {
//             cout << "Pilihan tidak valid." << endl;
//         }
//     }
// }