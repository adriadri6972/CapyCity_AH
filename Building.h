
#include <string>
#include "Material.h"
#include <map>

class Building
{
public:
	std::string name;
	std::string label;
	std::map<Material*,int> materialList;
	double price;

	double getGroundPrice();
	std::string getLabel();
	std::string getName();
	double sumMaterialCosts();
	double totalCosts();
	void generateMaterialList(int,int,int);
	std::string listMaterials();
};
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

