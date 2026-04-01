#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;


void menu_user(string username){
    cout << "\n==========================================" << endl;
    cout << "   Selamat Datang " << username << " di LEORA" << endl;
    cout << "==========================================" << endl;
    cout << "1. Now Playing" << endl;
    cout << "2. Tampilkan Semua Lagu" << endl;
    cout << "3. Cari Lagu" << endl;
    cout << "4. Playlist" << endl;
    cout << "5. Keluar" << endl;

    int input_pilihan;
    cout << "Pilih Menu : "; cin >> input_pilihan;
    if(input_pilihan == 1){
        //now_playing();
    }else if(input_pilihan == 2){
        //tampilkan_lagu();
    }else if(input_pilihan == 3){
        //cari_lagu();
    }else if(input_pilihan == 4){
        //playlist();
    }else if(input_pilihan == 5){
        exit(0);
    }

    
}