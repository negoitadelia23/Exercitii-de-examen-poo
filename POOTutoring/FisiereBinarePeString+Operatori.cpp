#include<iostream>
#include<fstream>
#include<map>
using namespace std;
class Reteta {
	char* nume;
	int nrIngrediente;
	string* ingrediente;
	int timpPreparare;
	
public:
	virtual int afiseazaDetalii() {
		return this->nrIngrediente;
	}
	Reteta() {
		this->nume = nullptr;
		this->nrIngrediente = 0;
		this->ingrediente = nullptr;
		this->timpPreparare = 0;
	}
	Reteta(const char* nume, int nrIngrediente, string* ingrediente, int timpPreparare) {
		if (nume && strlen(nume) > 3)
		{
			this->nume = new char[strlen(nume) + 1];
			strcpy_s(this->nume, strlen(nume) + 1, nume);
		}
		else this->nume = 0;
		if (nrIngrediente > 0)
			this->nrIngrediente = nrIngrediente;
		else this->nrIngrediente = 0;
		if (this->nrIngrediente && ingrediente) {
			this->ingrediente = new string[nrIngrediente];
			for (int i = 0; i < this->nrIngrediente; i++)
				this->ingrediente[i] = ingrediente[i];
		}
		else this->ingrediente = nullptr;
		if (timpPreparare > 0)
			this->timpPreparare = timpPreparare;
		else this->timpPreparare = 0;
	}
	Reteta(const Reteta& r) {
		if (r.nume && strlen(r.nume) > 3)
		{
			this->nume = new char[strlen(r.nume) + 1];
			strcpy_s(this->nume, strlen(r.nume) + 1, r.nume);
		}
		else this->nume = 0;
		if (r.nrIngrediente > 0)
			this->nrIngrediente = r.nrIngrediente;
		else this->nrIngrediente = 0;
		if (this->nrIngrediente && r.ingrediente) {
			this->ingrediente = new string[nrIngrediente];
			for (int i = 0; i < this->nrIngrediente; i++)
				this->ingrediente[i] = r.ingrediente[i];
		}
		else this->ingrediente = nullptr;
		if (r.timpPreparare > 0)
			this->timpPreparare = r.timpPreparare;
		else this->timpPreparare = 0;
	}
	~Reteta() {
		if (this->ingrediente)
			delete[]this->ingrediente;
		if (this->nume)
			delete[]this->nume;
	}
	Reteta& operator=(const Reteta& r) {
		if (&r != this) {
			if (r.nume && strlen(r.nume) > 3)
			{	if (this->nume)
					delete[]this->nume;
				this->nume = new char[strlen(r.nume) + 1];
				strcpy_s(this->nume, strlen(r.nume) + 1, r.nume);
			}
			else this->nume = 0;
			if (r.nrIngrediente > 0)
				this->nrIngrediente = r.nrIngrediente;
			else this->nrIngrediente = 0;
			if (this->nrIngrediente && r.ingrediente) {
				if (this->ingrediente)
					delete[]this->ingrediente;
				this->ingrediente = new string[nrIngrediente];
				for (int i = 0; i < this->nrIngrediente; i++)
					this->ingrediente[i] = r.ingrediente[i];
			}
			else this->ingrediente = nullptr;
			if (r.timpPreparare > 0)
				this->timpPreparare = r.timpPreparare;
			else this->timpPreparare = 0;
		}
		return *this;
	}
	int getTimpPreparare() {
		return this->timpPreparare;
	}
	void setTimpPreparare(int timpNou) {
		if (timpNou > 0)
			this->timpPreparare = timpNou;
	}
	string getIngrediente(int index) {
		if (index > 0 && index < this->nrIngrediente)
			return this->ingrediente[index];
		else throw 121;
	}
	void setIngrediente(int numarNou, string* ingrediente) {
		if (numarNou > 0)
		{
			this->nrIngrediente = numarNou;
			if (this->ingrediente)
				delete[]this->ingrediente;
		}
		this->ingrediente = new string[this->nrIngrediente];
		for (int i = 0; i < this->nrIngrediente; i++)
			this->ingrediente[i] = ingrediente[i];
	}
	friend ostream& operator<<(ostream& out, Reteta& r) {
		out << "Nume reteta: " << r.nume << endl;
		out << "Numar ingrediente: " << r.nrIngrediente << endl;
		if (r.nrIngrediente) {
			for (int i = 0; i < r.nrIngrediente; i++)
				out << "Ingredientul " << i + 1 << " este: " << r.ingrediente[i] << endl;
		}
		else out << "Nu avem ingrediente." << endl;
		out << "Timp de preparare: " << r.timpPreparare << endl;
		return out;
	}
	Reteta& operator+=(string ingredientNou) {
		string* aux = new string[this->nrIngrediente + 1];
		for (int i = 0; i < this->nrIngrediente; i++)
			aux[i] = this->ingrediente[i];
		aux[this->nrIngrediente] = ingredientNou;
		this->nrIngrediente++;
		if (this->ingrediente)
			delete[]this->ingrediente;
		this->ingrediente = new string[this->nrIngrediente];
		this->ingrediente = aux;
		return *this;
	}
	Reteta& operator-=(string ingredientScos) {
		string* aux = new string[this->nrIngrediente - 1];
		for (int i = 0; i < this->nrIngrediente - 1; i++)
			aux[i] = this->ingrediente[i];
		this->nrIngrediente--;
		if (this->ingrediente)
			delete[]this->ingrediente;
		this->ingrediente = new string[this->nrIngrediente];
		this->ingrediente = aux;
		return *this;
	}
	bool operator==(const Reteta& r)const {
		int c = 0;
		if (this->nrIngrediente == r.nrIngrediente) {
			for (int i = 0; i < this->nrIngrediente; i++)
			{
				if (this->ingrediente[i] == r.ingrediente[i])
					c++;
			}
			if (c == this->nrIngrediente)
				return 1;
			else return 0;
		}
		else return 0;
	}
	friend istream& operator>>(istream& in, Reteta& r) {
		cout << "Nume prajitura: ";
		char buffer[100];
		in.getline(buffer, 100);
		in.ignore();
		if (r.nume)
			delete[]r.nume;
		r.nume = new char[strlen(buffer) + 1];
		strcpy_s(r.nume, strlen(buffer) + 1, buffer);
		cout << "Nr ingrediente: ";
		in >> r.nrIngrediente;
		if (r.nrIngrediente>0) {
			if (r.ingrediente)
				delete[]r.ingrediente;
			r.ingrediente = new string[r.nrIngrediente];
			for (int i = 0; i < r.nrIngrediente; i++)
			{
				cout << "Ingredientul " << i + 1 << ": ";
				in >> r.ingrediente[i];
			}
		}
		else r.ingrediente = nullptr;
		cout << "Timp preparare: ";
		in >> r.timpPreparare;
		return in;
	}
	void scrieFisiereBinar(fstream&f) {
		int lungime = strlen(nume);
		f.write((char*)&lungime, sizeof(int));
		f.write((char*)this->nume, lungime * sizeof(char));
		f.write((char*)&this->nrIngrediente, sizeof(int));
		if (this->nrIngrediente) {
			for (int i = 0; i < this->nrIngrediente; i++) {
				int lungimet = this->ingrediente[i].length();
				f.write((char*)&lungimet, sizeof(int));
				f.write((char*)this->ingrediente[i].c_str(), sizeof(char)*lungimet);
			}
		}
		f.write((char*)&this->timpPreparare, sizeof(int));
	}
	void citesteFisierBinar(fstream& f) {
		int lungime;
		f.read((char*)&lungime, sizeof(int));
		if (lungime > 0) {
			if (this->nume)
				delete[] this->nume;
			this->nume = new char[lungime + 1];
			f.read((char*)this->nume, sizeof(char) * lungime);
			this->nume[lungime] = '\0';
		}
		f.read((char*)&this->nrIngrediente, sizeof(int));
		if (this->nrIngrediente) {
			if (this->ingrediente)
				delete[]this->ingrediente;
			this->ingrediente = new string[this->nrIngrediente];
			for (int i = 0; i < this->nrIngrediente; i++)
			{
				int lungimet;
				f.read((char*)&lungimet, sizeof(int));
				char buffer[50];
				f.read((char*)(&buffer), lungimet * sizeof(char));
				buffer[lungimet] = '\0';
				this->ingrediente[i] = buffer;
			}
		}
		f.read((char*)&this->timpPreparare, sizeof(int));

	}
};
class RetetaDePrajituri :public Reteta {
	char* tip;//cu gluten fara ...
	int cantitateZahar;
public:
	RetetaDePrajituri(const char* tip, int cantitateZahar) :Reteta() {
		if (tip && strlen(tip) > 3) {
			this->tip = new char[strlen(tip) + 1];
			strcpy_s(this->tip, strlen(tip) + 1, tip);
		}
		else this->tip = nullptr;
		if (cantitateZahar > 0)
			this->cantitateZahar = cantitateZahar;
		else this->cantitateZahar = 0;
	}
	RetetaDePrajituri(const RetetaDePrajituri& rd) :Reteta(rd) {
		if (rd.tip && strlen(rd.tip) > 3) {
			this->tip = new char[strlen(rd.tip) + 1];
			strcpy_s(this->tip, strlen(rd.tip) + 1, rd.tip);
		}
		else this->tip = nullptr;
		if (rd.cantitateZahar > 0)
			this->cantitateZahar = rd.cantitateZahar;
		else this->cantitateZahar = 0;
	}
	~RetetaDePrajituri() {
		if (this->tip)
			delete[]this->tip;
	}
	RetetaDePrajituri& operator=(const RetetaDePrajituri& rd) {
		if (&rd != this) {
			(Reteta)*this = (Reteta)rd;
			if (rd.tip && strlen(rd.tip) > 3) {
				if (this->tip)
					delete[]this->tip;
				this->tip = new char[strlen(rd.tip) + 1];
				strcpy_s(this->tip, strlen(rd.tip) + 1, rd.tip);
			}
			else this->tip = nullptr;
			if (rd.cantitateZahar > 0)
				this->cantitateZahar = rd.cantitateZahar;
			else this->cantitateZahar = 0;
		}
	}
	int sumaCantitateZahar(const RetetaDePrajituri rd)const {
		return this->cantitateZahar + rd.cantitateZahar;
	}
	int afiseazaDetalii() {
		return this->cantitateZahar;
	}
};
int main() {
	Reteta r;
	int numar = 2;
	int numar1 = 3;
	string* s = new string[numar];
	s[0] = "Delia";
	s[1] = "Negoita";
	string* s2 = new string[numar1];
	s2[0] = "Sara";
	s2[1] = "Sabina";
	s2[2] = "Ramona";
	Reteta r2("Ramona", numar, s, 3);
	Reteta r3 = r2;
	Reteta r4;
	r4 = r2;
	cout << r4 << endl;
	cout << r4.getTimpPreparare() << endl;
	r4.setTimpPreparare(2);
	cout << r4.getTimpPreparare() << endl;
	r4.setIngrediente(numar1, s2);
	cout << r4.getIngrediente(2) << endl;
	cout << (r4 == r3) << endl;
	RetetaDePrajituri rd("Gluten", 3);
	RetetaDePrajituri rd2 = rd;
	cout << rd.sumaCantitateZahar(rd2) << endl;
	fstream f("fisReteta.txt", ios::binary | ios::out);
	r4.scrieFisiereBinar(f);
	f.close();
	fstream f2("fisReteta.txt", ios::binary | ios::in);
	r4.citesteFisierBinar(f2);
	f2.close();
	string s3 = "Ramona";
	r4 += s3;
	cout << r4 << endl;
	r4 -= s3;
	r4 -= s[0];
	cout << r4 << endl;
	map<string, Reteta>mapReteta;
	mapReteta.insert(pair<string,Reteta>(s3, r4));
	mapReteta.insert(pair<string, Reteta>(s[0], r2));
	map<string, Reteta>::iterator it;
	for (it = mapReteta.begin(); it != mapReteta.end(); it++) {
		cout << it->first<<" ";
		cout << it->second;
	}
	cout << endl; 
	if (mapReteta.find(s3) != mapReteta.end()) {
		cout << "Am gasit reteta! " << endl;
	}
	else cout << "Nu am gasit reteta." << endl;

	cout << endl;
	Reteta* pr = new Reteta(r4);
	Reteta* prd = new RetetaDePrajituri(rd);
	cout << pr->afiseazaDetalii() << endl;
	cout << prd->afiseazaDetalii() << endl;
	delete[]s;
	delete[]s2;
	delete pr;
	delete prd;
	return 0;
}