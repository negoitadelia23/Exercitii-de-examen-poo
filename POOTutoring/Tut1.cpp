#include<iostream>
#include<fstream>
#include <string>
using namespace std;
class ClasaVirtuala {
public:
	virtual float Calculeaza() = 0;//clasa abstracta
};
class Comanda: public ClasaVirtuala {
	//4 atribute, unu const/static, atribut dinamic(pointer)
	const int id;//cel mai smecher atribut constant
	string numeClient;
	int ziComanda;
	int nrProduse;
	float* preturiProduse;//ca sunt mai multe produse intr-o comanda

public:
	Comanda():id(0) {
		this->numeClient = "Ramona";
		this->ziComanda = 1;
		this->nrProduse = 0;
		this->preturiProduse = nullptr;
	}
	Comanda(const int id, string nume, int zi, int nr, float* preturi) :id(id) {
		//la validari, se fac pe param nu pe this, si pune ce face pe ramura de else
		if (nume.length() > 3)
			this->numeClient = nume;
		else this->numeClient = "Ramona";
		if (zi >= 1 && zi <= 31)
		this->ziComanda = zi;
		if (nr >= 0 && preturi != nullptr)
		{
			this->nrProduse = nr;
			this->preturiProduse = new float[nr];
			for (int i = 0; i < nr; i++)
				this->preturiProduse[i] = preturi[i];
		}
	}
	Comanda(const Comanda& c):id(c.id){//trebuie sa copiez obiectul astfel trb sa am referinta(copiez atributele
		this->numeClient = c.numeClient;
		this->ziComanda = c.ziComanda;
		this->nrProduse = c.nrProduse;
		this->preturiProduse = new float[c.nrProduse];
		if (c.preturiProduse) {
			for (int i = 0; i < c.nrProduse; i++)
				this->preturiProduse[i] = c.preturiProduse[i];
		}
		else this->preturiProduse = nullptr;
	}
	int getZiComanda() {
		return this->ziComanda;
	}
	void setZiComanda(int ziNoua) {
		if(ziNoua>=1 && ziNoua<=31)
		this->ziComanda = ziNoua;
	}
	~Comanda() {
		if(this->preturiProduse)
		delete[] this->preturiProduse;
	}
	Comanda& operator=(const Comanda& c) {//op = se apeleaza intre doua ob deja construite
		//daca nu pun ref mai face un stop la constructorul de copiere
		if (&c != this)//pun ca sa nu se stea
		{
			this->numeClient = c.numeClient;
			this->ziComanda = c.ziComanda;
			this->nrProduse = c.nrProduse;
			if (this->preturiProduse)
				delete[] this->preturiProduse;
			this->preturiProduse = new float[c.nrProduse];
			if (c.preturiProduse) {
				for (int i = 0; i < c.nrProduse; i++)
					this->preturiProduse[i] = c.preturiProduse[i];
			}
			else { 
			this->nrProduse = 0;
			this->preturiProduse = nullptr;
			}
		}
		return *this;
	}
	float operator[](int index) {
		if (index >= 0 && index < this->nrProduse)
			return this->preturiProduse[index];
		else throw 121;
	}
	Comanda& operator++()//preincrementare 
	{
		Comanda aux = *this;
		for (int i = 0; i < this->nrProduse; i++)
			this->preturiProduse[i]++;
		return *this;
	}
	Comanda& operator++(int)//postincrementare
	{
		Comanda aux = *this;
		for (int i = 0; i < aux.nrProduse; i++)
			aux.preturiProduse[i]++;
		return *this;
	}
	friend ostream& operator<<(ostream& out, Comanda& c) {
		out <<"ID: "<< c.id << endl;
		out << "Nume client: " << c.numeClient << endl;
		out << "Zi comanda: " << c.ziComanda << endl;
		if (c.nrProduse >= 1)
		{
			out << "Numar produse: " << c.nrProduse << endl;
			for (int i = 0; i < c.nrProduse; i++)
				out << "Produsul " << i + 1 << " are pretul: " << c.preturiProduse[i] << endl;
		}
		else out << "Nu a facut comanda" << endl;
		return out;
	}
	friend ofstream& operator<<(ofstream& out, Comanda& c) {
		out << c.id << endl;
		out << c.numeClient << endl;
		out << c.ziComanda << endl;
		if (c.nrProduse >= 1)
		{
			out << c.nrProduse << endl;
			for (int i = 0; i < c.nrProduse; i++)
				out << c.preturiProduse[i] << endl;
		}
		return out;
	}
	void aplicaFiltruFisText(int nrZiComanda) {
		ofstream f("fiscuflitru.txt", ios::out);
		if (this->ziComanda <= nrZiComanda)
			f << *this << endl;
		f.close();
	}
	float Calculeaza() {
		float pretTotal = 0;
		for (int i = 0; i < this->nrProduse; i++)
			pretTotal += this->preturiProduse[i];
		return pretTotal;
	}
};
class Salariat :public ClasaVirtuala {
	string nume_sal;
	float salariu;//sal brut
public:
	Salariat() {
		this->nume_sal = "Ramona";
		this->salariu = 5000;
	}
	Salariat(string nume, float salariu) {
		this->nume_sal = nume;
		this->salariu = salariu;
	}
	Salariat(const Salariat& sal) {
		this->nume_sal = sal.nume_sal;
		this->salariu = sal.salariu;
	}
	~Salariat() {

	}
	float Calculeaza() {
		return 12 * this->salariu;//salariu anual brut
	}
};
int main() {
	Comanda c1;
	ofstream fis("fis.txt", ios::out);
	//cout << c1.getZiComanda() << endl;
	//c1.setZiComanda(4);
	//c1.setZiComanda(-1);
	//cout << c1.getZiComanda() << endl;
	int numar = 2;
	float* preturi = new float[numar];
	preturi[0] = 12.0f; preturi[1] = 15.0f;
	Comanda c2(1, "Ramona", 3, numar, preturi);
	cout << c2.getZiComanda() << endl;
	Comanda c = c1;
	cout << c1.getZiComanda() << endl;
	Comanda c3;
	c3 = c1;
	cout << c3.getZiComanda() << endl;
	Comanda c4 = c3;
	c4 = c1;
	cout << c4.getZiComanda() << endl;
	cout << c1 << endl;
	fis << c1<<endl;
	c3 = c2++;
	c1 = ++c2;
	cout << c1 << endl;
	cout << c3 << endl;
	cout << c2 << endl;
	try{
		cout << c2[0] << endl;
		cout << c2[90] << endl;
		cout << c2[1] << endl;
	}
	catch (int exc) {
		cout << exc << endl;
	}
	catch (...) {
		
	}
	ClasaVirtuala* cv = new Comanda(2, "Ram",3, numar, preturi);
	ClasaVirtuala* cv1 = new Salariat("Ana",5000);
	cout << cv->Calculeaza() << endl;
	cout << cv1->Calculeaza() << endl;
	fis << c3 << endl;
	c3.aplicaFiltruFisText(2);
	////shallow copy - copie superficiala (copiez la examen doar rezultatul)
	////int val = 50;
	////int* pVal = &val;
	////int* pVal1 = &val;
	////cout << *pVal << endl;
	////delete pVal;
	////cout << *pVal1 << endl;
	////deep copy - copie profunda (copiez la examen tot exercitiul)
	//int ex = 100;
	//int* pEx = new int(ex);
	//int* pEx1 = new int(ex);
	//cout << ex << endl << pEx << endl << pEx1 << endl;
	fis.close();
	return 0;
}