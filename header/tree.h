#pragma once
#include <iostream>
#include <string>

#include "lagu.h"
using namespace std;

struct NodeTree {
    Lagu data;
    NodeTree *left, *right;
};

extern NodeTree* rootTree;

void build_tree();
void insert_tree(NodeTree** root, Lagu lagu);
void inorder_tree(NodeTree** root);
NodeTree* cari_tree(NodeTree* root, string judul);
void tampilkan_tree();
void cari_lagu_tree();
void putar_lagu();
void aksi_lagu_tree(const Lagu& lagu);