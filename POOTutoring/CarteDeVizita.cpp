#include<iostream>
#include<set>
using namespace std;
class CarteDeVizita {
	const int id;
	string nume;
	char* companie;
	static int count;
	string adresaDeEmail;
public:
	CarteDeVizita() :id(++count) {
		this->nume = "Ramona";
		this->companie = nullptr;
		this->adresaDeEmail = "C";
	}
	CarteDeVizita(string nume, const char* companie, string adresaDeEmail) :id(++count) {
		if (nume.length() > 2)
			this->nume = nume;
		else this->nume = "Ramona";
		if (adresaDeEmail.length() > 3)
			this->adresaDeEmail = adresaDeEmail;
		else this->adresaDeEmail = "C";
		if (companie) {
			this->companie = new char[strlen(companie) + 1];
			strcpy_s(this->companie, strlen(companie) + 1, companie);
		}
		else this->companie = nullptr;
	}
	CarteDeVizita(const CarteDeVizita& cv):id(cv.id) {
		if (cv.nume.length() > 2)
			this->nume = cv.nume;
		else this->nume = "Ramona";
		if(cv.adresaDeEmail.length()>3)
			this->adresaDeEmail = cv.adresaDeEmail;
		else this->adresaDeEmail = "C";
		if (cv.companie) {
			this->companie = new char[strlen(cv.companie) + 1];
			strcpy_s(this->companie, strlen(cv.companie) + 1, cv.companie);
		}
		else this->companie = nullptr;
	}
	~CarteDeVizita() {
		if (this->companie)
			delete[]this->companie;
	}
	CarteDeVizita& operator=(const CarteDeVizita& cv) {
		if (&cv != this) {
			if (cv.nume.length() > 2)
				this->nume = cv.nume;
			else this->nume = "Ramona";
			if(cv.adresaDeEmail.length()>3)
				this->adresaDeEmail = cv.adresaDeEmail;
			else this->adresaDeEmail = "C";
			if (cv.companie) {
				if (this->companie)
					delete[]this->companie;
				this->companie = new char[strlen(cv.companie) + 1];
				strcpy_s(this->companie, strlen(cv.companie) + 1, cv.companie);
			}
			else this->companie = nullptr;
		}
		return *this;
	}
	friend ostream& operator<<(ostream& out, const CarteDeVizita& cv) {
		out << "ID: " << cv.id << endl;
		out << "Nume: " << cv.nume << endl;
		out << "Companie: " << cv.companie << endl;
		out << "Adresa de email: " << cv.adresaDeEmail << endl;
		return out;
	}
	bool operator>=(const CarteDeVizita& cv)const {
		return (this->nume.length() >= cv.nume.length());
	}
	friend istream& operator>>(istream& in, CarteDeVizita& cv) {
		cout << "Nume a celui(ei) de pe cartea de vizita: ";
		in >> cv.nume;
		cout<< "Compania celui(ei) de pe cartea de vizita: ";
		char buffer[100];
		in >> buffer;
		if (cv.companie)
			delete[]cv.companie;
		cv.companie = new char[strlen(buffer) + 1];
		strcpy_s(cv.companie, strlen(buffer) + 1, buffer);
		cout << "Adresa de email a celui(ei) de pe cartea de vizita:";
		in >> cv.adresaDeEmail;
		return in;
	}
	bool operator<(const CarteDeVizita& cv)const {
		return this->nume < cv.nume;
	}
	virtual string AfiseazaInformatii() {
		return this->adresaDeEmail;
	}

};
class CarteDeVizitaElectronica :public CarteDeVizita {
	string site;
public:
	CarteDeVizitaElectronica() :CarteDeVizita("Sara","Companie","mitrancasara23@stud.ase.ro") {
		this->site = "EuroMania";
	}
	string AfiseazaInformatii() {
		return this->site;
	}
};
int CarteDeVizita::count = 1;
int main() {
	CarteDeVizita cv;
	CarteDeVizita cv1("Delia", "Companie", "negoitadelia23@stud.ase.ro");
	CarteDeVizita cv2 = cv1;
	CarteDeVizita cv3;
	cv3 = cv2;
	cout << cv3 << endl;
	cout << (cv3 >= cv2) << endl;
	/*cin >> cv;
	cout << cv << endl;*/
	CarteDeVizita* pcv = new CarteDeVizita(cv1);
	CarteDeVizita* pcv1 = new CarteDeVizitaElectronica();
	cout << pcv->AfiseazaInformatii() << endl;
	cout << pcv1->AfiseazaInformatii() << endl;
	set<CarteDeVizita> setCV;
	setCV.insert(cv1);
	setCV.insert(cv2);//nu ar trb sa mi-l adauge
	setCV.insert(*pcv1);
	set<CarteDeVizita>::iterator it;
	for (it = setCV.begin(); it != setCV.end(); it++)
		cout << *it << endl;

	delete pcv;
	delete pcv1;
}