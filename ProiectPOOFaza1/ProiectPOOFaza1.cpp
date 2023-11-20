#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;
//---------------------------------------GESTIUNEA UNUI RESTAURANT---------------------------------------------------


class Ingredient {

private:
	char* numeIngredient;
	float cantitateDisponibila;
	bool existaIngredient;

public:
	Ingredient() : numeIngredient(nullptr), cantitateDisponibila(0), existaIngredient(false) {}

	//constructor cu doi parametri
	Ingredient(const char* numeIngredient, bool existaIngredient)
	{
		this->numeIngredient = new char[strlen(numeIngredient) + 1];
		strcpy(this->numeIngredient, numeIngredient);
		this->cantitateDisponibila = 0;
		this->existaIngredient = existaIngredient;
	}
	//constructor cu toti parametrii
	Ingredient(const char* numeIngredient, float cantitateDisponibila, bool existaIngredient)
	{
		this->numeIngredient = new char[strlen(numeIngredient) + 1];
		strcpy(this->numeIngredient, numeIngredient);
		this->cantitateDisponibila = cantitateDisponibila;
		this->existaIngredient = existaIngredient;
	}
	//getteri
	char* getNumeIngredient()
	{
		return this->numeIngredient;
	}
	float getCantitateDisponibila()
	{
		return this->cantitateDisponibila;
	}

	bool getExistaIngredient()
	{
		return this->existaIngredient;
	}


	//setteri
	void setNumeIngredient(const char* numeIngredientNou)
	{
		//1.dezalocare de memorie
		if (this->numeIngredient != NULL)
		{
			delete[] this->numeIngredient;
		}

		//2.alocare de memorie
		this->numeIngredient = new char[strlen(numeIngredientNou) + 1];

		//3.modificare atribut
		strcpy(this->numeIngredient, numeIngredientNou);
	}
	void setCantitateDisponibila(float cantitateDisponibilaNoua)
	{
		this->cantitateDisponibila = cantitateDisponibilaNoua;
	}

	

	void setExistaIngredient(bool existaIngredientNou)
	{
		this->existaIngredient = existaIngredientNou;
	}

	//destructor
	~Ingredient()
	{
		if (this->numeIngredient != nullptr)
		{
			delete[] this->numeIngredient;
		}

		//cout << "S-a apelat destructorul" << endl;
	}

	friend ostream& operator<<(ostream& out, const Ingredient& obj)
	{
		if (obj.numeIngredient != nullptr)
		{
		out << "Numele ingredientului este:" << obj.numeIngredient << endl;

		}
		out << "Exista ingredientul?";
		if (obj.existaIngredient == 1)
		{
			out << "DA\n";
			out << "Cantitate disponibila:" << obj.cantitateDisponibila << endl;

		}
		else {
			out << "NU\n";
		}

		return out;
	}
	friend istream& operator>>(istream& in, Ingredient& obj)
	{
		char buffer[100];

		cout << "Introdu numele ingredientului: ";
		in >> buffer;
		obj.setNumeIngredient(buffer);

		cout << "Exista ingredientul? (DA/NU): ";
		in >> buffer;
		if (strcmp(buffer, "DA") == 0)
		{
			obj.setExistaIngredient(true);

			cout << "Introdu cantitatea disponibila: ";
			in >> obj.cantitateDisponibila;
		}
		else
		{
			obj.setExistaIngredient(false);
			obj.cantitateDisponibila = 0; // Resetăm cantitatea în cazul în care nu există ingredientul
		}

		return in;
	}
	Ingredient& operator=(const Ingredient& other)
	{
		if (this != &other) // Verificăm auto-asignarea
		{
			// Dezalocăm resursele actuale
			delete[] this->numeIngredient;

			// Alocăm și copiem resursele din obiectul sursă
			this->numeIngredient = new char[strlen(other.numeIngredient) + 1];
			strcpy(this->numeIngredient, other.numeIngredient);
			this->cantitateDisponibila = other.cantitateDisponibila;
			this->existaIngredient = other.existaIngredient;
		}

		return *this; // Returnăm referința către obiectul curent
	}
	Ingredient operator+(const Ingredient& other) const
	{
		// Adunăm cantitățile și returnăm un nou obiect
		return Ingredient(this->numeIngredient, this->cantitateDisponibila + other.cantitateDisponibila, this->existaIngredient);
	}

	// Operator de decrementare (--), prefixat
	Ingredient& operator--()
	{
		// Scădem cantitatea disponibilă
		this->cantitateDisponibila--;
		return *this; // Returnăm referința către obiectul modificat
	}

	bool operator!() const
	{
		return !this->existaIngredient;
	}

	// Operator de indexare ([])
	char operator[](int index) const
	{
		if (index >= 0 && index < strlen(this->numeIngredient))
		{
			return this->numeIngredient[index];
		}
		else
		{
			// În cazul în care indexul este în afara limitelor, returnăm un caracter nul
			return '\0';
		}
	}
	bool operator>(const Ingredient& other) const
	{
		return this->cantitateDisponibila > other.cantitateDisponibila;
	}


};



class Preparat {
private:
	char* numePreparat;
	double pret;
	int nrIngredientePreparat;
	Ingredient** ingredientePreparat;


public:
	Preparat() : numePreparat(nullptr), pret(0.0), nrIngredientePreparat(0), ingredientePreparat(nullptr) {}

	//constructor cu doi parametri
	Preparat(const char* numePreparat, double pret, int nrIngredientePreparat)
	{
		this->numePreparat = new char[strlen(numePreparat) + 1];
		strcpy(this->numePreparat, numePreparat);
		this->pret = pret;
		this->nrIngredientePreparat = nrIngredientePreparat;

		this->ingredientePreparat = new Ingredient * [nrIngredientePreparat]; // Alocare memorie pentru vector

		for (int i = 0; i < nrIngredientePreparat; i++)
		{
			this->ingredientePreparat[i] = nullptr;
		}
	}

	Preparat(const char* numePreparat, double pret, int nrIngredientePreparat, Ingredient** ingredientePreparat)
	{
		this->numePreparat = new char[strlen(numePreparat) + 1];
		strcpy(this->numePreparat, numePreparat);
		this->pret = pret;
		this->nrIngredientePreparat = nrIngredientePreparat;
		this->ingredientePreparat = new Ingredient * [this->nrIngredientePreparat];

		for (int i = 0; i < this->nrIngredientePreparat; i++)
		{
			this->ingredientePreparat[i] = new Ingredient(*ingredientePreparat[i]);

		}
	}

	

	const char* getNumePreparat()
	{
		return this->numePreparat;
	}
	double getPret()
	{
		return this->pret;
	}
	int getNrIngredientePreparat()
	{
		return this->nrIngredientePreparat;
	}
	Ingredient** getIngredientePreparat()
	{
		return this->ingredientePreparat;

	}

	void setNumePreparat(const char* numePreparatNou)
	{
		//1.dezalocare de memorie
		if (this->numePreparat != NULL)
		{
			delete[] this->numePreparat;
		}

		//2.alocare de memorie
		this->numePreparat = new char[strlen(numePreparat) + 1];

		//3.modificare atribut
		strcpy(this->numePreparat, numePreparat);
	}
	

	void setPret(double pretNou)
	{
		this->pret = pretNou;

	}
	void setIngredientePreparat(int nrIngredientePreparatNou, Ingredient** ingredientePreparatNou)
	{
		for (int i = 0; i < this->nrIngredientePreparat; i++)
		{
			delete this->ingredientePreparat[i];
		}
		delete[] this->ingredientePreparat;

		this->nrIngredientePreparat = nrIngredientePreparatNou;
		this->ingredientePreparat = new Ingredient * [this->nrIngredientePreparat];

		for (int i = 0; i < this->nrIngredientePreparat; i++)
		{
			this->ingredientePreparat[i] = new Ingredient(*ingredientePreparatNou[i]);
		}
	}

	~Preparat()
	{
		if (this->numePreparat != NULL)
		{
			delete[] this->numePreparat;
		}
		for (int i = 0; i < this->nrIngredientePreparat; i++)
		{
			delete this->ingredientePreparat[i];
			this->ingredientePreparat[i] = nullptr;
		}
		delete[] this->ingredientePreparat;
		ingredientePreparat = nullptr;
	}
	friend ostream& operator<<(ostream& out, const Preparat& obj)
	{
		out << "\n-----------------------------------------------------------------\n";
		if (obj.numePreparat != nullptr)
		{
		out << "Nume preparat: " << obj.numePreparat << "   "  << obj.pret <<"lei" << endl;;

		}
		if (obj.ingredientePreparat != nullptr)
		{
out << "Ingrediente preparat: \n";
		for (int i = 0; i < obj.nrIngredientePreparat; i++)
		{
			out << "-"<<obj.ingredientePreparat[i]->getNumeIngredient() << "\n";
		}
		}
		
		return out;
	}


	friend istream& operator>>(istream& in, Preparat& preparat)
	{
		char buffer[100];

		std::cout << "Introdu numele preparatului: ";
		in >> buffer;
		preparat.setNumePreparat(buffer);

		std::cout << "Introdu pretul preparatului: ";
		in >> preparat.pret;

		std::cout << "Introdu numarul de ingrediente ale preparatului: ";
		in >> preparat.nrIngredientePreparat;

		// Dezalocăm resursele actuale
		for (int i = 0; i < preparat.nrIngredientePreparat; i++)
		{
			delete preparat.ingredientePreparat[i];
		}
		delete[] preparat.ingredientePreparat;

		preparat.ingredientePreparat = new Ingredient * [preparat.nrIngredientePreparat];

		for (int i = 0; i < preparat.nrIngredientePreparat; i++)
		{
			preparat.ingredientePreparat[i] = new Ingredient;
			std::cin >> *(preparat.ingredientePreparat[i]);
		}

		return in;
	}

	Preparat& operator=(const Preparat& other)
	{
		if (this != &other) // Verificăm auto-asignarea
		{
			// Dezalocăm resursele actuale
			delete[] this->numePreparat;
			for (int i = 0; i < this->nrIngredientePreparat; i++)
			{
				delete this->ingredientePreparat[i];
			}
			delete[] this->ingredientePreparat;

			// Alocăm și copiem resursele din obiectul sursă
			this->numePreparat = new char[strlen(other.numePreparat) + 1];
			strcpy(this->numePreparat, other.numePreparat);
			this->pret = other.pret;
			this->nrIngredientePreparat = other.nrIngredientePreparat;
			this->ingredientePreparat = new Ingredient * [this->nrIngredientePreparat];

			for (int i = 0; i < this->nrIngredientePreparat; i++)
			{
				this->ingredientePreparat[i] = new Ingredient(*other.ingredientePreparat[i]);
			}
		}

		return *this; // Returnăm referința către obiectul curent
	}

	// Operator de adunare (+)
	Preparat operator+(const Preparat& other) const
	{
		// Adunăm prețurile și returnăm un nou obiect
		return Preparat(this->numePreparat, this->pret + other.pret, this->nrIngredientePreparat + other.nrIngredientePreparat, nullptr);
	}

	// Operator de decrementare (--), prefixat
	Preparat& operator--()
	{
		// Scădem prețul
		this->pret--;
		return *this; // Returnăm referința către obiectul modificat
	}

	// Operator de negație (!)
	bool operator!() const
	{
		return this->pret == 0;
	}

	// Operator de indexare ([])
	Ingredient* operator[](int index) const
	{
		if (index >= 0 && index < this->nrIngredientePreparat)
		{
			return this->ingredientePreparat[index];
		}
		else
		{
			// În cazul în care indexul este în afara limitelor, returnăm nullptr
			return nullptr;
		}
	}

	// Operator de comparare (>), comparăm după preț
	bool operator>(const Preparat& other) const
	{
		return this->pret > other.pret;
	}

	// Operator de copiere (+=)
	Preparat& operator+=(const Ingredient& ingredient)
	{
		// Adăugăm un nou ingredient la preparat
		Ingredient** temp = new Ingredient * [this->nrIngredientePreparat + 1];

		for (int i = 0; i < this->nrIngredientePreparat; i++)
		{
			temp[i] = this->ingredientePreparat[i];
		}

		temp[this->nrIngredientePreparat] = new Ingredient(ingredient);
		delete[] this->ingredientePreparat;

		this->ingredientePreparat = temp;
		this->nrIngredientePreparat++;

		return *this;
	}

	

};


class Comanda {
private:
	int numarComanda;
	string numeClient;
	Preparat** preparateComanda;
	int numarPreparate;
	double totalComanda;

public:
	Comanda() : numarComanda(0), numeClient(""), totalComanda(0.0), preparateComanda(nullptr), numarPreparate(0) {}

	// Constructor
	Comanda(int numarComanda, const string& numeClient) : numarComanda(numarComanda), numeClient(numeClient), totalComanda(0.0), preparateComanda(nullptr), numarPreparate(0) {}

	// Getter pentru numărul comenzii
	int getNumarComanda() const {
		return numarComanda;
	}

	// Getter pentru numele clientului
	string getNumeClient() const {
		return numeClient;
	}

	// Getter pentru totalul comenzii
	double getTotalComanda() const {
		return totalComanda;
	}

	// Getter pentru array-ul de preparate
	Preparat** getPreparateComanda() const {
		return preparateComanda;
	}

	// Getter pentru numărul de preparate
	int getNumarPreparate() const {
		return numarPreparate;
	}

	// Setter pentru numărul comenzii
	void setNumarComanda(int numar) {
		numarComanda = numar;
	}

	// Setter pentru numele clientului
	void setNumeClient(const string& nume) {
		numeClient = nume;
	}

	// Setter pentru totalul comenzii
	void setTotalComanda(double total) {
		totalComanda = total;
	}

	// Setter pentru array-ul de preparate
	void setPreparateComanda(Preparat** preparate, int numarPreparate) {
		// Eliberează memoria existentă dacă există
		delete[] preparateComanda;

		// Alocă memorie pentru noul array de preparate
		preparateComanda = new Preparat * [numarPreparate];

		// Copiază obiectele Preparat din array-ul furnizat
		for (int i = 0; i < numarPreparate; ++i) {
			preparateComanda[i] = preparate[i];
		}

		// Actualizează numărul de preparate
		this->numarPreparate = numarPreparate;
	}

	// Metoda pentru a adăuga un preparat în comandă
	void adaugaPreparat(Preparat* preparat) {
		Preparat** temp = new Preparat * [numarPreparate + 1];
		for (int i = 0; i < numarPreparate; ++i) {
			temp[i] = preparateComanda[i];
		}
		temp[numarPreparate] = preparat;

		delete[] preparateComanda;
		preparateComanda = temp;
		++numarPreparate;

		totalComanda += preparat->getPret();
		

	}

	

	// Metoda pentru a afișa comanda
	void afiseazaComanda() const {
		cout << "Comanda #" << numarComanda << " pentru clientul " << numeClient << ":\n";
		for (int i = 0; i < numarPreparate; ++i) {
			cout << "- " << preparateComanda[i]->getNumePreparat() << "   " << preparateComanda[i]->getPret() << " lei\n";
		}
		cout << "Total comanda: " << totalComanda << " lei\n";
	}

	// Destructor pentru a elibera memoria alocata dinamic
	~Comanda() {
		delete[] preparateComanda;
	}
	friend istream& operator>>(istream& in, Comanda& comanda);
	friend ostream& operator<<(ostream& out, const Comanda& comanda);

	Comanda(const Comanda& other) {
		numarComanda = other.numarComanda;
		numeClient = other.numeClient;
		totalComanda = other.totalComanda;
		numarPreparate = other.numarPreparate;

		// Alocare memorie pentru noul array de preparate
		preparateComanda = new Preparat * [numarPreparate];

		// Copiază obiectele Preparat din array-ul furnizat
		for (int i = 0; i < numarPreparate; ++i) {
			preparateComanda[i] = new Preparat(*(other.preparateComanda[i]));
		}
	}

	// Operatorul de atribuire
	Comanda& operator=(const Comanda& other) {
		if (this != &other) {
			// Eliberează memoria existentă dacă există
			delete[] preparateComanda;

			numarComanda = other.numarComanda;
			numeClient = other.numeClient;
			totalComanda = other.totalComanda;
			numarPreparate = other.numarPreparate;

			// Alocare memorie pentru noul array de preparate
			preparateComanda = new Preparat * [numarPreparate];

			// Copiază obiectele Preparat din array-ul furnizat
			for (int i = 0; i < numarPreparate; ++i) {
				preparateComanda[i] = new Preparat(*(other.preparateComanda[i]));
			}
		}
		return *this;
	}

	// Operatorul de adunare (+)
	Comanda operator+(const Comanda& other) const {
		Comanda result(*this);

		for (int i = 0; i < other.numarPreparate; ++i) {
			result.adaugaPreparat(other.preparateComanda[i]);
		}

		return result;
	}

	// Operatorul de scădere (--)
	Comanda& operator--() {
		if (numarPreparate > 0) {
			--numarPreparate;
			totalComanda -= preparateComanda[numarPreparate]->getPret();
		}

		return *this;
	}


	// Operatorul de negație (!)
	bool operator!() const {
		return (numarPreparate == 0);
	}

	// Operatorul de comparare (>)
	bool operator>(const Comanda& other) const {
		return (totalComanda > other.totalComanda);
	}

	// Operatorul de indexare ([])
	Preparat* operator[](int index) const {
		if (index >= 0 && index < numarPreparate) {
			return preparateComanda[index];
		}

		return nullptr;
	}


	
};
ostream& operator<<(ostream& out, const Comanda& comanda) {
	out << "Comanda #" << comanda.numarComanda << " pentru clientul " << comanda.numeClient << ":\n";
	for (int i = 0; i < comanda.numarPreparate; ++i) {
		out << "- " << comanda.preparateComanda[i]->getNumePreparat() << "   " << comanda.preparateComanda[i]->getPret() << " lei\n";
	}
	out << "Total comanda: " << comanda.totalComanda << " lei\n";
	return out;
}
istream& operator>>(istream& in, Comanda& comanda) {
		cout << "Introduceti numarul comenzii: ";
		in >> comanda.numarComanda;

		cout << "Introduceti numele clientului: ";
		in.ignore();
		getline(in, comanda.numeClient);

		cout << "Introduceti numarul de preparate in comanda: ";
		in >> comanda.numarPreparate;

		// Eliberează memoria existentă dacă există
		delete[] comanda.preparateComanda;

		// Alocă memorie pentru noul array de preparate
		comanda.preparateComanda = new Preparat * [comanda.numarPreparate];

		// Citeste fiecare preparat
		for (int i = 0; i < comanda.numarPreparate; ++i) {
			comanda.preparateComanda[i] = new Preparat();
			in >> *comanda.preparateComanda[i];
			comanda.totalComanda += comanda.preparateComanda[i]->getPret();
		}

		return in;
	}
class Client {
private:
	string numeClient;
	Comanda** comenziClient;
	int numarComenzi;

public:
	// Constructor cu un parametru pentru numele clientului
	Client(const string& numeClient) : numeClient(numeClient), comenziClient(nullptr), numarComenzi(0) {}

	// Getter pentru numele clientului
	string getNumeClient() const {
		return numeClient;
	}

	// Setter pentru numele clientului
	void setNumeClient(const string& nume) {
		numeClient = nume;
	}

	// Adaugă o comandă pentru client
	void adaugaComanda(Comanda* comanda) {
		Comanda** temp = new Comanda * [numarComenzi + 1];
		for (int i = 0; i < numarComenzi; ++i) {
			temp[i] = comenziClient[i];
		}
		temp[numarComenzi] = comanda;

		delete[] comenziClient;
		comenziClient = temp;
		++numarComenzi;

		cout << "Comanda #" << comanda->getNumarComanda() << " a fost adaugata pentru clientul " << numeClient << ".\n";
	}

	// Afiseaza toate comenzile clientului
	void afiseazaComenzi() const {
		cout << "Comenzile clientului " << numeClient << ":\n";
		for (int i = 0; i < numarComenzi; ++i) {
			comenziClient[i]->afiseazaComanda();
		}
	}

	// Destructor pentru a elibera memoria alocata dinamic
	~Client() {
		for (int i = 0; i < numarComenzi; ++i) {
			delete comenziClient[i];
		}
		delete[] comenziClient;
	}
	friend istream& operator>>(istream& in, Client& client);
	friend ostream& operator<<(ostream& out, const Client& client);


	Client(const Client& other) {
		numeClient = other.numeClient;
		numarComenzi = other.numarComenzi;

		// Alocare memorie pentru noul array de comenzi
		comenziClient = new Comanda * [numarComenzi];

		// Copiază obiectele Comanda din array-ul furnizat
		for (int i = 0; i < numarComenzi; ++i) {
			comenziClient[i] = new Comanda(*(other.comenziClient[i]));
		}
	}

	// Operatorul de atribuire
	Client& operator=(const Client& other) {
		if (this != &other) {
			// Eliberează memoria existentă dacă există
			for (int i = 0; i < numarComenzi; ++i) {
				delete comenziClient[i];
			}
			delete[] comenziClient;

			numeClient = other.numeClient;
			numarComenzi = other.numarComenzi;

			// Alocare memorie pentru noul array de comenzi
			comenziClient = new Comanda * [numarComenzi];

			// Copiază obiectele Comanda din array-ul furnizat
			for (int i = 0; i < numarComenzi; ++i) {
				comenziClient[i] = new Comanda(*(other.comenziClient[i]));
			}
		}
		return *this;
	}

	// Operatorul de adunare (+)
	Client operator+(const Client& other) const {
		Client result(*this);

		for (int i = 0; i < other.numarComenzi; ++i) {
			result.adaugaComanda(other.comenziClient[i]);
		}

		return result;
	}

	// Operatorul de scădere (--)
	Client& operator--() {
		if (numarComenzi > 0) {
			delete comenziClient[numarComenzi - 1];
			--numarComenzi;
		}

		return *this;
	}

	// Operatorul de negație (!)
	bool operator!() const {
		return (numarComenzi == 0);
	}

	// Operatorul de comparare (==)
	bool operator==(const Client& other) const {
		return (numeClient == other.numeClient);
	}

	// Operatorul de indexare ([])
	Comanda* operator[](int index) const {
		if (index >= 0 && index < numarComenzi) {
			return comenziClient[index];
		}

		return nullptr;
	}


};
ostream& operator<<(ostream& out, const Client& client) {
	out << "Clientul " << client.numeClient << " are urmatoarele comenzi:\n";
	for (int i = 0; i < client.numarComenzi; ++i) {
		out << *client.comenziClient[i] << "\n";
	}
	return out;
}
istream& operator>>(istream& in, Client& client) {
		cout << "Introduceti numele clientului: ";
		in.ignore();
		getline(in, client.numeClient);

		cout << "Introduceti numarul de comenzi pentru client: ";
		in >> client.numarComenzi;

		// Eliberează memoria existentă dacă există
		for (int i = 0; i < client.numarComenzi; ++i) {
			delete client.comenziClient[i];
		}
		delete[] client.comenziClient;

		// Alocă memorie pentru noul array de comenzi
		client.comenziClient = new Comanda * [client.numarComenzi];

		// Citeste fiecare comanda
		for (int i = 0; i < client.numarComenzi; ++i) {
			client.comenziClient[i] = new Comanda();
			in >> *client.comenziClient[i];
		}

		return in;
	}

class Restaurant {
private:
	static char* numeRestaurantStatic;
	char* numeRestaurant;
	const int CUI;
	int numarPreparate;
	Preparat** preparateRestaurant;

public:
	// Constructor
	Restaurant(const char* numeRestaurant, int CUI) : CUI(CUI), numarPreparate(0), preparateRestaurant(nullptr) {
		this->numeRestaurant = new char[strlen(numeRestaurant) + 1];
		strcpy(this->numeRestaurant, numeRestaurant);
	}

	// Destructor
	~Restaurant() {
		delete[] numeRestaurantStatic;
		delete[] numeRestaurant;
		for (int i = 0; i < numarPreparate; ++i) {
			delete preparateRestaurant[i];
		}
		delete[] preparateRestaurant;
	}

	// Getter for static restaurant name
	static const char* getNumeRestaurantStatic() {
		return numeRestaurantStatic;
	}

	// Setter for static restaurant name
	static void setNumeRestaurantStatic(const char* nume) {
		if (numeRestaurantStatic) {
			delete[] numeRestaurantStatic;
		}
		numeRestaurantStatic = new char[strlen(nume) + 1];
		strcpy(numeRestaurantStatic, nume);
	}

	

	// Setter for constant restaurant name
	void setNumeRestaurant(const char* nume) {
		delete[] numeRestaurant;
		numeRestaurant = new char[strlen(nume) + 1];
		strcpy(numeRestaurant, nume);
	}

	// Getter for CUI
	int getCUI() const {
		return CUI;
	}

	// Getter for number of dishes
	int getNumarPreparate() const {
		return numarPreparate;
	}

	// Getter for dishes
	Preparat** getPreparateRestaurant() const {
		return preparateRestaurant;
	}

	// Setter for dishes
	void setPreparateRestaurant(Preparat** preparate, int numarPreparate) {
		// Assuming you want to delete existing dishes
		for (int i = 0; i < this->numarPreparate; ++i) {
			delete preparateRestaurant[i];
		}
		delete[] preparateRestaurant;

		// Allocate memory for new dishes
		this->numarPreparate = numarPreparate;
		this->preparateRestaurant = new Preparat * [numarPreparate];

		// Copy the dishes
		for (int i = 0; i < numarPreparate; ++i) {
			this->preparateRestaurant[i] = preparate[i];
		}
	}

	// Overloaded << operator for Restaurant
	friend ostream& operator<<(ostream& out, const Restaurant& restaurant) {
		out << "Restaurant " << restaurant.numeRestaurant<<endl;
		out << "Numar preparate " << restaurant.numarPreparate << "\n";
		out << "MENIU:\n";
		for (int i = 0; i < restaurant.numarPreparate; ++i) {
			out << *restaurant.preparateRestaurant[i] << "\n";
		}
		return out;
	}
	Restaurant(const Restaurant& other) : CUI(other.CUI), numarPreparate(other.numarPreparate), preparateRestaurant(nullptr) {
		// Alocare memorie pentru noul array de preparate
		preparateRestaurant = new Preparat * [numarPreparate];

		// Copiază obiectele Preparat din array-ul furnizat
		for (int i = 0; i < numarPreparate; ++i) {
			preparateRestaurant[i] = new Preparat(*(other.preparateRestaurant[i]));
		}

		// Copiază numele restaurantului
		numeRestaurant = new char[strlen(other.numeRestaurant) + 1];
		strcpy(numeRestaurant, other.numeRestaurant);
	}

	// Operatorul de atribuire
	Restaurant& operator=(const Restaurant& other) {
		if (this != &other) {
			// Eliberează memoria existentă dacă există
			delete[] numeRestaurant;
			for (int i = 0; i < numarPreparate; ++i) {
				delete preparateRestaurant[i];
			}
			delete[] preparateRestaurant;

			numarPreparate = other.numarPreparate;

			// Alocare memorie pentru noul array de preparate
			preparateRestaurant = new Preparat * [numarPreparate];

			// Copiază obiectele Preparat din array-ul furnizat
			for (int i = 0; i < numarPreparate; ++i) {
				preparateRestaurant[i] = new Preparat(*(other.preparateRestaurant[i]));
			}

			// Copiază numele restaurantului
			delete[] numeRestaurant;
			numeRestaurant = new char[strlen(other.numeRestaurant) + 1];
			strcpy(numeRestaurant, other.numeRestaurant);
		}
		return *this;
	}
	void adaugaPreparat(Preparat* preparat) {
		if (preparateRestaurant == nullptr) {
			preparateRestaurant = new Preparat * [1];
		}
		else {
			Preparat** temp = new Preparat * [numarPreparate + 1];
			for (int i = 0; i < numarPreparate; ++i) {
				temp[i] = preparateRestaurant[i];
			}
			delete[] preparateRestaurant;
			preparateRestaurant = temp;
		}

		preparateRestaurant[numarPreparate++] = preparat;
	}

	// Operatorul de adunare (+)
	Restaurant operator+(const Restaurant& other) const {
		Restaurant result(*this);

		for (int i = 0; i < other.numarPreparate; ++i) {
			result.adaugaPreparat(other.preparateRestaurant[i]);
		}

		return result;
	}

	// Operatorul de scădere (--)
	Restaurant& operator--() {
		if (numarPreparate > 0) {
			delete preparateRestaurant[numarPreparate - 1];
			--numarPreparate;
		}

		return *this;
	}

	// Operatorul de negație (!)
	bool operator!() const {
		return (numarPreparate == 0);
	}

	// Operatorul de comparare (==)
	bool operator==(const Restaurant& other) const {
		return (CUI == other.CUI);
	}

	// Operatorul de indexare ([])
	Preparat* operator[](int index) const {
		if (index >= 0 && index < numarPreparate) {
			return preparateRestaurant[index];
		}

		return nullptr;
	}
	void afiseazaPreparate() const {
		cout << "Meniu restaurant " << numeRestaurant;
		for (int i = 0; i < numarPreparate; ++i) {
			cout << *preparateRestaurant[i] << "\n";
		}
	}


};


char* Restaurant::numeRestaurantStatic = nullptr;


int main()
{
	




	Ingredient i1("Oua", 50.0, true);
	Ingredient i2("Apa", false);
	// 
	// 
	//-----------VERIFICARE OPERATORI-------------
	// //operatorul +
	        //Ingredient i3 = i1 + i2;
	         //cout << "i1 + i2: " << i3;
			 //operatorul --
			 //--i3;

			 //cout << "Dupa --i3: " << i3;
			 //operatorul >
			 //cout << "i1 > i2: " << (i1 > i2) <<endl;
			 //operatorul de indexare
			// cout << "i1[2]: " << i1[0] << endl;
			 //operatorul de negatie
			// cout << "!i1: " << !i1 <<endl;
			/* cin >> i1;
			 cout << i1;*/
	//---------------------------------------------



	Ingredient i3("Rosii", 20.0, true);
	Ingredient i4("Ceapa", 25.0, true);
	Ingredient i5("Branza cheddar", 5.0, true);

	Ingredient* ingredienteP1[] = { &i1, &i3, &i4,&i5 }; 

	Preparat P1("Omleta", 20.0,4, ingredienteP1);
	//cout << P1;

	Ingredient i6("Muschi de vita", 15.0, true);
	Ingredient i7("Ciuperci", 15.0, true);
	Ingredient i8("Trufe", 15.0, true);
	Ingredient i9("Tagliatelle", 15.0, true);

	Ingredient* ingredienteP2[] = { &i6, &i7, &i8, &i9 };
	Preparat P2("Tagliatelle cu muschi de vita", 55.0, 4, ingredienteP2);
	//cout << P2;


	Ingredient i10("Piept de pui", 15.0, true);
	Ingredient i11("Salata", 15.0, true);
	Ingredient i12("Crutoane", 15.0, true);
	Ingredient i13("Pancetta", 15.0, true);
	Ingredient i14("Parmezan", 16.0, true);

	Ingredient* ingredienteP3[] = {&i3, &i10, &i11, &i12, &i13, &i14 };
	Preparat P3("Salata Caesar", 35.0, 6, ingredienteP3);
	//cout << P3;

	Ingredient i15("Orez", 17.0, true);
	Ingredient i16("Vin", 15.0, true);
	Ingredient i17("Stoc de legume", 15.0, true);

	Ingredient* ingredienteP4[] = { &i4, &i7, &i8, &i15,&i16,&i17 };
	Preparat P4("Risotto cu ciuperci si trufe", 53.0, 6, ingredienteP4);
	//cout << P4;



	Ingredient i18("Tortilla", 15.0, true);
	Ingredient i19("Porumb", 15.0, true);
	Ingredient i20("Ardei capia", 15.0, true);
	Ingredient i21("Cartofi", 15.0, true);

	Ingredient* ingredienteP5[] = { &i18, &i19, &i4, &i20, &i21 };
	Preparat P5("Salata Caesar", 42.0, 5, ingredienteP5);
	//cout << P5;
	Client client1("Ana");

	// Creating orders
	Comanda comanda1(1, "Ana");
	comanda1.adaugaPreparat(&P1);
	comanda1.adaugaPreparat(&P3);

	Client client2("Mihai");

	Comanda comanda2(2, "Mihai");
	comanda2.adaugaPreparat(&P2);
	comanda2.adaugaPreparat(&P4);
	comanda2.adaugaPreparat(&P5);

	// Adding orders to clients
	client1.adaugaComanda(&comanda1);
	client2.adaugaComanda(&comanda2);

	// Displaying clients and their orders
	cout << client1 << endl;
	cout << client2 << endl;
	
	Restaurant restaurant("CEVA BUN", 123456789);

	// Setarea numelui pentru instanța specifică de restaurant
//	restaurant.setNumeRestaurant("La Gustare");

	// Setarea numelui pentru variabila statică de restaurant
	Restaurant::setNumeRestaurantStatic("NumeRestaurantImplicit");


	// Afișarea numelui restaurantului static
	//cout << "Numele restaurantului static: " << Restaurant::getNumeRestaurantStatic() << endl;
	
	restaurant.adaugaPreparat(&P1);
	restaurant.adaugaPreparat(&P2);
	restaurant.adaugaPreparat(&P3);
	restaurant.adaugaPreparat(&P4);
	restaurant.adaugaPreparat(&P5);

	// Afișarea informațiilor despre restaurant
	cout << restaurant<< endl;


	return 0;
}

