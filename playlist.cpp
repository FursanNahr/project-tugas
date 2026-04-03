#include <iostream>
using namespace std;

struct Playlist {
    string judul_playlist;
    string pemilik;
    int isi_lagu[50];
    int jumlah_lagu;
};

Playlist semua_playlist[100];
int total_playlist = 0;

void playlist(string username) {
    while (true) {
        cout << "\n -----------Playlist----------" << endl;
        cout << "1. Buat Playlist";
        cout << "2. Tampilkan Playlist";
        cout << "3. Cari Lagu di Playlist";
        int input_user;
        cin >> input_user;

        if (input_user == 1) {
            string input;
            cout << "Masukkan nama playlist : ";
            getline(cin, input);
            semua_playlist[total_playlist].judul_playlist = input;
        } else if (input_user == 2) {
            if (total_playlist == 0) {
                cout << "Tidak ada playlist!" << endl;
            } else {
                for (int i = 0; i < total_playlist; i++) {
                    cout << i + 1 << ". " << semua_playlist[i].judul_playlist << endl;
                }
                cout << "1. Pilih Playlist" << endl;
                cout << "2. Hapus Playlist" << endl;
                cout << "Pilih opsi : ";
                cin >> input_user;
                if (input_user == 1) {
                    cout << "Pilih Playlist";
                }
            }
        } else if (input_user == 3) {
        }
    }
}