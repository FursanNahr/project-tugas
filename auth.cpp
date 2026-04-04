#include <fstream>
#include <iostream>
using namespace std;

struct user {
    string username;
    string password;
    string role;
};

void register_user() {
    string username, password, role;

    cout << "===== REGISTER =====" << endl;
    cout << "Masukkan username: ";
    cin >> username;
    cout << "Masukkan password: ";
    cin >> password;

    while (true) {
        cout << "Masukkan role (admin/user): ";
        cin >> role;
        if (role == "admin" || role == "user") {
            break;
        } else {
            cout << "Role tidak valid! (admin/user)" << endl;
        }
    }

    // simpan ke file
    ofstream file("data_user.txt", ios::app);  // append biar nambah
    file << username << " " << password << " " << role << endl;
    file.close();

    cout << "User berhasil didaftarkan!\n"
         << endl;
}

pair<string, string> login() {
    string username, password;
    cout << "===== LOGIN =====" << endl;

    int kesempatan = 0;

    while (kesempatan < 3) {
        cout << "Username : ";
        cin >> username;
        cout << "Password : ";
        cin >> password;

        ifstream file("data_user.txt");
        string u, p, r;
        bool ketemu = false;

        while (file >> u >> p >> r) {
            if (username == u && password == p) {
                cout << "Login berhasil sebagai " << r << endl;
                file.close();
                return {u, r};
            }
        }

        file.close();

        kesempatan++;
        cout << "Username atau Password salah! (Sisa: "
             << 3 - kesempatan << ")" << endl;
    }

    cout << "Login gagal!\n"
         << endl;
    return {"", ""};
}