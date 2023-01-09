#include "Material.h"
using namespace std;

//get-Methode f�r MaterialTyp
string Material::getName() {
	return name;
}

//get-Methode f�r St�ckpreis
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
