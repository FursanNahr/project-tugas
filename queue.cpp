#include <cstdlib>
#include <iostream>
#include <limits>

#include "header/admin.h"
using namespace std;

struct QueueNode {
    string judul;
    string penyanyi;
    QueueNode* next;
    QueueNode* prev;
};

QueueNode* head_antrean = NULL;
QueueNode* tail_antrean = NULL;
QueueNode* current_antrean = NULL;

void putar_sekarang(string judul, string penyanyi) {
    if (current_antrean == NULL) {
        QueueNode* baru = new QueueNode();
        baru->judul = judul;
        baru->penyanyi = penyanyi;
        baru->next = NULL;
        baru->prev = NULL;

        head_antrean = tail_antrean = current_antrean = baru;
    } else {
        current_antrean->judul = judul;
        current_antrean->penyanyi = penyanyi;
    }
}

void tambah_antrean(string judul, string penyanyi) {
    QueueNode* baru = new QueueNode();
    baru->judul = judul;
    baru->penyanyi = penyanyi;
    baru->next = NULL;
    baru->prev = NULL;

    if (head_antrean == NULL) {
        head_antrean = tail_antrean = current_antrean = baru;
    } else {
        tail_antrean->next = baru;
        baru->prev = tail_antrean;
        tail_antrean = baru;
    }
}

void sedang_diputar() {
    int pilihan;

    while (true) {
        system("cls");

        cout << "========== Now Playing ==========" << endl;

        if (current_antrean == NULL) {
            cout << "  ❌ Belum ada lagu yang diputar nih." << endl;
            cout << "     (Coba play dari menu Cari/Playlist)" << endl;
        } else {
            cout << "  🎶 Judul    : " << current_antrean->judul << endl;
            cout << "  🎤 Penyanyi : " << current_antrean->penyanyi << endl;
        }

        cout << "🎧 ═══════════════════════════════════ 🎧" << endl;
        cout << "  Kontrol Musik:" << endl;
        cout << "  [1] ⏭️  Next" << endl;
        cout << "  [2] ⏮️  Previous" << endl;
        cout << "  ───────────────────────────────────" << endl;
        cout << "  [0] 🔙 Kembali" << endl;
        cout << "=======================================" << endl;

        cout << "-----Antrean-----" << endl;
        QueueNode* temp = current_antrean;

        while (temp != NULL && temp->prev != NULL) {
            temp = temp->prev;
        }

        while (temp != NULL) {
            if (temp == current_antrean) {
                cout << ">> ";
            } else {
                cout << "   ";
            }

            cout << temp->judul << " - " << temp->penyanyi << endl;
            temp = temp->next;
        }

        cout << "👉 Pilihan kamu (0-2): ";
        pilihan = ambil_input_angka();
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');

            cout << "❌ Input harus angka! Coba lagi.\n";
            continue;
        }

        if (pilihan == 1) {
            if (current_antrean != NULL && current_antrean->next != NULL) {
                current_antrean = current_antrean->next;
            } else {
                cout << "Tidak ada lagu berikutnya." << endl;
            }
        } else if (pilihan == 2) {
            if (current_antrean != NULL && current_antrean->prev != NULL) {
                current_antrean = current_antrean->prev;
            } else {
                cout << "Tidak ada lagu sebelumnya." << endl;
            }
        } else if (pilihan == 0) {
            break;
        } else {
            cout << "Pilihan tidak valid." << endl;
        }
    }
}