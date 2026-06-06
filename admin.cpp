#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>

#include "header/lagu.h"
#include "header/playlist.h"
#include "header/user.h"
using namespace std;

struct LaguAdmin {
    string judul;
    string penyanyi;
    string mood;
    string genre;
};

// ─── BST untuk pengurutan lagu admin ───────────────────────────────────────
struct NodeBSTAdmin {
    LaguAdmin data;
    NodeBSTAdmin* left;
    NodeBSTAdmin* right;
};

string lowercase_admin(string str) {
    for (char& c : str) c = tolower(c);
    return str;
}

void insert_bst_admin(NodeBSTAdmin** root, LaguAdmin lagu) {
    if (*root == NULL) {
        NodeBSTAdmin* node = new NodeBSTAdmin;
        node->data  = lagu;
        node->left  = NULL;
        node->right = NULL;
        *root = node;
        return;
    }
    string judul_baru = lowercase_admin(lagu.judul);
    string judul_root = lowercase_admin((*root)->data.judul);

    if (judul_baru < judul_root)
        insert_bst_admin(&(*root)->left,  lagu);
    else if (judul_baru > judul_root)
        insert_bst_admin(&(*root)->right, lagu);
}

void inorder_bst_admin(NodeBSTAdmin* root, LaguAdmin* hasil, int& n) {
    if (root == NULL) return;
    inorder_bst_admin(root->left,  hasil, n);
    hasil[n++] = root->data;
    inorder_bst_admin(root->right, hasil, n);
}

void delete_bst_admin(NodeBSTAdmin* root) {
    if (root == NULL) return;
    delete_bst_admin(root->left);
    delete_bst_admin(root->right);
    delete root;
}

int baca_dan_urutkan(LaguAdmin* hasil) {
    ifstream file_in("data_lagu.txt");
    if (!file_in.is_open()) return -1;

    NodeBSTAdmin* root = NULL;
    string line;
    while (getline(file_in, line)) {
        stringstream ss(line);
        string judul, penyanyi, mood, genre;
        getline(ss, judul,    '|');
        getline(ss, penyanyi, '|');
        getline(ss, mood,     '|');
        getline(ss, genre,    '|');
        if (!judul.empty())
            insert_bst_admin(&root, {judul, penyanyi, mood, genre});
    }
    file_in.close();

    int n = 0;
    inorder_bst_admin(root, hasil, n);
    delete_bst_admin(root);
    return n;
}

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
    system("cls");
    cout << "\n➕ ═════════ TAMBAH LAGU ═════════ ➕" << endl;
    cout << "   (Ketik 0 pada Judul untuk kembali)" << endl;
    cout << "───────────────────────────────────────" << endl;

    string judul, penyanyi, mood, genre;

    while (true) {
        cout << "  🎵 Judul Lagu  : ";
        getline(cin, judul);

        if (judul == "0") return;

        if (judul.empty() || judul.find_first_not_of(' ') == string::npos) {
            cout << "  ❌ Judul tidak boleh kosong!\n";
        } else {
            break;
        }
    }

    cout << "  ┌─────────────────────────────────┐" << endl;
    cout << "  │  🎶  " << judul << endl;
    cout << "  └─────────────────────────────────┘" << endl;

    while (true) {
        cout << "  🎤 Penyanyi    : ";
        getline(cin, penyanyi);

        if (penyanyi.empty() || penyanyi.find_first_not_of(' ') == string::npos) {
            cout << "  ❌ Nama penyanyi tidak boleh kosong!\n";
        } else {
            break;
        }
    }

    cout << "\n  🌈 Pilih Mood :" << endl;
    cout << "     [1] Bahagia    [2] Semangat" << endl;
    cout << "     [3] Romantis   [4] Santai" << endl;
    cout << "     [5] Tenang     [6] Renungan" << endl;
    cout << "     [7] Galau      [8] Sedih" << endl;
    string mood_list[] = {"Bahagia", "Semangat", "Romantis", "Santai", "Tenang", "Renungan", "Galau", "Sedih"};
    int pilih_mood;
    while (true) {
        cout << "  👉 Pilihan (1-8) : ";
        pilih_mood = ambil_input_angka();
        if (pilih_mood >= 1 && pilih_mood <= 8) { mood = mood_list[pilih_mood - 1]; break; }
        cout << "  ❌ Pilihan tidak valid!\n";
    }

    cout << "\n  🎸 Pilih Genre :" << endl;
    cout << "     [1] Pop        [2] Dangdut" << endl;
    cout << "     [3] Rock       [4] R&B" << endl;
    cout << "     [5] Jazz       [6] Hip-Hop" << endl;
    cout << "     [7] Classical  [8] Soul" << endl;
    string genre_list[] = {"Pop", "Dangdut", "Rock", "R&B", "Jazz", "Hip-Hop", "Classical", "Soul"};
    int pilih_genre;
    while (true) {
        cout << "  👉 Pilihan (1-8) : ";
        pilih_genre = ambil_input_angka();
        if (pilih_genre >= 1 && pilih_genre <= 8) { genre = genre_list[pilih_genre - 1]; break; }
        cout << "  ❌ Pilihan tidak valid! \n";
    }

    cout << "=======================================" << endl;

    ofstream file("data_lagu.txt", ios::app);
    if (file.is_open()) {
        file << judul << "|" << penyanyi << "|" << mood << "|" << genre << endl;
        file.close();
        cout << "✅ BERHASIL: '" << judul << " - " << penyanyi
             << "' [" << genre << " | " << mood << "] ditambahkan!" << endl;
    } else {
        cout << "❌ CRITICAL ERROR: Gagal membuka file 'data_lagu.txt'!" << endl;
    }
    load_lagu();
    pause();
}

void hapus() {
    system("cls");
    cout << "\n🗑️  ══════════ HAPUS LAGU ══════════ 🗑️" << endl;

    jumlah_lagu_admin = baca_dan_urutkan(daftar_lagu_admin);
    if (jumlah_lagu_admin == -1) {
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

    cout << "  ┌────┬────────────────────────┬─────────────────┬──────────────┬────────────┐" << endl;
    cout << "  │ No │ Judul                  │ Penyanyi        │ Genre        │ Mood       │" << endl;
    cout << "  ├────┼────────────────────────┼─────────────────┼──────────────┼────────────┤" << endl;
    for (int i = 0; i < jumlah_lagu_admin; i++) {
        auto pad = [](string s, int w) -> string {
            if ((int)s.size() > w) s = s.substr(0, w - 1) + "~";
            return s + string(w - s.size(), ' ');
        };
        cout << "  │ "  << pad(to_string(i + 1), 2)
             << " │ "   << pad(daftar_lagu_admin[i].judul,    22)
             << " │ "   << pad(daftar_lagu_admin[i].penyanyi, 15)
             << " │ "   << pad(daftar_lagu_admin[i].genre,    12)
             << " │ "   << pad(daftar_lagu_admin[i].mood,     10)
             << " │"    << endl;
    }
    cout << "  └────┴────────────────────────┴─────────────────┴──────────────┴────────────┘" << endl;
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
            file_out << daftar_lagu_admin[k].judul    << "|"
                     << daftar_lagu_admin[k].penyanyi << "|"
                     << daftar_lagu_admin[k].mood     << "|"
                     << daftar_lagu_admin[k].genre    << endl;
        }
        file_out.close();

        cout << "✅ BERHASIL: Lagu '" << lagu_dihapus << "' telah dihapus!" << endl;
        load_lagu();
        pause();
    } else {
        cout << "❌ ERROR: Nomor tidak valid!" << endl;
        pause();
    }
}

void tampilkan_semua_lagu() {
    system("cls");
    cout << "\n📋 ══════ DAFTAR SEMUA LAGU ══════ 📋" << endl;

    int total = baca_dan_urutkan(daftar_lagu_admin);
    if (total == -1) {
        cout << "  ❌ ERROR: File data_lagu.txt tidak ditemukan!" << endl;
        pause();
        return;
    }

    if (total == 0) {
        cout << "  📭 Belum ada lagu di dalam sistem." << endl;
        cout << "=======================================" << endl;
        pause();
        return;
    }

    cout << "  Total lagu : " << total << " lagu" << endl;
    cout << "  ┌────┬────────────────────────┬─────────────────┬──────────────┬────────────┐" << endl;
    cout << "  │ No │ Judul                  │ Penyanyi        │ Genre        │ Mood       │" << endl;
    cout << "  ├────┼────────────────────────┼─────────────────┼──────────────┼────────────┤" << endl;
    for (int i = 0; i < total; i++) {
        auto pad = [](string s, int w) -> string {
            if ((int)s.size() > w) s = s.substr(0, w - 1) + "~";
            return s + string(w - s.size(), ' ');
        };
        cout << "  │ "  << pad(to_string(i + 1), 2)
             << " │ "   << pad(daftar_lagu_admin[i].judul,    22)
             << " │ "   << pad(daftar_lagu_admin[i].penyanyi, 15)
             << " │ "   << pad(daftar_lagu_admin[i].genre,    12)
             << " │ "   << pad(daftar_lagu_admin[i].mood,     10)
             << " │"    << endl;
    }
    cout << "  └────┴────────────────────────┴─────────────────┴──────────────┴────────────┘" << endl;
    cout << "=======================================" << endl;
    pause();
}

void edit() {
    system("cls");
    cout << "\n✏️  ══════════ EDIT LAGU ══════════ ✏️" << endl;

    jumlah_lagu_admin = baca_dan_urutkan(daftar_lagu_admin);
    if (jumlah_lagu_admin == -1) {
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

    cout << "  ┌────┬────────────────────────┬─────────────────┬──────────────┬────────────┐" << endl;
    cout << "  │ No │ Judul                  │ Penyanyi        │ Genre        │ Mood       │" << endl;
    cout << "  ├────┼────────────────────────┼─────────────────┼──────────────┼────────────┤" << endl;
    for (int i = 0; i < jumlah_lagu_admin; i++) {
        auto pad = [](string s, int w) -> string {
            if ((int)s.size() > w) s = s.substr(0, w - 1) + "~";
            return s + string(w - s.size(), ' ');
        };
        cout << "  │ "  << pad(to_string(i + 1), 2)
             << " │ "   << pad(daftar_lagu_admin[i].judul,    22)
             << " │ "   << pad(daftar_lagu_admin[i].penyanyi, 15)
             << " │ "   << pad(daftar_lagu_admin[i].genre,    12)
             << " │ "   << pad(daftar_lagu_admin[i].mood,     10)
             << " │"    << endl;
    }
    cout << "  └────┴────────────────────────┴─────────────────┴──────────────┴────────────┘" << endl;
    cout << "  [0] 🔙 Batal / Kembali" << endl;
    cout << "========================================" << endl;
    cout << "👉 Masukkan nomor lagu yang ingin diedit : ";

    int input_user = ambil_input_angka();

    if (input_user == 0) return;

    if (input_user < 1 || input_user > jumlah_lagu_admin) {
        cout << "❌ ERROR: Nomor tidak valid!" << endl;
        pause();
        return;
    }

    int idx = input_user - 1;
    LaguAdmin& lagu = daftar_lagu_admin[idx];

    system("cls");
    cout << "\n✏️  ══════════ EDIT LAGU ══════════ ✏️" << endl;
    cout << "   (Tekan Enter untuk mempertahankan nilai lama)" << endl;
    cout << "   (Ketik 0 pada Judul untuk batal)" << endl;
    cout << "─────────────────────────────────────────────────" << endl;
    cout << "  Lagu yang diedit: " << lagu.judul << " - " << lagu.penyanyi << endl;
    cout << "========================================" << endl;

    string input;
    cout << "  🎵 Judul Lagu [" << lagu.judul << "] : ";
    getline(cin, input);
    if (input == "0") {
        cout << "  ↩️  Edit dibatalkan." << endl;
        pause();
        return;
    }
    if (!input.empty() && input.find_first_not_of(' ') != string::npos)
        lagu.judul = input;

    cout << "  🎤 Penyanyi   [" << lagu.penyanyi << "] : ";
    getline(cin, input);
    if (!input.empty() && input.find_first_not_of(' ') != string::npos)
        lagu.penyanyi = input;

    string mood_list[] = {"Bahagia", "Semangat", "Romantis", "Santai", "Tenang", "Renungan", "Galau", "Sedih"};
    cout << "\n  🌈 Pilih Mood baru (Enter untuk skip):" << endl;
    cout << "     [1] Bahagia    [2] Semangat" << endl;
    cout << "     [3] Romantis   [4] Santai" << endl;
    cout << "     [5] Tenang     [6] Renungan" << endl;
    cout << "     [7] Galau      [8] Sedih" << endl;
    cout << "  👉 Mood saat ini [" << lagu.mood << "] - Pilihan (1-8, Enter=skip) : ";
    getline(cin, input);
    if (!input.empty()) {
        try {
            int pilih = stoi(input);
            if (pilih >= 1 && pilih <= 8)
                lagu.mood = mood_list[pilih - 1];
            else
                cout << "  ⚠️  Pilihan tidak valid, mood tidak diubah." << endl;
        } catch (...) {
            cout << "  ⚠️  Input tidak valid, mood tidak diubah." << endl;
        }
    }

    string genre_list[] = {"Pop", "Dangdut", "Rock", "R&B", "Jazz", "Hip-Hop", "Classical", "Soul"};
    cout << "\n  🎸 Pilih Genre baru (Enter untuk skip):" << endl;
    cout << "     [1] Pop        [2] Dangdut" << endl;
    cout << "     [3] Rock       [4] R&B" << endl;
    cout << "     [5] Jazz       [6] Hip-Hop" << endl;
    cout << "     [7] Classical  [8] Soul" << endl;
    cout << "  👉 Genre saat ini [" << lagu.genre << "] - Pilihan (1-8, Enter=skip) : ";
    getline(cin, input);
    if (!input.empty()) {
        try {
            int pilih = stoi(input);
            if (pilih >= 1 && pilih <= 8)
                lagu.genre = genre_list[pilih - 1];
            else
                cout << "  ⚠️  Pilihan tidak valid, genre tidak diubah." << endl;
        } catch (...) {
            cout << "  ⚠️  Input tidak valid, genre tidak diubah." << endl;
        }
    }

    ofstream file_out("data_lagu.txt");
    for (int k = 0; k < jumlah_lagu_admin; k++) {
        file_out << daftar_lagu_admin[k].judul    << "|"
                 << daftar_lagu_admin[k].penyanyi << "|"
                 << daftar_lagu_admin[k].mood     << "|"
                 << daftar_lagu_admin[k].genre    << endl;
    }
    file_out.close();

    cout << "\n✅ BERHASIL: Lagu '" << lagu.judul << "' telah diperbarui!" << endl;
    load_lagu();
    pause();
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
        cout << "  [3] 📋 Tampilkan Semua Lagu" << endl;
        cout << "  [4] ✏️  Edit Lagu" << endl;
        cout << "  ────────────────────────────────────" << endl;
        cout << "  [0] 🚪 Logout" << endl;
        cout << "======================================" << endl;
        cout << "👉 Pilih menu (0-4): ";
        pilihan = ambil_input_angka();

        if      (pilihan == 1) tambah();
        else if (pilihan == 2) hapus();
        else if (pilihan == 3) tampilkan_semua_lagu();
        else if (pilihan == 4) edit();
        else if (pilihan == 0) {
            cout << "\n👋 Sampai jumpa, Admin " << username << "!" << endl;
            pause();
        } else {
            cout << "❌ Pilihan tidak valid! Silakan pilih 0-4." << endl;
            pause();
        }
    } while (pilihan != 0);

    return 0;
}