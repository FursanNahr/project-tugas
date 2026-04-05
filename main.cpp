#include <windows.h>

#include <cstdlib>
#include <iostream>
using namespace std;
#include "header/admin.h"
#include "header/auth.h"
#include "header/lagu.h"
#include "header/user.h"

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    while (true)
    {
        system("cls");
        load_lagu();
        cout << "\n🎵 ═════════════════════════════════════════ 🎵" << endl;
        cout << " ✨       HALLO, SELAMAT DATANG DI LEORA!   ✨" << endl;
        cout << "🎵 ═════════════════════════════════════════ 🎵" << endl;
        cout << "  Silakan pilih menu untuk mulai:" << endl;
        cout << "  [1] 🔐 Login" << endl;
        cout << "  [2] 📝 Register" << endl;
        cout << "  ─────────────────────────────────────────" << endl;
        cout << "  [3] 🚪 Exit" << endl;
        cout << "===========================================" << endl;
        cout << "👉 Pilihan kamu (1-3): ";
        int pilihan;

        cout << "Masukkan pilihan: ";
        cin >> pilihan;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');

            cout << "❌ Input harus angka! Coba lagi.\n";
            continue;
        }

        if (pilihan == 1)
        {
            pair<string, string> hasil = login();

            string username = hasil.first;
            string role = hasil.second;

            if (role == "admin")
            {
                menu_admin(username);
            }
            else if (role == "user")
            {
                menu_user(username);
            }
            else
            {
                return 0;
            }
        }
        else if (pilihan == 2)
        {
            register_user();
        }
        else if (pilihan == 3)
        {
            cout << "Terima kasih telah menggunakan Leora. Sampai jumpa!" << endl;
            break;
        }
        else
        {
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    }
}