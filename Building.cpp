#include "Building.h"
#include <iostream>
#include <string>
using namespace std;

//get-Methode für den Grundpreis (Preis eines Quadretmeters auf dem gebaut werden soll)
double Building::getGroundPrice() {
	return price;
}

//get-Methode für die erzeugten MW (die auf einem Quardratmeter erzeugt werden)
double Building::getMegaWatt() {
	return megaWatt;
}

//get-Methode um den passenden Buchstaben für jeder Gebäude zu erhalten
std::string Building::getLabel() {
	return label;
}

//get-Methode für den GebäudeTypen
std::string Building::getName() {
	return name;
}

//berechne die kosten aller Materialien (für einen Quadratmeter)
double Building::sumMaterialCosts() {
	double sum = 0;
	for (std::pair<Material*, int> i : materialList) {
		sum += (i.first->price * i.second);
	}
	return sum;
}

//berechne die Gesamtkosten (für einen Quadratmeter)
double Building::totalCosts() {
	return getGroundPrice() + sumMaterialCosts();
}

//befülle die materialliste des Gebäudes mit den übergebenen Werten für Holz,Eisen und Kunststoff
//wird im Konstruktor von Gebäuden verwendet
void Building::generateMaterialList(int woodCount, int ironCount, int plasticCount) {

	materialList.insert(std::pair<Material*, int>(new Wood(), woodCount));
	materialList.insert(std::pair<Material*, int>(new Iron(), ironCount));
	materialList.insert(std::pair<Material*, int>(new Plastic(), plasticCount));
}

//auflistung von Materialtypen und der zugehörigen Anzahl in einem String
//da MaterialTyp und Anzahl in einer ungeordneten Map sind, wird hier auch sortiert um immer die gleiche
//Ausgaben Reihenfolge zu behalten
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
	}
	return strList;
}


//Konstruktoren
AquaEnergie::AquaEnergie() {
	name = "Wasserkraftwerk";
	label = "A";
	price = 300;
	megaWatt = 50;
	generateMaterialList(10, 20, 15);
}
WindEnergie::WindEnergie() {
	name = "Windkraftwerk";
	label = "W";
	price = 100;
	megaWatt = 30;
	generateMaterialList(20, 10, 15);
}
SolarEnergie::SolarEnergie() {
	name = "Solarkraftwerk";
	label = "S";
	price = 200;
	megaWatt = 10;
	generateMaterialList(10, 10, 10);
}