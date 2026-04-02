#include <iostream>
#include <string>
using namespace std;

// ============================================================
// RECORD (struct) = tempat nyimpan data 1 lagu
// POINTER        = next adalah pointer ke node berikutnya
// Ini adalah dasar dari SINGLE LINKED LIST
// ============================================================
struct Node {
    string judul;
    string penyanyi;
    string genre;
    int    durasi;  // dalam detik
    string lirik;

    Node* next; // pointer ke node berikutnya
};

// Head = pointer ke node pertama
// nullptr artinya linked list masih kosong
Node* head = nullptr;

// ============================================================
// Fungsi bantu: bikin node baru
// ============================================================
Node* buatNodeBaru(string judul, string penyanyi, string genre,
                   int durasi, string lirik) {
    Node* nodeBaru     = new Node();
    nodeBaru->judul    = judul;
    nodeBaru->penyanyi = penyanyi;
    nodeBaru->genre    = genre;
    nodeBaru->durasi   = durasi;
    nodeBaru->lirik    = lirik;
    nodeBaru->next     = nullptr;
    return nodeBaru;
}

// ============================================================
// Fungsi bantu: sambungkan node baru ke akhir linked list
// ============================================================
void sambungKeAkhir(Node* nodeBaru) {
    if (head == nullptr) {
        head = nodeBaru;
    } else {
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = nodeBaru;
    }
}

// ============================================================
// FITUR 1: Tambah Lagu (termasuk lirik)
// ============================================================
void tambahLagu() {
    string judul, penyanyi, genre, lirik, baris;
    int durasi;

    cout << "\n--- TAMBAH LAGU ---\n";
    cout << "Masukkan judul    : "; cin.ignore(); getline(cin, judul);
    cout << "Masukkan penyanyi : "; getline(cin, penyanyi);
    cout << "Masukkan genre    : "; getline(cin, genre);
    cout << "Masukkan durasi (detik): "; cin >> durasi;

    // Input lirik bisa lebih dari 1 baris
    // Ketik SELESAI di baris baru untuk mengakhiri
    cin.ignore();
    cout << "Masukkan lirik (ketik SELESAI di baris baru untuk selesai):\n";
    lirik = "";
    while (true) {
        getline(cin, baris);
        if (baris == "SELESAI") break;
        if (!lirik.empty()) lirik += "\n";
        lirik += baris;
    }

    Node* nodeBaru = buatNodeBaru(judul, penyanyi, genre, durasi, lirik);
    sambungKeAkhir(nodeBaru);

    cout << "Lagu \"" << judul << "\" berhasil ditambahkan!\n";
}

// ============================================================
// Fungsi bantu: tampilkan semua lagu TANPA lirik
// (dipakai di fitur Hapus dan saat Keluar)
// ============================================================
void tampilkanDaftarLagu() {
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

// ============================================================
// FITUR 2: Hapus Lagu (lirik tidak ditampilkan)
// ============================================================
void hapusLagu() {
    cout << "\n--- HAPUS LAGU ---\n";
    tampilkanDaftarLagu();

    if (head == nullptr) return;

    string cariJudul;
    cout << "Masukkan judul lagu yang ingin dihapus: ";
    cin.ignore();
    getline(cin, cariJudul);

    // Kasus 1: lagu ada di posisi pertama (head)
    if (head->judul == cariJudul) {
        Node* hapus = head;
        head        = head->next;
        delete hapus;
        cout << "Lagu \"" << cariJudul << "\" berhasil dihapus!\n";
        return;
    }

    // Kasus 2: lagu ada di tengah atau akhir
    Node* temp = head;
    while (temp->next != nullptr) {
        if (temp->next->judul == cariJudul) {
            Node* hapus = temp->next;
            temp->next  = hapus->next;
            delete hapus;
            cout << "Lagu \"" << cariJudul << "\" berhasil dihapus!\n";
            return;
        }
        temp = temp->next;
    }

    cout << "Lagu \"" << cariJudul << "\" tidak ditemukan.\n";
}

// ============================================================
// FITUR 3: Keluar
// ============================================================
void keluar() {
    cout << "\n--- KELUAR ---\n";
    tampilkanDaftarLagu();
    cout << "Sampai jumpa!\n";
}

// ============================================================
// MENU ADMIN UTAMA
// ============================================================
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
            case 1: tambahLagu(); break;
            case 2: hapusLagu();  break;
            case 3: keluar();     break;
            default:
                cout << "Pilihan tidak valid! Masukkan angka 1-3.\n";
        }

    } while (pilihan != 3);
}

// ============================================================
// Main: jalankan file ini secara mandiri
// ============================================================
int main() {
    menu_admin();
    return 0;
}