#include "Building.h"
#include <iostream>
#include <string>
using namespace std;

double Building::getGroundPrice() {
	return price;
}
std::string Building::getLabel() {
	return label;
}
std::string Building::getName() {
	return name;
}
double Building::sumMaterialCosts() {
	double sum = 0;
	for (std::pair<Material*, int> i : materialList) {
		sum += (i.first->price * i.second);
	}
	return sum;
}
double Building::totalCosts() {
	return getGroundPrice() + sumMaterialCosts();
}

void Building::generateMaterialList(int woodCount, int ironCount, int plasticCount) {

	materialList.insert(std::pair<Material*, int>(new Wood(), woodCount));
	materialList.insert(std::pair<Material*, int>(new Iron(), ironCount));
	materialList.insert(std::pair<Material*, int>(new Plastic(), plasticCount));
}
string Building::listMaterials() {
	string strWood = "";
	string strIron = "";
	string strPlastic = "";
	string strList = "";
	for (std::pair<Material*, int> i : materialList) {
		if (i.first->name == "Holz") {
			strWood= to_string(i.second) + "x " + i.first->name + "   ";
		}
		if (i.first->name == "Eisen") {
			strIron = to_string(i.second) + "x " + i.first->name + "   ";
		}
		if (i.first->name == "Kunststoff") {
			strPlastic = to_string(i.second) + "x " + i.first->name + "   ";
		}
		strList = strWood + strIron + strPlastic;

		//std::cout << to_string(i.second) + "x " + i.first->name +"   ";
	}
	return strList;
}

AquaEnergie::AquaEnergie() {
	name = "Wasserkraftwerk";
	label = "A";
	price = 200;
	generateMaterialList(10, 20, 15);
}
WindEnergie::WindEnergie() {
	name = "Windkraftwerk";
	label = "W";
	price = 100;
	generateMaterialList(20, 10, 15);
}
SolarEnergie::SolarEnergie() {
	name = "Solarkraftwerk";
	label = "S";
	price = 150;
	generateMaterialList(10, 10, 10);
}