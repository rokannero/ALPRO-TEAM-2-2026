#include <iostream>
#include <iomanip>
#include <vector>
#include <ctime>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
using namespace std;

class Obat {
private:
	string namaCari;
	
    string kodeObat;
    string namaObat;
    double harga;
    int stok;
    string tanggalExpired;
    string kategori;
    string satuan;

public:
	string getkodeObat(){
		return kodeObat;
	}
	string getnamaObat(){
		return namaObat;
	}
    double getHarga(){
    	return harga;
	}
    int getStok(){
    	return stok;
	}
    string gettanggalExpired(){
    	return tanggalExpired;
	}
    string getKategori(){
    	return kategori;
	}
    string getSatuan(){
    	return satuan;
	}
    
bool cariObat(string namaCari){
    ifstream file("daftar_obat.txt");
    string line;

    if(!file.is_open()){
        return false;
    }

    while(getline(file, line)){
        stringstream ss(line);

        string kode;
        string nama;
        string hargaStr;
        string stokStr;
        string exp;
        string kat;
        string sat;

        getline(ss, kode, '|');
        getline(ss, nama, '|');
        getline(ss, hargaStr, '|');
        getline(ss, stokStr, '|');
        getline(ss, exp, '|');
        getline(ss, kat, '|');
        getline(ss, sat, '|');

        if(nama == namaCari){

            kodeObat = kode;
            namaObat = nama;
            harga = atof(hargaStr.c_str());
            stok = atoi(stokStr.c_str());
            tanggalExpired = exp;
            kategori = kat;
            satuan = sat;

            file.close();
            return true;
        }
    }

    file.close();
    return false;
}	
    
    void inputObat(){
    	ofstream file("daftar_obat.txt", ios::app);

	    if (file.is_open()) {
	    	
			cout << "Masukkan Kode Obat : ";
	    	cin >> kodeObat;
	    	cin.ignore();
			cout << "Masukkan Nama Obat : ";
			getline(cin, namaObat);
			cout << "Masukkan Harga Obat :";
			cin >> harga;
			cout << "Masukkan Stok Obat :";
			cin >> stok;
			cout << "Masukkan Tanggal Expired Obat (Tgl/Bln/Thn):";
			cin >> tanggalExpired;
			cout << "Masukkan Kategori Obat :";
			cin >> kategori;
			cout << "Masukkan Satuan Obat per kaplet/tablet :";
			cin >> satuan;
			
	        file << kodeObat << "|"
	             << namaObat << "|"
	             << harga << "|"
	             << stok << "|"
	             << tanggalExpired << "|"
	             << kategori << "|"
	             << satuan << "\n";
	
	        file.close();
	    } 
	    else {
	        cout << "File tidak bisa dibuka!\n";
	    }
	}
//    void tampilObat(){
//    	cout << kodeObat << "|"
//	         << namaObat << "|"
//	         << harga << "|"
//	         << stok << "|"
//	         << tanggalExpired << "|"
//	         << kategori << "|"
//	         << satuan << "|" << endl;
//	}	
    void updateStok(int jumlah);
    void tambahStok(int jumlah);
    void kurangiStok(int jumlah);

    bool cekKadaluarsa();
    bool stokMenipis();

    void ubahHarga();
    void ubahDataObat();

    void simpanData(){
    	ofstream file("daftar_obat.txt", ios::app);

	    if (file.is_open()) {
	    	cout << "Masukkan Kode Obat : ";
	    	cin >> kodeObat;
	    	cin.ignore();
			cout << "Masukkan Nama Obat : ";
			getline(cin, namaObat);
			
	        file << kodeObat << "|"
	             << namaObat << "|"
	             << harga << "|"
	             << stok << "|"
	             << tanggalExpired << "|"
	             << kategori << "|"
	             << satuan << "\n";
	
	        file.close();
	    } 
	    else {
	        cout << "File tidak bisa dibuka!\n";
	    }
	}
	
    void bacaData(){	//membaca dan menampilkan data di file.txt
    	 ifstream file("daftar_obat.txt");

	    string line;
	
	    if (!file.is_open()) {
	        cout << "File tidak ditemukan!" << endl;
	        return;
	    }
	
	    cout << "KODE|NAMA|HARGA|STOK|TGL EXP|KATEGORI|SATUAN|" << endl << endl;
	
	    while (getline(file, line)) {
	
	        string temp = "";
	        int field = 0;
	
	        kodeObat = "";
	        namaObat = "";
	        tanggalExpired = "";
	        kategori = "";
	        satuan = "";
	
	        string tempHarga = "";
	        string tempStok = "";
	
	        for (int i = 0; i < line.length(); i++) {
	
	            if (line[i] == '|') {
	                field++;
	                temp = "";
	            } 
	            else {
	                if (field == 0) kodeObat += line[i];
	                else if (field == 1) namaObat += line[i];
	                else if (field == 2) tempHarga += line[i];
	                else if (field == 3) tempStok += line[i];
	                else if (field == 4) tanggalExpired += line[i];
	                else if (field == 5) kategori += line[i];
	                else if (field == 6) satuan += line[i];
	            }
	        }
	
	        harga = atof(tempHarga.c_str());
	        stok  = atoi(tempStok.c_str());
	
	        cout << kodeObat << "|"
	             << namaObat << "|"
	             << harga << "|"
	             << stok << "|"
	             << tanggalExpired << "|"
	             << kategori << "|"
	             << satuan << "|" << endl << endl;
	    }
	
	    file.close();
	}
};

class Transaksi {
	private:
		Obat getObat;
		string namaObat; //sementara
		
	    string idTransaksi;
	    string tanggal;
	    vector<Obat> daftarObat;
	    vector<int> jumlahBeli;
	    double totalPembayaran;
	
	public:
	    void inputTransaksi();
	    void prosesPembayaran();
	    string cetakWaktu() {
	    time_t sekarang = time(0);
	    tm *waktu = localtime(&sekarang);
	
	    stringstream ss;
	
	    ss << setfill('0')
	       << setw(2) << waktu->tm_hour << ":"
	       << setw(2) << waktu->tm_min;
	
	    return ss.str();
	}
	
	string cetakTanggal() {
	    time_t sekarang = time(0);
	    tm *waktu = localtime(&sekarang);
	
	    stringstream ss;
	
	    ss << setfill('0')
	       << setw(2) << waktu->tm_mday << "/"
	       << setw(2) << waktu->tm_mon + 1 << "/"
	       << waktu->tm_year + 1900;
	
	    return ss.str();
	}
	
	void pilihObat() {

	    cout << "Masukkan Nama Obat : ";
	    getline(cin >> ws, namaObat);
	
	    if (getObat.cariObat(namaObat)) {
	
	        cout << "\nObat ditemukan!\n";
	        cout << "Nama     : " << getObat.getnamaObat() << endl;
	        cout << "Harga    : " << getObat.getHarga() << endl;
	        cout << "Stok     : " << getObat.getStok() << endl;
	
	    } else {
	
	        cout << "Obat tidak ditemukan!\n";
	
	    }
	    system("pause");
	    system("cls");
	}
	
	void cetakStruk() {

	pilihObat();
    cout << "\n\n===== APOTEK K24 WIROSABAN =====\n";
    cout << "Jl. Sorogenen, KP Nitikan 240\n";
    cout << "Telp : 0274-450893\n";
    cout << "	KASIR 1\n";
    cout << "----- " << cetakTanggal()
         << " " << cetakWaktu()
         << " -----\n";
         
    cout << "---------------------------------------\n";
    cout << "Nama Obat : " << getObat.getnamaObat() << endl;
    cout << "Kategori  : " << getObat.getKategori() << endl;
    cout << "Satuan    : " << getObat.getSatuan() << endl;
    cout << "Harga     : Rp " << getObat.getHarga() << endl;
    cout << "---------------------------------------\n";
}

    double hitungTotal();
    void simpanRiwayat();
    void tampilRiwayat();

    void batalkanTransaksi();
    void refundTransaksi();

    string getIDTransaksi();
    double getTotal();
};

int main(){
	Transaksi transaksi;
	Obat obat;
//	obat.inputObat(); //Fungsi untuk menginput obat baru ke dalam file.txt
	obat.bacaData();
	
	transaksi.cetakStruk();	
}
