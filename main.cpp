#include <iostream>
uisng namespace std;
#include auth.cpp

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
            login();

        } else if(pilihan == 2){
            register_user();
    
        } else if(pilihan == 3){
            cout << "Terima kasih telah menggunakan Leora. Sampai jumpa!" << endl;
            break; // Keluar dari loop
        } else {
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    }
}