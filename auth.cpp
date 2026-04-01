#include <iostream>
using namespace std;

struct user {
    string username;
    string password;
    string role;
};

int jumlah_user = 0;
user daftar_user[100]; 

void register_user() {
    string cek_username, cek_password, cek_role;
    cout << "Masukkan username: "; cin >> cek_username;
    cout << "Masukkan password: "; cin >> cek_password;
    while(true){
        cout << "Masukkan role (admin/user): "; cin >> cek_role;
        if(cek_role == "admin" || cek_role == "user"){
            daftar_user[jumlah_user].username = cek_username;
            daftar_user[jumlah_user].password = cek_password;
            daftar_user[jumlah_user].role = cek_role;
            jumlah_user++;
            break; 
            
        } else {
            cout << "Role tidak valid. Silakan masukkan 'admin' atau 'user'." << endl;
        }
    }

    cout << "User berhasil didaftarkan!" << endl;
}

pair<string, string> login(){
    string username, password;
    cout << "--------- SELAMAT DATANG DI LEORA SILAHKAN LOGIN ---------" << endl;
    int kesempatan = 0;

    while(kesempatan < 3){
        
        cout << "Username : "; cin >> username;
        cout << "Password : "; cin >> password;
        for(int i=0; i<jumlah_user; i++){
            if(username == daftar_user[i].username && password == daftar_user[i].password){
                cout << "Login Berhasil Sebagai" << daftar_user[i].role << endl;
                return {daftar_user[i].username, daftar_user[i].role};
            }
        }
        kesempatan++;
        cout << "Username atau Password Salah! (Sisa percobaan: " << 3 - kesempatan << ")" << endl;   
        
    }
    cout << "Login gagal! Kesempatan anda sudah habis." << endl;
    return {"", ""}; 
}

