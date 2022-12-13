#pragma once
#include <string>

class Material
{
public:
	std::string name;
	double price;
	std::string getName();
	double getPrice();
};

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
