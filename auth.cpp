#include <iostream>
using namespace std;

struct user {
    string username;
    string password;
    string role;
};

jumlah_user = 0;
user daftar_user[100]; 

void register_user() {
    user daftar_user;
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

int main(){

}