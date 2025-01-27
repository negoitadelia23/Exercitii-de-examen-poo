#include<iostream>
#include<fstream>
using namespace std;
class SubiectTema {
	const int id;
	static int count;
	int termenLimita;
	float punctaj;

protected:
	char* tipFisierIncarcat;
public:
	char* cerinta;
	SubiectTema():id(++count) {
		this->termenLimita = 1;
		this->punctaj = 100.0f;
		this->tipFisierIncarcat = nullptr;
		this->cerinta = nullptr;
	}
	SubiectTema(int termenLimita, float punctaj, const char* tipFisierIncarcat, const char* cerinta) :id(++count) {
		if (termenLimita>=0&&termenLimita <= 14)
			this->termenLimita = termenLimita;
		else this->termenLimita = 1;
		if (punctaj >= 0 && punctaj <= 100)
			this->punctaj = punctaj;
		else this->punctaj = 100.0f;
		if (tipFisierIncarcat)
		{
			this->tipFisierIncarcat = new char[strlen(tipFisierIncarcat) + 1];
			strcpy_s(this->tipFisierIncarcat, strlen(tipFisierIncarcat) + 1, tipFisierIncarcat);
		}
		else this->tipFisierIncarcat = nullptr;
		if (cerinta)
		{
			this->cerinta = new char[strlen(cerinta) + 1];
			strcpy_s(this->cerinta, strlen(cerinta) + 1, cerinta);
		}
		else this->cerinta = nullptr;
	}
	SubiectTema(const SubiectTema& t):id(t.id) {
		if (t.termenLimita>=0 and t.termenLimita <= 14)
			this->termenLimita = t.termenLimita;
		else this->termenLimita = 1;
		if (t.punctaj >= 0 && t.punctaj <= 100)
			this->punctaj = t.punctaj;
		else this->punctaj = 100.0f;
		if (t.tipFisierIncarcat)
		{
			this->tipFisierIncarcat = new char[strlen(t.tipFisierIncarcat) + 1];
			strcpy_s(this->tipFisierIncarcat, strlen(t.tipFisierIncarcat) + 1, t.tipFisierIncarcat);
		}
		else this->tipFisierIncarcat = nullptr;
		if (t.cerinta)
		{
			this->cerinta = new char[strlen(t.cerinta) + 1];
			strcpy_s(this->cerinta, strlen(t.cerinta) + 1, t.cerinta);
		}
		else this->cerinta = nullptr;
	}
	~SubiectTema() {
		if (this->cerinta)
			delete[] this->cerinta;
		if (this->tipFisierIncarcat)
			delete[] this->tipFisierIncarcat;
	}
	SubiectTema& operator=(const SubiectTema& t) {
		if (&t != this) {
			if (t.termenLimita>=0 and t.termenLimita <= 14)
				this->termenLimita = t.termenLimita;
			else this->termenLimita = 1;
			if (t.punctaj >= 0 && t.punctaj <= 100)
				this->punctaj = t.punctaj;
			else this->punctaj = 100.0f;
			if (t.tipFisierIncarcat)
			{
				if (this->tipFisierIncarcat)
					delete[] this->tipFisierIncarcat;
				this->tipFisierIncarcat = new char[strlen(t.tipFisierIncarcat) + 1];
				strcpy_s(this->tipFisierIncarcat, strlen(t.tipFisierIncarcat) + 1, t.tipFisierIncarcat);
			}
			else this->tipFisierIncarcat = nullptr;
			if (t.cerinta)
			{
				if (this->cerinta)
					delete[] this->cerinta;
				this->cerinta = new char[strlen(t.cerinta) + 1];
				strcpy_s(this->cerinta, strlen(t.cerinta) + 1, t.cerinta);
			}
			else this->cerinta = nullptr;
		}
		return *this;
	}
	int getTermenLimita() {
		return this->termenLimita;
	}
	void setTermenLimita(int termenNou) {
		if (termenNou>=0&&termenNou <= 14)
			this->termenLimita = termenNou;
		else throw 121;
	}
	SubiectTema& operator+=(float cresterePunctaj) {
		if (this->punctaj + cresterePunctaj <= 100.0f)
			this->punctaj += cresterePunctaj;
		else if (this->punctaj + cresterePunctaj >= 100.0f)
			this->punctaj = 100.0f;
		return *this;
	}
	float getPunctaj() {
		return this->punctaj;
	}
	void scrieFisierBinar(fstream& f) {
		f.write((char*)&this->id, sizeof(int));
		f.write((char*)&this->termenLimita, sizeof(int));
		f.write((char*)&this->punctaj, sizeof(float));
		int lungime = strlen(this->cerinta);
		f.write((char*)&this->cerinta, sizeof(char)*lungime);
		int lungimet = strlen(this->tipFisierIncarcat);
		f.write((char*)&this->tipFisierIncarcat, sizeof(char)*lungimet);
	}
	void citesteFisierBinar(fstream& f) {
		f.read((char*)&this->id, sizeof(int));
		f.read((char*)&this->termenLimita, sizeof(int));
		f.read((char*)&this->id, sizeof(float));
		int lungime;
		f.read((char*)&lungime, sizeof(int));
		if (this->cerinta)
			delete[] this->cerinta;
		this->cerinta = new char[lungime + 1];
		f.read((char*)&this->cerinta, sizeof(char) * lungime);
		this->cerinta[lungime] = '\0';
		int lungimet;
		f.read((char*)&lungimet, sizeof(int));
		if (this->tipFisierIncarcat)
			delete[] this->tipFisierIncarcat;
		this->tipFisierIncarcat = new char[lungimet + 1];
			f.read((char*)&this->tipFisierIncarcat, sizeof(char)*lungimet);
		this->tipFisierIncarcat[lungimet] = '\0';
	}
	friend ostream& operator<<(ostream& out, SubiectTema& s) {
		out << "ID: " << s.id << endl;
		out << "Termen limita in: " << s.termenLimita << " zile" << endl;
		out << "Punctaj primit: " << s.punctaj << endl;
		out << "Tip fisier incarcat: " << s.tipFisierIncarcat << endl;
		out << "Cerinta: " << s.cerinta << endl;
		return out;
	}
};
class MapaTeme {
	//puteam sa fac cu vector stl dar nu vr sa ma complic
	int nrTeme;
	SubiectTema* vector;
public:
	MapaTeme() {
		this->nrTeme = 0;
		this->vector = nullptr;
	}
	MapaTeme(int nrTeme, SubiectTema* vector) {
		if (nrTeme > 0)
		{
			this->nrTeme = nrTeme;

		}
		else this->nrTeme = 0;
		if (this->nrTeme && vector) {
			this->vector = new SubiectTema[this->nrTeme];
			for (int i = 0; i < this->nrTeme; i++)
				this->vector[i] = vector[i];
		}
		else this->vector = nullptr;
	}
	MapaTeme(const MapaTeme& m) {
		if (m.nrTeme > 0)
		{
			this->nrTeme = m.nrTeme;

		}
		else this->nrTeme = 0;
		if (this->nrTeme && m.vector) {
			this->vector = new SubiectTema[this->nrTeme];
			for (int i = 0; i < this->nrTeme; i++)
				this->vector[i] = m.vector[i];
		}
		else this->vector = nullptr;
	}
	~MapaTeme() {
		if (this->vector)
			delete[]this->vector;
	}
	MapaTeme& operator=(const MapaTeme& m) {
		if (&m != this) {
			if (m.nrTeme > 0)
			{
				this->nrTeme = m.nrTeme;

			}
			else this->nrTeme = 0;
			if (this->nrTeme && m.vector) {
				this->vector = new SubiectTema[this->nrTeme];
				for (int i = 0; i < this->nrTeme; i++)
					this->vector[i] = m.vector[i];
			}
			else this->vector = nullptr;
		}
		return *this;
	}
	MapaTeme& operator+=(SubiectTema s) {
		SubiectTema* aux = new SubiectTema[this->nrTeme + 1];
		for (int i = 0; i < this->nrTeme; i++)
			aux[i] = this->vector[i];
		aux[this->nrTeme] = s;
		this->nrTeme++;
		if (this->vector)
			delete[]this->vector;
		this->vector = new SubiectTema[this->nrTeme];
		this->vector = aux;
		return *this;
	}
	friend ostream& operator<<(ostream& out, MapaTeme& m) {
		out << "Nr teme: " << m.nrTeme << endl;
		if (m.nrTeme > 0) {
			for (int i = 0; i < m.nrTeme; i++)
				out << "Tema " << i + 1 << ": " << m.vector[i] << endl;
		}
		else out << "Nu avem teme in mapa." << endl;
		return out;
	}
};
int SubiectTema::count = 1;
void main() {
	SubiectTema t;
	SubiectTema t2(13, 65.0f, ".docx", "Ramona");
	SubiectTema t3 = t2;
	SubiectTema t4;
	t4 = t3;
	cout << t4.getTermenLimita() << endl;
	t4.setTermenLimita(10);
	cout << t4.getTermenLimita() << endl;
	cout << t4.getPunctaj() << endl;
	t4 += 25.0f;
	cout << t4.getPunctaj() << endl;
	t4 += 25.0f;
	cout << t4.getPunctaj() << endl;
	try {
		t4.setTermenLimita(10);
		t4.setTermenLimita(-4);
	}
	catch (int exc) {
		cout << exc << endl;
	}
	catch (...) {

	}
/*	fstream f2("fisBin.txt", ios::out | ios::binary);
		t4.scrieFisierBinar(f2); 
		f2.close();             
	fstream f("fisBin.txt", ios::in | ios::binary);
		t4.citesteFisierBinar(f);
		f.close();        */      
	MapaTeme m;
	m += t2;
	cout << m << endl;
}