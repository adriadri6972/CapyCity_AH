
#include <string>
#include "Material.h"
#include <map>

class Building
{
public:

	//Variablen
	std::string name;
	std::string label;
	double price;
	double megaWatt;

	//ich habe die Materialien des Gebäude in einer map gespeichert weil ich so nur ein Objekt des jeweiligen Materials
	//als Key brauche und die Stückzahl im Value speichern kann
	//(machte für mich mehr Sinn als ein ewig langes Array/Vektor bei dem die Stückzahl durch die länge bestimmt wird)
	std::map<Material*, int> materialList;

	//Methoden
	double getGroundPrice();
	double getMegaWatt();
	std::string getLabel();
	std::string getName();
	double sumMaterialCosts();
	double totalCosts();
	void generateMaterialList(int,int,int);
	std::string listMaterials();
};

//Konstruktoren
class AquaEnergie : public Building {
public:
	AquaEnergie();
};
class WindEnergie : public Building {
public:
	WindEnergie();
};
class SolarEnergie : public Building {
public:
	SolarEnergie();
};

