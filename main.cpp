#include <iostream>
#include <string>
using namespace std;

struct Node {
    string judul;
    string penyanyi;
    string genre;
    int    durasi;
    string lirik;

    Node* next;
};

Node* head = nullptr;

Node* buat_node_baru(string judul, string penyanyi, string genre,
                     int durasi, string lirik) {
    Node* node_baru     = new Node();
    node_baru->judul    = judul;
    node_baru->penyanyi = penyanyi;
    node_baru->genre    = genre;
    node_baru->durasi   = durasi;
    node_baru->lirik    = lirik;
    node_baru->next     = nullptr;
    return node_baru;
}

void sambung_ke_akhir(Node* node_baru) {
    if (head == nullptr) {
        head = node_baru;
    } else {
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = node_baru;
    }
}

void tambah_lagu() {
    string judul, penyanyi, genre, lirik, baris;
    int durasi;

    cout << "\n--- TAMBAH LAGU ---\n";
    cout << "Masukkan judul    : "; cin.ignore(); getline(cin, judul);
    cout << "Masukkan penyanyi : "; getline(cin, penyanyi);
    cout << "Masukkan genre    : "; getline(cin, genre);
    cout << "Masukkan durasi (detik): "; cin >> durasi;

    cin.ignore();
    cout << "Masukkan lirik (ketik SELESAI di baris baru untuk selesai):\n";
    lirik = "";
    while (true) {
        getline(cin, baris);
        if (baris == "SELESAI") break;
        if (!lirik.empty()) lirik += "\n";
        lirik += baris;
    }

    Node* node_baru = buat_node_baru(judul, penyanyi, genre, durasi, lirik);
    sambung_ke_akhir(node_baru);

    cout << "Lagu \"" << judul << "\" berhasil ditambahkan!\n";
}

void tampilkan_daftar_lagu() {
    if (head == nullptr) {
        cout << "(Belum ada lagu)\n";
        return;
    }

    Node* temp = head;
    int nomor  = 1;
    cout << "\nDaftar Lagu:\n";
    cout << "--------------------------------------------\n";
    while (temp != nullptr) {
        cout << nomor << ". " << temp->judul
             << " - "  << temp->penyanyi
             << " ["   << temp->genre << "]"
             << " ("   << temp->durasi << " detik)\n";
        temp = temp->next;
        nomor++;
    }
    cout << "--------------------------------------------\n";
}

void hapus_lagu() {
    cout << "\n--- HAPUS LAGU ---\n";
    tampilkan_daftar_lagu();

    if (head == nullptr) return;

    string cari_judul;
    cout << "Masukkan judul lagu yang ingin dihapus: ";
    cin.ignore();
    getline(cin, cari_judul);

    if (head->judul == cari_judul) {
        Node* hapus = head;
        head        = head->next;
        delete hapus;
        cout << "Lagu \"" << cari_judul << "\" berhasil dihapus!\n";
        return;
    }

    Node* temp = head;
    while (temp->next != nullptr) {
        if (temp->next->judul == cari_judul) {
            Node* hapus = temp->next;
            temp->next  = hapus->next;
            delete hapus;
            cout << "Lagu \"" << cari_judul << "\" berhasil dihapus!\n";
            return;
        }
        temp = temp->next;
    }

    cout << "Lagu \"" << cari_judul << "\" tidak ditemukan.\n";
}

void keluar() {
    cout << "\n--- KELUAR ---\n";
    tampilkan_daftar_lagu();
    cout << "Sampai jumpa!\n";
}

void menu_admin() {
    int pilihan;

    cout << "\n============================\n";
    cout << "     SELAMAT DATANG ADMIN   \n";
    cout << "============================\n";

    do {
        cout << "\n=== MENU ADMIN ===\n";
        cout << "1. Tambah Lagu\n";
        cout << "2. Hapus Lagu\n";
        cout << "3. Keluar\n";
        cout << "Pilih menu (1-3): ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: tambah_lagu(); break;
            case 2: hapus_lagu();  break;
            case 3: keluar();      break;
            default:
                cout << "Pilihan tidak valid! Masukkan angka 1-3.\n";
        }

    } while (pilihan != 3);
}

int main() {
    menu_admin();
    return 0;
}