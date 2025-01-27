#include<iostream>
#include<map>
using namespace std;

class Marker {
	string proprietar;
public:
	virtual char* afiseazaProducator() = 0;
	Marker() {
		this->proprietar = "N/A";
	}
	Marker(string proprietar) {
		this->proprietar = proprietar;
	}
	Marker(const Marker& m) {
		this->proprietar = m.proprietar;
	}

};
class MarkerElectronic:public Marker {
	const int id;
	static int count;
	float dimensiune;
	char* producator;
public:
	MarkerElectronic() :id(++count),Marker() {
		this->dimensiune = 5.0f;
		this->producator = nullptr;
	}
	MarkerElectronic(float dimensiune, const char* producator) :Marker(),id(++count) {
		if (dimensiune >= 5.0f)
			this->dimensiune = dimensiune;
		else this->dimensiune = 5.0f;
		if (producator && (strlen(producator) > 2)) {

			this->producator = new char[strlen(producator) + 1];
			strcpy_s(this->producator, strlen(producator) + 1, producator);
		}
		else this->producator = nullptr;
	}
	MarkerElectronic(const MarkerElectronic& me):id(me.id),Marker(me) {
		if (me.dimensiune >= 5.0f)
			this->dimensiune = me.dimensiune;
		else this->dimensiune = 5.0f;
		if (me.producator && (strlen(me.producator) > 2)) {

			this->producator = new char[strlen(me.producator) + 1];
			strcpy_s(this->producator, strlen(me.producator) + 1, me.producator);
		}
		else this->producator = nullptr;
	}
	MarkerElectronic& operator=(const MarkerElectronic& me) {
		if (&me != this) {
			if (me.dimensiune >= 5.0f)
				this->dimensiune = me.dimensiune;
			else this->dimensiune = 5.0f;
			if (me.producator && (strlen(me.producator) > 2)) {
				if (this->producator)
					delete[]this->producator;
				this->producator = new char[strlen(me.producator) + 1];
				strcpy_s(this->producator, strlen(me.producator) + 1, me.producator);
			}
			else this->producator = nullptr;
		}
		return *this;
	}
	~MarkerElectronic() {
		if (this->producator)
			delete[]this->producator;
	}
	friend ostream& operator<<(ostream& out, MarkerElectronic& me) {
		out << "ID: " << me.id << endl;
		out << "Dimensiune: " << me.dimensiune << endl;
		out << "Producator: " << me.producator << endl;
		return out;
	}
	friend istream& operator>>(istream& in, MarkerElectronic& me) {
		cout << "Dimensiune: ";
		in >> me.dimensiune;
		cout << "Producator: ";
		char buffer[100];
		in >> buffer;
		if (me.producator)
			delete[]me.producator;
		me.producator = new char[strlen(buffer) + 1];
		strcpy_s(me.producator, strlen(buffer) + 1, buffer);
		return in;
	}
	char* afiseazaProducator(){
		return this->producator;
	}
	bool operator==(const MarkerElectronic me)const {
		return (this->dimensiune == me.dimensiune && strlen(this->producator) == strlen(me.producator));
	}
	bool operator<(const MarkerElectronic& me)const {
		return this->dimensiune < me.dimensiune;
	}
};
class MarkerInteligent : public Marker {
	float grosime;
	string tipLinie;
	char* producator;
public:
	MarkerInteligent():Marker() {
		this->grosime = 4.5f;
		this->tipLinie = "Groasa";
		this->producator = new char[strlen("Delia") + 1];
		strcpy_s(this->producator, strlen("Delia") + 1, "Delia");
	}
	char* afiseazaProducator() {
		return this->producator;
	}
};
int MarkerElectronic::count = 1;
int main() {
	MarkerElectronic me;
	MarkerElectronic me2(6.8f, "Ramona");
	MarkerElectronic me3 = me2;
	MarkerElectronic me4;
	me4 = me3;
	//cin >> me;
	//cout << me << endl;
	//cout << (me == me2) << endl; //:)
	Marker* m = new MarkerElectronic(me2);
	Marker* m1 = new MarkerInteligent();
	cout << m->afiseazaProducator() << endl;
	cout << m1->afiseazaProducator() << endl;

	return 0;
}