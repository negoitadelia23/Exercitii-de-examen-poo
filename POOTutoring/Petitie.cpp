#include <iostream>
#include<fstream>
#include <map>
using namespace std;
class ActCivic {
public:
	virtual char* Categorie() = 0;
};
class Petitie: public ActCivic {
	const int id;
	static int count;
	int dataDepunere;
	char* categoriePetitie;
	bool petitieDeschisa;
	bool areRaspuns;
public:
	Petitie() :id(++count) {
		this->dataDepunere = 1;
		this->categoriePetitie = nullptr;
		this->petitieDeschisa = 0;
		this->areRaspuns = 0;
	}
	Petitie(int dataDepunere,const char* categoriePetitie, bool petitieDeschisa, bool areRaspuns) :id(++count) {
		if (dataDepunere >= 1 && dataDepunere<=31)
			this->dataDepunere = dataDepunere;
		else this->dataDepunere = 1;
		if (strlen(categoriePetitie) > 4)
		{
			this->categoriePetitie = new char[strlen(categoriePetitie) + 1];
			strcpy_s(this->categoriePetitie, strlen(categoriePetitie) + 1, categoriePetitie);
		}
		else this->categoriePetitie = nullptr;
		this->petitieDeschisa = petitieDeschisa;
		this->areRaspuns = areRaspuns;
	}
	Petitie(const Petitie& petitie) :id(petitie.id) {
		if (petitie.dataDepunere >= 1 && petitie.dataDepunere<=31)
			this->dataDepunere = petitie.dataDepunere;
		else this->dataDepunere = 1;
		if(petitie.categoriePetitie && strlen(petitie.categoriePetitie)>4)
		{
				this->categoriePetitie = new char[strlen(petitie.categoriePetitie) + 1];
				strcpy_s(this->categoriePetitie, strlen(petitie.categoriePetitie) + 1, petitie.categoriePetitie);
		
		}
		else this->categoriePetitie = nullptr;
		this->petitieDeschisa = petitie.petitieDeschisa;
		this->areRaspuns = petitie.areRaspuns;
	}
	~Petitie() {
		if (this->categoriePetitie)
			delete[] this->categoriePetitie;
	}
	Petitie& operator=(const Petitie& petitie) {
		if (&petitie != this) {
			if (petitie.dataDepunere >= 1&&petitie.dataDepunere<=31)
				this->dataDepunere = petitie.dataDepunere;
			else this->dataDepunere = 1;
			if (petitie.categoriePetitie && strlen(petitie.categoriePetitie) > 4)
			{
				if (this->categoriePetitie)
					delete[] this->categoriePetitie;
				this->categoriePetitie = new char[strlen(petitie.categoriePetitie) + 1];
				strcpy_s(this->categoriePetitie, strlen(petitie.categoriePetitie) + 1, petitie.categoriePetitie);

			}
			else this->categoriePetitie = nullptr;
			this->petitieDeschisa = petitie.petitieDeschisa;
			this->areRaspuns = petitie.areRaspuns;
		}
		return *this;
	}
	friend ofstream& operator<<(ofstream& out, Petitie& p) {
		out << p.id << endl;
		out << p.dataDepunere << endl;
		out << p.categoriePetitie << endl;
		out << (p.petitieDeschisa ? "Deschisa" : "Rezolvata")<<endl;
		out << (p.areRaspuns ? "Are raspuns" : "Nu are raspuns") << endl;
		return out;
	}
	friend ifstream& operator>>(ifstream& in, Petitie& p) {
		in >> p.dataDepunere;
		char buffer[100];
		in.ignore();
		in.getline(buffer, 100);
		if (strlen(buffer) > 4) {
			if (p.categoriePetitie)
				delete[] p.categoriePetitie;
			p.categoriePetitie = new char[strlen(buffer) + 1];
			strcpy_s(p.categoriePetitie, strlen(buffer) + 1, buffer);
		}
		else p.categoriePetitie = nullptr;
		in >> p.petitieDeschisa;
		in >> p.areRaspuns;
		return in;
	}
	string operator!() {
		if (this->areRaspuns != 1)
			return "Nu are raspuns";
	}
	Petitie operator~() {
		this->petitieDeschisa = !this->petitieDeschisa;
		this->areRaspuns = !this->areRaspuns;
		return *this;
	}
	friend ostream& operator<<(ostream& out, Petitie& p) {
		out << "ID: " << p.id << endl;
		out << "Data depunere: " << p.dataDepunere << endl;
		if (p.categoriePetitie)
			out << "Categorie: " << p.categoriePetitie << endl;
		else out << "Ramona" << endl;
		out << "Petitie deschisa: " << (p.petitieDeschisa ? "DA" : "NU") << endl;
		out << "Are raspuns?: " << (p.areRaspuns ? "DA" : "NU") << endl;
		return out;
	}
	char* Categorie() {
		return this->categoriePetitie;
	}
	bool operator<(const Petitie p)const {
		return this->categoriePetitie < p.categoriePetitie;
	}
	void setCategorie(const char buffer[100]) {
		if (strlen(buffer) > 4) {
			if (this->categoriePetitie)
				delete[] categoriePetitie;
			categoriePetitie = new char[strlen(buffer) + 1];
			strcpy_s(categoriePetitie, strlen(buffer) + 1, buffer);
		}
	}
};
class Protest :public ActCivic {
	char* tipProtest;
public:
	Protest() {
		this->tipProtest = new char[strlen("Local") + 1];
		strcpy_s(this->tipProtest, strlen("Local") + 1, "Local");
	}
	char* Categorie() {
		return this->tipProtest;
	}
};
int Petitie :: count = 1;
int main() {
	Petitie p;
	Petitie p1(23, "Nationala", 1, 0);//petitie deschisa=1
	Petitie p2 = p1;
	cout << p2 << endl;
	//Petitie p3(32, "Blah", 2);//strlen("Blah")<=4 :)
	//cout << p3 << endl;
	/*cout << !p2 << endl;
	~p2;
	cout << p2 << endl;*/
	/*ifstream f("fiscit.txt", ios::in);
	f >> p2;
	ofstream f2("fisscris.txt", ios::out);
	f2 << p2 << endl;*/
	p2.setCategorie("Locala");
	ActCivic* act1 = new Protest;
	ActCivic* act2 = new Petitie(p2);
	cout << act1->Categorie() << endl;
	cout << act2->Categorie() << endl;
	map<char*, Petitie> mapPetitii;
	mapPetitii.insert(pair<char*,Petitie>(p1.Categorie(), p1));
	mapPetitii.insert(pair<char*, Petitie>(p2.Categorie(), p2));
	map<char*, Petitie>::iterator it;
	for (it = mapPetitii.begin(); it != mapPetitii.end(); it++)
	{
		cout << it->first<<" ";
		cout << it->second<<" ";
	}
	char* cheie = new char[strlen(p2.Categorie()) + 1];
	strcpy_s(cheie, strlen(p2.Categorie()) + 1, p2.Categorie());
	if (mapPetitii.find(cheie) != mapPetitii.end())
	{
		cout << "Interventie gasita!" << endl;
	}
	else cout << "Nasol momentul" << endl;
	delete[] cheie;
	return 0;
}