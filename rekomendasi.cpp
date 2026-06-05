#include "header/rekomendasi.h"

#include <iostream>
#include <string>

#include "header/lagu.h"
using namespace std;

extern Lagu daftar_lagu[100];
extern int jumlah_lagu;

const int ukuran_queue = 10;
struct LaguQ {
    string judul, penyanyi;
};
struct AntrianLagu {
    int top, current_index;
    LaguQ isi[ukuran_queue];
};
extern AntrianLagu antrian_lagu;

struct NodeRek {
    string label;  // misal mood galau atau genre pop
    int frekuensi;
    NodeRek *left, *right;
};

NodeRek* rootRek = NULL;
int total_lagu = 10;  // hardcode

// insert/update frekuensi di BST
void insert_rek(NodeRek** root, string label) {
    if (*root == NULL) {
        NodeRek* node = new NodeRek;
        node->label = label;
        node->frekuensi = 1;
        node->left = NULL;
        node->right = NULL;
        *root = node;
    }

    else if (label == (*root)->label) {
        (*root)->frekuensi++;
    }

    else if (label < (*root)->label) {
        insert_rek(&(*root)->left, label);
    }

    else {
        insert_rek(&(*root)->right, label);
    }
}

// cari node dengan label tertentu
NodeRek* cari_rek(NodeRek* root, string label) {
    while (root != NULL) {
        if (label == root->label)
            return root;
        root = (label < root->label) ? root->left : root->right;
    }

    return NULL;
}

// Cari label dengan frekuensi tertinggi
void cari_tertinggi(NodeRek* root, string prefix, string& hasilLabel, int& hasilFreq) {
    if (root == NULL)
        return;

    cari_tertinggi(root->left, prefix, hasilLabel, hasilFreq);

    if (root->label.substr(0, prefix.size()) == prefix) {
        if (root->frekuensi > hasilFreq) {
            hasilFreq = root->frekuensi;
            hasilLabel = root->label.substr(prefix.size());
        }
    }

    cari_tertinggi(root->right, prefix, hasilLabel, hasilFreq);
}

bool ada_di_antrean(string judul) {
    for (int i = 0; i < antrian_lagu.top; i++) {
        if (antrian_lagu.isi[i].judul == judul)
            return true;
    }
    return false;
}

void catat_preferensi(string mood, string genre) {
    insert_rek(&rootRek, "mood:" + mood);
    insert_rek(&rootRek, "genre:" + genre);
}

void tampilkan_rekomendasi() {
    if (rootRek == NULL) {
        cout << "⚠️ Belum ada preferensi, cobalah mulai mainkan lagu" << endl;
        return;
    }

    string moodTeratas = "", genreTeratas = "";
    int freqMood = 0, freqGenre = 0;
    cari_tertinggi(rootRek, "mood:", moodTeratas, freqMood);
    cari_tertinggi(rootRek, "genre:", genreTeratas, freqGenre);

    cout << "\n🎯 ══════ REKOMENDASI UNTUKMU ══════ 🎯" << endl;
    cout << "  Mood favorit  : " << moodTeratas << endl;
    cout << "  Genre favorit : " << genreTeratas << endl;
    cout << "  ────────────────────────────────────" << endl;

    bool ada = false;
    cout << "  🔥 Paling Cocok:" << endl;
    for (int i = 0; i < jumlah_lagu; i++) {
        if (daftar_lagu[i].mood == moodTeratas &&
            daftar_lagu[i].genre == genreTeratas &&
            !ada_di_antrean(daftar_lagu[i].judul)) {
            cout << "    🎵 " << daftar_lagu[i].judul
                 << " - " << daftar_lagu[i].penyanyi << endl;
            ada = true;
        }
    }
    if (!ada)
        cout << "    (tidak ada)" << endl;

    ada = false;
    cout << "  ✨ Mungkin Kamu Suka:" << endl;
    for (int i = 0; i < jumlah_lagu; i++) {
        bool cocokMood = daftar_lagu[i].mood == moodTeratas;
        bool cocokGenre = daftar_lagu[i].genre == genreTeratas;
        bool keduanya = cocokMood && cocokGenre;

        if (!keduanya && (cocokMood || cocokGenre) &&
            !ada_di_antrean(daftar_lagu[i].judul)) {
            cout << "    🎵 " << daftar_lagu[i].judul
                 << " - " << daftar_lagu[i].penyanyi << endl;
            ada = true;
        }
    }
    if (!ada)
        cout << "    (tidak ada)" << endl;
    cout << "  ════════════════════════════════════" << endl;
}