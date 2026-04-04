#pragma once
#include <iostream>
#include <string>
using namespace std;

struct Lagu {
    string judul;
    string penyanyi;
};

extern Lagu daftar_lagu[100];
extern int jumlah_lagu;

void load_lagu();
void cari_lagu();
void tampilkan_lagu();
string lowercase(string teks);