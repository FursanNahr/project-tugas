// clang-format off
#include <windows.h>
#include <mmsystem.h>
// clang-format on
#include "header/tree.h"

#include <cctype>
#include <iostream>
#include <string>

#include "header/admin.h"
#include "header/lagu.h"
#include "header/playlist.h"
#include "header/queue.h"
using namespace std;

extern Lagu daftar_lagu[100];
extern int jumlah_lagu;

NodeTree* rootTree = NULL;
int nomor_urut_tree = 1;

string pad(string s, int w) {
    if ((int)s.size() > w) s = s.substr(0, w - 1) + "~";
    return s + string(w - s.size(), ' ');
}

string lowercase(string str) {
    for (char& c : str) c = tolower(c);
    return str;
}

void insert_tree(NodeTree** root, Lagu lagu) {
    if (*root == NULL) {
        NodeTree* node = new NodeTree;
        node->data = lagu;
        node->left = NULL;
        node->right = NULL;
        *root = node;
        return;
    }
    string judul_baru = lowercase(lagu.judul);
    string judul_root = lowercase((*root)->data.judul);

    if (judul_baru < judul_root)
        insert_tree(&(*root)->left, lagu);
    else if (judul_baru > judul_root)
        insert_tree(&(*root)->right, lagu);
}

void build_tree() {
    rootTree = NULL;
    for (int i = 0; i < jumlah_lagu; i++)
        insert_tree(&rootTree, daftar_lagu[i]);
}

static Lagu hasil_urut[100];
static int jumlah_urut = 0;

void putar_lagu(Lagu lagu) {
    string file_midi = lagu.midi;

    if (file_midi == "" || file_midi == "-") {
        cout << "\n❌ File MIDI untuk lagu \"" << lagu.judul << "\" belum tersedia!" << endl;
        return;
    }

    string lokasi_file = "lagu/" + file_midi;

    mciSendStringA("close musik_cli", NULL, 0, NULL);
    string perintah_buka = "open \"" + lokasi_file + "\" type sequencer alias musik_cli";
    mciSendStringA(perintah_buka.c_str(), NULL, 0, NULL);

    mciSendStringA("play musik_cli", NULL, 0, NULL);

    cout << "\n========================================================" << endl;
    cout << "🎵 SEDANG MEMUTAR (MIDI) : " << lagu.judul << " - " << lagu.penyanyi << endl;
    cout << "🔊 (Lagu diputar dari folder /lagu/, silakan pilih menu lain)" << endl;
    cout << "========================================================" << endl;
}

void kumpulkan_inorder(NodeTree* root) {
    if (root == NULL) return;
    kumpulkan_inorder(root->left);
    hasil_urut[jumlah_urut++] = root->data;
    kumpulkan_inorder(root->right);
}

void cetak_baris(int nomor, const Lagu& l) {
    cout << "  │ " << pad(to_string(nomor), 2)
         << " │ " << pad(l.judul, 22)
         << " │ " << pad(l.penyanyi, 15)
         << " │ " << pad(l.genre, 12)
         << " │ " << pad(l.mood, 10)
         << " │" << endl;
}

void aksi_lagu_tree(const Lagu& lagu) {
    int pilihan;
    while (true) {
        system("cls");
        cout << "\n 🎧 Kamu memilih: " << lagu.judul << " - " << lagu.penyanyi << endl;
        cout << "    [" << lagu.genre << " | " << lagu.mood << "]\n"
             << endl;

        cout << "🎵 ════════ OPSI LAGU ════════ 🎵" << endl;
        cout << "  [1] ➕ Masukkan ke Antrean" << endl;
        cout << "  [2] ▶️  Putar Sekarang" << endl;
        cout << "  ──────────────────────────────" << endl;
        cout << "  [0] 🔙 Kembali" << endl;
        cout << "================================" << endl;
        cout << "👉 Pilih aksi (0-2): ";

        pilihan = ambil_input_angka();

        if (pilihan == 1) {
            tambah_antrean(lagu.judul, lagu.penyanyi);
            cout << "✅ Dimasukkan ke antrean!" << endl;
            pause();
            return;
        } else if (pilihan == 2) {
            putar_lagu(lagu);

            putar_sekarang(lagu.judul, lagu.penyanyi);
            cout << "▶️  Sedang diputar!" << endl;
            pause();
            return;
        } else if (pilihan == 0) {
            return;
        } else {
            cout << "❌ Pilihan tidak valid!" << endl;
            pause();
        }
    }
}

void tampilkan_tree() {
    build_tree();
    if (rootTree == NULL) {
        cout << "⚠️  Tree kosong, data lagu belum dimuat." << endl;
        return;
    }

    int pilihan;
    while (true) {
        system("cls");

        jumlah_urut = 0;
        kumpulkan_inorder(rootTree);

        cout << "\n🌳 ══════════════ DAFTAR LAGU (Urut A-Z) ══════════════ 🌳\n"
             << endl;
        cout << "  ┌────┬────────────────────────┬─────────────────┬──────────────┬────────────┐" << endl;
        cout << "  │ No │ Judul                  │ Penyanyi        │ Genre        │ Mood       │" << endl;
        cout << "  ├────┼────────────────────────┼─────────────────┼──────────────┼────────────┤" << endl;

        for (int i = 0; i < jumlah_urut; i++)
            cetak_baris(i + 1, hasil_urut[i]);

        cout << "  └────┴────────────────────────┴─────────────────┴──────────────┴────────────┘" << endl;
        cout << "  [0] 🔙 Kembali\n";
        cout << "\n👉 Pilih nomor lagu (1-" << jumlah_urut << "): ";

        pilihan = ambil_input_angka();

        if (pilihan == 0) {
            return;
        } else if (pilihan >= 1 && pilihan <= jumlah_urut) {
            aksi_lagu_tree(hasil_urut[pilihan - 1]);
        } else {
            cout << "❌ Pilihan tidak valid!" << endl;
            pause();
        }
    }
}

NodeTree* cari_tree(NodeTree* root, string judul) {
    if (root == NULL) return NULL;

    string judul_cari = lowercase(judul);
    string judul_node = lowercase(root->data.judul);

    if (judul_cari == judul_node) return root;
    if (judul_cari < judul_node) return cari_tree(root->left, judul);
    return cari_tree(root->right, judul);
}

void cari_lagu_tree() {
    build_tree();
    if (rootTree == NULL) {
        cout << "⚠️  Tree kosong, data lagu belum dimuat." << endl;
        return;
    }

    system("cls");
    cout << "\n🔍 ══════ CARI LAGU (BST) ══════ 🔍" << endl;
    cout << "  👉 Masukkan judul lagu: ";

    string keyword;
    getline(cin, keyword);

    NodeTree* hasil = cari_tree(rootTree, keyword);

    if (hasil != NULL) {
        cout << "\n  ✅ Lagu ditemukan!\n"
             << endl;

        cout << "  ┌────┬────────────────────────┬─────────────────┬──────────────┬────────────┐" << endl;
        cout << "  │ No │ Judul                  │ Penyanyi        │ Genre        │ Mood       │" << endl;
        cout << "  ├────┼────────────────────────┼─────────────────┼──────────────┼────────────┤" << endl;
        cetak_baris(1, hasil->data);
        cout << "  └────┴────────────────────────┴─────────────────┴──────────────┴────────────┘" << endl;

        cout << "\n🎵 ════════ OPSI LAGU ════════ 🎵" << endl;
        cout << "  [1] ➕ Masukkan ke Antrean" << endl;
        cout << "  [2] ▶️  Putar Sekarang" << endl;
        cout << "  ──────────────────────────────" << endl;
        cout << "  [0] 🔙 Kembali" << endl;
        cout << "================================" << endl;
        cout << "👉 Pilih aksi (0-2): ";

        int pilihan = ambil_input_angka();

        if (pilihan == 1) {
            tambah_antrean(hasil->data.judul, hasil->data.penyanyi);
            cout << "✅ Dimasukkan ke antrean!" << endl;
        } else if (pilihan == 2) {
            putar_lagu(hasil->data);

            putar_sekarang(hasil->data.judul, hasil->data.penyanyi);
            cout << "▶️  Sedang diputar!" << endl;
        }

        pause();

    } else {
        cout << "\n  ❌ Lagu \"" << keyword << "\" tidak ditemukan di database." << endl;
        pause();
    }
}