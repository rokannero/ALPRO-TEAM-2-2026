#include <iostream>
#include <iomanip>
#include <vector>
#include <ctime>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <algorithm> // baru
#include <cctype> // baru
using namespace std;

void header(string judul);

class User {
	private :
		string idUser;
		string nama;
		string username;
		string password;
		string role;
		bool statusLogin;
	
	public :
		User()
    {
        idUser = "";
        nama = "";
        username = "";
        password = "";
        role = "";
    }

    User(string id, string n, string user, string pass, string r)
    {
        idUser = id;
        nama = n;
        username = user;
        password = pass;
        role = r;
    }

    // =========================
    // Setter
    // =========================
    void setIdUser(string id)
    {
        idUser = id;
    }

    void setNama(string n)
    {
        nama = n;
    }

    void setUsername(string user)
    {
        username = user;
    }

    void setPassword(string pass)
    {
        password = pass;
    }

    void setRole(string r)
    {
        role = r;
    }

    // =========================
    // Getter
    // =========================
    string getIdUser()
    {
        return idUser;
    }

    string getNama()
    {
        return nama;
    }

    string getUsername()
    {
        return username;
    }

    string getPassword()
    {
        return password;
    }

    string getRole()
    {
        return role;
    }

    // =========================
    // Output
    // =========================
    void tampil()
    {
        cout << "ID User  : " << idUser << endl;
        cout << "Nama     : " << nama << endl;
        cout << "Username : " << username << endl;
        cout << "Role     : " << role << endl;
    }
};

//	=======================================
//	Void Diluar Class Untuk Registrasi User
//	=======================================
		User user[100];
		int jumlahUser = 0;
		int loginIndex = -1;
		
		void simpanUserKeFile(User user[], int jumlahUser) 
		{
			ofstream file("user_data.txt");

			if (!file.is_open()) 
			{
				cout << "Gagal membuka file untuk menyimpan data!\n";
				return;
			}

			for (int i = 0; i < jumlahUser; i++) 
			{
				file << user[i].getIdUser() << "|"
					<< user[i].getNama() << "|"
					<< user[i].getUsername() << "|"
					<< user[i].getPassword() << "|"
					<< user[i].getRole() << endl;
			}

			file.close();
		}

		void bacaUserDariFile(User user[], int &jumlahUser) 
		{
			ifstream file("user_data.txt");

			if (!file.is_open()) 
			{
				jumlahUser = 0;
				return;
			}

			jumlahUser = 0;

			string id, nama, username, password, role;

			while (
				getline(file, id, '|') &&
				getline(file, nama, '|') &&
				getline(file, username, '|') &&
				getline(file, password, '|') &&
				getline(file, role)
			) {
				if (jumlahUser >= 100)
				{
					break;
				}

				user[jumlahUser].setIdUser(id);
				user[jumlahUser].setNama(nama);
				user[jumlahUser].setUsername(username);
				user[jumlahUser].setPassword(password);
				user[jumlahUser].setRole(role);

				jumlahUser++;
			}

			file.close();
		}

		string generateIdUser(int jumlahUser) 
		{
			//MENGGUNAKAN LIBRARY STRING UNTUK MENGUBAH NOMOR MENJADI STRING (to_string (nomor))
			int nomor = jumlahUser + 1;

			if (nomor < 10) {
				return "USR00" + to_string(nomor);
			} else if (nomor < 100) {
				return "USR0" + to_string(nomor);
			} else {
				return "USR" + to_string(nomor);
			}
		}

		void inputUser(User user[], int &jumlahUser) 
		{
			string id, nama, username, password, role;

			id = generateIdUser(jumlahUser);

			cout << "===== REGISTRASI AKUN USER =====\n";
			cout << "ID User   : " << id << endl;

			cout << "Nama      : ";
			getline(cin, nama);

			cout << "Username  : ";
			getline(cin, username);

			cout << "Password  : ";
			getline(cin, password);

			cout << "Role      : ";
			getline(cin, role);

			user[jumlahUser].setIdUser(id);
			user[jumlahUser].setNama(nama);
			user[jumlahUser].setUsername(username);
			user[jumlahUser].setPassword(password);
			user[jumlahUser].setRole(role);
		}

		void registrasiUser(User user[], int &jumlahUser) {
			bacaUserDariFile(user, jumlahUser);

			if (jumlahUser >= 100) {
				cout << "Data user sudah penuh!\n";
				return;
			}

			inputUser(user, jumlahUser);
			jumlahUser++;

			simpanUserKeFile(user, jumlahUser);

			cout << "Registrasi berhasil dan data disimpan ke file.txt!\n";
		}
		
		//====================================================
		// LOGIN USER
		//====================================================
		void login() 
		{
			string username, password;

			bacaUserDariFile(user, jumlahUser);

			cout << "\n=== LOGIN ===\n";

			cout << "Username : ";
			getline(cin, username);

			cout << "Password : ";
			getline(cin, password);

			loginIndex = -1;

			for (int i = 0; i < jumlahUser; i++) 
			{
				if (user[i].getUsername() == username &&
					user[i].getPassword() == password) 
				{
					loginIndex = i;
					break;
				}
			}

			if (loginIndex != -1) 
			{
				cout << "Login berhasil!\n";
				cout << "Selamat datang, " << user[loginIndex].getNama() << "\n";
			} 
			else 
			{
				cout << "Login gagal! Username atau password salah.\n";
			}
		}
		
		//====================================================
		// LOGOUT
		//====================================================
		void logout()
		{
		    loginIndex = -1;
		    cout << "Logout berhasil!\n";
		}
		
		//====================================================
		// GANTI PASSWORD
		//====================================================
		void gantiPassword() 
		{
			if (loginIndex == -1) 
			{
				cout << "Anda belum login!\n";
				return;
			}

			string passwordBaru;

			cout << "Masukkan password baru: ";
			getline(cin, passwordBaru);

			user[loginIndex].setPassword(passwordBaru);
			simpanUserKeFile(user, jumlahUser);

			cout << "Password berhasil diubah!\n";
		}

class Admin {
	private :
		string idAdmin;
		string nama;
		double gaji;
	public :
			Admin()
		{
		    idAdmin = "";
		    nama = "";
		    gaji = 0;
		}
		
		Admin(string id, string n, double g)
		{
		    idAdmin = id;
		    nama = n;
		    gaji = g;
		}
		
		void setIdAdmin(string id)
		{
		    idAdmin = id;
		}
		
		void setNama(string n)
		{
		    nama = n;
		}
		
		void setGaji(double g)
		{
		    gaji = g;
		}
		
		string getIdAdmin()
		{
		    return idAdmin;
		}
		
		string getNama()
		{
		    return nama;
		}
		
		double getGaji()
		{
		    return gaji;
		}
		
		void tampilAdmin()
		{
		    cout << "\n===== DATA ADMIN =====" << endl;
		    cout << "ID Admin : " << idAdmin << endl;
		    cout << "Nama     : " << nama << endl;
		    cout << "Gaji  : " << gaji << endl;
		}
};

class Karyawan {
	private :
		string idKaryawan;
		string nama;
		string jabatan;
		double gaji;
		
	public :
		Karyawan()
		{
		    idKaryawan = "";
		    nama = "";
		    jabatan = "";
		    gaji = 0;
		}
		
		Karyawan(string id, string n, string jab, double g)
		{
		    idKaryawan = id;
		    nama = n;
		    jabatan = jab;
		    gaji = g;
		}
		
		void setIdKaryawan(string id)
		{
		    idKaryawan = id;
		}
		
		void setNama(string n)
		{
		    nama = n;
		}
		
		void setJabatan(string jab)
		{
		    jabatan = jab;
		}
		
		void setGaji(double g)
		{
		    gaji = g;
		}
		
		string getIdKaryawan()
		{
		    return idKaryawan;
		}
		
		string getNama()
		{
		    return nama;
		}
		
		string getJabatan()
		{
		    return jabatan;
		}
		
		double getGaji()
		{
		    return gaji;
		}
		
		void tampilKaryawan()
		{
		    cout << "\n===== DATA KARYAWAN =====" << endl;
		    cout << "ID Karyawan : " << idKaryawan << endl;
		    cout << "Nama        : " << nama << endl;
		    cout << "Jabatan     : " << jabatan << endl;
		    cout << "Gaji        : Rp " << gaji << endl;
		}
};



class Supplier {
	private :
		string idSupplier;
		string namaPerusahaan;
		string noHP;
		string alamat;
		
	public :
		Supplier()
		{
		    idSupplier = "";
		    namaPerusahaan = "";
		}
		
		Supplier(string id, string n)
		{
		    idSupplier = id;
		    namaPerusahaan = n;
		}
		
		void setIdSupplier(string id)
		{
		    idSupplier = id;
		}
		
		void setNama(string n)
		{
		    namaPerusahaan = n;
		}
		
		string getIdSupplier()
		{
		    return idSupplier;
		}
		
		string getNama()
		{
		    return namaPerusahaan;
		}
		
		void tampilSupplier()
		{
		    cout << "\n===== DATA SUPPLIER =====" << endl;
		    cout << "ID Supplier     : " << idSupplier << endl;
		    cout << "Nama Perusahaan : " << namaPerusahaan << endl;
		}
};

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
	// getter
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
	
	// Setter
	void setStok(int stokBaru){
    stok = stokBaru;
	}
	
	void setKodeObat(string kode){
	    kodeObat = kode;
	}
	
	void setNamaObat(string nama){
	    namaObat = nama;
	}
	
	void setHarga(double h){
	    harga = h;
	}
	
//	void setStok(int s){
//	    stok = s;
//	}
	
	void setTanggalExpired(string tgl){
	    tanggalExpired = tgl;
	}
	
	void setKategori(string kat){
	    kategori = kat;
	}
	
	void setSatuan(string sat){
	    satuan = sat;
	}
	
	// mengubah string menjadi huruf kecil
	string ubahKeLower(string teks){
	    for(int i = 0; i < teks.length(); i++){
	        teks[i] = tolower(teks[i]);
	    }
	    return teks;
	}
    
    // 
	bool cariObat(string namaCari){

	    ifstream file("daftar_obat.txt");
	
	    if(!file.is_open()){
	        cout<<"File tidak ditemukan!\n";
	        return false;
	    }
	
	    namaCari = ubahKeLower(namaCari);
	
	    string line;
	
	    while(getline(file,line)){
	
	        stringstream ss(line);
	
	        string kode;
	        string nama;
	        string hargaStr;
	        string stokStr;
	        string exp;
	        string kat;
	        string sat;
	
	        getline(ss,kode,'|');
	        getline(ss,nama,'|');
	        getline(ss,hargaStr,'|');
	        getline(ss,stokStr,'|');
	        getline(ss,exp,'|');
	        getline(ss,kat,'|');
	        getline(ss,sat,'|');
	
	        if(ubahKeLower(nama)==namaCari){
	
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
	
	// 
	void sortingNama(){

	    vector<Obat> data;
	
	    ifstream file("daftar_obat.txt");
	
	    if(!file.is_open()){
	        cout << "File tidak ditemukan!" << endl;
	        return;
	    }
	
	    string line;
	
	    while(getline(file, line)){
	
	        stringstream ss(line);
	
	        Obat obat;
	
	        string hargaStr;
	        string stokStr;
	
	        getline(ss, obat.kodeObat, '|');
	        getline(ss, obat.namaObat, '|');
	        getline(ss, hargaStr, '|');
	        getline(ss, stokStr, '|');
	        getline(ss, obat.tanggalExpired, '|');
	        getline(ss, obat.kategori, '|');
	        getline(ss, obat.satuan, '|');
	
	        obat.harga = atof(hargaStr.c_str());
	        obat.stok = atoi(stokStr.c_str());
	
	        data.push_back(obat);
	    }
	
	    file.close();
	
	    // Bubble Sort berdasarkan nama obat
	    for(int i = 0; i < data.size() - 1; i++){
	
	        for(int j = 0; j < data.size() - i - 1; j++){
	
	            string nama1 = ubahKeLower(data[j].namaObat);
	            string nama2 = ubahKeLower(data[j+1].namaObat);
	
	            if(nama1 > nama2){
	
	                Obat temp = data[j];
	                data[j] = data[j+1];
	                data[j+1] = temp;
	
	            }
	
	        }
	
	    }
	
	    cout << "\n===== DAFTAR OBAT (SORTING NAMA A-Z) =====\n\n";
	
	    cout << "KODE|NAMA|HARGA|STOK|TGL EXP|KATEGORI|SATUAN|\n\n";
	
	    for(int i = 0; i < data.size(); i++){
	
	        cout << data[i].kodeObat << "|"
	             << data[i].namaObat << "|"
	             << data[i].harga << "|"
	             << data[i].stok << "|"
	             << data[i].tanggalExpired << "|"
	             << data[i].kategori << "|"
	             << data[i].satuan << "|" << endl << endl;
	
	    }
	
	}
	
	//
	void sortingHarga(){

	    vector<Obat> data;
	
	    ifstream file("daftar_obat.txt");
	
	    if(!file.is_open()){
	        cout << "File tidak ditemukan!" << endl;
	        return;
	    }
	
	    string line;
	
	    while(getline(file, line)){
	
	        stringstream ss(line);
	
	        Obat obat;
	
	        string hargaStr;
	        string stokStr;
	
	        getline(ss, obat.kodeObat, '|');
	        getline(ss, obat.namaObat, '|');
	        getline(ss, hargaStr, '|');
	        getline(ss, stokStr, '|');
	        getline(ss, obat.tanggalExpired, '|');
	        getline(ss, obat.kategori, '|');
	        getline(ss, obat.satuan, '|');
	
	        obat.harga = atof(hargaStr.c_str());
	        obat.stok = atoi(stokStr.c_str());
	
	        data.push_back(obat);
	    }
	
	    file.close();
	
	    // Bubble Sort berdasarkan harga (termurah ke termahal)
	    for(int i = 0; i < data.size() - 1; i++){
	
	        for(int j = 0; j < data.size() - i - 1; j++){
	
	            if(data[j].harga > data[j+1].harga){
	
	                Obat temp = data[j];
	                data[j] = data[j+1];
	                data[j+1] = temp;
	
	            }
	
	        }
	
	    }
	
	    cout << "\n===== DAFTAR OBAT (SORTING HARGA TERMURAH) =====\n\n";
	
	    cout << "KODE|NAMA|HARGA|STOK|TGL EXP|KATEGORI|SATUAN|\n\n";
	
	    for(int i = 0; i < data.size(); i++){
	
	        cout << data[i].kodeObat << "|"
	             << data[i].namaObat << "|"
	             << data[i].harga << "|"
	             << data[i].stok << "|"
	             << data[i].tanggalExpired << "|"
	             << data[i].kategori << "|"
	             << data[i].satuan << "|" << endl << endl;
	
	    }
	
	}
	
	void ubahDataObat() {
		
    	ifstream file("daftar_obat.txt");
	
	    vector<Obat> daftar;
	    string line;
	
	    while(getline(file,line)){
	
	        stringstream ss(line);
	
	        Obat o;
	
	        string kode,nama,hargaStr,stokStr,exp,kat,sat;
	
	        getline(ss,kode,'|');
	        getline(ss,nama,'|');
	        getline(ss,hargaStr,'|');
	        getline(ss,stokStr,'|');
	        getline(ss,exp,'|');
	        getline(ss,kat,'|');
	        getline(ss,sat,'|');
	
	        // ===========================
	        // Mengisi object menggunakan setter
	        // ===========================
	        o.setKodeObat(kode);
	        o.setNamaObat(nama);
	        o.setHarga(atof(hargaStr.c_str()));
	        o.setStok(atoi(stokStr.c_str()));
	        o.setTanggalExpired(exp);
	        o.setKategori(kat);
	        o.setSatuan(sat);
	
	        daftar.push_back(o);
	    }
	
	    file.close();
		
		bacaData();
		
		cout << endl;
	
	    string kodeCari;
	
	    cout << "Masukkan Kode Obat yang ingin diubah : ";
		cin >> kodeCari;
	
	    bool ketemu=false;
	
	    for(int i=0;i<daftar.size();i++){
	
	        if(daftar[i].getkodeObat()==kodeCari){
	
	            ketemu=true;
	
	            string nama;
	            double harga;
	            int stok;
	            string exp;
	            string kat;
	            string sat;
	
	            cin.ignore();
	
	            cout<<"Nama baru : ";
	            getline(cin,nama);
	
	            cout<<"Harga baru : ";
	            cin>>harga;
	
	            cout<<"Stok baru : ";
	            cin>>stok;
	
	            cout<<"Tanggal Expired baru : ";
	            cin>>exp;
	
	            cout<<"Kategori baru : ";
	            cin>>kat;
	
	            cout<<"Satuan baru : ";
	            cin>>sat;
	
	            daftar[i].setNamaObat(nama);
	            daftar[i].setHarga(harga);
	            daftar[i].setStok(stok);
	            daftar[i].setTanggalExpired(exp);
	            daftar[i].setKategori(kat);
	            daftar[i].setSatuan(sat);
	
	            break;
	        }
	
	    }
	
	    if(!ketemu){
	
	        cout<<"Data tidak ditemukan.\n";
	        return;
	
	    }
	
	    ofstream tulis("daftar_obat.txt");
	
	    for(int i=0;i<daftar.size();i++){
	
	        tulis<<daftar[i].getkodeObat()<<"|"
	             <<daftar[i].getnamaObat()<<"|"
	             <<daftar[i].getHarga()<<"|"
	             <<daftar[i].getStok()<<"|"
	             <<daftar[i].gettanggalExpired()<<"|"
	             <<daftar[i].getKategori()<<"|"
	             <<daftar[i].getSatuan()<<endl;
	
	    }
	
	    tulis.close();
	
	    cout<<"Data berhasil diubah.\n";
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

	//
    void updateStok(int jumlah) {

    	stok = jumlah;

	}
	
	//
    void tambahStok(int jumlah) {

	    stok += jumlah;
	
	}
	
	//
    void kurangiStok(int jumlah){

	    if(jumlah <= stok){
	
	        stok -= jumlah;
	
	    } else {
	        cout << "Stok tidak mencukupi!" << endl;
	    }
	
	}
	
	//
	void simpanPerubahanStok(){

	    vector<Obat> data;
	
	    ifstream file("daftar_obat.txt");
	
	    string line;
	
	    while(getline(file,line)){
	
	        stringstream ss(line);
	
	        Obat obat;
	
	        string hargaStr;
	        string stokStr;
	
	        getline(ss,obat.kodeObat,'|');
	        getline(ss,obat.namaObat,'|');
	        getline(ss,hargaStr,'|');
	        getline(ss,stokStr,'|');
	        getline(ss,obat.tanggalExpired,'|');
	        getline(ss,obat.kategori,'|');
	        getline(ss,obat.satuan,'|');
	
	        obat.harga = atof(hargaStr.c_str());
	        obat.stok = atoi(stokStr.c_str());
	
	        data.push_back(obat);
	
	    }
	
	    file.close();
	
	    // Cari obat berdasarkan kode
	    for(int i = 0; i < data.size(); i++){
	
	        if(data[i].kodeObat == kodeObat){
	
	            data[i].updateStok(stok);
	
	            break;
	
	        }
	
	    }
	
	    ofstream simpan("daftar_obat.txt");
	
	    for(int i = 0; i < data.size(); i++){
	
	        simpan << data[i].kodeObat << "|"
	               << data[i].namaObat << "|"
	               << data[i].harga << "|"
	               << data[i].stok << "|"
	               << data[i].tanggalExpired << "|"
	               << data[i].kategori << "|"
	               << data[i].satuan << endl;
	
	    }
	
	    simpan.close();
	
	}

    void cekKadaluarsa(){

		ifstream file("daftar_obat.txt");

		if(!file.is_open()){
			cout << "File tidak ditemukan!" << endl;
			return;
		}

		time_t sekarang = time(0);

		string line;

		bool adaKadaluarsa = false;
		bool adaHampir = false;

		vector<string> daftarKadaluarsa;
		vector<string> daftarHampir;

		while(getline(file,line)){

			stringstream ss(line);

			string kode,nama,harga,stok,exp,kategori,satuan;

			getline(ss,kode,'|');
			getline(ss,nama,'|');
			getline(ss,harga,'|');
			getline(ss,stok,'|');
			getline(ss,exp,'|');
			getline(ss,kategori,'|');
			getline(ss,satuan,'|');

			int hari,bulan,tahun;
			char slash;

			stringstream tgl(exp);
			tgl >> hari >> slash >> bulan >> slash >> tahun;

			tm waktuExp = {};

			waktuExp.tm_mday = hari;
			waktuExp.tm_mon  = bulan - 1;
			waktuExp.tm_year = tahun - 1900;

			time_t tanggalExp = mktime(&waktuExp);

			double selisihHari = difftime(tanggalExp,sekarang)/(60*60*24);

			if(selisihHari < 0){

				adaKadaluarsa = true;

				stringstream data;
				data << kode << " | "
					<< nama << " | "
					<< exp;

				daftarKadaluarsa.push_back(data.str());

			}
			else if(selisihHari <= 7){

				adaHampir = true;

				stringstream data;
				data << kode << " | "
					<< nama << " | "
					<< exp
					<< " (" << (int)selisihHari << " hari lagi)";

				daftarHampir.push_back(data.str());

			}

		}

		file.close();

		cout << "\n=========================================\n";
		cout << "       DAFTAR OBAT KADALUARSA\n";
		cout << "=========================================\n";

		if(adaKadaluarsa){

			for(int i=0;i<daftarKadaluarsa.size();i++)
				cout << daftarKadaluarsa[i] << endl;

		}else{

			cout << "Tidak ada obat yang sudah kadaluarsa.\n";

		}

		cout << "\n=========================================\n";
		cout << "   DAFTAR OBAT HAMPIR KADALUARSA\n";
		cout << "=========================================\n";

		if(adaHampir)
		{

			for(int i=0;i<daftarHampir.size();i++)
				cout << daftarHampir[i] << endl;

		}
		else
		{

			cout << "Tidak ada obat yang hampir kadaluarsa.\n";

		}

	}
    
    void stokMenipis(){

    ifstream file("daftar_obat.txt");

    if(!file.is_open()){
        cout << "File tidak ditemukan!" << endl;
        return;
    }

    string line;
    bool ada = false;

    cout << "\n===== DAFTAR STOK MENIPIS =====\n\n";
    cout << "KODE|NAMA|STOK\n\n";

    while(getline(file,line)){

        stringstream ss(line);

        string kode;
        string nama;
        string hargaStr;
        string stokStr;
        string exp;
        string kat;
        string sat;

        getline(ss,kode,'|');
        getline(ss,nama,'|');
        getline(ss,hargaStr,'|');
        getline(ss,stokStr,'|');
        getline(ss,exp,'|');
        getline(ss,kat,'|');
        getline(ss,sat,'|');

        int stok = atoi(stokStr.c_str());

        if(stok <= 10){

            ada = true;

            cout << kode << " | "
                 << nama << " | "
                 << stok << endl;
        }
    }

    if(!ada){
        cout << "Tidak ada obat yang stoknya menipis." << endl;
    }

    file.close();
}

    void ubahHarga(){

    ifstream file("daftar_obat.txt");

    if(!file.is_open()){
        cout << "File tidak ditemukan!" << endl;
        return;
    }

    vector<Obat> daftar;
    string line;

    while(getline(file, line)){

        stringstream ss(line);

        Obat o;

        string kode, nama, hargaStr, stokStr, exp, kat, sat;

        getline(ss, kode, '|');
        getline(ss, nama, '|');
        getline(ss, hargaStr, '|');
        getline(ss, stokStr, '|');
        getline(ss, exp, '|');
        getline(ss, kat, '|');
        getline(ss, sat, '|');

        o.setKodeObat(kode);
        o.setNamaObat(nama);
        o.setHarga(atof(hargaStr.c_str()));
        o.setStok(atoi(stokStr.c_str()));
        o.setTanggalExpired(exp);
        o.setKategori(kat);
        o.setSatuan(sat);

        daftar.push_back(o);
    }

    file.close();

    bacaData();

    string kodeCari;
    cout << "\nMasukkan Kode Obat yang akan diubah harganya : ";
    cin >> kodeCari;

    bool ketemu = false;

    for(int i = 0; i < daftar.size(); i++){

        if(daftar[i].getkodeObat() == kodeCari){

            ketemu = true;

            double hargaBaru;

            cout << "Harga lama : " << daftar[i].getHarga() << endl;
            cout << "Masukkan harga baru : ";
            cin >> hargaBaru;

            daftar[i].setHarga(hargaBaru);

            break;
        }
    }

    if(!ketemu){
        cout << "Kode obat tidak ditemukan." << endl;
        return;
    }

    ofstream tulis("daftar_obat.txt");

    for(int i = 0; i < daftar.size(); i++){

        tulis << daftar[i].getkodeObat() << "|"
              << daftar[i].getnamaObat() << "|"
              << daftar[i].getHarga() << "|"
              << daftar[i].getStok() << "|"
              << daftar[i].gettanggalExpired() << "|"
              << daftar[i].getKategori() << "|"
              << daftar[i].getSatuan() << endl;
    }

    tulis.close();

    cout << "\nHarga obat berhasil diubah." << endl;
}
    
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

// perubahan class
class Keranjang{
private:

    vector<Obat> daftarObat;
    vector<int> jumlah;
    double subtotalobat;

public:

	// tambahobat baru
    void tambahObat(Obat obat, int qty) {

	    int index = cariIndex(obat.getnamaObat());
	
	    // Jika obat sudah ada di keranjang
	    if(index != -1){

		    if(jumlah[index] + qty > daftarObat[index].getStok()){
		
		        cout << "\nJumlah pembelian melebihi stok yang tersedia!" << endl;
		        return;
		    }
		
		    jumlah[index] += qty;
		
		    cout << "\nJumlah obat berhasil diperbarui." << endl;
		
		} else {
	
	        daftarObat.push_back(obat);
	        jumlah.push_back(qty);
	
	        cout << "\nObat berhasil ditambahkan ke keranjang." << endl;
	    }
	}

    void kosongkanKeranjang(){

        daftarObat.clear();
        jumlah.clear();

    }

    vector<Obat> getDaftarObat(){

        return daftarObat;

    }

    vector<int> getJumlah(){

        return jumlah;

    }

    int getSize(){

        return daftarObat.size();

    }
    
    // baru
    int cariIndex(string namaObat) {

	    for(int i = 0; i < daftarObat.size(); i++){
	
	        if(daftarObat[i].getnamaObat() == namaObat){
	
	            return i;
	
	        }
	
	    }
	
	    return -1;
	}
    
    // baru
    bool keranjangKosong() {

    	return daftarObat.empty();

	}

    double hitungSubtotal(){

        subtotalobat = 0;

        for(int i=0;i<daftarObat.size();i++){

            subtotalobat += daftarObat[i].getHarga()*jumlah[i];

        }

        return subtotalobat;

    }
    
    //tampilkeranjang baru
	void tampilKeranjang() {
		
	    if (daftarObat.empty())
	    {
	        cout << "\nKeranjang masih kosong.\n";
	        return;
	    }
	
	    cout << "\n===============================================================\n";
	    cout << left << setw(5) << "No"
	         << setw(20) << "Nama Obat"
	         << setw(10) << "Harga"
	         << setw(8) << "Qty"
	         << setw(12) << "Subtotal" << endl;
	    cout << "===============================================================\n";
	
	    for (int i = 0; i < daftarObat.size(); i++)
	    {
	        cout << left << setw(5) << i + 1
	             << setw(20) << daftarObat[i].getnamaObat()
	             << setw(10) << daftarObat[i].getHarga()
	             << setw(8) << jumlah[i]
	             << setw(12) << daftarObat[i].getHarga() * jumlah[i]
	             << endl;
	    }
	
	    cout << "===============================================================\n";
	    cout << "Total : Rp " << hitungSubtotal() << endl;
	    cout << "===============================================================\n";
	}
    
    // baru
    void ubahJumlah(int index, int jumlahBaru) {
    	
	    if(index < 0 || index >= jumlah.size())
	        return;
	
	    if(jumlahBaru <= 0)
	    {
	        cout<<"Jumlah tidak valid!\n";
	        return;
	    }
	
	    if(jumlahBaru > daftarObat[index].getStok())
	    {
	        cout<<"Stok tidak mencukupi!\n";
	        return;
	    }
	
	    jumlah[index] = jumlahBaru;
	
	    cout<<"Jumlah berhasil diubah.\n";
	}
	
	// baru
	void hapusItem(int index) {
		
	    if(index < 0 || index >= daftarObat.size())
	    {
	        cout << "Item tidak ditemukan!" << endl;
	        return;
	    }
	
	    daftarObat.erase(daftarObat.begin() + index);
	    jumlah.erase(jumlah.begin() + index);
	
	    cout << "Item berhasil dihapus." << endl;
	}
	
};

class Transaksi {
private:
	Keranjang keranjang;
	
	Obat obatDipilih; // perubahan variabel
	string namaObat;
	string idTransaksi;
	string tanggal;
	
	double subtotal;
	double totalPembayaran;
	double uangBayar;
	double uangKembali;
	double diskon;
	
public:
	
	//
	void generateID(){

	    ifstream file("riwayat_transaksi.txt");
	
	    int nomor = 1;
	    string baris;
	
	    while(getline(file, baris)){
	        nomor++;
	    }
	
	    file.close();
	
	    stringstream ss;
	
	    ss << "TRX";
	
	    if(nomor < 10)
	        ss << "000";
	    else if(nomor < 100)
	        ss << "00";
	    else if(nomor < 1000)
	        ss << "0";
	
	    ss << nomor;
	
	    idTransaksi = ss.str();
	}
	
	// baru
	void tambahObatKeKeranjang(){

	    Obat obat;
	
	    string nama;
	    int jumlah;
	
	    cout << "Masukkan Nama Obat : ";
	    getline(cin, nama);
	
	    if(obat.cariObat(nama))
	    {
	        cout << "\n==========================================" << endl;
	        cout << "          DATA OBAT DITEMUKAN" << endl;
	        cout << "==========================================" << endl;
	
	        cout << left << setw(15) << "Nama"
	             << ": " << obat.getnamaObat() << endl;
	
	        cout << left << setw(15) << "Harga"
	             << ": Rp " << obat.getHarga() << endl;
	
	        cout << left << setw(15) << "Stok"
	             << ": " << obat.getStok() << endl;
	
	        cout << "==========================================" << endl;
	
	        cout << "\nJumlah Beli : ";
	        cin >> jumlah;
	        cin.ignore();
	
	        if(jumlah <= obat.getStok())
	        {
	            keranjang.tambahObat(obat, jumlah);
	
	        }
	        else
	        {
	            cout << "\n>> Stok tidak mencukupi!" << endl;
	        }
	    }
	    else
	    {
	        cout << "\n>> Obat tidak ditemukan!" << endl;
	    }
	
	}
	
	// inputtransaksi baru
	void inputTransaksi(){

	    generateID();
	
	    keranjang.kosongkanKeranjang(); // ? BENAR
	
	    char pilih;
	
	    do{

		    header("TRANSAKSI PENJUALAN");
		
		    cout << "ID Transaksi : " << idTransaksi << endl;
		
		    tambahObatKeKeranjang();
		
		    cout << "\nTambah obat lagi? (Y/T) : ";
		    cin >> pilih;
		    cin.ignore();
		
		}while(toupper(pilih)=='Y');
	    
	    menuKeranjang();
			    
	}
	
	void menuKeranjang(){

	    // Jika keranjang kosong, tidak perlu menampilkan menu
	    if(keranjang.keranjangKosong()){
	        cout << "\nKeranjang masih kosong!" << endl;
	        return;
	    }
	
	    int pilihan;
	    bool checkout = false;
	
	    do{
	
	        system("cls");
	
	        header("MENU KERANJANG");
	
	        cout << "\n================ MENU =================" << endl;
	        cout << "1. Tambah Obat" << endl;
	        cout << "2. Ubah Jumlah" << endl;
	        cout << "3. Hapus Item" << endl;
	        cout << "4. Lihat Ringkasan" << endl;
	        cout << "5. Checkout" << endl;
	        cout << "6. Batalkan Transaksi" << endl;
	        cout << "=======================================" << endl;
	
	        cout << "Masukkan Pilihan : ";
	        cin >> pilihan;
	        cin.ignore();
	
	        switch(pilihan){
	
	        case 1:
	        {
	            tambahObatKeKeranjang();
	            break;
	        }
	
	        case 2:
	        {
	            if(keranjang.keranjangKosong())
			    {
			        cout << "\nKeranjang masih kosong!" << endl;
			        break;
			    }
			
			    int nomor;
			    int jumlahBaru;
			
			    cout << "\nNomor Item : ";
			    cin >> nomor;
			
			    cout << "Jumlah Baru : ";
			    cin >> jumlahBaru;
			    cin.ignore();
			
			    keranjang.ubahJumlah(nomor - 1, jumlahBaru);
			    
	            break;
	        }
	
	        case 3:
	        {
	            if(keranjang.keranjangKosong())
			    {
			        cout << "\nKeranjang masih kosong!" << endl;
			        break;
			    }
			
			    int nomor;
			
			    cout << "\nNomor Item : ";
			    cin >> nomor;
			    cin.ignore();
			
			    keranjang.hapusItem(nomor - 1);
			
			    if(keranjang.keranjangKosong())
			    {
			        cout << "\nSemua item telah dihapus." << endl;
			    }
    
	            break;
	        }
	
	        case 4:
			{
				
				keranjang.tampilKeranjang();
				
			    cout << "\n\n========== RINGKASAN ==========" << endl;
			
			    cout << "Jumlah Item     : "
			         << keranjang.getSize() << endl;
			
			    cout << "Total Belanja   : Rp "
			         << keranjang.hitungSubtotal() << endl;
			
			    break;
			}
	
	        case 5:
			{
			    if(keranjang.keranjangKosong())
			    {
			        cout << "\nKeranjang masih kosong!" << endl;
			        break;
			    }
			
			    char konfirmasi;
			
			    cout << "\nYakin lanjut ke pembayaran? (Y/T) : ";
			    cin >> konfirmasi;
			    cin.ignore();
			
			    if(toupper(konfirmasi) == 'Y')
			    {
			        checkout = true;
			    }
			
			    break;
			}
	
	        case 6:
			{
			    char konfirmasi;
			
			    cout << "\nYakin ingin membatalkan transaksi? (Y/T) : ";
			    cin >> konfirmasi;
			    cin.ignore();
			
			    if(toupper(konfirmasi) == 'Y')
			    {
			        keranjang.kosongkanKeranjang();
			
			        cout << "\nTransaksi berhasil dibatalkan." << endl;
			
			        system("pause");
			
			        return;
			    }
			
			    break;
			}
	
	        default:
	
	            cout << "\nPilihan tidak tersedia!" << endl;
	        }
	
	        if(!checkout){
	            cout << endl;
	            system("pause");
	        }
	
	    }while(!checkout);
	
	}
	    
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
	
	    if (obatDipilih.cariObat(namaObat)) {
	    
	        cout << "\nObat ditemukan!\n";
	        cout << "Nama     : " << obatDipilih.getnamaObat() << endl;
			cout << "Harga    : " << obatDipilih.getHarga() << endl;
			cout << "Stok     : " << obatDipilih.getStok() << endl;
	
	    } else {
	
	        cout << "Obat tidak ditemukan!\n";
	
	    }
	    system("pause");
	    system("cls");
	}
	
	double hitungTotal(){

	  subtotal = 0;
	    
	    vector<Obat> daftarObat = keranjang.getDaftarObat();
    	vector<int> jumlahBeli = keranjang.getJumlah();
	
	    cout << "\n==============================================" << endl;
	    cout << "            RINCIAN PEMBELIAN" << endl;
	    cout << "==============================================" << endl;
	
	    for(int i = 0; i < daftarObat.size(); i++){
	
	        double subtotalobat = daftarObat[i].getHarga() * jumlahBeli[i];
	
	        cout << setw(20) << left << daftarObat[i].getnamaObat()
	             << jumlahBeli[i] << " x "
	             << daftarObat[i].getHarga()
	             << " = "
	             << subtotalobat << endl;
	
	        subtotal += subtotalobat;
	
	    }
	
	    cout << "----------------------------------------------" << endl;
	    cout << "Total Pembayaran : Rp " << subtotal << endl;
	
	    return subtotal;
	
	}
	
	void diskonBelanja(){

    diskon = 0;

    if(subtotal >= 300000){
        diskon = subtotal * 0.20;
    }
    else if( subtotal >= 150000){
        diskon = subtotal * 0.15;
    }
    else if(subtotal >= 75000){
        diskon = subtotal * 0.10;
    }

    cout << "\nTotal Belanja : Rp " << subtotal << endl;
    cout << "Diskon        : Rp " << diskon << endl;

    totalPembayaran = subtotal - diskon;

    cout << "Total Bayar   : Rp " << totalPembayaran << endl;
}

	void prosesPembayaran(){

	    uangBayar = 0;
	
	    cout << "\nMasukkan Uang Pembeli : Rp ";
	    cin >> uangBayar;
	
	    while(uangBayar < totalPembayaran){
	
	        cout << "\nUang tidak mencukupi!" << endl;
	
	        cout << "Masukkan Uang Pembeli : Rp ";
	        cin >> uangBayar;
	
	    }
	
	    uangKembali = uangBayar - totalPembayaran;
	
	    cout << "Kembalian : Rp " << uangKembali << endl;
	
	    // AMBIL DATA DARI KERANJANG
	    vector<Obat> daftarObat = keranjang.getDaftarObat();
	    vector<int> jumlahBeli = keranjang.getJumlah();
	
	    // Kurangi stok setiap obat
	    for(int i = 0; i < daftarObat.size(); i++){
	
	        daftarObat[i].kurangiStok(jumlahBeli[i]);
	        daftarObat[i].simpanPerubahanStok();
	
	    }
	
	    simpanRiwayat();
	
	    cout << "\nPembayaran Berhasil." << endl;
	}
	
    void simpanRiwayat(){

	    ofstream file("riwayat_transaksi.txt", ios::app);
	
	    if(!file.is_open()){
	        cout << "File riwayat tidak dapat dibuka!" << endl;
	        return;
	    }
	
	    vector<Obat> daftarObat = keranjang.getDaftarObat();
	    vector<int> jumlahBeli = keranjang.getJumlah();
	
	    for(int i = 0; i < daftarObat.size(); i++){
	
	        file << idTransaksi << "|"
	             << cetakTanggal() << "|"
	             << cetakWaktu() << "|"
	             << daftarObat[i].getnamaObat() << "|"
	             << jumlahBeli[i] << "|"
	             << daftarObat[i].getHarga() << "|"
	             << daftarObat[i].getHarga() * jumlahBeli[i]
	             << endl;
	    }
	
	    file.close();
	}
	
	void cetakStruk(){

	    // Memulai transaksi
	    inputTransaksi();
	    
	    //menghitung total belanjaan
		hitungTotal();
		
		//mengecek apakah mendapatkan diskon atau tidak
	    diskonBelanja();
	
	    // Melakukan pembayaran
	    prosesPembayaran();
	
	    cout << "\n\n";
	    cout << "==============================================" << endl;
	    cout << "          APOTEK K24 WIROSABAN" << endl;
	    cout << "==============================================" << endl;
	    cout << "ID Transaksi : " << idTransaksi << endl;
	    cout << "Tanggal      : " << cetakTanggal() << endl;
	    cout << "Jam          : " << cetakWaktu() << endl;
	    cout << "==============================================" << endl;
	
	    cout << left
	         << setw(20) << "Nama Obat"
	         << setw(8) << "Qty"
	         << setw(10) << "Harga"
	         << setw(12) << "Subtotal" << endl;
	
	    cout << "----------------------------------------------" << endl;
	    
	    vector<Obat> daftarObat = keranjang.getDaftarObat();
		vector<int> jumlahBeli = keranjang.getJumlah();
	
	    for(int i=0;i<daftarObat.size();i++){
	
	        cout << left
	             << setw(20) << daftarObat[i].getnamaObat()
	             << setw(8) << jumlahBeli[i]
	             << setw(10) << daftarObat[i].getHarga()
	             << setw(12) << daftarObat[i].getHarga()*jumlahBeli[i]
	             << endl;
	
	    }

	    cout << "----------------------------------------------" << endl;
	
	    cout << right << setw(28) << "TOTAL            : Rp "
	         << subtotal << endl;
	         
	    cout << right << setw(28) << "DISKON           : Rp "
	         << diskon << endl;
	         
	    cout << right << setw(28) << "SETELAH DISKON   : Rp "
	         << totalPembayaran << endl;
	    cout << right << setw(28) << "BAYAR            : Rp "
	         << uangBayar << endl;
	
	    cout << right << setw(28) << "KEMBALI          : Rp "
	         << uangKembali << endl;
	
	    cout << "==============================================" << endl;
	    cout << "      TERIMA KASIH TELAH BERBELANJA" << endl;
	    cout << "==============================================" << endl;
	
	}

    void tampilRiwayat(){

	    ifstream file("riwayat_transaksi.txt");
	
	    if(!file.is_open()){
	
	        cout << "Riwayat transaksi belum tersedia." << endl;
	        return;
	
	    }
	
	    string line;
	
	    string idLama = "";
	
	    cout << "==============================================" << endl;
	    cout << "           RIWAYAT TRANSAKSI" << endl;
	    cout << "==============================================" << endl;
	
	    while(getline(file,line)){
	
	        stringstream ss(line);
	
	        string id;
	        string tanggal;
	        string jam;
	        string nama;
	        string jumlah;
	        string harga;
	        string subtotal;
	
	        getline(ss,id,'|');
	        getline(ss,tanggal,'|');
	        getline(ss,jam,'|');
	        getline(ss,nama,'|');
	        getline(ss,jumlah,'|');
	        getline(ss,harga,'|');
	        getline(ss,subtotal,'|');
	
	        if(id != idLama){
	
	            if(idLama != ""){
	
	                cout << "------------------------------------------------" << endl << endl;
	
	            }
	
	            cout << "\nID Transaksi : " << id << endl;
	            cout << "Tanggal      : " << tanggal << endl;
	            cout << "Jam          : " << jam << endl;
	
	            cout << "------------------------------------------------" << endl;
	
	            cout << left
	                 << setw(20) << "Nama Obat"
	                 << setw(8) << "Qty"
	                 << setw(10) << "Harga"
	                 << setw(12) << "Subtotal"
	                 << endl;
	
	            cout << "------------------------------------------------" << endl;
	
	            idLama = id;
	
	        }
	
	        cout << left
	             << setw(20) << nama
	             << setw(8) << jumlah
	             << setw(10) << harga
	             << setw(12) << subtotal
	             << endl;
	
	    }
	
	    cout << "------------------------------------------------" << endl;
	
	    file.close();
	
	}

    void batalkanTransaksi();
    void refundTransaksi();

    string getIDTransaksi();
    double getTotal();
};

class Pesanan {
	private :
		string idPesanan;
		Supplier supplier;
		vector<Obat> daftarObat;
		string tanggalPesan;
		string statusPesanan;
	
	public :
		
};

class Laporan {
	private :
		vector<Transaksi> dataTransaksi;
		string periode;
		double totalPendapatan;
		int jumlahTransaksi;
		
	public :
};

class Logaktivitas {
	private :
		string idUser;
		string aktivitas;
		string waktu;
		string keterangan;
		
	public :

};

		void menuAdmin(){
					Obat obat;
					Transaksi transaksi;
					int pilih;
					string namaCari;
				
					do
					{
						cout << "\n=== MENU ADMIN ===\n";
						cout << "1. Lihat User\n";
						cout<<"2. Lihat Obat\n";
						cout<<"3. Cari Obat\n";
						cout<<"4. Tambah Obat\n";
						cout<<"5. Edit Data Obat\n";
						cout<<"6. Ubah Harga Obat\n";
						cout<<"7. Stok Menipis\n";
						cout<<"8. Cek Kadaluarsa\n";
						cout<<"9. Riwayat Transaksi\n";
						cout<<"10. Logout\n";
						cout<<"Pilih : ";
						cin>>pilih;
						cin.ignore();
				
						switch (pilih)
						{
							case 1:
								cout << "\nDATA USER:\n";
								for (int i = 0; i < jumlahUser; i++)
								{
									user[i].tampil();
									cout << endl;
								}
								break;

							case 2:
								obat.bacaData();
								break;

							case 3:
								cout<<"Nama Obat : ";
								getline(cin,namaCari);

								if(obat.cariObat(namaCari)){

									cout<<"\nKode       : "<<obat.getkodeObat()<<endl;
									cout<<"Nama       : "<<obat.getnamaObat()<<endl;
									cout<<"Harga      : "<<obat.getHarga()<<endl;
									cout<<"Stok       : "<<obat.getStok()<<endl;
									cout<<"Expired    : "<<obat.gettanggalExpired()<<endl;

								}
								else
								{
									cout<<"Obat tidak ditemukan.\n";
								}
								break;

							case 4:
								obat.inputObat();
								break;

							case 5:
								obat.ubahDataObat();
								break;

							case 6:
								obat.ubahHarga();
								break;

							case 7:
								obat.stokMenipis();
								break;

							case 8:
								obat.cekKadaluarsa();
								break;

							case 9:
								transaksi.tampilRiwayat();
								break;

							case 10:
								logout();
								return;

							default:
							cout<<"Pilihan salah!\n";
					}

				system("pause");
				break;

			}while(true);
			
		}

		void menuKaryawan(){
		    int pilih;
		
		    do
		    {
		        cout << "\n=== MENU KARYAWAN ===\n";
		        cout << "1. Input Transaksi\n";
		        cout << "2. Lihat Obat\n";
		        cout << "3. Hitung Total\n";
		        cout << "4. Logout\n";
		        cout << "Pilih: ";
		        cin >> pilih;
		        cin.ignore();
		
		        switch (pilih)
		        {
		        case 2:
		            cout << "Menampilkan data obat...\n";
		            break;
		
		        case 4:
		            logout();
		            return;
		        }
		
		    } while (true);
		}
		
			void menuSupplier(){
		    int pilih;
		
		    do
		    {
		        cout << "\n=== MENU SUPPLIER ===\n";
		        cout << "1. Konfirmasi Barang\n";
		        cout << "2. Update Status Pesanan\n";
		        cout << "3. Logout\n";
		        cout << "Pilih: ";
		        cin >> pilih;
		        cin.ignore();
		
		        switch (pilih)
		        {
		        case 3:
		            logout();
		            return;
		        }
		
		    } while (true);
		}
    
    void menuUtama(){
		    if (loginIndex == -1)
		    {
		        cout << "Anda belum login!\n";
		        return;
		    }
		
		    string role = user[loginIndex].getRole();
		    if (role == "Admin")
		    {
		        menuAdmin();
		    }
		    else if (role == "Karyawan")
		    {
		        menuKaryawan();
		    }
		    else if (role == "Supplier")
		    {
		        menuSupplier();
		    }
		    else
		    {
		        cout << "Role tidak dikenal!\n";
		    }
		}
int main(){

    Transaksi transaksi;
    Obat obat;

    int pilihan, pilih;
    string namaCari;
    
    
    do
    {
        cout << "\n=== SISTEM APOTEK ===\n";
        cout << "1. Registrasi\n";
        cout << "2. Login\n";
        cout << "3. Keluar\n";
        cout << "Pilih: ";
        cin >> pilih;
        cin.ignore();

        switch (pilih)
        {
        case 1:
            registrasiUser(user, jumlahUser);
            break;

        case 2:
            login();
            if (loginIndex != -1)
            {
                menuUtama();
            }
            break;
        }
        
        } while (pilih != 3);
    
    return 0;
}
