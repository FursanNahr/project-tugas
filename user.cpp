#include <iostream>
#include <cstdlib>
#include <string>
#include "playlist.cpp"
#include "lagu.cpp"
// #include "queue.cpp"
using namespace std;


void menu_user(string username){
    while (true) {
        system("cls");

        cout << "\n==========================================" << endl;
        cout << "   Selamat Datang " << username << " di LEORA" << endl;
        cout << "==========================================" << endl;
        cout << "0. Keluar" << endl;
        cout << "1. Now Playing" << endl;
        cout << "2. Tampilkan Semua Lagu" << endl;
        cout << "3. Cari Lagu" << endl;
        cout << "4. Playlist" << endl;
    
        int input_pilihan;
        cout << "Pilih Menu : "; cin >> input_pilihan;

        if(input_pilihan == 1){
            sedang_diputar();
        }else if(input_pilihan == 2){
            tampilkan_lagu();
        }else if(input_pilihan == 3){
            cari_lagu();
        }else if(input_pilihan == 4){
            playlist(username);
        }else if(input_pilihan == 0){
            exit(0);
        }else {
            cout << "Pilihan tidak valid.";
        }
    }

    
}