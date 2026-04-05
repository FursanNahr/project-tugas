#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>

#include "header/playlist.h"
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

        cout << "\n📝 ═════════════ REGISTRASI ═════════════ 📝" << endl;
        cout << "    (Ketik '0' kapan saja untuk batal)" << endl;
        cout << "────────────────────────────────────────────" << endl;

        cout << "  👤 Username : ";
        cin >> username;

        if (username == "0") {
            return;
        }
        if (username_sudah_ada(username)) {
            cout << "❌ ERROR: Username '" << username << "' sudah digunakan! Cari nama lain ya." << endl;
            pause();
        } else {
            break;
        }
    }

    while (true) {
        cout << "  🔑 Password : ";
        cin >> password;

        if (password == "0") {
            return;
        }
        if (validasi_password(password)) {
            break;
        } else {
            cout << "❌ ERROR: Password minimal 8 karakter, wajib mengandung huruf besar, huruf kecil, dan angka!" << endl;
            pause();
        }
    }
    cout << "────────────────────────────────────────────" << endl;

    while (true) {
        cout << "  🎭 Pilih Role (admin/user) : ";
        cin >> role;
        if (role == "admin" || role == "user") {
            break;
        } else {
            cout << "❌ ERROR: Role tidak valid! Tolong ketik 'admin' atau 'user'." << endl;
            pause();
        }
    }

    ofstream file("data_user.txt", ios::app);
    file << username << " " << password << " " << role << endl;
    file.close();

    cout << "============================================" << endl;
    cout << "✅ BERHASIL! Akun '" << username << "' (" << role << ") telah didaftarkan." << endl;
    pause();
}

pair<string, string> login() {
    string username, password;

    int kesempatan = 0;

    while (kesempatan < 3) {
        system("cls");

        cout << "\n🔐 ═════════════ LOGIN SYSTEM ═════════════ 🔐" << endl;
        cout << "   (Ketik '0' pada Username untuk kembali)" << endl;
        cout << "──────────────────────────────────────────────" << endl;
        cout << "  👤 Username : ";
        cin >> username;
        if (username == "0")
            return {"", ""};

        cout << "  🔑 Password : ";
        cin >> password;

        ifstream file("data_user.txt");
        string u, p, r;
        bool ketemu = false;

        while (file >> u >> p >> r) {
            if (username == u && password == p) {
                cout << "\n✅ Akses Diterima! Selamat datang, " << u << " (" << r << ")." << endl;
                file.close();
                pause();
                return {u, r};
            }
        }

        file.close();

        kesempatan++;
        cout << "\n❌ ERROR: Username atau Password salah!" << endl;
        cout << "⚠️  Sisa percobaan login: " << 3 - kesempatan << " kali." << endl;
        pause();
    }

    cout << "\n🚫 ══════════ AKSES DITOLAK ══════════ 🚫" << endl;
    cout << "  Anda telah gagal login sebanyak 3 kali." << endl;
    cout << "  Silakan coba lagi nanti." << endl;
    cout << "=========================================" << endl;
    pause();
    return {"", ""};
}