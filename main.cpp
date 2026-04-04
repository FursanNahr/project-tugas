#include <cstdlib>
#include <iostream>
using namespace std;
#include "header/admin.h"
#include "header/auth.h"
#include "header/lagu.h"
#include "header/user.h"

int main() {
    cout << "------- Hallo Selamat Datang di Leora ------" << endl;
    while (true) {
        system("cls");
        load_lagu();
        cout << "Pilih menu: " << endl;
        cout << "1. Login" << endl;
        cout << "2. Register" << endl;
        cout << "3. Exit" << endl;
        int pilihan;

        cout << "Masukkan pilihan: ";
        cin >> pilihan;
        if (pilihan == 1) {
            pair<string, string> hasil = login();

            string username = hasil.first;
            string role = hasil.second;

            if (role == "admin") {
                menu_admin(username);
            } else if (role == "user") {
                menu_user(username);
            } else {
                return 0;
            }

        } else if (pilihan == 2) {
            register_user();

        } else if (pilihan == 3) {
            cout << "Terima kasih telah menggunakan Leora. Sampai jumpa!" << endl;
            break;
        } else {
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    }
}