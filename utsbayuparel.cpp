#include <iostream>
#include <string>

using namespace std;

// DEKLARASI STRUCT
struct DataKendaraan {
    string nomorPlat;
    int jenisKendaraan; // 1 untuk Motor, 2 untuk Mobil
    float waktuMasuk;   // Format jam (misal 8.00)
};

// PENYIMPANAN GLOBAL (Array Biasa)
DataKendaraan parkir[100]; 
int jumlahKendaraan = 0;   

// FUNGSI MENGHITUNG BIAYA MOTOR
float hitungBiayaMotor(float durasi) {
    float biaya = durasi * 2000;
    return biaya;
}

// FUNGSI MENGHITUNG BIAYA MOBIL
float hitungBiayaMobil(float durasi) {
    float biaya = durasi * 5000;
    return biaya;
}

int main() {
    int pilihanMenu;
    
    // MULAI LOOPING MENU UTAMA
    do {
        cout << "\n=== MENU UTAMA PARKIR ===" << endl;
        cout << "1. Kendaraan Masuk" << endl;
        cout << "2. Kendaraan Keluar" << endl;
        cout << "3. Selesai" << endl;
        cout << "Pilih menu: ";
        cin >> pilihanMenu;
        
        if (pilihanMenu == 1) {
            // PROSES KENDARAAN MASUK (Check-In)
            if (jumlahKendaraan < 100) {
                cout << "\n=== KENDARAAN MASUK (Check-In) ===" << endl;
                
                cout << "Input Nomor Plat (e.g. B1234ABC): ";
                cin.ignore(); // Membersihkan sisa enter dari cin sebelumnya
                getline(cin, parkir[jumlahKendaraan].nomorPlat);
                
                cout << "Input Jenis Kendaraan (1. Motor, 2. Mobil): ";
                cin >> parkir[jumlahKendaraan].jenisKendaraan;
                
                cout << "Input Waktu Masuk (Jam) (e.g., 8.00): ";
                cin >> parkir[jumlahKendaraan].waktuMasuk;
                
                jumlahKendaraan = jumlahKendaraan + 1;
                cout << "Data berhasil disimpan!" << endl;
            } else {
                cout << "Kapasitas parkir penuh!" << endl;
            }
            
        } else if (pilihanMenu == 2) {
            // PROSES KENDARAAN KELUAR (Check-Out)
            string platKeluar;
            cout << "\n=== KENDARAAN KELUAR (Check-Out) ===" << endl;
            cout << "Input Nomor Plat Keluar: ";
            cin.ignore();
            getline(cin, platKeluar);
            
            // Cari Data Plat
            bool ditemukan = false;
            int indexDitemukan = -1;
            
            for (int i = 0; i < jumlahKendaraan; i++) {
                if (parkir[i].nomorPlat == platKeluar) {
                    ditemukan = true;
                    indexDitemukan = i;
                    break;
                }
            }
            
            // Pengecekan Hasil Pencarian
            if (!ditemukan) {
                cout << "Data Tidak Ada" << endl;
            } else {
                float waktuKeluar;
                cout << "Input Waktu Keluar (Jam) (e.g., 14.00): ";
                cin >> waktuKeluar;
                
                // Hitung Durasi
                float durasi = waktuKeluar - parkir[indexDitemukan].waktuMasuk;
                
                // Cek Total Biaya Jenis Kendaraan  untuk Memanggil Fungsi yang Sesuai
                float totalBiaya = 0;
                int jenis = parkir[indexDitemukan].jenisKendaraan;
                
                if (jenis == 1) {
                    totalBiaya = hitungBiayaMotor(durasi);
                } else if (jenis == 2) {
                    totalBiaya = hitungBiayaMobil(durasi);
                }
                
                // Tampilkan Struk
                cout << "\n--- STRUK BIAYA PARKIR ---" << endl;
                cout << "Nomor Plat : " << parkir[indexDitemukan].nomorPlat << endl;
                cout << "Durasi     : " << durasi << " Jam" << endl;
                cout << "Total Biaya: Rp " << totalBiaya << endl;
                cout << "--------------------------" << endl;
            }
            
        } else if (pilihanMenu == 3) {
            cout << "Program Selesai" << endl;
        } else {
            cout << "Pilihan tidak valid, silakan coba lagi." << endl;
        }
        
    } while (pilihanMenu != 3);
    
    return 0;
}