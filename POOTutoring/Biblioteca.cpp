#include <iostream>
#include <fstream>
#include<set>
using namespace std;
class Carte{
	const int idExemplar;
	static int count;
protected:
	bool eFictiune;
public:
	char* numeCarte;
	char* autor;
	Carte():idExemplar(++count) {
		this->eFictiune = 0;
		this->numeCarte = nullptr;
		this->autor = nullptr;
	}
	Carte(bool eFictiune, const char* numeCarte, const char* autor) :idExemplar(++count) {
		if (strlen(numeCarte) > 2)
		{
			this->numeCarte = new char[strlen(numeCarte) + 1];
			strcpy_s(this->numeCarte, strlen(numeCarte) + 1, numeCarte);
		}
		else this->numeCarte = nullptr;
		if (strlen(autor) > 2)
		{
			this->autor = new char[strlen(autor) + 1];
			strcpy_s(this->autor, strlen(autor) + 1, autor);
		}
		else this->autor = nullptr;
		this->eFictiune = eFictiune;
	}
	Carte(const Carte& c):idExemplar(c.idExemplar) {
		if (strlen(c.numeCarte) > 2 && c.numeCarte)
		{
			this->numeCarte = new char[strlen(c.numeCarte) + 1];
			strcpy_s(this->numeCarte, strlen(c.numeCarte) + 1, c.numeCarte);
		}
		else this->numeCarte = nullptr;
		if (strlen(c.autor) > 2 && c.autor)
		{
			this->autor = new char[strlen(c.autor) + 1];
			strcpy_s(this->autor, strlen(c.autor) + 1, c.autor);
		}
		else this->autor = nullptr;
		this->eFictiune = c.eFictiune;
	}
	~Carte() {
		if (this->autor)
			delete[]this->autor;
		if (this->numeCarte)
			delete[]this->numeCarte;
	}
	Carte& operator=(const Carte& c) {
		if (&c != this) {
			if (strlen(c.numeCarte) > 2 && c.numeCarte)
			{
				if (this->numeCarte)
					delete[]this->numeCarte;
				this->numeCarte = new char[strlen(c.numeCarte) + 1];
				strcpy_s(this->numeCarte, strlen(c.numeCarte) + 1, c.numeCarte);
			}
			else this->numeCarte = nullptr;
			if (strlen(c.autor) > 2 && c.autor)
			{
				if (this->autor)
					delete[]this->autor;
				this->autor = new char[strlen(c.autor) + 1];
				strcpy_s(this->autor, strlen(c.autor) + 1, c.autor);
			}
			else this->autor = nullptr;
			this->eFictiune = c.eFictiune;
		}
		return *this;
	}
	friend ostream& operator<<(ostream& out, const Carte& c) {
		out << "ID Exemplar: " << c.idExemplar << endl;
		out << "Nume carte: " << c.numeCarte << endl;
		out << "Autor: " << c.autor << endl;
		out << "E fictiune: " << (c.eFictiune ? "DA" : "NU") << endl;
		return out;
	}
	bool operator==(const Carte& c)const {
		if (this->eFictiune == c.eFictiune) {
			for (int i = 0; i < strlen(this->numeCarte); i++)
				if (this->numeCarte[i] == c.numeCarte[i]) {
					for (int i = 0; i < strlen(this->autor); i++)
						if (this->autor[i] == c.autor[i])
							return 1;
						else return 0;
				}
				else return 0;
		}
		else return 0;//imi cer scz ptr toate ifurile </3
	}
	bool getFictiune() {
		return this->eFictiune;
	}
	void setFictiune(bool setareFictiune) {
		this->eFictiune = setareFictiune;
	}
	bool operator<(const Carte& c)const {
		return this->eFictiune < c.eFictiune;
	}
	bool operator>(Carte& c) {
		return this->eFictiune > c.eFictiune;
	}
	void scrieFisierBinar(fstream& f) {
		f.write((char*)&this->idExemplar, sizeof(int));
		f.write((char*)&this->eFictiune, sizeof(bool));
		int lungime = strlen(this->numeCarte);
		f.write((char*)this->numeCarte, sizeof(char) * lungime);
		
		int lungimet = strlen(this->autor);
		f.write((char*)this->autor, sizeof(char) * lungimet);
	
	}
	void citesteFisierBinar(fstream& f) {
		f.read((char*)&this->idExemplar, sizeof(int));
		f.read((char*)&this->eFictiune, sizeof(bool));
		int lungime;
		f.read((char*)&lungime, sizeof(int));
		if (this->numeCarte)
			delete[]this->numeCarte;
		this->numeCarte = new char[lungime+1];
		f.read((char*)this->numeCarte, sizeof(char) * lungime);
		this->numeCarte[lungime] = '\0';
		int lungimet;
		f.read((char*)&lungimet, sizeof(int));
		if (this->autor)
			delete[]this->autor;
		this->autor = new char[lungimet+1];
		f.read((char*)this->autor, sizeof(char) * lungimet);
		this->autor[lungimet] = '\0';
	}
};
class Cititor {
protected:
	int nrCartiImprumutate;
	const int CNP;
	Carte* carti;
public:
	Cititor():CNP(605) {
		this->nrCartiImprumutate = 0;
		this->carti = nullptr;
	}
	Cititor(const int CNP, int nrCartiImprumutate, Carte* carti) :CNP(CNP) {
		if (nrCartiImprumutate > 0)
			this->nrCartiImprumutate = nrCartiImprumutate;
		else this->nrCartiImprumutate = 0;
		if (this->nrCartiImprumutate) {
			this->carti = new Carte[this->nrCartiImprumutate];
			for (int i = 0; i < this->nrCartiImprumutate; i++)
				this->carti[i] = carti[i];
		}
		else this->carti = nullptr;
	}
	Cititor(const Cititor& c) :CNP(c.CNP) {
		if (c.nrCartiImprumutate > 0)
			this->nrCartiImprumutate = c.nrCartiImprumutate;
		else this->nrCartiImprumutate = 0;
		if (this->nrCartiImprumutate && c.carti) {
			this->carti = new Carte[this->nrCartiImprumutate];
			for (int i = 0; i < this->nrCartiImprumutate; i++)
				this->carti[i] = c.carti[i];
		}
		else this->carti = nullptr;
	}
	~Cititor() {
		if (this->carti)
			delete[]this->carti;
}
	Cititor& operator=(const Cititor& c) {
		if (&c != this) {
			if (c.nrCartiImprumutate > 0)
				this->nrCartiImprumutate = c.nrCartiImprumutate;
			else this->nrCartiImprumutate = 0;
			if (this->nrCartiImprumutate && c.carti) {
				if (this->carti)
					delete[]this->carti;
				this->carti = new Carte[this->nrCartiImprumutate];
				for (int i = 0; i < this->nrCartiImprumutate; i++)
					this->carti[i] = c.carti[i];
			}
			else this->carti = nullptr;
		}
		return *this;
		}
	friend ostream& operator<<(ostream& out, Cititor& c) {
		out << "CNP: " << c.CNP << endl;
		out << "Nr carti imprumutate: " << c.nrCartiImprumutate << endl;
		if (c.nrCartiImprumutate) {
			out << "Cartile imprumutate: " << endl;
			for (int i = 0; i < c.nrCartiImprumutate; i++)
				out << c.carti[i] << endl;
		}
		else cout << "Cititorul nu are carti imprumutate." << endl;
		return out;
	}
	Cititor& operator+=(Carte carte) {
		Carte* aux = new Carte[this->nrCartiImprumutate + 1];
		for (int i = 0; i < this->nrCartiImprumutate; i++)
			aux[i] = this->carti[i];
		aux[this->nrCartiImprumutate] = carte;
		this->nrCartiImprumutate++;
		if (this->carti)
			delete[]this->carti;
		this->carti = new Carte[this->nrCartiImprumutate];
		this->carti = aux;
		return *this;
	}
	Cititor& operator-=(Carte carte) {
		Carte* aux = new Carte[this->nrCartiImprumutate-1];
		for (int i = 0; i < this->nrCartiImprumutate - 1; i++)
			aux[i] = this->carti[i];
		this->nrCartiImprumutate--;
		if (this->carti)
			delete[]this->carti;
		this->carti = new Carte[this->nrCartiImprumutate];
		this->carti = aux;
		return *this;
	}

};
int Carte::count = 1;
int main() {
	Carte c;
	Carte c2(1, "Ion", "Liviu Rebreanu");
	Carte c3(0, "Amintiri din copilarie", "Ion Creanga");
	cout << c2 << endl;
	Carte c4 = c3;
	c3 = c4;//autoasignare
	Carte c5(1, "Maitreyi", "Mircea Eliade");
	//Carte* vc = new Carte[3];
	//vc[0] = c2;
	//vc[1] = c4;
	//vc[2] = c5;
	//Cititor cit(606, 3, vc);
	//cit -= c4;
	//cout << cit << endl;
	//cout << (c4 == c3) << endl;
	//cout << c2.getFictiune() << endl;
	//c2.setFictiune(0);
	//cout << c2.getFictiune() << endl;
	//cout << (c4 < c3) << endl;
	//cout << (c4 > c3) << endl;
	/*fstream f("fisBib.txt", ios::binary | ios::in);
	fstream f2("fisBib.txt", ios::binary | ios::out);
	c3.scrieFisierBinar(f2);
	f2.close();
	c3.citesteFisierBinar(f);
	f.close();*/
	set<Carte> setCarti;
	setCarti.insert(c3);
	setCarti.insert(c4);
	set<Carte>::iterator it;
	for (it = setCarti.begin(); it != setCarti.end(); it++)
		cout << *it << endl;
	if (setCarti.find(c5) != setCarti.end()) {
		//cauta dupa eFictiune, daca are o carte fictionala, arata ca a gasit
		cout << "Am gasit in sistem" << endl;
	}
	else cout << "Nu am gasit in sistem";
	//delete[]vc;
	return 0;
}