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

void footer();

// baru
void kembaliMenu() { 
	cout << "\nTekan Enter untuk lanjut...";
    cin.get();
    // system("cls");
}


bool hanyaAngka(string teks) {
    if (teks == "") 
	{
        return false;
    }

    for (int i = 0; i < teks.length(); i++) 
	{
        if (teks[i] < '0' || teks[i] > '9') 
		{
            return false;
        }
    }

    return true;
}

int ubahKeAngka(string teks) 
{
    int angka = 0;

    for (int i = 0; i < teks.length(); i++) 
	{
        angka = angka * 10 + (teks[i] - '0');
    }

    return angka;
}

int stringKeAngka(string teks) {
    int angka = 0;

    for (int i = 0; i < teks.length(); i++) {
        if (teks[i] >= '0' && teks[i] <= '9') {
            angka = angka * 10 + (teks[i] - '0');
        }
    }

    return angka;
}

string angkaKeString(int angka) {
    return to_string(angka);
}

string ambilField(string baris, int posisiField) {
    string hasil = "";
    int field = 0;

    for (int i = 0; i < baris.length(); i++) {
        if (baris[i] == '|') {
            field++;
        } else if (field == posisiField) {
            hasil += baris[i];
        }
    }

    return hasil;
}

bool cocokPrefix(string id, string prefix) {
    if (id.length() < prefix.length()) {
        return false;
    }

    for (int i = 0; i < prefix.length(); i++) {
        if (id[i] != prefix[i]) {
            return false;
        }
    }

    return true;
}

int ambilNomorDariId(string id, string prefix) {
    string nomor = "";

    if (!cocokPrefix(id, prefix)) {
        return 0;
    }

    for (int i = prefix.length(); i < id.length(); i++) {
        nomor += id[i];
    }

    return stringKeAngka(nomor);
}

string formatId(string prefix, int nomor, int jumlahDigit) {
    string angka = angkaKeString(nomor);
    string nol = "";

    while (nol.length() + angka.length() < jumlahDigit) {
        nol += "0";
    }

    return prefix + nol + angka;
}

string generateIdDariFile(string namaFile, string prefix, int jumlahDigit, int posisiFieldId) {
    ifstream file(namaFile);

    int nomorTerbesar = 0;
    string baris;

    if (!file.is_open()) {
        return formatId(prefix, 1, jumlahDigit);
    }

    while (getline(file, baris)) {
        string id = ambilField(baris, posisiFieldId);
        int nomor = ambilNomorDariId(id, prefix);

        if (nomor > nomorTerbesar) {
            nomorTerbesar = nomor;
        }
    }

    file.close();

    return formatId(prefix, nomorTerbesar + 1, jumlahDigit);
}

int inputPilihanMenu() {
    string input;

    getline(cin, input);

    if (!hanyaAngka(input)) 
	{
        return -1;
    }

    return ubahKeAngka(input);
}

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
		
class Logaktivitas {
private:
    string namaFile = "log_aktivitas.txt";

public:
    string getTanggal() {
        time_t sekarang = time(0);
        tm *waktu = localtime(&sekarang);

        stringstream ss;
        ss << setfill('0')
           << setw(2) << waktu->tm_mday << "/"
           << setw(2) << waktu->tm_mon + 1 << "/"
           << waktu->tm_year + 1900;

        return ss.str();
    }

    string getWaktu() {
        time_t sekarang = time(0);
        tm *waktu = localtime(&sekarang);

        stringstream ss;
        ss << setfill('0')
           << setw(2) << waktu->tm_hour << ":"
           << setw(2) << waktu->tm_min;

        return ss.str();
    }

    void catatLog(string aktivitas, string keterangan) {
        ofstream file(namaFile, ios::app);

        if (!file.is_open()) {
            cout << "File log aktivitas tidak dapat dibuka!\n";
            return;
        }

        string id = "-";
        string nama = "-";
        string role = "-";

        if (loginIndex != -1) {
            id = user[loginIndex].getIdUser();
            nama = user[loginIndex].getNama();
            role = user[loginIndex].getRole();
        }

        file << getTanggal() << "|"
             << getWaktu() << "|"
             << id << "|"
             << nama << "|"
             << role << "|"
             << aktivitas << "|"
             << keterangan << endl;

        file.close();
    }

    void tampilLog() {
        ifstream file(namaFile);

        if (!file.is_open()) {
            cout << "Belum ada log aktivitas.\n";
            return;
        }

        string tanggal, waktu, id, nama, role, aktivitas, keterangan;

        cout << "\n================ LOG AKTIVITAS ================\n";
        cout << left
             << setw(12) << "Tanggal"
             << setw(8) << "Waktu"
             << setw(12) << "ID User"
             << setw(18) << "Nama"
             << setw(12) << "Role"
             << setw(18) << "Aktivitas"
             << "Keterangan"
             << endl;

        cout << "--------------------------------------------------------------------------\n";

        while (getline(file, tanggal, '|') &&
               getline(file, waktu, '|') &&
               getline(file, id, '|') &&
               getline(file, nama, '|') &&
               getline(file, role, '|') &&
               getline(file, aktivitas, '|') &&
               getline(file, keterangan)) {

            cout << left
                 << setw(12) << tanggal
                 << setw(8) << waktu
                 << setw(12) << id
                 << setw(18) << nama
                 << setw(12) << role
                 << setw(18) << aktivitas
                 << keterangan
                 << endl;
        }

        file.close();
    }
};

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

			for (int i = 0; i < role.length(); i++)
			{
				role[i] = tolower(role[i]);
			}

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

			cout << "Registrasi berhasil dan data disimpan ke user_data.txt!\n";
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
                Logaktivitas log;
                log.catatLog("LOGIN", "User berhasil login");
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
            Logaktivitas log;
            log.catatLog("LOGOUT", "User logout dari sistem");
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
            Logaktivitas log;
            log.catatLog("GANTI PASSWORD", "User mengganti password akun");
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

class Karyawan{
private:

    //=========================
    // Data Karyawan
    //=========================

    string idKaryawan;
    string nama;
    string jabatan;
    string alamat;
    string noHP;
    int umur;
    char jk;
    double gajiPokok;

    //=========================
    // Data Penggajian
    //=========================

    int hariMasuk;
    int hariIzin;
    int hariAlpha;

    double bonus;
    double potongan;
    double totalGaji;

public:

    //=================================================
    // Constructor Default
    //=================================================

    Karyawan(){

        idKaryawan="";
        nama="";
        jabatan="";
        alamat="";
        noHP="";
        umur=0;
        jk='-';
        gajiPokok=0;

        hariMasuk=0;
        hariIzin=0;
        hariAlpha=0;

        bonus=0;
        potongan=0;
        totalGaji=0;

    }

    //=================================================
    // Constructor Parameter
    //=================================================

    Karyawan(string id,
              string n,
              string jab,
              string alm,
              string hp,
              int u,
              char jenis,
              double gaji){

        idKaryawan=id;
        nama=n;
        jabatan=jab;
        alamat=alm;
        noHP=hp;
        umur=u;
        jk=jenis;
        gajiPokok=gaji;

        hariMasuk=0;
        hariIzin=0;
        hariAlpha=0;

        bonus=0;
        potongan=0;
        totalGaji=0;
    }

    //=================================================
    // SETTER
    //=================================================

    void setIdKaryawan(string id){
        idKaryawan=id;
    }

    void setNama(string n){
        nama=n;
    }

    void setJabatan(string jab){
        jabatan=jab;
    }

    void setAlamat(string alm){
        alamat=alm;
    }

    void setNoHP(string hp){
        noHP=hp;
    }

    void setUmur(int u){
        umur=u;
    }

    void setJenisKelamin(char jenis){
        jk=jenis;
    }

    void setGajiPokok(double gaji){
        gajiPokok=gaji;
    }

    void setHariMasuk(int hm){
        hariMasuk=hm;
    }

    void setHariIzin(int hi){
        hariIzin=hi;
    }

    void setHariAlpha(int ha){
        hariAlpha=ha;
    }

    void setBonus(double b){
        bonus=b;
    }

    void setPotongan(double p){
        potongan=p;
    }

    void setTotalGaji(double t){
        totalGaji=t;
    }

    //=================================================
    // GETTER
    //=================================================

    string getIdKaryawan(){
        return idKaryawan;
    }

    string getNama(){
        return nama;
    }

    string getJabatan(){
        return jabatan;
    }

    string getAlamat(){
        return alamat;
    }

    string getNoHP(){
        return noHP;
    }

    int getUmur(){
        return umur;
    }

    char getJenisKelamin(){
        return jk;
    }

    double getGajiPokok(){
        return gajiPokok;
    }

    int getHariMasuk(){
        return hariMasuk;
    }

    int getHariIzin(){
        return hariIzin;
    }

    int getHariAlpha(){
        return hariAlpha;
    }

    double getBonus(){
        return bonus;
    }

    double getPotongan(){
        return potongan;
    }

    double getTotalGaji(){
        return totalGaji;
    }

    //=================================================
    // Tampilkan Data
    //=================================================

    void tampilKaryawan(){

        cout << "\n======================================" << endl;
        cout << "          DATA KARYAWAN" << endl;
        cout << "======================================" << endl;

        cout << "ID Karyawan    : " << idKaryawan << endl;
        cout << "Nama           : " << nama << endl;
        cout << "Jabatan        : " << jabatan << endl;
        cout << "Alamat         : " << alamat << endl;
        cout << "No HP          : " << noHP << endl;
        cout << "Umur           : " << umur << " Tahun" << endl;
        cout << "Jenis Kelamin  : " << jk << endl;
        cout << "Gaji Pokok     : Rp " << gajiPokok << endl;

        cout << "======================================" << endl;

    }
    //=================================================
    // Fungsi Input kayrawan
    //=================================================
    
    //====================================================
// CEK HAK AKSES MENU GAJI
//====================================================
bool cekHakAksesGaji()
{
    if(jabatan == "General Manager")
        return true;

    if(jabatan == "Manager")
        return true;

    if(jabatan == "Vice President")
        return true;

    return false;
}

    void inputKaryawan()
    {
    ofstream file("data_karyawan.txt", ios::app);

    if(file.is_open()){

        cout << "\n==========================================" << endl;
        cout << "         INPUT DATA KARYAWAN" << endl;
        cout << "==========================================" << endl;


        idKaryawan = generateIdDariFile("data_karyawan.txt", "KRY", 3, 0);

        cout << "ID Karyawan        : " << idKaryawan << endl;
        
        cout << "Nama               : ";
        getline(cin,nama);

        cout << "Jabatan            : ";
        getline(cin,jabatan);

        cout << "Alamat             : ";
        getline(cin,alamat);

        cout << "No HP              : ";
        getline(cin,noHP);

        cout << "Umur               : ";
        cin >> umur;

        cout << "Jenis Kelamin (L/P): ";
        cin >> jk;

        cout << "Gaji Pokok         : ";
        cin >> gajiPokok;

        // Nilai awal absensi
        hariMasuk = 0;
        hariIzin = 0;
        hariAlpha = 0;

        // Nilai awal penggajian
        bonus = 0;
        potongan = 0;
        totalGaji = 0;

        // Simpan ke file
        file << idKaryawan << "|"
             << nama << "|"
             << jabatan << "|"
             << alamat << "|"
             << noHP << "|"
             << umur << "|"
             << jk << "|"
             << gajiPokok << "|"
             << hariMasuk << "|"
             << hariIzin << "|"
             << hariAlpha << "|"
             << bonus << "|"
             << potongan << "|"
             << totalGaji
             << endl;

        file.close();

        cout << "\n==========================================" << endl;
        cout << "Data karyawan berhasil disimpan." << endl;
        cout << "==========================================" << endl;

    }
    else{

        cout << "File data_karyawan.txt tidak dapat dibuka!" << endl;

    }	
}
    void bacaDataKaryawan()
    {

    ifstream file("data_karyawan.txt");

    if(!file.is_open()){

        cout<<"File tidak ditemukan!"<<endl;
        return;

    }

    string line;

    cout<<"\n==============================================================\n";
    cout<<"                    DATA KARYAWAN\n";
    cout<<"==============================================================\n\n";

    cout<<"ID|NAMA|JABATAN|ALAMAT|NO HP|UMUR|JK|GAJI"<<endl<<endl;

    while(getline(file,line)){

        string id="";
        string nama="";
        string jabatan="";
        string alamat="";
        string noHP="";
        string umur="";
        string jk="";
        string gaji="";

        int field=0;

        for(int i=0;i<line.length();i++){

            if(line[i]=='|'){

                field++;

            }
            else{

                if(field==0)
                    id+=line[i];

                else if(field==1)
                    nama+=line[i];

                else if(field==2)
                    jabatan+=line[i];

                else if(field==3)
                    alamat+=line[i];

                else if(field==4)
                    noHP+=line[i];

                else if(field==5)
                    umur+=line[i];

                else if(field==6)
                    jk+=line[i];

                else if(field==7)
                    gaji+=line[i];

            }

        }

        cout<<id<<" | "
            <<nama<<" | "
            <<jabatan<<" | "
            <<alamat<<" | "
            <<noHP<<" | "
            <<umur<<" | "
            <<jk<<" | Rp "
            <<gaji<<endl;

    }

    file.close();	
}
    	void cariKaryawan()
{
    ifstream file("data_karyawan.txt");

    if(!file.is_open())
    {
        cout << "File data karyawan tidak ditemukan!\n";
        return;
    }

    string cari;
    cout << "Masukkan ID atau Nama Karyawan : ";
    getline(cin, cari);

    string line;
    bool ketemu = false;

    while(getline(file, line))
    {
        string id = "";
        string nama = "";
        string jabatan = "";
        string alamat = "";
        string nohp = "";
        string umur = "";
        string jk = "";
        string gaji = "";

        int field = 0;

        for(int i = 0; i < line.length(); i++)
        {
            if(line[i] == '|')
            {
                field++;
            }
            else
            {
                if(field == 0)
                    id += line[i];
                else if(field == 1)
                    nama += line[i];
                else if(field == 2)
                    jabatan += line[i];
                else if(field == 3)
                    alamat += line[i];
                else if(field == 4)
                    nohp += line[i];
                else if(field == 5)
                    umur += line[i];
                else if(field == 6)
                    jk += line[i];
                else if(field == 7)
                    gaji += line[i];
            }
        }

        if(id == cari || nama == cari)
        {
            ketemu = true;

            cout << "\n=========== DATA KARYAWAN ===========\n";
            cout << "ID Karyawan : " << id << endl;
            cout << "Nama        : " << nama << endl;
            cout << "Jabatan     : " << jabatan << endl;
            cout << "Alamat      : " << alamat << endl;
            cout << "No HP       : " << nohp << endl;
            cout << "Umur        : " << umur << endl;
            cout << "Jenis Kelamin : " << jk << endl;
            cout << "Gaji Pokok  : Rp " << gaji << endl;
            cout << "=====================================\n";

            break;
        }
    }

    if(!ketemu)
    {
        cout << "\nData karyawan tidak ditemukan.\n";
    }

    file.close();
}

    void ubahDataKaryawan()
	{
    bacaDataKaryawan();

    cout << endl;

    string idCari;
    cout << "Masukkan ID Karyawan yang ingin diubah : ";
    getline(cin, idCari);

    ifstream file("data_karyawan.txt");
    ofstream temp("temp.txt");

    if(!file.is_open())
    {
        cout << "File tidak ditemukan!\n";
        return;
    }

    string line;
    bool ketemu = false;

    while(getline(file, line))
    {
        string id = "";
        string nama = "";
        string jabatan = "";
        string alamat = "";
        string nohp = "";
        string umur = "";
        string jk = "";
        string gaji = "";

        int field = 0;

        for(int i = 0; i < line.length(); i++)
        {
            if(line[i] == '|')
            {
                field++;
            }
            else
            {
                if(field == 0)
                    id += line[i];
                else if(field == 1)
                    nama += line[i];
                else if(field == 2)
                    jabatan += line[i];
                else if(field == 3)
                    alamat += line[i];
                else if(field == 4)
                    nohp += line[i];
                else if(field == 5)
                    umur += line[i];
                else if(field == 6)
                    jk += line[i];
                else if(field == 7)
                    gaji += line[i];
            }
        }

        if(id == idCari)
        {
            ketemu = true;

            cout << "\n===== INPUT DATA BARU =====\n";

            cout << "Nama            : ";
            getline(cin, nama);

            cout << "Jabatan         : ";
            getline(cin, jabatan);

            cout << "Alamat          : ";
            getline(cin, alamat);

            cout << "No HP           : ";
            getline(cin, nohp);

            cout << "Umur            : ";
            getline(cin, umur);

            cout << "Jenis Kelamin   : ";
            getline(cin, jk);

            cout << "Gaji Pokok      : ";
            getline(cin, gaji);

            temp << id << "|"
                 << nama << "|"
                 << jabatan << "|"
                 << alamat << "|"
                 << nohp << "|"
                 << umur << "|"
                 << jk << "|"
                 << gaji << endl;
        }
        else
        {
            temp << line << endl;
        }
    }

    file.close();
    temp.close();

    remove("data_karyawan.txt");
    rename("temp.txt", "data_karyawan.txt");

    if(ketemu)
        cout << "\nData karyawan berhasil diubah.\n";
    else
        cout << "\nID Karyawan tidak ditemukan.\n";
}

    void hapusDataKaryawan()
	{
    bacaDataKaryawan();

    cout << endl;

    string idCari;

    cout << "Masukkan ID Karyawan yang ingin dihapus : ";
    getline(cin, idCari);

    ifstream file("data_karyawan.txt");

    if(!file.is_open())
    {
        cout << "File tidak ditemukan!\n";
        return;
    }

    ofstream temp("temp.txt");

    string line;
    bool ketemu = false;

    while(getline(file, line))
    {
        string id = "";
        int field = 0;

        for(int i = 0; i < line.length(); i++)
        {
            if(line[i] == '|')
            {
                field++;

                if(field > 0)
                    break;
            }
            else
            {
                id += line[i];
            }
        }

        if(id == idCari)
        {
            ketemu = true;
        }
        else
        {
            temp << line << endl;
        }
    }

    file.close();
    temp.close();

    remove("data_karyawan.txt");
    rename("temp.txt", "data_karyawan.txt");

    if(ketemu)
    {
        cout << "\nData karyawan berhasil dihapus.\n";
        Logaktivitas log;
        log.catatLog("HAPUS KARYAWAN", "Menghapus data karyawan");
    }
    else
    {
        cout << "\nID Karyawan tidak ditemukan.\n";
    }
}	

    void inputAbsensi()
{
    ifstream file("data_karyawan.txt");

    if(!file.is_open())
    {
        cout << "Data karyawan belum ada.\n";
        return;
    }

    cout << "========== DATA KARYAWAN ==========\n";

    string line;

    while(getline(file,line))
    {
        string id="";
        string nama="";

        int field=0;

        for(int i=0;i<line.length();i++)
        {
            if(line[i]=='|')
            {
                field++;
            }
            else
            {
                if(field==0)
                    id+=line[i];
                else if(field==1)
                    nama+=line[i];
            }
        }

        cout<<id<<" - "<<nama<<endl;
    }

    file.close();

    string idCari;
    string nama="";
    string tanggal;
    string jam;
    string status;

    cout<<"\nMasukkan ID Karyawan : ";
    getline(cin,idCari);

    file.open("data_karyawan.txt");

    bool ketemu=false;

    while(getline(file,line))
    {
        string id="";
        int field=0;

        for(int i=0;i<line.length();i++)
        {
            if(line[i]=='|')
            {
                field++;
            }
            else
            {
                if(field==0)
                    id+=line[i];
                else if(field==1)
                    nama+=line[i];
            }
        }

        if(id==idCari)
        {
            ketemu=true;
            break;
        }

        nama="";
    }

    file.close();

    if(!ketemu)
    {
        cout<<"ID Karyawan tidak ditemukan.\n";
        return;
    }

    cout<<"Tanggal (dd/mm/yyyy) : ";
    getline(cin,tanggal);

    cout<<"Jam Masuk (HH:MM) : ";
    getline(cin,jam);

    cout<<"Status (Hadir/Izin/Sakit/Alpha/Terlambat) : ";
    getline(cin,status);

    ofstream simpan("absensi_karyawan.txt",ios::app);

    simpan<<idCari<<"|"
          <<nama<<"|"
          <<tanggal<<"|"
          <<jam<<"|"
          <<status<<endl;

    simpan.close();

    cout<<"\nAbsensi berhasil disimpan.\n";
}
    void hitungGaji()
	{
    bacaDataKaryawan();

    cout << endl;

    string idCari;

    cout << "Masukkan ID Karyawan : ";
    getline(cin,idCari);

    ifstream file("data_karyawan.txt");

    if(!file.is_open())
    {
        cout<<"File data karyawan tidak ditemukan.\n";
        return;
    }

    string line;

    string nama="";
    string jabatan="";
    string alamat="";
    string nohp="";
    string umur="";
    string jk="";
    string gajiStr="";

    bool ketemu=false;

    while(getline(file,line))
    {
        string id="";

        nama="";
        jabatan="";
        alamat="";
        nohp="";
        umur="";
        jk="";
        gajiStr="";

        int field=0;

        for(int i=0;i<line.length();i++)
        {
            if(line[i]=='|')
            {
                field++;
            }
            else
            {
                if(field==0)
                    id+=line[i];
                else if(field==1)
                    nama+=line[i];
                else if(field==2)
                    jabatan+=line[i];
                else if(field==3)
                    alamat+=line[i];
                else if(field==4)
                    nohp+=line[i];
                else if(field==5)
                    umur+=line[i];
                else if(field==6)
                    jk+=line[i];
                else if(field==7)
                    gajiStr+=line[i];
            }
        }

        if(id==idCari)
        {
            ketemu=true;
            break;
        }
    }

    file.close();

    if(!ketemu)
    {
        cout<<"Data karyawan tidak ditemukan.\n";
        return;
    }

    double gajiPokok=atof(gajiStr.c_str());

    int hadir=0;
    int izin=0;
    int sakit=0;
    int alpha=0;
    int terlambat=0;

    ifstream absen("absensi_karyawan.txt");

    while(getline(absen,line))
    {
        string id="";
        string nama="";
        string tanggal="";
        string jam="";
        string status="";

        int field=0;

        for(int i=0;i<line.length();i++)
        {
            if(line[i]=='|')
            {
                field++;
            }
            else
            {
                if(field==0)
                    id+=line[i];
                else if(field==1)
                    nama+=line[i];
                else if(field==2)
                    tanggal+=line[i];
                else if(field==3)
                    jam+=line[i];
                else if(field==4)
                    status+=line[i];
            }
        }

        if(id==idCari)
        {
            if(status=="Hadir")
                hadir++;
            else if(status=="Izin")
                izin++;
            else if(status=="Sakit")
                sakit++;
            else if(status=="Alpha")
                alpha++;
            else if(status=="Terlambat")
                terlambat++;
        }
    }

    absen.close();

    double bonus=hadir*10000;

    double potonganAlpha=alpha*50000;

    double potonganTerlambat=terlambat*5000;

    double gajiBersih=
    gajiPokok
    +bonus
    -potonganAlpha
    -potonganTerlambat;

    cout<<"\n========================================\n";
    cout<<"          SLIP GAJI KARYAWAN\n";
    cout<<"========================================\n";

    cout<<"ID Karyawan      : "<<idCari<<endl;
    cout<<"Nama             : "<<nama<<endl;
    cout<<"Jabatan          : "<<jabatan<<endl;

    cout<<"\nRekap Absensi\n";
    cout<<"Hadir            : "<<hadir<<endl;
    cout<<"Izin             : "<<izin<<endl;
    cout<<"Sakit            : "<<sakit<<endl;
    cout<<"Alpha            : "<<alpha<<endl;
    cout<<"Terlambat        : "<<terlambat<<endl;

    cout<<"\n----------------------------------------\n";

    cout<<"Gaji Pokok       : Rp "<<gajiPokok<<endl;
    cout<<"Bonus Hadir      : Rp "<<bonus<<endl;
    cout<<"Potongan Alpha   : Rp "<<potonganAlpha<<endl;
    cout<<"Potongan Telat   : Rp "<<potonganTerlambat<<endl;

    cout<<"----------------------------------------\n";

    cout<<"GAJI BERSIH      : Rp "<<gajiBersih<<endl;

    cout<<"========================================\n";
}	
    void cetakSlipGaji()
	{
  
    bacaDataKaryawan();

    cout << endl;

    string idCari;

    cout << "Masukkan ID Karyawan : ";
    getline(cin,idCari);

    ifstream file("data_karyawan.txt");

    if(!file.is_open())
    {
        cout<<"File data karyawan tidak ditemukan.\n";
        return;
    }

    string line;

    string nama="";
    string jabatan="";
    string alamat="";
    string nohp="";
    string umur="";
    string jk="";
    string gajiStr="";

    bool ketemu=false;

    while(getline(file,line))
    {
        string id="";

        nama="";
        jabatan="";
        alamat="";
        nohp="";
        umur="";
        jk="";
        gajiStr="";

        int field=0;

        for(int i=0;i<line.length();i++)
        {
            if(line[i]=='|')
            {
                field++;
            }
            else
            {
                if(field==0)
                    id+=line[i];
                else if(field==1)
                    nama+=line[i];
                else if(field==2)
                    jabatan+=line[i];
                else if(field==3)
                    alamat+=line[i];
                else if(field==4)
                    nohp+=line[i];
                else if(field==5)
                    umur+=line[i];
                else if(field==6)
                    jk+=line[i];
                else if(field==7)
                    gajiStr+=line[i];
            }
        }

        if(id==idCari)
        {
            ketemu=true;
            break;
        }
    }

    file.close();

    if(!ketemu)
    {
        cout<<"Data karyawan tidak ditemukan.\n";
        return;
    }

    double gajiPokok = atof(gajiStr.c_str());

    int hadir=0;
    int izin=0;
    int sakit=0;
    int alpha=0;
    int terlambat=0;

    ifstream absen("absensi_karyawan.txt");

    while(getline(absen,line))
    {
        string id="";
        string namaAbsen="";
        string tanggal="";
        string jam="";
        string status="";

        int field=0;

        for(int i=0;i<line.length();i++)
        {
            if(line[i]=='|')
            {
                field++;
            }
            else
            {
                if(field==0)
                    id+=line[i];
                else if(field==1)
                    namaAbsen+=line[i];
                else if(field==2)
                    tanggal+=line[i];
                else if(field==3)
                    jam+=line[i];
                else if(field==4)
                    status+=line[i];
            }
        }

        if(id==idCari)
        {
            if(status=="Hadir")
                hadir++;
            else if(status=="Izin")
                izin++;
            else if(status=="Sakit")
                sakit++;
            else if(status=="Alpha")
                alpha++;
            else if(status=="Terlambat")
                terlambat++;
        }
    }

    absen.close();

    double bonus = hadir * 10000;
    double potonganAlpha = alpha * 50000;
    double potonganTerlambat = terlambat * 5000;

    double gajiBersih =
    gajiPokok
    + bonus
    - potonganAlpha
    - potonganTerlambat;

    cout << "\n=============================================\n";
    cout << "             SLIP GAJI KARYAWAN\n";
    cout << "=============================================\n";

    cout << "ID Karyawan     : " << idCari << endl;
    cout << "Nama            : " << nama << endl;
    cout << "Jabatan         : " << jabatan << endl;

    cout << "---------------------------------------------\n";

    cout << "Jumlah Hadir    : " << hadir << endl;
    cout << "Jumlah Izin     : " << izin << endl;
    cout << "Jumlah Sakit    : " << sakit << endl;
    cout << "Jumlah Alpha    : " << alpha << endl;
    cout << "Jumlah Terlambat: " << terlambat << endl;

    cout << "---------------------------------------------\n";

    cout << "Gaji Pokok      : Rp " << gajiPokok << endl;
    cout << "Bonus Hadir     : Rp " << bonus << endl;
    cout << "Potongan Alpha  : Rp " << potonganAlpha << endl;
    cout << "Potongan Telat  : Rp " << potonganTerlambat << endl;

    cout << "---------------------------------------------\n";

    cout << "GAJI BERSIH     : Rp " << gajiBersih << endl;

    cout << "=============================================\n";

    ofstream slip("slip_gaji.txt",ios::app);

    slip << idCari << "|"
         << nama << "|"
         << jabatan << "|"
         << hadir << "|"
         << izin << "|"
         << sakit << "|"
         << alpha << "|"
         << terlambat << "|"
         << gajiPokok << "|"
         << bonus << "|"
         << potonganAlpha << "|"
         << potonganTerlambat << "|"
         << gajiBersih
         << endl;

    slip.close();

    cout << "\nSlip gaji berhasil disimpan ke slip_gaji.txt\n";
}

    void cariSlipGaji()
{
    ifstream file("slip_gaji.txt");

    if(!file.is_open())
    {
        cout << "File slip gaji tidak ditemukan!" << endl;
        return;
    }

    string cari;
    cout << "Masukkan ID Karyawan atau Nama : ";
    getline(cin, cari);

    bool ketemu = false;
    string line;

    while(getline(file, line))
    {
        string id = "";
        string nama = "";
        string jabatan = "";
        string tanggal = "";
        string hadir = "";
        string gaji = "";

        int field = 0;

        for(int i = 0; i < line.length(); i++)
        {
            if(line[i] == '|')
            {
                field++;
            }
            else
            {
                if(field == 0)
                    id += line[i];

                else if(field == 1)
                    nama += line[i];

                else if(field == 2)
                    jabatan += line[i];

                else if(field == 3)
                    tanggal += line[i];

                else if(field == 4)
                    hadir += line[i];

                else if(field == 5)
                    gaji += line[i];
            }
        }

        if(id == cari || nama == cari)
        {
            ketemu = true;

            cout << "\n===============================" << endl;
            cout << "        SLIP GAJI" << endl;
            cout << "===============================" << endl;
            cout << "ID Karyawan   : " << id << endl;
            cout << "Nama          : " << nama << endl;
            cout << "Jabatan       : " << jabatan << endl;
            cout << "Periode       : " << tanggal << endl;
            cout << "Total Hadir   : " << hadir << endl;
            cout << "Total Gaji    : Rp " << gaji << endl;
            cout << "===============================" << endl;

            break;
        }
    }

    if(!ketemu)
    {
        cout << "\nSlip gaji tidak ditemukan." << endl;
    }

    file.close();
}	
 
 
 void rekapGajiBulanan()
{
    ifstream file("slip_gaji.txt");

    if(!file.is_open())
    {
        cout << "File slip gaji tidak ditemukan!" << endl;
        return;
    }

    string periodeCari;

    cout << "Masukkan Periode (MM/YYYY) : ";
    getline(cin, periodeCari);

    string line;

    bool ada = false;

    int jumlahKaryawan = 0;

    double totalGaji = 0;

    cout << "\n===============================================" << endl;
    cout << "           REKAP GAJI BULANAN" << endl;
    cout << "===============================================" << endl;

    while(getline(file,line))
    {
        string id="";
        string nama="";
        string jabatan="";
        string periode="";
        string hadir="";
        string gaji="";

        int field=0;

        for(int i=0;i<line.length();i++)
        {
            if(line[i]=='|')
            {
                field++;
            }
            else
            {
                if(field==0)
                    id+=line[i];
                else if(field==1)
                    nama+=line[i];
                else if(field==2)
                    jabatan+=line[i];
                else if(field==3)
                    periode+=line[i];
                else if(field==4)
                    hadir+=line[i];
                else if(field==5)
                    gaji+=line[i];
            }
        }

        if(periode==periodeCari)
        {
            ada=true;

            jumlahKaryawan++;

            double nominal=atof(gaji.c_str());

            totalGaji += nominal;

            cout << "ID        : " << id << endl;
            cout << "Nama      : " << nama << endl;
            cout << "Jabatan   : " << jabatan << endl;
            cout << "Hadir     : " << hadir << " Hari" << endl;
            cout << "Gaji      : Rp " << nominal << endl;
            cout << "-----------------------------------------------" << endl;
        }
    }

    file.close();

    if(!ada)
    {
        cout << "Data periode tersebut tidak ditemukan." << endl;
        return;
    }

    cout << endl;
    cout << "Jumlah Karyawan : " << jumlahKaryawan << endl;
    cout << "Total Pengeluaran Gaji : Rp " << totalGaji << endl;
    cout << "===============================================" << endl;
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

		bacaDataObat();

		cout << endl;
	
	    string kodeCari;
	
	    cout << "Masukkan Kode Obat yang ingin diubah : ";
		cin >> kodeCari;
		cin.ignore();

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
        Logaktivitas log;
        log.catatLog("EDIT OBAT", "Mengubah data obat dengan kode: " + kodeCari);
	}

    void inputObat(){
    	ofstream file("daftar_obat.txt", ios::app);

	    if (file.is_open()) {
	    	
			kodeObat = generateIdDariFile("daftar_obat.txt", "OBT", 3, 0);

            cout << "Kode Obat : " << kodeObat << endl;

			cout << "Masukkan Nama Obat : ";
			getline(cin, namaObat);
			
			cout << "Masukkan Harga Obat :";
			cin >> harga;
	    	cin.ignore();
			
			cout << "Masukkan Stok Obat :";
			cin >> stok;
	    	cin.ignore();
			
			cout << "Masukkan Tanggal Expired Obat (Tgl/Bln/Thn):";
			cin >> tanggalExpired;
	    	cin.ignore();
			
			cout << "Masukkan Kategori Obat :";
			cin >> kategori;
	    	cin.ignore();
			
			cout << "Masukkan Satuan Obat per kaplet/tablet :";
			cin >> satuan;
	    	cin.ignore();
			
	        file << kodeObat << "|"
	             << namaObat << "|"
	             << harga << "|"
	             << stok << "|"
	             << tanggalExpired << "|"
	             << kategori << "|"
	             << satuan << "\n";
	
	        file.close();

            Logaktivitas log;
            log.catatLog("TAMBAH OBAT", "Menambahkan obat: " + namaObat);
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

        cout<<"File tidak ditemukan!\n";
        return;

    }

    time_t sekarang=time(0);

		string line;

    bool adaKadaluarsa=false;
    bool adaHampir=false;

    cout<<"\n=========================================\n";
    cout<<"          DAFTAR OBAT KADALUARSA\n";
    cout<<"=========================================\n";

		while(getline(file,line)){

        string kode="";
        string nama="";
        string harga="";
        string stok="";
        string exp="";
        string kategori="";
        string satuan="";

        int field=0;

        for(int i=0;i<line.length();i++){

            if(line[i]=='|'){

                field++;

            }else{

                if(field==0)
                    kode+=line[i];

                else if(field==1)
                    nama+=line[i];

                else if(field==2)
                    harga+=line[i];

                else if(field==3)
                    stok+=line[i];

                else if(field==4)
                    exp+=line[i];

                else if(field==5)
                    kategori+=line[i];

                else if(field==6)
                    satuan+=line[i];

            }

        }

        int hari=0;
        int bulan=0;
        int tahun=0;

        sscanf(exp.c_str(),"%d/%d/%d",&hari,&bulan,&tahun);

        tm waktuExp={};

        waktuExp.tm_mday=hari;
        waktuExp.tm_mon=bulan-1;
        waktuExp.tm_year=tahun-1900;

        time_t tanggalExp=mktime(&waktuExp);

        double selisih=difftime(tanggalExp,sekarang)/(60*60*24);

        if(selisih<0){

            adaKadaluarsa=true;

            cout<<kode<<" | "
                <<nama<<" | "
                <<exp<<endl;

			}

		}

    if(!adaKadaluarsa){

        cout<<"Tidak ada obat yang sudah kadaluarsa.\n";

    }

    file.clear();
    file.seekg(0);

    cout<<"\n=========================================\n";
    cout<<"     DAFTAR OBAT HAMPIR KADALUARSA\n";
    cout<<"=========================================\n";

    while(getline(file,line)){

        string kode="";
        string nama="";
        string harga="";
        string stok="";
        string exp="";
        string kategori="";
        string satuan="";

        int field=0;

        for(int i=0;i<line.length();i++){

            if(line[i]=='|'){

                field++;

            }else{

                if(field==0)
                    kode+=line[i];

                else if(field==1)
                    nama+=line[i];

                else if(field==2)
                    harga+=line[i];

                else if(field==3)
                    stok+=line[i];

                else if(field==4)
                    exp+=line[i];

                else if(field==5)
                    kategori+=line[i];

                else if(field==6)
                    satuan+=line[i];

            }

        }

        int hari=0;
        int bulan=0;
        int tahun=0;

        sscanf(exp.c_str(),"%d/%d/%d",&hari,&bulan,&tahun);

        tm waktuExp={};

        waktuExp.tm_mday=hari;
        waktuExp.tm_mon=bulan-1;
        waktuExp.tm_year=tahun-1900;

        time_t tanggalExp=mktime(&waktuExp);

        double selisih=difftime(tanggalExp,sekarang)/(60*60*24);

        if(selisih>=0 && selisih<=7){

            adaHampir=true;

            cout<<kode<<" | "
                <<nama<<" | "
                <<exp
                <<" ("<<(int)selisih<<" hari lagi)"
                <<endl;

        }

		}

    if(!adaHampir){

        cout<<"\nTidak ada obat yang hampir kadaluarsa.\n";

    }

    file.close();

}
    
    void stokMenipis(){

    ifstream file("daftar_obat.txt");

    if(!file.is_open()){
        cout<<"File tidak ditemukan!\n";
        return;
    }

    string line;

    bool ada=false;

    cout<<"\n===== DAFTAR STOK MENIPIS =====\n\n";
    cout<<"KODE|NAMA|STOK\n\n";

    while(getline(file,line)){

        string kode="";
        string nama="";
        string hargaStr="";
        string stokStr="";
        string exp="";
        string kategori="";
        string satuan="";

        int field=0;

        for(int i=0;i<line.length();i++){

            if(line[i]=='|'){

                field++;

            }
			else
			{

                if(field==0)
                    kode+=line[i];

                else if(field==1)
                    nama+=line[i];

                else if(field==2)
                    hargaStr+=line[i];

                else if(field==3)
                    stokStr+=line[i];

                else if(field==4)
                    exp+=line[i];

                else if(field==5)
                    kategori+=line[i];

                else if(field==6)
                    satuan+=line[i];

            }

        }

        int stok=atoi(stokStr.c_str());

        if(stok<=10){

            ada=true;

            cout<<kode<<" | "
                <<nama<<" | "
                <<stok<<endl;

        }

    }

    if(!ada){

        cout<<"Tidak ada obat yang stoknya menipis.\n";

    }

    file.close();

}

    void tampilMonitoring(){

        Obat obat;

        cout<<"=========================================\n";
        cout<<"      MONITORING STOK APOTEK\n";
        cout<<"=========================================\n";

        cout<<"\n1. STOK MENIPIS\n";
        obat.stokMenipis();

        cout<<"\n\n2. STATUS KADALUARSA\n";
        obat.cekKadaluarsa();

        cout<<"\n=========================================\n";
        cout<<"Monitoring selesai.\n";
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

    bacaDataObat();

    string kodeCari;
    cout << "\nMasukkan Kode Obat yang akan diubah harganya : ";
    cin >> kodeCari;
	cin.ignore();
    bool ketemu = false;

    for(int i = 0; i < daftar.size(); i++){

        if(daftar[i].getkodeObat() == kodeCari){

            ketemu = true;

            double hargaBaru;

            cout << "Harga lama : " << daftar[i].getHarga() << endl;
            cout << "Masukkan harga baru : ";
            cin >> hargaBaru;
			cin.ignore();

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
    Logaktivitas log;
    log.catatLog("UBAH HARGA OBAT", "Mengubah harga obat");
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
	
    void bacaDataObat() {
    ifstream file("daftar_obat.txt");

    string line;

    if (!file.is_open()) {
        cout << "File tidak ditemukan!" << endl;
        return;
    }

    cout << "\n=================================================================================================================\n";
    cout << "                                             DATA OBAT\n";
    cout << "=================================================================================================================\n";

    cout << left
         << setw(12) << "Kode"
         << setw(25) << "Nama Obat"
         << setw(15) << "Harga"
         << setw(8)  << "Stok"
         << setw(15) << "Expired"
         << setw(18) << "Kategori"
         << setw(12) << "Satuan"
         << endl;

    cout << "-----------------------------------------------------------------------------------------------------------------\n";

    while (getline(file, line)) {
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
            } else {
                if (field == 0)
                    kodeObat += line[i];
                else if (field == 1)
                    namaObat += line[i];
                else if (field == 2)
                    tempHarga += line[i];
                else if (field == 3)
                    tempStok += line[i];
                else if (field == 4)
                    tanggalExpired += line[i];
                else if (field == 5)
                    kategori += line[i];
                else if (field == 6)
                    satuan += line[i];
            }
        }

        harga = atof(tempHarga.c_str());
        stok = atoi(tempStok.c_str());

        cout << left
             << setw(12) << kodeObat
             << setw(25) << namaObat
             << "Rp " << setw(12) << harga
             << setw(8)  << stok
             << setw(15) << tanggalExpired
             << setw(18) << kategori
             << setw(12) << satuan
             << endl;
    }

    cout << "=================================================================================================================\n";

    file.close();
}
	
	// Menambah stok obat setelah barang diterima dari supplier
	void tambahStok(string kodeCari, int jumlahTambah){
	
	    ifstream file("daftar_obat.txt");
	    ofstream temp("temp.txt");
	
	    if(!file.is_open()){
	        cout << "File daftar obat tidak ditemukan!" << endl;
	        return;
	    }
	
	    string kode;
	    string nama;
	    string harga;
	    string stok;
	    string exp;
	    string kategori;
	    string satuan;
	
	    while(getline(file,kode,'|') &&
	          getline(file,nama,'|') &&
	          getline(file,harga,'|') &&
	          getline(file,stok,'|') &&
	          getline(file,exp,'|') &&
	          getline(file,kategori,'|') &&
	          getline(file,satuan))
	    {
	
	        if(kode == kodeCari)
	        {
	            int stokBaru = atoi(stok.c_str());
	            stokBaru += jumlahTambah;
	
	            temp << kode << "|"
	                 << nama << "|"
	                 << harga << "|"
	                 << stokBaru << "|"
	                 << exp << "|"
	                 << kategori << "|"
	                 << satuan << endl;
	        }
	        else
	        {
	            temp << kode << "|"
	                 << nama << "|"
	                 << harga << "|"
	                 << stok << "|"
	                 << exp << "|"
	                 << kategori << "|"
	                 << satuan << endl;
	        }
	    }
	
	    file.close();
	    temp.close();
	
	    remove("daftar_obat.txt");
	    rename("temp.txt","daftar_obat.txt");
	}

};

class Supplier{
private:

    // Identitas supplier
    string idSupplier;
    string namaPerusahaan;
    string noHP;
    string alamat;
    
    // Data pemesanan
	string idPesanan;
	string kodeObat;
	string namaObat;
	int jumlahPesan;
	string tanggalPesan;
	string statusPesanan;

public:

    // Constructor default
    Supplier()
    {
        idSupplier = "";
        namaPerusahaan = "";
        noHP = "";
        alamat = "";
    }

    // Constructor dengan parameter
    Supplier(string id, string nama, string hp, string almt)
    {
        idSupplier = id;
        namaPerusahaan = nama;
        noHP = hp;
        alamat = almt;
    }

    // Setter ID Supplier
    void setIdSupplier(string id)
    {
        idSupplier = id;
    }

    // Setter Nama Perusahaan
    void setNama(string nama)
    {
        namaPerusahaan = nama;
    }

    // Setter Nomor HP
    void setNoHP(string hp)
    {
        noHP = hp;
    }

    // Setter Alamat Supplier
    void setAlamat(string almt)
    {
        alamat = almt;
    }

    // Getter ID Supplier
    string getIdSupplier()
    {
        return idSupplier;
    }

    // Getter Nama Perusahaan
    string getNama()
    {
        return namaPerusahaan;
    }

    // Getter Nomor HP
    string getNoHP()
    {
        return noHP;
    }

    // Getter Alamat Supplier
    string getAlamat()
    {
        return alamat;
    }

    // Menampilkan informasi supplier ke layar
    void tampilSupplier()
    {
        cout << "\n==========================================" << endl;
        cout << "            DATA SUPPLIER" << endl;
        cout << "==========================================" << endl;
        cout << "ID Supplier      : " << idSupplier << endl;
        cout << "Nama Perusahaan  : " << namaPerusahaan << endl;
        cout << "No. HP           : " << noHP << endl;
        cout << "Alamat           : " << alamat << endl;
        cout << "==========================================" << endl;
    }
    
   // Menambahkan data supplier baru ke file
	void tambahSupplier() {
        header("TAMBAH SUPPLIER");

        string idBaru = generateIdDariFile("supplier.txt", "SUP", 3, 0);

        cout << "ID Supplier      : " << idBaru << endl;

        if (cariSupplier(idBaru)) {
            cout << "\nID Supplier sudah digunakan!" << endl;
            footer();
            return;
        }

        idSupplier = idBaru;

        cout << "Nama Perusahaan  : ";
        getline(cin, namaPerusahaan);

        cout << "No. HP           : ";
        getline(cin, noHP);

        cout << "Alamat           : ";
        getline(cin, alamat);

        ofstream file("supplier.txt", ios::app);

        if (!file.is_open()) {
            cout << "File supplier tidak dapat dibuka!" << endl;
            footer();
            return;
        }

        file << idSupplier << "|"
            << namaPerusahaan << "|"
            << noHP << "|"
            << alamat << endl;

        file.close();

        cout << "\nData supplier berhasil disimpan." << endl;
        Logaktivitas log;
        log.catatLog("TAMBAH SUPPLIER", "Menambahkan supplier baru: " + namaPerusahaan);
        footer();
    }
	
	// Menampilkan seluruh data supplier
	void bacaSupplier(){
	
	    ifstream file("supplier.txt");
	
	    if(!file.is_open()){
	        cout << "File supplier tidak ditemukan!" << endl;
	        return;
	    }
        
        cout << "==========================================================================" << endl;
	    cout << left
	         << setw(12) << "ID"
	         << setw(25) << "Nama Perusahaan"
	         << setw(18) << "No HP"
	         << setw(25) << "Alamat"
	         << endl;
	    cout << "--------------------------------------------------------------------------" << endl;
	
	    while(getline(file,idSupplier,'|') &&
	          getline(file,namaPerusahaan,'|') &&
	          getline(file,noHP,'|') &&
	          getline(file,alamat))
	    {
	
	        cout << left
	             << setw(12) << idSupplier
	             << setw(25) << namaPerusahaan
	             << setw(18) << noHP
	             << setw(25) << alamat
	             << endl;
	
	    }
	
	    cout << "--------------------------------------------------------------------------" << endl;
	
	    file.close();
	}
	
	// Mencari supplier berdasarkan ID
	bool cariSupplier(string idCari) {
        ifstream file("supplier.txt");

        if (!file.is_open()) {
            return false;
        }

        string idTemp, namaTemp, hpTemp, alamatTemp;

        while (getline(file, idTemp, '|') &&
            getline(file, namaTemp, '|') &&
            getline(file, hpTemp, '|') &&
            getline(file, alamatTemp)) {

            if (idTemp == idCari) {
                idSupplier = idTemp;
                namaPerusahaan = namaTemp;
                noHP = hpTemp;
                alamat = alamatTemp;

                file.close();
                return true;
            }
        }

        file.close();
        return false;
    }
	
	// Memilih supplier yang akan digunakan untuk restock
	bool pilihSupplier(){
	
	    // system("cls");
	
	    header("PILIH SUPPLIER");
	
	    bacaSupplier();
	
	    string idCari;
	
	    cout << "\nMasukkan ID Supplier : ";
	    getline(cin, idCari);
	
	    if(cariSupplier(idCari))
	    {
	        cout << "\nSupplier berhasil dipilih." << endl;
	        cout << "ID Supplier   : " << idSupplier << endl;
	        cout << "Nama Supplier : " << namaPerusahaan << endl;
	
	        footer();
	
	        return true;
	    }
	
	    cout << "\nSupplier tidak ditemukan!" << endl;
	
	    footer();
	
	    return false;
	}
	
	// Mengubah data supplier berdasarkan ID
	void ubahSupplier(){
	
	    string idCari;
	
	    cout << "\nMasukkan ID Supplier : ";
	    getline(cin, idCari);
	
	    ifstream file("supplier.txt");
	    ofstream temp("temp_supplier.txt");
	
	    if(!file.is_open() || !temp.is_open()){
	        cout << "\nFile tidak dapat dibuka!" << endl;
	        return;
	    }
	
	    bool ditemukan = false;
	
	    while(getline(file,idSupplier,'|') &&
	          getline(file,namaPerusahaan,'|') &&
	          getline(file,noHP,'|') &&
	          getline(file,alamat))
	    {
	
	        if(idSupplier == idCari){
	
	            ditemukan = true;
	
	            cout << "\n===== DATA LAMA =====" << endl;
	            tampilSupplier();
	
	            cout << "\n===== INPUT DATA BARU =====" << endl;
	
	            cout << "Nama Perusahaan : ";
	            getline(cin,namaPerusahaan);
	
	            cout << "No. HP          : ";
	            getline(cin,noHP);
	
	            cout << "Alamat          : ";
	            getline(cin,alamat);
	        }
	
	        temp << idSupplier << "|"
	             << namaPerusahaan << "|"
	             << noHP << "|"
	             << alamat << endl;
	    }
	
	    file.close();
	    temp.close();
	
	    remove("supplier.txt");
	    rename("temp_supplier.txt","supplier.txt");
	
	    if(ditemukan)
	        cout << "\nData supplier berhasil diubah." << endl;
	    else
	        cout << "\nSupplier tidak ditemukan." << endl;
	}
	
	// Menghapus data supplier berdasarkan ID
	void hapusSupplier(){
	
	    string idCari;
	
	    cout << "\nMasukkan ID Supplier : ";
	    getline(cin,idCari);
	
	    ifstream file("supplier.txt");
	    ofstream temp("temp_supplier.txt");
	
	    if(!file.is_open() || !temp.is_open()){
	        cout << "\nFile tidak dapat dibuka!" << endl;
	        return;
	    }
	
	    bool ditemukan = false;
	
	    while(getline(file,idSupplier,'|') &&
	          getline(file,namaPerusahaan,'|') &&
	          getline(file,noHP,'|') &&
	          getline(file,alamat))
	    {
	
	        if(idSupplier == idCari){
	            ditemukan = true;
	            continue;
	        }
	
	        temp << idSupplier << "|"
	             << namaPerusahaan << "|"
	             << noHP << "|"
	             << alamat << endl;
	    }
	
	    file.close();
	    temp.close();
	
	    remove("supplier.txt");
	    rename("temp_supplier.txt","supplier.txt");
	
	    if(ditemukan){
	        cout << "\nSupplier berhasil dihapus." << endl;
            Logaktivitas log;
            log.catatLog("HAPUS SUPPLIER", "Menghapus supplier dengan ID: " + idCari);
        }
	    else
        { 
	        cout << "\nSupplier tidak ditemukan." << endl;
	    }
    }
	
	// Membuat ID pesanan supplier otomatis
	void generateIDPesanan(){
	
	    ifstream file("pesanan_supplier.txt");
	
	    int nomor = 1;
	    string baris;
	
	    while(getline(file, baris)){
	        nomor++;
	    }
	
	    file.close();
	
	    stringstream ss;
	
	    ss << "PS";
	
	    if(nomor < 10)
	        ss << "000";
	    else if(nomor < 100)
	        ss << "00";
	    else if(nomor < 1000)
	        ss << "0";
	
	    ss << nomor;
	
	    idPesanan = ss.str();
	}
	
	// Memilih obat yang akan direstock
	bool pilihObat(){
	
	    // system("cls");
	
	    header("PILIH OBAT");
	
	    Obat obat;
	
	    obat.bacaDataObat();
	
	    string namaCari;
	
	    cout << "\nMasukkan Nama Obat : ";
	    getline(cin, namaCari);
	
	    if(obat.cariObat(namaCari))
	    {
	        kodeObat = obat.getkodeObat();
	        namaObat = obat.getnamaObat();
	
	        cout << "\nObat berhasil dipilih." << endl;
	        cout << "Kode Obat : " << kodeObat << endl;
	        cout << "Nama Obat : " << namaObat << endl;
	
	        footer();
	
	        return true;
	    }
	
	    cout << "\nObat tidak ditemukan!" << endl;
	
	    footer();
	
	    return false;
	}
	
	// Menginput data pemesanan restock
	void inputDataPesanan(){
	
	    cout << "\n========== DATA PEMESANAN ==========\n";
	
	    do{
	
	        cout << "Jumlah Pesanan : ";
	        cin >> jumlahPesan;
	        cin.ignore();
	
	        if(jumlahPesan <= 0)
	        {
	            cout << "\nJumlah pesanan harus lebih dari 0!\n";
	        }
	
	    }while(jumlahPesan <= 0);
	
	    cout << "Tanggal Pesanan (dd-mm-yyyy) : ";
	    getline(cin, tanggalPesan);
	
	    statusPesanan = "Menunggu";
	}
	
	// Menampilkan ringkasan pesanan sebelum disimpan
	void tampilRingkasanPesanan(){
	
	    header("RINGKASAN PESANAN");
	
	    cout << "ID Pesanan      : " << idPesanan << endl;
	    cout << "ID Supplier     : " << idSupplier << endl;
	    cout << "Nama Supplier   : " << namaPerusahaan << endl;
	    cout << "Kode Obat       : " << kodeObat << endl;
	    cout << "Nama Obat       : " << namaObat << endl;
	    cout << "Jumlah Pesanan  : " << jumlahPesan << endl;
	    cout << "Tanggal Pesanan : " << tanggalPesan << endl;
	    cout << "Status          : " << statusPesanan << endl;
	
	    footer();
	}
	
	// Menyimpan data pesanan supplier ke file
	void simpanPesanan(){
	
	    ofstream file("pesanan_supplier.txt", ios::app);
	
	    if(!file.is_open()){
	        cout << "File pesanan supplier tidak dapat dibuka!" << endl;
	        return;
	    }
	
	    file << idPesanan << "|"
	         << idSupplier << "|"
	         << kodeObat << "|"
	         << namaObat << "|"
	         << jumlahPesan << "|"
	         << tanggalPesan << "|"
	         << statusPesanan << endl;
	
	    file.close();
	
	    cout << "\nPesanan supplier berhasil disimpan." << endl;
        Logaktivitas log;
        log.catatLog("RESTOCK", "Membuat pesanan restock obat: " + namaObat);
	}
	
	// Melakukan pemesanan restock ke supplier
	void pesanRestock(){
	
	    generateIDPesanan();
	
	    if(!pilihSupplier())
	        return;
	
	    if(!pilihObat())
	        return;
	
	    inputDataPesanan();
	
	    tampilRingkasanPesanan();
	
	    char pilih;
	
	    cout << "\nSimpan pesanan? (Y/T) : ";
	    cin >> pilih;
	    cin.ignore();
	
	    if(toupper(pilih) == 'Y')
	    {
	        simpanPesanan();
	
	        cout << "\nPesanan berhasil disimpan." << endl;
            Logaktivitas log;
            log.catatLog("RESTOCK", "Membuat pesanan restock obat: " + namaObat);
	    }
	    else
	    {
	        cout << "\nPesanan dibatalkan." << endl;
	    }
	}
	
	// Menampilkan seluruh data pesanan supplier
	void bacaPesanan(){
	
	    ifstream file("pesanan_supplier.txt");
	
	    if(!file.is_open()){
	        cout << "File pesanan supplier tidak ditemukan!" << endl;
	        return;
	    }
	
	    string id;
	    string supplier;
	    string kode;
	    string nama;
	    string jumlah;
	    string tanggal;
	    string status;
	
	    cout << left
	         << setw(10) << "ID"
	         << setw(10) << "Supplier"
	         << setw(10) << "Kode"
	         << setw(20) << "Nama Obat"
	         << setw(10) << "Jumlah"
	         << setw(15) << "Tanggal"
	         << setw(15) << "Status"
	         << endl;
	
	    cout << "------------------------------------------------------------------------------------------" << endl;
	
	    while(getline(file,id,'|') &&
	          getline(file,supplier,'|') &&
	          getline(file,kode,'|') &&
	          getline(file,nama,'|') &&
	          getline(file,jumlah,'|') &&
	          getline(file,tanggal,'|') &&
	          getline(file,status))
	    {
	
	        cout << left
	             << setw(10) << id
	             << setw(10) << supplier
	             << setw(10) << kode
	             << setw(20) << nama
	             << setw(10) << jumlah
	             << setw(15) << tanggal
	             << setw(15) << status
	             << endl;
	    }
	
	    file.close();
	}
	
	// Mencari pesanan berdasarkan ID Pesanan
	bool cariPesanan(string idCari){
	
	    ifstream file("pesanan_supplier.txt");
	
	    if(!file.is_open()){
	        cout << "File pesanan supplier tidak ditemukan!" << endl;
	        return false;
	    }
	
	    while(getline(file,idPesanan,'|') &&
	          getline(file,idSupplier,'|') &&
	          getline(file,kodeObat,'|') &&
	          getline(file,namaObat,'|') &&
	          file >> jumlahPesan)
	    {
	        file.ignore();
	
	        getline(file,tanggalPesan,'|');
	        getline(file,statusPesanan);
	
	        if(idPesanan == idCari)
			{
				cout << "\n========== DATA PESANAN ==========\n";
				cout << "ID Pesanan      : " << idPesanan << endl;
				cout << "ID Supplier     : " << idSupplier << endl;
				cout << "Kode Obat       : " << kodeObat << endl;
				cout << "Nama Obat       : " << namaObat << endl;
				cout << "Jumlah Pesanan  : " << jumlahPesan << endl;
				cout << "Tanggal Pesanan : " << tanggalPesan << endl;
				cout << "Status Saat Ini : " << statusPesanan << endl;

				file.close();
				return true;
			}
	    }
	    
	    cout << "\n========== DATA PESANAN ==========\n";

		cout << "ID Pesanan      : " << idPesanan << endl;
		cout << "ID Supplier     : " << idSupplier << endl;
		cout << "Kode Obat       : " << kodeObat << endl;
		cout << "Nama Obat       : " << namaObat << endl;
		cout << "Jumlah Pesanan  : " << jumlahPesan << endl;
		cout << "Tanggal Pesanan : " << tanggalPesan << endl;
		cout << "Status Saat Ini : " << statusPesanan << endl;
	
	    file.close();
	
	    return false;
	}
	
	// Memilih status baru pesanan
	void pilihStatusBaru(){
	
	    int pilihan;
	
	    cout << "\n========== UPDATE STATUS ==========\n";
	    cout << "1. Diproses" << endl;
	    cout << "2. Dikirim" << endl;
	
	    cout << "\nPilih Status : ";
	    
		pilihan = inputPilihanMenu();
	
	    switch(pilihan)
	    {
	        case 1:
	            statusPesanan = "Diproses";
	            break;
	
	        case 2:
	            statusPesanan = "Dikirim";
	            break;
	
	        default:
	            cout << "\nPilihan tidak valid!" << endl;
	            statusPesanan = "";
				break;
	    }
	}
	
	// Mengubah status pesanan supplier
	void updateStatus(){
	
	    header("UPDATE STATUS PESANAN");
	
	    bacaPesanan();
	
	    string idCari;
	
	    cout << "\nMasukkan ID Pesanan : ";
	    getline(cin, idCari);
	
	    if(!cariPesanan(idCari))
	    {
	        cout << "\nPesanan tidak ditemukan!" << endl;
	        footer();
	        return;
	    }
	
	    // Simpan status lama
		string statusLama = statusPesanan;
		
		// User memilih status baru
		pilihStatusBaru();
		
		// Jika pilihan tidak valid
		if(statusPesanan == "")
		{
		    footer();
		    return;
		}
		
		// Validasi perubahan status
		if(!validasiStatus(statusLama, statusPesanan))
		{
		    cout << "\nPerubahan status tidak valid!" << endl;
		    cout << "Status hanya boleh berubah secara berurutan." << endl;
		
		    footer();
		    return;
		}
	
	    ubahStatusPesanan(idCari, statusPesanan);

		cout << "\nStatus pesanan berhasil diperbarui." << endl;
		
		footer();
	}
	
	// Memvalidasi perubahan status pesanan
	bool validasiStatus(string statusLama, string statusBaru){
	
	    if(statusLama == "Menunggu" && statusBaru == "Diproses")
	        return true;
	
	    if(statusLama == "Diproses" && statusBaru == "Dikirim")
	        return true;
	
	    return false;
	}
	
	// Menampilkan pesanan yang sedang dikirim
	bool bacaPesananDikirim() {
        ifstream file("pesanan_supplier.txt");

        if (!file.is_open()) {
            cout << "File pesanan supplier tidak ditemukan!" << endl;
            return false;
        }

        string id;
        string supplier;
        string kode;
        string nama;
        string jumlah;
        string tanggal;
        string status;

        bool ada = false;

        cout << left
            << setw(10) << "ID"
            << setw(10) << "Supplier"
            << setw(10) << "Kode"
            << setw(20) << "Nama Obat"
            << setw(10) << "Jumlah"
            << setw(15) << "Tanggal"
            << setw(15) << "Status"
            << endl;

        cout << "------------------------------------------------------------------------------------------" << endl;

        while (getline(file, id, '|') &&
            getline(file, supplier, '|') &&
            getline(file, kode, '|') &&
            getline(file, nama, '|') &&
            getline(file, jumlah, '|') &&
            getline(file, tanggal, '|') &&
            getline(file, status)) {

            if (status == "Dikirim") {
                ada = true;

                cout << left
                    << setw(10) << id
                    << setw(10) << supplier
                    << setw(10) << kode
                    << setw(20) << nama
                    << setw(10) << jumlah
                    << setw(15) << tanggal
                    << setw(15) << status
                    << endl;
            }
        }

        file.close();

        if (!ada) {
            cout << "\nTidak ada pesanan dengan status Dikirim.\n";
        }

        return ada;
    }
	
	// Mengonfirmasi bahwa barang dari supplier telah diterima
	void konfirmasiBarang() {
        header("KONFIRMASI PENERIMAAN BARANG");

        if (!bacaPesananDikirim()) {
            footer();
            return;
        }

        string idCari;

        cout << "\nMasukkan ID Pesanan : ";
        getline(cin, idCari);

        if (!cariPesanan(idCari)) {
            cout << "\nPesanan tidak ditemukan!" << endl;
            footer();
            return;
        }

        if (statusPesanan != "Dikirim") {
            cout << "\nPesanan belum dapat dikonfirmasi." << endl;
            cout << "Status saat ini : " << statusPesanan << endl;

            footer();
            return;
        }

        cout << "\n========== DATA PESANAN ==========\n";
        cout << "ID Pesanan      : " << idPesanan << endl;
        cout << "Nama Obat       : " << namaObat << endl;
        cout << "Jumlah Pesanan  : " << jumlahPesan << endl;
        cout << "Status          : " << statusPesanan << endl;

        string pilih;

        cout << "\nKonfirmasi barang diterima? (Y/T) : ";
        getline(cin, pilih);

        if (pilih != "Y" && pilih != "y") {
            cout << "\nKonfirmasi dibatalkan." << endl;
            footer();
            return;
        }

        Obat obat;

        obat.tambahStok(kodeObat, jumlahPesan);

        ubahStatusPesanan(idCari, "Diterima");

        cout << "\nBarang berhasil diterima." << endl;
        cout << "Stok obat berhasil diperbarui." << endl;

        Logaktivitas log;
        log.catatLog("KONFIRMASI BARANG", "Barang restock diterima: " + namaObat);

        footer();
    }
	
	// Mengubah status pesanan berdasarkan ID Pesanan
	void ubahStatusPesanan(string idCari, string statusBaru){
	
	    ifstream file("pesanan_supplier.txt");
	    ofstream temp("temp.txt");
	
	    if(!file.is_open()){
	        cout << "File pesanan supplier tidak ditemukan!" << endl;
	        return;
	    }
	
	    string id;
	    string supplier;
	    string kode;
	    string nama;
	    string jumlah;
	    string tanggal;
	    string status;
	
	    while(getline(file,id,'|') &&
	          getline(file,supplier,'|') &&
	          getline(file,kode,'|') &&
	          getline(file,nama,'|') &&
	          getline(file,jumlah,'|') &&
	          getline(file,tanggal,'|') &&
	          getline(file,status))
	    {
	
	        if(id == idCari)
	        {
	            status = statusBaru;
	        }
	
	        temp << id << "|"
	             << supplier << "|"
	             << kode << "|"
	             << nama << "|"
	             << jumlah << "|"
	             << tanggal << "|"
	             << status << endl;
	    }
	
	    file.close();
	    temp.close();
	
	    remove("pesanan_supplier.txt");
	    rename("temp.txt","pesanan_supplier.txt");
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

class LaporanKeuangan {
private:
    string fileKeuangan = "keuangan.txt";

public:
    string tanggalHariIni() {
        time_t sekarang = time(0);
        tm *waktu = localtime(&sekarang);

        stringstream ss;

        ss << setfill('0')
           << setw(2) << waktu->tm_mday << "/"
           << setw(2) << waktu->tm_mon + 1 << "/"
           << waktu->tm_year + 1900;

        return ss.str();
    }

    void catatKeuangan(string id, string jenis, string kategori, string keterangan, double pemasukan, double pengeluaran) {
        ofstream file(fileKeuangan, ios::app);

        if (!file.is_open()) 
        {
            cout << "File keuangan tidak dapat dibuka!\n";
            return;
        }

        file << id << "|"
             << tanggalHariIni() << "|"
             << jenis << "|"
             << kategori << "|"
             << keterangan << "|"
             << pemasukan << "|"
             << pengeluaran << endl;

        file.close();
    }

    void catatPemasukanPenjualan(string idTransaksi, double total) {
        catatKeuangan(
            idTransaksi,
            "PEMASUKAN",
            "PENJUALAN",
            "Penjualan obat",
            total,
            0
        );
    }

    void catatPengeluaranRestock(string idPesanan, string namaObat, double totalBiaya) {
        catatKeuangan(
            idPesanan,
            "PENGELUARAN",
            "RESTOCK",
            "Restock " + namaObat,
            0,
            totalBiaya
        );
    }

    void catatPengeluaranGaji(string idGaji, string namaKaryawan, double totalGaji) {
        catatKeuangan(
            idGaji,
            "PENGELUARAN",
            "GAJI",
            "Gaji " + namaKaryawan,
            0,
            totalGaji
        );
    }

    void inputPengeluaranRutin() {
        string id, kategori, keterangan;
        double nominal;

        cout << "\n=== INPUT PENGELUARAN RUTIN ===\n";
        id = generateIdDariFile("keuangan.txt", "PG", 3, 0);

        cout << "ID Pengeluaran : " << id << endl;  

        cout << "Kategori (SEWA/LISTRIK/AIR/INTERNET/LAINNYA) : ";
        getline(cin, kategori);

        cout << "Keterangan : ";
        getline(cin, keterangan);

        cout << "Nominal Pengeluaran : Rp ";
        cin >> nominal;
        cin.ignore();

        if (nominal <= 0) 
        {
            cout << "Nominal harus lebih dari 0!\n";
            return;
        }

        catatKeuangan(
            id,
            "PENGELUARAN",
            kategori,
            keterangan,
            0,
            nominal
        );

        cout << "Pengeluaran berhasil dicatat.\n";
    }

    bool cocokTanggal(string tanggal, int hari, int bulan, int tahun) {
        int h, b, t;
        char s1, s2;

        stringstream ss(tanggal);
        ss >> h >> s1 >> b >> s2 >> t;

        return h == hari && b == bulan && t == tahun;
    }

    bool cocokBulan(string tanggal, int bulan, int tahun) {
        int h, b, t;
        char s1, s2;

        stringstream ss(tanggal);
        ss >> h >> s1 >> b >> s2 >> t;

        return b == bulan && t == tahun;
    }

    bool cocokTahun(string tanggal, int tahun) {
        int h, b, t;
        char s1, s2;

        stringstream ss(tanggal);
        ss >> h >> s1 >> b >> s2 >> t;

        return t == tahun;
    }

    void tampilLaporan(int mode) {
        ifstream file(fileKeuangan);

        if (!file.is_open()) 
        {
            cout << "Belum ada data keuangan.\n";
            return;
        }

        int hari = 0, bulan = 0, tahun = 0;

        if (mode == 1) 
        {
            cout << "Masukkan tanggal  : ";
            cin >> hari;
            cout << "Masukkan bulan : ";
            cin >> bulan;
            cout << "Masukkan tahun : ";
            cin >> tahun;
            cin.ignore();
        } 
        else if (mode == 2) 
        {
            cout << "Masukkan bulan : ";
            cin >> bulan;
            cout << "Masukkan tahun : ";
            cin >> tahun;
            cin.ignore();
        } 
        else if (mode == 3) 
        {
            cout << "Masukkan tahun : ";
            cin >> tahun;
            cin.ignore();
        }

        string line;
        double totalPemasukan = 0;
        double totalPengeluaran = 0;
        bool adaData = false;

        cout << "\n================ LAPORAN KEUANGAN ================\n";
        cout << left
             << setw(12) << "Tanggal"
             << setw(14) << "Jenis"
             << setw(14) << "Kategori"
             << setw(25) << "Keterangan"
             << setw(14) << "Masuk"
             << setw(14) << "Keluar"
             << endl;

        cout << "--------------------------------------------------------------------------\n";

        while (getline(file, line)) {
            stringstream ss(line);

            string id, tanggal, jenis, kategori, keterangan;
            string pemasukanStr, pengeluaranStr;

            getline(ss, id, '|');
            getline(ss, tanggal, '|');
            getline(ss, jenis, '|');
            getline(ss, kategori, '|');
            getline(ss, keterangan, '|');
            getline(ss, pemasukanStr, '|');
            getline(ss, pengeluaranStr);

            bool tampil = false;

            if (mode == 1 && cocokTanggal(tanggal, hari, bulan, tahun)) 
            {
                tampil = true;
            } 
            else if (mode == 2 && cocokBulan(tanggal, bulan, tahun)) 
            {
                tampil = true;
            } 
            else if (mode == 3 && cocokTahun(tanggal, tahun)) 
            {
                tampil = true;
            }

            if (tampil) 
            {
                double pemasukan = stod(pemasukanStr);
                double pengeluaran = stod(pengeluaranStr);

                cout << left
                     << setw(12) << tanggal
                     << setw(14) << jenis
                     << setw(14) << kategori
                     << setw(25) << keterangan
                     << setw(14) << pemasukan
                     << setw(14) << pengeluaran
                     << endl;

                totalPemasukan += pemasukan;
                totalPengeluaran += pengeluaran;
                adaData = true;
            }
        }

        file.close();

        if (!adaData) 
        {
            cout << "Tidak ada data pada periode tersebut.\n";
            return;
        }

        cout << "--------------------------------------------------------------------------\n";
        cout << "Total Pemasukan   : Rp " << totalPemasukan << endl;
        cout << "Total Pengeluaran : Rp " << totalPengeluaran << endl;
        cout << "Saldo Bersih      : Rp " << totalPemasukan - totalPengeluaran << endl;
    }

    void laporanHarian() {
        tampilLaporan(1);
    }

    void laporanBulanan() {
        tampilLaporan(2);
    }

    void laporanTahunan() {
        tampilLaporan(3);
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
	
	void menuKeranjang(){

	    // Jika keranjang kosong, tidak perlu menampilkan menu
	    if(keranjang.keranjangKosong()){
	        cout << "\nKeranjang masih kosong!" << endl;
	        return;
	    }
	
	    int pilihan;
	    bool checkout = false;
	
	    do{
	
	        // system("cls");
	
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
	        pilihan = inputPilihanMenu();
	
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
				cin.ignore();

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
					cout << "\nTekan Enter untuk lanjut...";
			        cin.get();
			
			        return;
			    }
			
			    break;
			}
	
	        default:
	
	            cout << "\nPilihan tidak tersedia!" << endl;
	        }
	
	        if(!checkout){
	            cout << "\nTekan Enter untuk lanjut...";
	            cin.get();
	        }
	
	    }while(!checkout);
	
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
			
			if (keranjang.keranjangKosong()) 
			{
            	cout << "\nBelum ada obat di keranjang." << endl;
        	}

		    cout << "\nTambah obat lagi? (Y/T) : ";
		    cin >> pilih;
		    cin.ignore();
		
		}while(toupper(pilih)=='Y');

		if (keranjang.keranjangKosong()) 
		{
			cout << "\nTransaksi dibatalkan karena keranjang kosong." << endl;
			cout << "\nTekan Enter untuk lanjut...";
			cin.get();
			return;
    	}
	    
	    menuKeranjang();
			    
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
		cout << "\nTekan Enter untuk lanjut...";
	    cin.get();
	    // system("cls");
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
		cin.ignore();
		
	    while(uangBayar < totalPembayaran){
			
			cout << "\nUang tidak mencukupi!" << endl;
			
	        cout << "Masukkan Uang Pembeli : Rp ";
	        cin >> uangBayar;
			cin.ignore();
	
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
        LaporanKeuangan laporan;
        laporan.catatPemasukanPenjualan(idTransaksi, totalPembayaran);
	
	    cout << "\nPembayaran Berhasil." << endl;
        Logaktivitas log;
        log.catatLog("TRANSAKSI", "Transaksi penjualan berhasil: " + idTransaksi);
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

	void menuPenggajian(){

    Karyawan karyawan;

    int pilih;

    do
    {
        cout << "\n===== MENU PENGGAJIAN =====" << endl;
        cout << "1. Hitung Gaji" << endl;
        cout << "2. Cetak Slip Gaji" << endl;
        cout << "3. Cari Slip Gaji" << endl;
        cout << "4. Rekap Gaji Bulanan" << endl;
        cout << "0. Kembali" << endl;

        cout << "Pilih : ";
        
        pilih = inputPilihanMenu();

        switch(pilih)
        {
            case 1:
                karyawan.hitungGaji();
                break;

            case 2:
                karyawan.cetakSlipGaji();
                break;

            case 3:
                karyawan.cariSlipGaji();
                break;

            case 4:
                karyawan.rekapGajiBulanan();
                break;

            case 0:
                break;

            default:
                cout << "Pilihan tidak tersedia." << endl;
                break;
        }

    }while(pilih != 0);
}

	void menuSDM()
{
    Karyawan karyawan;

    int pilih;

    do
    {
        cout<<"\n==================================="<<endl;
        cout<<"         MENU MANAJEMEN SDM"<<endl;
        cout<<"==================================="<<endl;
        cout<<"1. Input Karyawan"<<endl;
        cout<<"2. Data Karyawan"<<endl;
        cout<<"3. Cari Karyawan"<<endl;
        cout<<"4. Ubah Data"<<endl;
        cout<<"5. Hapus Data"<<endl;
        cout<<"6. Input Absensi"<<endl;
        cout<<"7. Penggajian"<<endl;
        cout<<"0. Kembali"<<endl;

        cout<<"Pilih : ";
        cin>>pilih;
        cin.ignore();

        switch(pilih)
        {
            case 1:
                karyawan.inputKaryawan();
                break;

            case 2:
                karyawan.bacaDataKaryawan();
                break;

            case 3:
                karyawan.cariKaryawan();
                break;

            case 4:
                karyawan.ubahDataKaryawan();
                break;

            case 5:
                karyawan.hapusDataKaryawan();
                break;

            case 6:
                karyawan.inputAbsensi();
                break;

            case 7:

                if(karyawan.cekHakAksesGaji())
                {
                    menuPenggajian();
                }
                else
                {
                    cout<<"Akses Ditolak!"<<endl;
                }

                break;

            case 0:
                break;

            default:
                cout<<"Pilihan tidak tersedia."<<endl;
        }

    }while(pilih!=0);
}

void menuKelolaObat() {
    Obat obat;
    int pilih;
    string namaCari;

    do {
        // system("cls");

        cout << "\n=== KELOLA OBAT ===\n";
        cout << "1. Lihat Obat\n";
        cout << "2. Cari Obat\n";
        cout << "3. Tambah Obat\n";
        cout << "4. Edit Data Obat\n";
        cout << "5. Ubah Harga Obat\n";
        cout << "6. Stok Menipis\n";
        cout << "7. Cek Kadaluarsa\n";
        cout << "8. Monitoring Obat\n";
        cout << "0. Kembali\n";
        cout << "Pilih : ";

        pilih = inputPilihanMenu();

        switch (pilih) {
        case 1:
            obat.bacaDataObat();
            break;

        case 2:
            cout << "Nama Obat : ";
            getline(cin, namaCari);

            if (obat.cariObat(namaCari)) {
                cout << "===============================\n";
                cout << "|     DATA OBAT DITEMUKAN     |\n";
                cout << "===============================";
                cout << "\nKode    : " << obat.getkodeObat() << endl;
                cout << "Nama    : " << obat.getnamaObat() << endl;
                cout << "Harga   : " << obat.getHarga() << endl;
                cout << "Stok    : " << obat.getStok() << endl;
                cout << "Expired : " << obat.gettanggalExpired() << endl;
                cout << "===============================\n";
            } else {
                cout << "Obat tidak ditemukan.\n";
            }
            break;

        case 3:
            obat.inputObat();
            break;

        case 4:
            obat.ubahDataObat();
            break;

        case 5:
            obat.ubahHarga();
            break;

        case 6:
            obat.stokMenipis();
            break;

        case 7:
            obat.cekKadaluarsa();
            break;

        case 8:
            obat.tampilMonitoring();
            break;

        case 0:
            return;

        default:
            cout << "Pilihan salah! Masukkan angka 0 sampai 8.\n";
            break;
        }

        kembaliMenu();

    } while (true);
}

void menuKelolaSupplier() {
    Supplier supplier;
    int pilih;
    string idCari;

    do {
        // system("cls");

        cout << "\n=== KELOLA SUPPLIER ===\n";
        cout << "1. Tambah Supplier\n";
        cout << "2. Lihat Data Supplier\n";
        cout << "3. Cari Supplier\n";
        cout << "4. Ubah Data Supplier\n";
        cout << "5. Hapus Supplier\n";
        cout << "6. Buat Pesanan Restock\n";
        cout << "7. Lihat Pesanan Supplier\n";
        cout << "8. Update Status Pesanan\n";
        cout << "9. Konfirmasi Barang Diterima\n";
        cout << "0. Kembali\n";
        cout << "Pilih : ";

        pilih = inputPilihanMenu();

        switch (pilih) {
        case 1:
            supplier.tambahSupplier();
            break;

        case 2:
            supplier.bacaSupplier();
            break;

        case 3:
            cout << "\nMasukkan ID Supplier : ";
            getline(cin, idCari);

            if (supplier.cariSupplier(idCari)) 
			{
                supplier.tampilSupplier();
            } 
			else 
			{
                cout << "\nSupplier tidak ditemukan.\n";
            }
            break;

        case 4:
            supplier.ubahSupplier();
            break;

        case 5:
            supplier.hapusSupplier();
            break;

        case 6:
            supplier.pesanRestock();
            break;

        case 7:
            supplier.bacaPesanan();
            break;

        case 8:
            supplier.updateStatus();
            break;

        case 9:
            supplier.konfirmasiBarang();
            break;

        case 0:
            return;

        default:
            cout << "Pilihan salah! Masukkan angka 0 sampai 9.\n";
            break;
        }

        kembaliMenu();

    } while (true);
}

void menuLaporanKeuangan() {
    LaporanKeuangan laporan;
    int pilih;

    do {
        cout << "\n=== MENU LAPORAN KEUANGAN ===\n";
        cout << "1. Laporan Harian\n";
        cout << "2. Laporan Bulanan\n";
        cout << "3. Laporan Tahunan\n";
        cout << "4. Input Pengeluaran Rutin\n";
        cout << "0. Kembali\n";
        cout << "Pilih : ";

        pilih = inputPilihanMenu();

        switch (pilih) {
        case 1:
            laporan.laporanHarian();
            break;

        case 2:
            laporan.laporanBulanan();
            break;

        case 3:
            laporan.laporanTahunan();
            break;

        case 4:
            laporan.inputPengeluaranRutin();
            break;

        case 0:
            return;

        default:
            cout << "Pilihan salah! Masukkan angka 0 sampai 4.\n";
            break;
        }

        kembaliMenu();

    } while (true);
}

void menuLogAktivitas() {
    Logaktivitas log;
    int pilih;

    do {
        cout << "\n=== MENU LOG AKTIVITAS ===\n";
        cout << "1. Lihat Semua Log\n";
        cout << "0. Kembali\n";
        cout << "Pilih : ";

        pilih = inputPilihanMenu();

        switch (pilih) {
        case 1:
            log.tampilLog();
            break;

        case 0:
            return;

        default:
            cout << "Pilihan salah! Masukkan angka 0 sampai 1.\n";
            break;
        }

        kembaliMenu();

    } while (true);
}

void menuAdmin() {
    Obat obat;
    Supplier supplier;
    Transaksi transaksi;
    int pilih;
    string namaCari;

    do {
        system("cls");

        cout << "\n=== MENU ADMIN ===\n";
        cout << "1. Lihat User\n";
        cout << "2. Kelola Obat\n";
        cout << "3. Kelola Supplier\n";
        cout << "4. Kelola Karyawan\n";
        cout << "5. Riwayat Transaksi\n";
        cout << "6. Laporan Keuangan\n";
        cout << "7. Log Aktivitas\n";
        cout << "8. Ganti Password\n";
        cout << "0. Logout\n";
        cout << "Pilih : ";

        pilih = inputPilihanMenu();

        switch (pilih) {
        case 1:
            bacaUserDariFile(user, jumlahUser);
            cout << "\nDATA USER:\n";
            if (jumlahUser == 0) 
			{
                cout << "Belum ada data user.\n";
            } 
			else 
			{
                for (int i = 0; i < jumlahUser; i++) {
                    user[i].tampil();
                    cout << endl;
                }
            }
            break;

        case 2:
            menuKelolaObat();
            break;

        case 3:
            menuKelolaSupplier();
            break;

        case 4:
            menuSDM();
            break;

        case 5:
            transaksi.tampilRiwayat();
            break;

        case 6:
            menuLaporanKeuangan();
            break;

        case 7:
            menuLogAktivitas();
            break;

        case 8:
            gantiPassword();
            break;

        case 0:
            logout();
            return;

        default:
            cout << "Pilihan salah! Masukkan angka 0 sampai 8.\n";
            break;
        }

        kembaliMenu();

    } while (true);
}

void menuKaryawan() {
    Transaksi transaksi;
    Supplier supplier;
    Obat obat;
    int pilih;

    do {
        // system("cls");

        cout << "\n=== MENU KARYAWAN ===\n";
        cout << "1. Transaksi Penjualan\n";
        cout << "2. Lihat Obat\n";
        cout << "3. Cari Obat\n";
        cout << "4. Buat Pesanan Restock\n";
        cout << "5. Konfirmasi Penerimaan Barang\n";
        cout << "6. Riwayat Transaksi\n";
        cout << "7. Ganti Password\n";
        cout << "0. Logout\n";
        cout << "Pilih : ";

        pilih = inputPilihanMenu();

        switch (pilih) {
        case 1:
            transaksi.cetakStruk();
            break;

        case 2:
            obat.bacaDataObat();
            break;

        case 3:
        {
            string namaCari;
            cout << "Nama Obat : ";
            getline(cin, namaCari);

            if (obat.cariObat(namaCari)) {
                cout << "\nKode    : " << obat.getkodeObat() << endl;
                cout << "Nama    : " << obat.getnamaObat() << endl;
                cout << "Harga   : " << obat.getHarga() << endl;
                cout << "Stok    : " << obat.getStok() << endl;
                cout << "Expired : " << obat.gettanggalExpired() << endl;
            } else {
                cout << "Obat tidak ditemukan.\n";
            }
            break;
        }

        case 4:
            supplier.pesanRestock();
            break;

        case 5:
            supplier.konfirmasiBarang();
            break;

        case 6:
            transaksi.tampilRiwayat();
            break;

        case 7:
            gantiPassword();
            break;

        case 0:
            logout();
            return;

        default:
            cout << "Pilihan salah! Masukkan angka 0 sampai 7.\n";
            break;
        }

        kembaliMenu();

    } while (true);
}

void menuSupplier() {
    Supplier supplier;
    int pilih;

    do {
        // system("cls");

        cout << "\n=== MENU SUPPLIER ===\n";
        cout << "1. Lihat Pesanan Masuk\n";
        cout << "2. Update Status Pesanan\n";
        cout << "3. Ganti Password\n";
        cout << "0. Logout\n";
        cout << "Pilih : ";

        pilih = inputPilihanMenu();

        switch (pilih) {
        case 1:
            supplier.bacaPesanan();
            break;

        case 2:
            supplier.updateStatus();
            break;

        case 3:
            gantiPassword();
            break;

        case 0:
            logout();
            return;

        default:
            cout << "Pilihan salah! Masukkan angka 0 sampai 3.\n";
            break;
        }

        kembaliMenu();

    } while (true);
}

void menuUtama(){
		if (loginIndex == -1)
		{
			cout << "Anda belum login!\n";
			return;
		}
	
		string role = user[loginIndex].getRole();

        for (int i = 0; i < role.length(); i++)
			{
				role[i] = tolower(role[i]);
			}

		if (role == "admin")
		{
			menuAdmin();
		}
		else if (role == "karyawan")
		{
			menuKaryawan();
		}
		else if (role == "supplier")
		{
			menuSupplier();
		}
		else
		{
			cout << "Role tidak dikenal!\n";
		}
	}

// baru
void header(string judul) {
    	
    const int lebar = 50;

    cout << "\n";
    cout << string(lebar, '=') << endl;

    int spasi = (lebar - judul.length()) / 2;

    cout << string(spasi, ' ')
         << judul << endl;

    cout << string(lebar, '=') << endl;
}

// baru
void footer() {
    cout << string(50, '=') << endl;
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
        
		pilih = inputPilihanMenu();
        
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
        case 3:
            cout << "Terima kasih telah menggunakan sistem ini.\n";
            break;
		default:
			cout << "[!] Pilihan salah! Masukkan angka 1 sampai 3.\n";
			break;
        }
        
        } while (pilih != 3);

    return 0;
}