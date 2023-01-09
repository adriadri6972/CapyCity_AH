#pragma once
#include <map>
#include <vector>
#include "Blueprint.h"



class CapyCity{
public:
	//variablen

	//map zur verwaltung mehrerer Blueprints
	//ich habe mich bei der Verwaltung von anfang an für eine map entschieden weil hier nur jeweils ein Objekt mit einem dazugehörigen index
	//benötigt wird und eine map genau dies mit einem Key und Value Wert bietet
	std::map<int,Blueprint> blueprintList;

	//zeigt auf den aktuell ausgewählten Blueprint
	Blueprint* currentBlueprint;

	//Methoden
	void addBlueprint();
	void blueprintMenue();
	void switchBlueprint();
	string formate(double cost);
	void printAll();
	void compare();
	bool wannaDelete(int);
	static int getcurrentBlueprintNumber();
};
