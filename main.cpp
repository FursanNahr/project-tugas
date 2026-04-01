#include <iostream>
using namespace std;
#include "auth.cpp"

int main(){
    cout << "------- Hallo Selamat Datang di Leora ------" << endl;
    while(true){
        cout << "Pilih menu: " << endl;
        cout << "1. Login" << endl;
        cout << "2. Register" << endl;
        cout <<"3. Exit" << endl;
        int pilihan;

        cout << "Masukkan pilihan: ";
        cin >> pilihan;

        if(pilihan == 1){
            auto [username, role] = login();
            if(role == "admin"){
                cout << "Menu admin" << endl;
                //menu_admin(username);
            }
            else if(role == "user"){
                cout << "Menu user" << endl;
                //menu_user(username);
            }else{
                return 0;
            }

        } else if(pilihan == 2){
            register_user();
    
        } else if(pilihan == 3){
            cout << "Terima kasih telah menggunakan Leora. Sampai jumpa!" << endl;
            break; // buat keluar programnya
        } else {
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    }
}   