#include <iostream>
using namespace std;
class Scara {
	const int idScara;
	static int count;
	string numeScara;
	int nrApartamente;
	int* apartamente;
public:
	Scara() :idScara(++count) {
		this->numeScara = "Ramona";
		this->nrApartamente = 0;
		this->apartamente = nullptr;
	}
	Scara(string numeScara,int nrApartamente, int* apartamente) :idScara(++count) {
		if (nrApartamente)
			this->nrApartamente = nrApartamente;
		else this->nrApartamente = 0;
		if (this->nrApartamente)
		{
			this->apartamente = new int[this->nrApartamente];
			for (int i = 0; i < nrApartamente; i++)
				this->apartamente[i] = apartamente[i];
		}
		else this->apartamente = nullptr;
		if (this->numeScara.length() > 1)
			this->numeScara = numeScara;
		else this->numeScara = "Ramona";
		}	
	Scara(const Scara& s):idScara(s.idScara) {
		if (s.nrApartamente)
			this->nrApartamente = s.nrApartamente;
		else this->nrApartamente = 0;
		if (this->nrApartamente)
		{
			this->apartamente = new int[this->nrApartamente];
			for (int i = 0; i < nrApartamente; i++)
				this->apartamente[i] = s.apartamente[i];
		}
		else this->apartamente = nullptr;
		if (this->numeScara.length() > 1)
			this->numeScara = s.numeScara;
		else this->numeScara = "Ramona";
	}
	~Scara() {
		if (this->apartamente)
			delete[]this->apartamente;
	}
	Scara& operator=(const Scara& s) {
		if (&s != this) {
			if (s.nrApartamente)
				this->nrApartamente = s.nrApartamente;
			else this->nrApartamente = 0;
			if (this->nrApartamente)
			{
				this->apartamente = new int[this->nrApartamente];
				for (int i = 0; i < nrApartamente; i++)
					this->apartamente[i] = s.apartamente[i];
			}
			else this->apartamente = nullptr;
			if (this->numeScara.length() > 1)
				this->numeScara = s.numeScara;
			else this->numeScara = "Ramona";
		}
		return *this;
	}
	friend ostream& operator<<(ostream& out, Scara& s) {
		out << "ID Scara: " << s.idScara << endl;
		out << "Nume scara: " << s.numeScara << endl;
		out << "Numar apartemente: " << s.nrApartamente << endl;
		if (s.nrApartamente) {
			out << "Apartamente: ";
			for (int i = 0; i < s.nrApartamente; i++)
				out << endl << s.apartamente[i];
		}
		else out << "Nu are apartamente scara." << endl;
		return out;
	}
	int& operator[](int index) {
		if (index >= 0 && index <= this->nrApartamente)
			return this->apartamente[index];
	}
};
int Scara::count = 1;
class Bloc {
	int nrScari;
	float* productivitate;
	Scara* scari;
public:
	Bloc() {
		this->nrScari = 0;
		this->productivitate = nullptr;
		this->scari = nullptr;
	}
	Bloc(int nrScari, float* productivitate, Scara* scari) {
		if (nrScari > 0)
			this->nrScari = nrScari;
		else this->nrScari = 0;
		if (this->nrScari) {
			if (productivitate) {
				this->productivitate = new float[this->nrScari];
				for (int i = 0; i < this->nrScari; i++)
					this->productivitate[i] = productivitate[i];
			}
			else this->productivitate = nullptr;
			if (scari) {
				this->scari = new Scara[this->nrScari];
				for (int i = 0; i < this->nrScari; i++)
					this->scari[i] = scari[i];
			}
			else this->scari = nullptr;
		}
		else {
			this->productivitate = nullptr;
			this->scari = nullptr;
		}
	}
	Bloc(const Bloc& b) {
		if (b.nrScari > 0)
			this->nrScari = b.nrScari;
		else this->nrScari = 0;
		if (this->nrScari) {
			if (b.productivitate) {
				this->productivitate = new float[this->nrScari];
				for (int i = 0; i < this->nrScari; i++)
					this->productivitate[i] = b.productivitate[i];
			}
			else this->productivitate = nullptr;
			if (b.scari) {
				this->scari = new Scara[this->nrScari];
				for (int i = 0; i < this->nrScari; i++)
					this->scari[i] = b.scari[i];
			}
			else this->scari = nullptr;
		}
		else {
			this->productivitate = nullptr;
			this->scari = nullptr;
		}
	}
	~Bloc() {
		if (this->productivitate)
			delete[]this->productivitate;
		if (this->scari)
			delete[]this->scari;
	}
	Bloc& operator=(const Bloc& b) {
		if (&b != this) {
			if (b.nrScari > 0)
				this->nrScari = b.nrScari;
			else this->nrScari = 0;
			if (this->nrScari) {
				if (b.productivitate) {
					if (this->productivitate)
						delete[]this->productivitate;
					this->productivitate = new float[this->nrScari];
					for (int i = 0; i < this->nrScari; i++)
						this->productivitate[i] = b.productivitate[i];
				}
				else this->productivitate = nullptr;
				if (b.scari) {
					if (this->scari)
						delete[]this->scari;
					this->scari = new Scara[this->nrScari];
					for (int i = 0; i < this->nrScari; i++)
						this->scari[i] = b.scari[i];
				}
				else this->scari = nullptr;
			}
			else {
				this->productivitate = nullptr;
				this->scari = nullptr;
			}
		}
		return *this;
	}
	Bloc& operator+=(Scara s) {
		Scara* aux = new Scara[this->nrScari + 1];
		for (int i = 0; i < this->nrScari; i++)
			aux[i] = this->scari[i];
		aux[this->nrScari] = s;
		this->nrScari++;
		if (this->scari)
			delete[]this->scari;
		this->scari = new Scara[this->nrScari];
		this->scari = aux;
		return *this;
	}
	Bloc& operator+=(float productivitateNoua) {
		float* aux = new float[this->nrScari];
		for (int i = 0; i < this->nrScari; i++)
			aux[i] = this->productivitate[i];
		aux[this->nrScari-1] = productivitateNoua;
		if (this->productivitate)
			delete[]this->productivitate;
		this->productivitate = new float[this->nrScari];
		this->productivitate = aux;
		return *this;
	}
	friend ostream& operator<<(ostream& out, Bloc& b) {
		out << "Nr scari: " << b.nrScari << endl;
		if (b.nrScari) {
			if (b.scari) {
				out << "Scari:";
				for (int i = 0; i < b.nrScari; i++)
					out << endl << b.scari[i] << endl;
			}
			if (b.productivitate) {
				out << "Productivitate:";
				for (int i = 0; i < b.nrScari; i++)
					out << endl << b.productivitate[i] << endl;
			}
		}
		else out << "Blocul nu are scari." << endl;
		return out;
	}
	float afiseazaProductivitateMimina() {
		float min = productivitate[0];
		for (int i = 1; i < this->nrScari; i++)
		{
			if (productivitate[i] < min)
				min = productivitate[i];
		}
		return min;
	}
	float afiseazaProductivitateMaxima() {
		float max = productivitate[0];
		for (int i = 1; i < this->nrScari; i++) {
			if (productivitate[i] > max)
				max = productivitate[i];
		}
		return max;
	}
};
void main() {
	Scara s;
	int numar = 3;
	int* vector = new int[numar];
	vector[0] = 23;
	vector[1] = 34;
	vector[2] = 25;
	Scara s2("M3", numar, vector);
	Scara s3 = s2;
	Scara s4;
	s4 = s3;
	s4[1] = 24;
	cout << s4 << endl;
	Scara* scari = new Scara[numar];
	float* vectorf = new float[numar];
	scari[0] = s2;
	scari[1] = s3;
	scari[2] = s4;
	vectorf[0] = 23;
	vectorf[1] = 34;
	vectorf[2] = 25;
	Bloc b(numar, vectorf, scari);
	Scara s5("Delia", numar,vector);
	b += s5;
	b += 34.5;
	cout << b << endl;
	cout << b.afiseazaProductivitateMimina() << endl;
	cout << b.afiseazaProductivitateMaxima() << endl;
	delete[]vector;
	delete[]scari;
	delete[]vectorf;
}