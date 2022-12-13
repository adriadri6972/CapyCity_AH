#include "Material.h"
using namespace std;

string Material::getName() {
	return name;
}
double Material::getPrice() {
	return price;
}
Wood::Wood() {
	name = "Holz";
	price = 10;
}
Iron::Iron() {
	name = "Eisen";
	price = 15;
}
Plastic::Plastic() {
	name = "Kunststoff";
	price = 10;
}
