#include <cstdlib>
#include <iostream>
#include <string>
#include <limits>

#include "lagu.cpp"
#include "playlist.cpp"
// #include "queue.cpp"
using namespace std;

void menu_user(string username)
{
    while (true)
    {
        system("cls");

        cout << "\n==========================================" << endl;
        cout << "   Selamat Datang " << username << " di LEORA" << endl;
        cout << "==========================================" << endl;
        cout << "0. Logout" << endl;
        cout << "1. Now Playing" << endl;
        cout << "2. Tampilkan Semua Lagu" << endl;
        cout << "3. Cari Lagu" << endl;
        cout << "4. Playlist" << endl;

        int input_pilihan;
        cout << "Pilih Menu : ";
        cin >> input_pilihan;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input harus angka! \n";
            continue;
        }

        switch (input_pilihan)
        {
        case 1:
            sedang_diputar();
            break;
        case 2:
            tampilkan_lagu();
            break;
        case 3:
            cari_lagu();
            break;
        case 4:
            playlist(username);
            break;
        case 0:
            return;
        default:
            cout << "Pilihan tidak valid.";
        }
    }
}
