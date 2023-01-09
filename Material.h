#pragma once
#include <string>

class Material
{
public:

	//Variablen
	std::string name;
	double price;

	//Methoden
	std::string getName();
	double getPrice();
};

//Konstruktoren
class Wood : public Material {
public:
	Wood();
};
class Iron : public Material {
public:
	Iron();
};
class Plastic : public Material {
public:
	Plastic();
};
