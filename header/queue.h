#pragma once
#include <iostream>
#include <string>

#include "lagu.h"
using namespace std;

const int ukuran_queue = 100;

void tambah_antrean(string judul, string penyanyi, string mood, string genre);
void putar_sekarang(string judul, string penyanyi, string mood, string genre);
void sedang_diputar();
int isEmpty();
int isFull();

struct AntrianLagu {
    int top;
    int current_index;
    Lagu isi[ukuran_queue];
};

extern AntrianLagu antrian_lagu;