#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
using namespace std;

struct user {
    string username;
    string password;
    string role;
};

bool username_sudah_ada(string username) {
    ifstream file("data_user.txt");
    string u, p, r;

    while (file >> u >> p >> r) {
        if (u == username) {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

bool validasi_password(string pass) {
    if (pass.length() < 8)
        return false;

    bool ada_besar = false, ada_kecil = false, ada_angka = false;

    for (char c : pass) {
        if (isupper(c))
            ada_besar = true;
        else if (islower(c))
            ada_kecil = true;
        else if (isdigit(c))
            ada_angka = true;
    }

    return ada_besar && ada_kecil && ada_angka;
}

void register_user() {
    string username, password, role;

    while (true) {
        system("cls");

        cout << "========== REGISTER ==========" << endl;
        cout << "Masukkan username (0 untuk kembali): ";
        cin >> username;

        if (username == "0") {
            return;
        }
        if (username_sudah_ada(username)) {
            cout << "Username sudah digunakan!" << endl;
            cout << "Tekan Enter untuk lanjut...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        } else {
            break;
        }
    }

    while (true) {
        cout << "Masukkan password (0 untuk kembali): ";
        cin >> password;

        if (password == "0") {
            return;
        }
        if (validasi_password(password)) {
            break;
        } else {
            cout << "Password harus 8 angka, ada huruf kecil & besar, dan angka!" << endl;
            cout << "Tekan Enter untuk lanjut...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
    }

    while (true) {
        cout << "Masukkan role (admin/user): ";
        cin >> role;
        if (role == "admin" || role == "user") {
            break;
        } else {
            cout << "Role tidak valid! (admin/user)" << endl;
        }
    }

    ofstream file("data_user.txt", ios::app);
    file << username << " " << password << " " << role << endl;
    file.close();

    cout << "User berhasil didaftarkan!\n"
         << endl;
    cout << "Tekan Enter untuk lanjut...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

pair<string, string> login() {
    string username, password;

    int kesempatan = 0;

    while (kesempatan < 3) {
        system("cls");

        cout << "========== LOGIN ==========" << endl;
        cout << "Username (0 untuk kembali): ";
        cin >> username;
        if (username == "0")
            return {"", ""};

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
        cout << "Tekan Enter untuk lanjut...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }

    cout << "Login gagal!\n"
         << endl;
    return {"", ""};
}