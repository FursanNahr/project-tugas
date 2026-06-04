#include "header/tree.h"

#include <cctype>
#include <iostream>
#include <string>

#include "header/lagu.h"
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
    for (int i = 0; i < str.length(); i++) {
        str[i] = tolower(str[i]);
    }
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

    if (judul_baru < judul_root) {
        insert_tree(&(*root)->left, lagu);
    } else if (judul_baru > judul_root) {
        insert_tree(&(*root)->right, lagu);
    }
}

void build_tree() {
    rootTree = NULL;
    for (int i = 0; i < jumlah_lagu; i++) {
        insert_tree(&rootTree, daftar_lagu[i]);
    }
}

void inorder_tree(NodeTree* root) {
    if (root == NULL) {
        return;
    }

    inorder_tree(root->left);

    cout << "  │ " << pad(to_string(nomor_urut_tree++), 2)
         << " │ " << pad(root->data.judul, 22)
         << " │ " << pad(root->data.penyanyi, 15)
         << " │ " << pad(root->data.genre, 12)
         << " │ " << pad(root->data.mood, 10)
         << " │" << endl;

    inorder_tree(root->right);
}

NodeTree* cari_tree(NodeTree* root, string judul) {
    if (root == NULL) {
        return NULL;
    }

    string judul_cari = lowercase(judul);
    string judul_node = lowercase(root->data.judul);

    if (judul_cari == judul_node) {
        return root;
    } else if (judul_cari < judul_node) {
        return cari_tree(root->left, judul);
    } else {
        return cari_tree(root->right, judul);
    }
}

void tampilkan_tree() {
    build_tree();

    if (rootTree == NULL) {
        cout << "⚠️  Tree kosong, data lagu belum dimuat." << endl;
        return;
    }

    cout << "\n🌳 ══════════════ DAFTAR LAGU (Urut A-Z) ══════════════ 🌳\n"
         << endl;

    cout << "  ┌────┬────────────────────────┬─────────────────┬──────────────┬────────────┐" << endl;
    cout << "  │ No │ Judul                  │ Penyanyi        │ Genre        │ Mood       │" << endl;
    cout << "  ├────┼────────────────────────┼─────────────────┼──────────────┼────────────┤" << endl;

    nomor_urut_tree = 1;
    inorder_tree(rootTree);

    cout << "  └────┴────────────────────────┴─────────────────┴──────────────┴────────────┘" << endl;
}

void cari_lagu_tree() {
    build_tree();

    if (rootTree == NULL) {
        cout << "⚠️  Tree kosong, data lagu belum dimuat." << endl;
        return;
    }

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

        cout << "  │ " << pad("1", 2)
             << " │ " << pad(hasil->data.judul, 22)
             << " │ " << pad(hasil->data.penyanyi, 15)
             << " │ " << pad(hasil->data.genre, 12)
             << " │ " << pad(hasil->data.mood, 10)
             << " │" << endl;

        cout << "  └────┴────────────────────────┴─────────────────┴──────────────┴────────────┘" << endl;
    } else {
        cout << "\n  ❌ Lagu \"" << keyword << "\" tidak ditemukan di database." << endl;
    }
}