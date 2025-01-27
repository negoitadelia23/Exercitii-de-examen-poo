#include<iostream>
#include<map>
using namespace std;
//clasa abstracta= clasa care contine cel putin o fct virtual pura
//clasa care contine doar fct virt pure s.n interfata
class Interventie {
public:
	virtual float Calcul() = 0;
	virtual void Afisare() = 0;
	virtual string gasesteDenumire() = 0;
};
class CabinetStomatologic {
private:
	const int CodCUI;
	const int CAEN;
protected:
	char* denumire;
	string adresa;
	int nrMedici;
public:
	static int numarator;
	static float valoareTaxaAnulareConsult;
	CabinetStomatologic() :CodCUI(0), CAEN(0)
	{
		this->denumire = new char[strlen("X") + 1];
		strcpy_s(this->denumire, strlen("X") + 1, "X");
		this->adresa = "Ramona";
		this->nrMedici = 1;
	}
	CabinetStomatologic(int CodCUI, const char* denumire, string adresa, int nr) :CodCUI(CodCUI), CAEN(++numarator) 
	{
		this->denumire = new char[strlen(denumire) + 1];
		strcpy_s(this->denumire, strlen(denumire) + 1, denumire);
		this->adresa = adresa;
		this->nrMedici = nr;
	}
	CabinetStomatologic(const CabinetStomatologic& cs) :CodCUI(cs.CodCUI), CAEN(cs.CAEN) 
	{
		if (cs.denumire) {
			this->denumire = new char[strlen(cs.denumire) + 1];
			strcpy_s(this->denumire, strlen(cs.denumire) + 1, denumire);
		}
		else this->denumire = nullptr;
		this->adresa = cs.adresa;
		this->nrMedici = cs.nrMedici;
	}
	CabinetStomatologic& operator=(const CabinetStomatologic& cs)
	{
		if(&cs != this) {
			if (cs.denumire) {
				this->denumire = new char[strlen(cs.denumire) + 1];
				strcpy_s(this->denumire, strlen(cs.denumire) + 1, denumire);
			}
			else this->denumire = nullptr;
			this->adresa = cs.adresa;
			this->nrMedici = cs.nrMedici;
		}
		return *this;
	}
	friend istream& operator>>(istream& in, CabinetStomatologic& cs) {
		cout << "Denumire = ";
		char buffer[200];
		in >> ws;
		in.getline(buffer, 199);
		strcpy_s(cs.denumire, strlen(buffer) + 1, buffer);
		in >> ws;
		cout << "Adresa = ";
		in >> cs.adresa;
		cout << "Numar medici = ";
		in >> cs.nrMedici;
	}
};
class Plomba :public Interventie {
	string material;
	int manopera;
public:	
	Plomba(string material, int manopera) :material(material), manopera(manopera) {

	}
	float Calcul() {
		return 100 + this->manopera;
	}
	void Afisare() {
		cout << this->material << endl;
		cout << this->manopera << endl;
	}
	string gasesteDenumire() {
		return this->material;
	}
};
class Extractie :public Interventie {
	string tipExtractie;
	int manopera;
public:
	Extractie(string tip, int manopera) :tipExtractie(tip), manopera(manopera) {

	}
	void Afisare() {
		cout << this->tipExtractie << endl;
		cout << this->manopera << endl;
	}
	float Calcul() {
		return 300 + this->manopera;
	}
	string gasesteDenumire() {
		return this->tipExtractie;
	}
};

int CabinetStomatologic::numarator = 1;
float CabinetStomatologic::valoareTaxaAnulareConsult = 300;
void main() {
	Interventie* p = new Plomba("Ramona", 304);
	Interventie* e = new Extractie("Molar", 39);
	cout << p->Calcul() << endl;
	cout << e->Calcul() << endl;
	map < string, float > mapInterventii;
	mapInterventii.insert(pair<string, float>(p->gasesteDenumire(), p->Calcul()));
	mapInterventii.insert(pair<string, float>(e->gasesteDenumire(), e->Calcul()));
	map<string, float>::iterator  it;
	for (it = mapInterventii.begin(); it != mapInterventii.end(); it++) {
		cout << it->first << endl;
		cout << it->second << endl;
	}
	string denumCautat = "Molar";
	if (mapInterventii.find(denumCautat) != mapInterventii.end())
	{
		cout << "Interventie gasita!" << endl;
	}
	else cout << "Nasol momentul" << endl;
}
