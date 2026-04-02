#include <iostream>
using namespace std;

struct QueueNode {
    string judul;
    string penyanyi;
    QueueNode* next;
    QueueNode* prev;
};

QueueNode* head = NULL;
QueueNode* tail = NULL;
QueueNode* current = NULL;

void putar_sekarang(string judul, string penyanyi) {
    if (current == NULL) {
        QueueNode* baru = new QueueNode();
        baru->judul = judul;
        baru->penyanyi = penyanyi;
        baru->next = NULL;
        baru->prev = NULL;
    
        head = tail = current = baru;
    } else {
        current->judul = judul;
        current->penyanyi = penyanyi;
    }

    cout << "Memutar sekarang: " << judul << endl;
}

void tambah_antrean(string judul, string penyanyi) {
    QueueNode* baru = new QueueNode();
    baru->judul = judul;
    baru->penyanyi = penyanyi;
    baru->next = NULL;
    baru->prev = NULL;

    if (head == NULL) {
        head = tail = current = baru;
    } else {
            tail->next = baru;
            baru->prev = tail;
            tail = baru;
    }

    cout << "Ditambahkan ke antrean: " << judul << endl;
}
void sedang_diputar() {
    int pilihan;

    while (true) {
        cout << "----------Now Playing----------" << endl;

        if (current == NULL) {
            cout << "Tidak ada lagu yang diputar.";
        } else {
            cout << "Judul: " << current->judul << endl;
            cout << "Penyanyi: " << current->penyanyi << endl;
        }

        cout << "Menu: " << endl;
        cout << "1. Next" << endl;
        cout << "2. Previous" << endl;
        cout << "0. Kembali" << endl;

        cout << "-----Antrean-----" << endl;
        QueueNode* temp = current;

        while (temp != NULL) {
            cout << temp->judul << " - " << temp->penyanyi << endl;
            temp = temp->next;
        }

        cout << "Pilih: "; cin >> pilihan;

        if (pilihan == 1) {
            if (current != NULL && current->next != NULL) {
                current = current->next;
            } else {
                cout << "Tidak ada lagu berikutnya." << endl;
            }
        } else if (pilihan == 2) {
            if (current != NULL && current->prev != NULL) {
                current = current->prev;
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