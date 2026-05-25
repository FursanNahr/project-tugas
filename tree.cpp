#include <iostream>
#include <string>
#include "header/lagu.h"
#include "header/tree.h"
using namespace std;

extern Lagu daftar_lagu[100];
extern int jumlah_lagu;

NodeTree *rootTree = NULL;

void insert_tree(NodeTree **root, Lagu lagu)
{
    if (*root == NULL)
    {
        NodeTree *node = new NodeTree;
        node->data = lagu;
        node->left = NULL;
        node->right = NULL;
        *root = node;
        return;
    }

    string judul_baru = lowercase(lagu.judul);
    string judul_root = lowercase((*root)->data.judul);

    if (judul_baru < judul_root)
    {
        insert_tree(&(*root)->left, lagu);
    }
    else if (judul_baru > judul_root)
    {
        insert_tree(&(*root)->right, lagu);
    }
}

void build_tree()
{
    rootTree = NULL;
    for (int i = 0; i < jumlah_lagu; i++)
    {
        insert_tree(&rootTree, daftar_lagu[i]);
    }
}

void inorder_tree(NodeTree *root)
{
    if (root == NULL)
    {
        return;
    }

    inorder_tree(root->left);

    cout << "    🎵 " << root->data.judul
         << " - " << root->data.penyanyi
         << "  |  " << root->data.mood
         << "  |  " << root->data.genre << endl;

    inorder_tree(root->right);
}

NodeTree *cari_tree(NodeTree *root, string judul)
{
    if (root == NULL)
    {
        return NULL;
    }

    string judul_cari = lowercase(judul);
    string judul_node = lowercase(root->data.judul);

    if (judul_cari == judul_node)
    {
        return root;
    }
    else if (judul_cari < judul_node)
    {
        return cari_tree(root->left, judul);
    }
    else
    {
        return cari_tree(root->right, judul);
    }
}

void tampilkan_tree()
{
    if (rootTree == NULL)
    {
        cout << "⚠️  Tree kosong, data lagu belum dimuat." << endl;
        return;
    }

    cout << "\n🌳 ══════ DAFTAR LAGU (Urut A-Z) ══════ 🌳" << endl;
    cout << "    " << "Judul"
         << " - " << "Penyanyi"
         << "  |  " << "Mood"
         << "  |  " << "Genre" << endl;
    cout << "    ──────────────────────────────────────────" << endl;
    inorder_tree(rootTree);
    cout << "  ════════════════════════════════════════════" << endl;
}

void cari_lagu_tree()
{
    if (rootTree == NULL)
    {
        cout << "⚠️  Tree kosong, data lagu belum dimuat." << endl;
        return;
    }

    cout << "\n🔍 ══════ CARI LAGU (BST) ══════ 🔍" << endl;
    cout << "  Masukkan judul lagu: ";

    string keyword;
    getline(cin, keyword);

    NodeTree *hasil = cari_tree(rootTree, keyword);

    if (hasil != NULL)
    {
        cout << "\n  ✅ Lagu ditemukan!" << endl;
        cout << "  ────────────────────────────────" << endl;
        cout << "  🎵 Judul    : " << hasil->data.judul << endl;
        cout << "  🎤 Penyanyi : " << hasil->data.penyanyi << endl;
        cout << "  😊 Mood     : " << hasil->data.mood << endl;
        cout << "  🎸 Genre    : " << hasil->data.genre << endl;
        cout << "  ────────────────────────────────" << endl;
    }
    else
    {
        cout << "\n  ❌ Lagu \"" << keyword << "\" tidak ditemukan." << endl;
    }
}
