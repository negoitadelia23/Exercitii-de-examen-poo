#include<iostream>
#include<vector>
#include<fstream>
using namespace std;

class Asigurat {
	const int id;
	static int numarator;
	char* nume;
	double suma;
	string tipAsigurare;
public:
	Asigurat() :id(++numarator) {
		this->nume = nullptr;
		this->suma = 234.45;
		this->tipAsigurare = "Ramona";
	}
	Asigurat(const char* nume, double suma, string tip) :id(++numarator) {
		this->nume = new char[strlen(nume) + 1];
		strcpy_s(this->nume, strlen(nume) + 1, nume);
		this->suma = suma;
		this->tipAsigurare = tip;
	}
	Asigurat(const Asigurat& a) :id(a.id) {
		if (a.nume) {
			this->nume = new char[strlen(a.nume) + 1];
			strcpy_s(this->nume, strlen(a.nume) + 1, a.nume);
		}
		else this->nume = nullptr;
		this->suma = a.suma;
		this->tipAsigurare = a.tipAsigurare;
	}
	Asigurat& operator=(const Asigurat& a) {
		if (&a != this) {
			if (a.nume) {
				this->nume = new char[strlen(a.nume) + 1];
				strcpy_s(this->nume, strlen(a.nume) + 1, a.nume);
			}
			else this->nume = nullptr;
			this->suma = a.suma;
			this->tipAsigurare = a.tipAsigurare;
		}
		return *this;
	}
	~Asigurat() {
		if (this->nume)
			delete this->nume;
	}
	friend ostream& operator<<(ostream& out, Asigurat& a) {
		out << "ID: " << a.id << endl;
		out << "Nume: " << a.nume << endl;
		out << "Suma asigurata: " << a.suma << endl;
		out << "Tip asigurare: " << a.tipAsigurare << endl;
		return out;
	}
	char* getNume() {
		return this->nume;
	}
	void setNume(char* numeNou) {
		if (strlen(numeNou) > 2)
			this->nume = numeNou;
	}
	double operator()(double curs) {
		return this->suma / curs;
	}
	operator double() {
		return this->suma;
	}
	void scriereFisierBinar(fstream& f) {
		int lungime = strlen(this->nume);
		for (int i = 0; i < lungime; i++)
			f.write((char*)&this->nume[i], sizeof(char));
		f.write((char*)&this->suma, sizeof(double));
		int lungimes = this->tipAsigurare.length();
		f.write(this->tipAsigurare.c_str(), sizeof(char) * lungimes);
	}
	void citesteFisierBinar(fstream& f)
	{
		if (!f.is_open())
		{
			cerr << "Eroare" << endl;
			return;
		}
		else
		{
			cout << "Lungime:";
			int lungime;
			f.read((char*)&lungime, sizeof(int));
			if (this->nume)
				delete this->nume;
			this->nume = new char[lungime + 1];
			cout << endl << "Nume: ";
			for (int i = 0; i < lungime; i++)
				f.read((char*)&this->nume[i], sizeof(char));
			this->nume[lungime] = '\0';
			cout << endl << "Suma: ";
			f.read((char*)&this->suma, sizeof(double));
			cout << endl << "Lungime:";
			int lungimes;
			f.read((char*)&lungimes, sizeof(lungimes));
			char buffer[100];
			cout << endl << "Tip asigurare: ";
			f.read(buffer, lungimes);
			buffer[lungimes] = '\0';
			string tipAsigurare(buffer);
		}
}
};
int Asigurat::numarator = 1;
int *sum( vector<int> vector) {
	int sum = 0;
	for (int i = 0; i < vector.size(); i++)
		sum += vector[i];
	return &sum;
}
int main() {
	Asigurat a;
	Asigurat a1("Ramona", 2340.45, "De viata");
	Asigurat a2 = a1;
	Asigurat a3;
	a3 = a2;
	cout << a3 << endl;
	cout << a3(4.95) << endl;
	cout << (double)a3 << endl;
	fstream f("fis.txt", ios::binary || ios::out);
	fstream f1("fiscit.txt", ios::binary||ios::in);
	a3.scriereFisierBinar(f1);
	a2.citesteFisierBinar(f1);
	f.close();
	f1.close();
	return 0;
}