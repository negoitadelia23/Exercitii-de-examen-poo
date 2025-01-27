#include <iostream>
#include <map>
using namespace std;

class Magazin {
	static float tva;
	int nrProduse;
	float* pretProduse;
	bool* expiraZiuaUrmatoare;
public:
	Magazin() {
		this->nrProduse = 0;
		this->pretProduse = nullptr;
		this->expiraZiuaUrmatoare = nullptr;
	}
	Magazin(int nr, float* pret, bool* data) {
		if (nr > 0)
			this->nrProduse = nr;
		else this->nrProduse = 0;
		if (pret && this->nrProduse) {
			this->pretProduse = new float[this->nrProduse];
			for (int i = 0; i < this->nrProduse; i++)
				this->pretProduse[i] = pret[i];
		}
		if (data && this->nrProduse) {
			this->expiraZiuaUrmatoare = new bool[this->nrProduse];
			for (int i = 0; i < this->nrProduse; i++)
				this->expiraZiuaUrmatoare[i] = data[i];
		}
	}
	Magazin(const Magazin& m) {
		if (m.nrProduse > 0)
			this->nrProduse = m.nrProduse;
		else this->nrProduse = 0;
		if (m.pretProduse && this->nrProduse) {
			this->pretProduse = new float[this->nrProduse];
			for (int i = 0; i < this->nrProduse; i++)
				this->pretProduse[i] = m.pretProduse[i];
		}
		else this->pretProduse = nullptr;
		if (m.expiraZiuaUrmatoare && this->nrProduse) {
			this->expiraZiuaUrmatoare = new bool[this->nrProduse];
			for (int i = 0; i < this->nrProduse; i++)
				this->expiraZiuaUrmatoare[i] = m.expiraZiuaUrmatoare[i];
		}
	}
	~Magazin() {
		if (this->pretProduse)
			delete[]this->pretProduse;
		if (this->expiraZiuaUrmatoare)
			delete[] this->expiraZiuaUrmatoare;
	}
	Magazin& operator=(const Magazin& m) {
		if (&m != this) {
			if (m.nrProduse > 0)
				this->nrProduse = m.nrProduse;
			else this->nrProduse = 0;
			if (m.pretProduse && this->nrProduse) {
				if (this->pretProduse)
					delete[]this->pretProduse;
				this->pretProduse = new float[this->nrProduse];
				for (int i = 0; i < this->nrProduse; i++)
					this->pretProduse[i] = m.pretProduse[i];
			}
			else this->pretProduse = nullptr;
			if (m.expiraZiuaUrmatoare && this->nrProduse) {
				if (this->expiraZiuaUrmatoare)
					delete[] this->expiraZiuaUrmatoare;
				this->expiraZiuaUrmatoare = new bool[this->nrProduse];
				for (int i = 0; i < this->nrProduse; i++)
					this->expiraZiuaUrmatoare[i] = m.expiraZiuaUrmatoare[i];
			}
		}
		return *this;
	}
	friend ostream& operator<<(ostream& out, Magazin& m) {
		out << "TVA: " << Magazin::tva << endl;
		out << "Numar produse: " << m.nrProduse << endl;
		if (m.nrProduse)
			for (int i = 0; i < m.nrProduse; i++)
			{
				out << "Produsul " << i + 1 << " are pretul " << m.pretProduse[i] << endl;
				out << "Produsul " << i + 1 << " expira: " << (m.expiraZiuaUrmatoare[i] ? "DA":"NU") << endl;
			}
		else out << "Nu avem produse in magazin." << endl;
		
		return out;
	}
	Magazin& operator*=(float reducere) {
		for (int i = 0; i < this->nrProduse; i++) 
			if (this->expiraZiuaUrmatoare[i]) {
				if (reducere >= 0 && reducere <= 1) {

					this->pretProduse[i] *= (1 - reducere);
				}
			}
		return *this;
	}
	bool operator==(const Magazin& m) {
		if (this->nrProduse == m.nrProduse) {
			for (int i = 0; i < this->nrProduse; i++)
				if (this->pretProduse[i] == m.pretProduse[i] && this->expiraZiuaUrmatoare[i] == m.expiraZiuaUrmatoare[i])
					return true;
				else return false;
		}
		else return false;
	}
};
class ProduseInStoc {
	int stoc;
	string tipProduse;
	string* produse;
public:
	ProduseInStoc() {
		this->stoc = 0;
		this->tipProduse = "N/A";
		this->produse = nullptr;
	}
	ProduseInStoc(int stoc, string tipProduse, string* produse) {
		if (stoc)
			this->stoc = stoc;
		else this->stoc = 0;
		if (tipProduse.length() >= 3)
			this->tipProduse = tipProduse;
		if (produse && stoc) {
			this->produse = new string[stoc];
			for (int i = 0; i < stoc; i++)
				this->produse[i] = produse[i];
		}
		else this->produse = nullptr;
	}
	ProduseInStoc(const ProduseInStoc& ps) {
		if (ps.stoc)
			this->stoc = ps.stoc;
		else this->stoc = 0;
		if (ps.tipProduse.length() >= 3)
			this->tipProduse = ps.tipProduse;
		if (ps.produse && ps.stoc) {
			this->produse = new string[ps.stoc];
			for (int i = 0; i < ps.stoc; i++)
				this->produse[i] = ps.produse[i];
		}
		else this->produse = nullptr;
	}
	~ProduseInStoc() {
		if (this->produse)
			delete[]this->produse;
	}
	ProduseInStoc& operator=(const ProduseInStoc& ps) {
		if (&ps != this) {
			if (ps.stoc)
				this->stoc = ps.stoc;
			else this->stoc = 0;
			if (ps.tipProduse.length() >= 3)
				this->tipProduse = ps.tipProduse;
			if (ps.produse && ps.stoc) {
				if (this->produse)
					delete[]this->produse;
				this->produse = new string[ps.stoc];
				for (int i = 0; i < ps.stoc; i++)
					this->produse[i] = ps.produse[i];
			}
			else this->produse = nullptr;
		}
		return *this;
	}
	ProduseInStoc& operator+=(string produsNou) {
		string* aux = new string[stoc+1];
		for (int i = 0; i < stoc; i++)
			aux[i] = this->produse[i];
		aux[stoc] = produsNou;
		stoc++;
		if (this->produse)
			delete[]this->produse;
		this->produse = new string[stoc];
		this->produse = aux;
		return *this;
	}
	friend ostream& operator<<(ostream& out, ProduseInStoc& m) {
		out << "Tip Produs: " << m.tipProduse << endl;
		out << "Stoc: " << m.stoc << endl;
		if (m.stoc) {
			for (int i = 0; i < m.stoc; i++)
				out << "Produsul " << i + 1 << " = " << m.produse[i] << endl;
		}
		else out << "Nu avem produse in stoc" << endl;
		return out;
	}
	void operator()() {
		if (stoc == 0)
			cout << "Produsele nu mai sunt in stoc";
	}
	string getProdus(int index) {
		if (index >= 0 && index < this->stoc)
			return this->produse[index];
		else throw 121;
	}
};
float Magazin::tva = 0.19;
void main(){
	Magazin m;
	int numar = 2;
	float* pret = new float[numar];
	for (int i = 0; i < numar; i++)
		pret[i] = 34.5;
	bool* expirare = new bool[numar];
	expirare[0] = 1;
	expirare[1] = 0;
	Magazin m1(numar, pret, expirare);
	Magazin m2 = m1;
	Magazin m3;
	m3 = m2;
	cout << m3 << endl;
	m3 *= 0.2;
	cout << m3 << endl; //S-a aplicat reducerea !!
	cout << (m1 == m2) << endl;
	cout << (m3 == m) << endl;
	string* carne = new string[numar];
	carne[0] = "Macrou";
	carne[1] = "Crap";
	ProduseInStoc ps(numar, "Peste", carne);
	cout << ps << endl;
	string prodNou = "Hering";
	ps += prodNou;
	cout << ps << endl;//:DDDDD
	try {
		cout << ps.getProdus(1) << endl;
		cout << ps.getProdus(3) << endl;
	}
	catch (int exc) {
		cout << exc << endl;
	}
	catch (...) {

	}
	map<string, ProduseInStoc> mapSpeciePesti;
	mapSpeciePesti.insert(pair<string, ProduseInStoc>(ps.getProdus(0), ps));
	mapSpeciePesti.insert(pair<string, ProduseInStoc>(ps.getProdus(1), ps));
	map<string, ProduseInStoc>::iterator it;
	for (it = mapSpeciePesti.begin(); it != mapSpeciePesti.end(); it++)
	{
		cout << it->first;
		cout << it->second;
	}
	string specie = "Crap";
	if (mapSpeciePesti.find(specie) != mapSpeciePesti.end()) {
		cout << "Am gasit!" << endl;
	}
	else cout << "Nu am gasit" << endl;
	delete[] carne;
	delete[] expirare;
	delete[] pret;
	///SHHUUUUUU
}