#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Node {
    string judul;
    string penyanyi;
    Node* next;
};

Node* head = nullptr;

void simpan() {
    ofstream file("../data_lagu.txt");
    if (!file.is_open()) {
        cout << "Gagal membuka file!" << endl;
        return;
    }

    Node* sekarang = head;
    while (sekarang != nullptr) {
        file << sekarang->judul << "|" << sekarang->penyanyi << "\n";
        sekarang = sekarang->next;
    }

    file.close();
}

void muat() {
    ifstream file("../data_lagu.txt");
    if (!file.is_open()) {
        return;
    }

    string baris;
    while (getline(file, baris)) {
        int pos = baris.find("|");
        string judul = baris.substr(0, pos);
        string penyanyi = baris.substr(pos + 1);

        Node* baru = new Node();
        baru->judul = judul;
        baru->penyanyi = penyanyi;
        baru->next = nullptr;

        if (head == nullptr) {
            head = baru;
        } else {
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = baru;
        }
    }

    file.close();
}

void tampil() {
    if (head == nullptr) {
        cout << "(Belum ada lagu)" << endl;
        return;
    }

    cout << "\nDaftar Lagu:" << endl;
    cout << "--------------------------------------------" << endl;

    Node* temp = head;
    int nomor = 1;

    while (temp != nullptr) {
        cout << nomor << ". " << temp->judul;
        cout << " - " << temp->penyanyi << endl;
        nomor = nomor + 1;
        temp = temp->next;
    }

    cout << "--------------------------------------------" << endl;
}

void tambah() {
    string judul, penyanyi;

    cout << "\n--- TAMBAH LAGU ---" << endl;
    cout << "Judul         : ";
    cin.ignore();
    getline(cin, judul);

    cout << "Penyanyi      : ";
    getline(cin, penyanyi);

    Node* baru = new Node();
    baru->judul = judul;
    baru->penyanyi = penyanyi;
    baru->next = nullptr;

    if (head == nullptr) {
        head = baru;
    } else {
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = baru;
    }

    simpan();
    cout << "Lagu berhasil ditambahkan!" << endl;
}

void hapus() {
    cout << "\n--- HAPUS LAGU ---" << endl;
    tampil();

    if (head == nullptr) {
        return;
    }

    string cari;
    cout << "Masukkan judul lagu yang ingin dihapus: ";
    cin.ignore();
    getline(cin, cari);

    if (head->judul == cari) {
        Node* hapus = head;
        head = head->next;
        delete hapus;
        simpan();
        cout << "Lagu berhasil dihapus!" << endl;
        return;
    }

    Node* temp = head;
    while (temp->next != nullptr) {
        if (temp->next->judul == cari) {
            Node* hapus = temp->next;
            temp->next = hapus->next;
            delete hapus;
            simpan();
            cout << "Lagu berhasil dihapus!" << endl;
            return;
        }
        temp = temp->next;
    }

    cout << "Lagu tidak ditemukan." << endl;
}

int main() {
    muat();

    cout << "============================" << endl;
    cout << "     SELAMAT DATANG ADMIN   " << endl;
    cout << "============================" << endl;

    int pilihan;

    do {
        cout << "\n=== MENU ADMIN ===" << endl;
        cout << "1. Tambah Lagu" << endl;
        cout << "2. Hapus Lagu" << endl;
        cout << "3. Keluar" << endl;
        cout << "Pilih menu (1-3): ";
        cin >> pilihan;

        if (pilihan == 1) {
            tambah();
        } else if (pilihan == 2) {
            hapus();
        } else if (pilihan == 3) {
            cout << "\nSampai jumpa!" << endl;
            tampil();
        } else {
            cout << "Pilihan tidak valid!" << endl;
        }

    } while (pilihan != 3);

    return 0;
}