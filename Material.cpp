#include "Material.h"
using namespace std;

//get-Methode für MaterialTyp
string Material::getName() {
	return name;
}

//get-Methode für Stückpreis
double Material::getPrice() {
	return price;
}

//Konstruktoren
Wood::Wood() {
	name = "Holz";
	price = 2;
}
Iron::Iron() {
	name = "Eisen";
	price = 3;
}
Plastic::Plastic() {
	name = "Kunststoff";
	price = 1;
}
