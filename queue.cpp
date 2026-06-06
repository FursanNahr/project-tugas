// clang-format off
#include <windows.h> 
#include <mmsystem.h>
// clang-format on
#include <conio.h>

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>

#include "header/admin.h"
#include "header/history.h"
#include "header/lagu.h"
#include "header/rekomendasi.h"
#include "header/tree.h"
using namespace std;

const int ukuran_queue = 100;
HANDLE mtx_antrian = CreateMutex(NULL, FALSE, NULL);

struct AutoLock {
    HANDLE mtx;
    AutoLock(HANDLE m) : mtx(m) { WaitForSingleObject(mtx, INFINITE); }
    ~AutoLock() { ReleaseMutex(mtx); }
};

extern void putar_lagu(Lagu lagu);

struct AntrianLagu {
    int top;
    int current_index;
    Lagu isi[ukuran_queue];
} antrian_lagu;

int isEmpty() {
    if (antrian_lagu.top == 0)
        return 1;
    else
        return 0;
}

int isFull() {
    if (antrian_lagu.top >= ukuran_queue)
        return 1;
    else
        return 0;
}

// ─── HELPER: cari Lagu lengkap dari daftar_lagu ───────────────────────────
// Mengembalikan pointer ke elemen daftar_lagu yang cocok, atau nullptr.
static Lagu* cari_lagu_lengkap(const string& judul, const string& penyanyi) {
    for (int i = 0; i < jumlah_lagu; i++) {
        if (daftar_lagu[i].judul == judul && daftar_lagu[i].penyanyi == penyanyi) {
            return &daftar_lagu[i];
        }
    }
    return nullptr;
}

// ─── HELPER: isi slot antrian dengan data lengkap (termasuk midi) ──────────
static void isi_slot(int slot, const string& judul, const string& penyanyi,
                     const string& mood, const string& genre) {
    Lagu* found = cari_lagu_lengkap(judul, penyanyi);
    if (found) {
        antrian_lagu.isi[slot] = *found;   // salin seluruh struct, termasuk midi
    } else {
        // fallback: isi manual (midi akan kosong, tidak ada MIDI yang diputar)
        antrian_lagu.isi[slot].judul    = judul;
        antrian_lagu.isi[slot].penyanyi = penyanyi;
        antrian_lagu.isi[slot].mood     = mood;
        antrian_lagu.isi[slot].genre    = genre;
        antrian_lagu.isi[slot].midi     = "";
    }
}

// ─── putar_sekarang ───────────────────────────────────────────────────────
// Langsung ganti lagu yang sedang diputar dan mulai MIDI-nya sekarang.
void putar_sekarang(string judul, string penyanyi, string mood, string genre) {
    AutoLock lock(mtx_antrian);

    if (isEmpty() == 1) {
        // Antrian kosong → tambah slot baru
        isi_slot(antrian_lagu.top, judul, penyanyi, mood, genre);
        antrian_lagu.top++;
        antrian_lagu.current_index = 0;
    } else {
        // Antrian sudah ada → timpa slot current
        isi_slot(antrian_lagu.current_index, judul, penyanyi, mood, genre);
    }

    push_stack(judul, penyanyi);
    catat_preferensi(mood, genre);

    // Putar MIDI sekarang juga
    putar_lagu(antrian_lagu.isi[antrian_lagu.current_index]);
}

// ─── tambah_antrean ───────────────────────────────────────────────────────
// Masukkan lagu ke belakang antrian (tidak langsung diputar).
void tambah_antrean(string judul, string penyanyi, string mood, string genre) {
    bool antrean_tadinya_kosong = (isEmpty() == 1);

    if (isFull() == 1) {
        cout << "Maaf, antrian lagu penuh!" << endl;
        Sleep(1500);
        return;
    }

    isi_slot(antrian_lagu.top, judul, penyanyi, mood, genre);
    antrian_lagu.top++;

    if (antrian_lagu.current_index == -1 || antrean_tadinya_kosong) {
        antrian_lagu.current_index = 0;

        for (int i = 0; i < jumlah_lagu; i++) {
            if (daftar_lagu[i].judul == judul && daftar_lagu[i].penyanyi == penyanyi) {
                putar_lagu(daftar_lagu[i]);
                break;
            }
        }
    }

    catat_preferensi(mood, genre);
}

// ─── next_lagu ────────────────────────────────────────────────────────────
void next_lagu() {
    AutoLock lock(mtx_antrian);
    if (isEmpty() == 1 || antrian_lagu.current_index == -1) {
        cout << "  Antrian kosong." << endl;
        Sleep(1500);
        return;
    }

    if (antrian_lagu.current_index >= antrian_lagu.top - 1) {
        cout << "  Tidak ada lagu berikutnya di antrean." << endl;
        Sleep(1500);
    } else {
        antrian_lagu.current_index++;
        int idx = antrian_lagu.current_index;
        push_stack(antrian_lagu.isi[idx].judul, antrian_lagu.isi[idx].penyanyi);
        putar_lagu(antrian_lagu.isi[idx]);
    }
}

// ─── prev_lagu ────────────────────────────────────────────────────────────
void prev_lagu() {
    AutoLock lock(mtx_antrian);
    if (isEmpty() == 1 || antrian_lagu.current_index == -1) {
        cout << "  Antrian kosong." << endl;
        Sleep(1500);
        return;
    }

    if (antrian_lagu.current_index <= 0) {
        cout << "  Ini sudah lagu pertama di antrean." << endl;
        Sleep(1500);
    } else {
        antrian_lagu.current_index--;
        int idx = antrian_lagu.current_index;
        push_stack(antrian_lagu.isi[idx].judul, antrian_lagu.isi[idx].penyanyi);
        putar_lagu(antrian_lagu.isi[idx]);
    }
}

// ─── sedang_diputar ───────────────────────────────────────────────────────
void sedang_diputar() {
    while (true) {
        system("cls");

        cout << "========== Now Playing ==========" << endl;

        WaitForSingleObject(mtx_antrian, INFINITE);

        bool is_kosong = (isEmpty() == 1 || antrian_lagu.current_index == -1);
        int idx = antrian_lagu.current_index;
        string judul_now = "", penyanyi_now = "";

        if (!is_kosong) {
            judul_now    = antrian_lagu.isi[idx].judul;
            penyanyi_now = antrian_lagu.isi[idx].penyanyi;
        }

        ReleaseMutex(mtx_antrian);

        if (is_kosong) {
            cout << "  ❌ Belum ada lagu yang diputar nih." << endl;
            cout << "     (Coba play dari menu Cari/Playlist)" << endl;
        } else {
            cout << "  🎶 Judul    : " << judul_now << endl;
            cout << "  🎤 Penyanyi : " << penyanyi_now << endl;

            char length_buf[128] = {0};
            char pos_buf[128]    = {0};
            char status_buf[128] = {0};

            mciSendStringA("set musik_cli time format milliseconds", NULL, 0, NULL);
            mciSendStringA("status musik_cli length",   length_buf, sizeof(length_buf), NULL);
            mciSendStringA("status musik_cli position", pos_buf,    sizeof(pos_buf),    NULL);
            mciSendStringA("status musik_cli mode",     status_buf, sizeof(status_buf), NULL);

            int total_len    = atoi(length_buf);
            int current_pos  = atoi(pos_buf);
            string cur_status = status_buf;

            if (total_len > 0) {
                int percent   = (current_pos * 100) / total_len;
                int bar_width = 30;
                int filled    = (percent * bar_width) / 100;

                if (cur_status.find("playing") != string::npos)
                    cout << "  ▶️  [";
                else if (cur_status.find("paused") != string::npos)
                    cout << "  ⏸️  [";
                else
                    cout << "  ⏹️  [";

                for (int i = 0; i < bar_width; i++) {
                    cout << (i < filled ? "█" : "-");
                }

                int cur_sec = (current_pos / 1000) % 60;
                int cur_min = (current_pos / 60000);
                int tot_sec = (total_len / 1000) % 60;
                int tot_min = (total_len / 60000);

                cout << "] " << setfill('0') << setw(2) << cur_min << ":"
                     << setfill('0') << setw(2) << cur_sec << " / "
                     << setfill('0') << setw(2) << tot_min << ":"
                     << setfill('0') << setw(2) << tot_sec;

                if (cur_status.find("paused") != string::npos) cout << " (PAUSED)";
                cout << endl;
            }
        }

        cout << "\n========== Queue Lagu ==========" << endl;

        WaitForSingleObject(mtx_antrian, INFINITE);

        if (isEmpty() == 1) {
            cout << "   (antrian kosong)" << endl;
        } else {
            for (int i = 0; i < antrian_lagu.top; i++) {
                if (i == antrian_lagu.current_index)
                    cout << ">> ";
                else
                    cout << "   ";
                cout << antrian_lagu.isi[i].judul << " - "
                     << antrian_lagu.isi[i].penyanyi << endl;
            }
        }

        ReleaseMutex(mtx_antrian);

        cout << "🎧 ═══════════════════════════════════ 🎧" << endl;
        cout << "  Kontrol Musik:" << endl;
        cout << "  [1] ⏭️  Next" << endl;
        cout << "  [2] ⏮️  Previous" << endl;
        cout << "  [3] ⏸️/▶️  Pause / Resume" << endl;
        cout << "  ───────────────────────────────────" << endl;
        cout << "  [0] 🔙 Kembali" << endl;
        cout << "=======================================" << endl;
        cout << "(Pilih menu (angka 0, 1, 2, atau 3):\n";

        int timer   = 0;
        int pilihan = -1;

        while (timer < 10) {
            if (_kbhit()) {
                char ch = _getch();
                if      (ch == '0') pilihan = 0;
                else if (ch == '1') pilihan = 1;
                else if (ch == '2') pilihan = 2;
                else if (ch == '3') pilihan = 3;
            }
            Sleep(100);
            timer++;
        }

        if (pilihan == 0) {
            break;
        } else if (pilihan == 1) {
            next_lagu();
        } else if (pilihan == 2) {
            prev_lagu();
        } else if (pilihan == 3) {
            char status_check[128] = {0};
            mciSendStringA("status musik_cli mode", status_check, sizeof(status_check), NULL);
            string check_mode = status_check;

            if (check_mode.find("playing") != string::npos) {
                mciSendStringA("pause musik_cli", NULL, 0, NULL);
            } else {
                mciSendStringA("play musik_cli", NULL, 0, NULL);
            }
        }
    }
}