#include <iostream>
#include <string>

using namespace std;

// 1. STRUCT: Entitas utama kendaraan
struct DataKendaraan {
    string nomorPlat;
    int jenisKendaraan; // 1 untuk Motor, 2 untuk Mobil
    float waktuMasuk;
};

// 4. NAMESPACE: Membungkus logika utama 
namespace LogikaParkir {
    
    // 6. INLINE FUNCTION: Fungsi pendek untuk efisiensi 
    inline void sapaPengguna(string pesan = "Selamat Datang di Sistem Parkir") { // 6. DEFAULT ARGUMENT 
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

    // Fungsi logika perhitungan
    float biayaMotor(float durasi) { return durasi * 2000; }
    float biayaMobil(float durasi) { return durasi * 5000; }

    // 5. CALLBACK FUNCTION: Menerima fungsi lain sebagai argumen 
    float eksekusiHitung(float d, float (*kalkulator)(float)) {
        return kalkulator(d);
    }
}

// 3. REFERENCES (&): Akses data tanpa copy 
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
    // Menggunakan Array Statis 
    DataKendaraan parkir[100]; 
    int jumlahKendaraan = 0;
    int pilihanMenu;

    LogikaParkir::sapaPengguna(); // Menggunakan Default Argument

    do {
        cout << "\n1. Kendaraan Masuk" << endl;
        cout << "2. Kendaraan Keluar" << endl;
        cout << "3. Selesai" << endl;
        cout << "Pilih Menu: ";
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
            } else {
                cout << "Parkiran Penuh!" << endl;
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
                // 2. POINTER (*): Navigasi data pada struct 
                DataKendaraan* ptrK = &parkir[index]; 
                
                float waktuKeluar, total = 0;
                cout << "Waktu Keluar: ";
                cin >> waktuKeluar;
                float durasi = waktuKeluar - ptrK->waktuMasuk;

                // Menggunakan Logika Callback
                if (ptrK->jenisKendaraan == 1) {
                    total = LogikaParkir::eksekusiHitung(durasi, LogikaParkir::biayaMotor);
                } else {
                    total = LogikaParkir::eksekusiHitung(durasi, LogikaParkir::biayaMobil);
                }

                // Memanggil fungsi dengan Reference
                tampilkanStruk(*ptrK, durasi, total);
            } else {
                cout << "Data tidak ditemukan!" << endl;
            }
        }
    } while (pilihanMenu != 3);

    LogikaParkir::sapaPengguna("Terima Kasih, Program Selesai");
    return 0;
}
