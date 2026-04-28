#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 1. STRUCT: Entitas utama kendaraan 
struct DataKendaraan {
    string nomorPlat;
    int jenisKendaraan; // 1 untuk Motor, 2 untuk Mobil
    float waktuMasuk;
};

// 4. NAMESPACE: Membungkus logika utama agar rapi [cite: 23]
namespace LogikaParkir {
    
    // 6. INLINE FUNCTION: Optimasi kinerja untuk fungsi pendek [cite: 27]
    inline void sapaPengguna(string pesan = "Selamat Datang di Sistem Parkir") { // 6. DEFAULT ARGUMENT [cite: 26]
        cout << "\n>>> " << pesan << " <<<" << endl;
    }

    // 7. FUNCTION OVERLOADING: Nama sama, parameter berbeda 
    void cetakGaris() { 
        cout << "------------------------------------------" << endl; 
    }
    void cetakGaris(char simbol, int jumlah) { 
        for(int i = 0; i < jumlah; i++) cout << simbol;
        cout << endl;
    }

    // Fungsi perhitungan biaya
    float biayaMotor(float durasi) { return durasi * 2000; }
    float biayaMobil(float durasi) { return durasi * 5000; }

    // 5. CALLBACK FUNCTION: Menerima fungsi lain sebagai parameter 
    float eksekusiHitung(float d, float (*kalkulator)(float)) {
        return kalkulator(d);
    }
}

// 3. REFERENCES (&): Menghindari penyalinan data berat 
void tampilkanStruk(const DataKendaraan &k, float durasi, float total) {
    LogikaParkir::cetakGaris('=', 30);
    cout << "      STRUK BIAYA PARKIR      " << endl;
    LogikaParkir::cetakGaris();
    cout << "Nomor Plat : " << k.nomorPlat << endl;
    cout << "Durasi     : " << durasi << " Jam" << endl;
    cout << "Total Bayar: Rp " << total << endl;
    LogikaParkir::cetakGaris('=', 30);
}

int main() {
    DataKendaraan parkir[100]; 
    int jumlahKendaraan = 0;
    int pilihanMenu;

    LogikaParkir::sapaPengguna(); // Menggunakan default argument

    do {
        cout << "\n1. Kendaraan Masuk\n2. Kendaraan Keluar\n3. Selesai\nPilih: ";
        cin >> pilihanMenu;

        if (pilihanMenu == 1) {
            if (jumlahKendaraan < 100) {
                cout << "Input Nomor Plat: ";
                cin.ignore();
                getline(cin, parkir[jumlahKendaraan].nomorPlat);
                cout << "Jenis (1. Motor, 2. Mobil): ";
                cin >> parkir[jumlahKendaraan].jenisKendaraan;
                cout << "Waktu Masuk (Jam): ";
                cin >> parkir[jumlahKendaraan].waktuMasuk;
                
                jumlahKendaraan++;
                cout << "Data tersimpan!" << endl;
            }
        } 
        else if (pilihanMenu == 2) {
            string platCari;
            cout << "Input Plat Keluar: ";
            cin.ignore();
            getline(cin, platCari);

            int index = -1;
            for (int i = 0; i < jumlahKendaraan; i++) {
                if (parkir[i].nomorPlat == platCari) {
                    index = i;
                    break;
                }
            }

            if (index != -1) {
                // 2. POINTER (*): Manipulasi alamat memori 
                DataKendaraan* ptrK = &parkir[index]; 
                
                float waktuKeluar, total = 0;
                cout << "Waktu Keluar: ";
                cin >> waktuKeluar;
                float durasi = waktuKeluar - ptrK->waktuMasuk;

                // Menggunakan Callback logic
                if (ptrK->jenisKendaraan == 1) {
                    total = LogikaParkir::eksekusiHitung(durasi, LogikaParkir::biayaMotor);
                } else {
                    total = LogikaParkir::eksekusiHitung(durasi, LogikaParkir::biayaMobil);
                }

                tampilkanStruk(*ptrK, durasi, total);
            } else {
                cout << "Data tidak ditemukan!" << endl;
            }
        }
    } while (pilihanMenu != 3);

    LogikaParkir::sapaPengguna("Terima Kasih");
    return 0;
}