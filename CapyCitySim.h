#pragma once

#include <iostream>
#include <list>
#include <regex>
#include <iomanip>
#include <sstream>
#include "Building.h"

using namespace std;

class CapyCitySim{
	int rows = 0, columns = 0, sizeTolerance = 40;
	double currentTotalCost = 0, currentBuildingCost = 0, currentAquaCost = 0, currentWindCost = 0, currentSolaCost = 0;
	const char BLANK = 32;		// 32 ist ASCII-Code und erzeugt ein leeres Feld
	string field[40][40];
	//static list<CapyCitySim> allLists;
public:
	CapyCitySim();

void print(std::string out);
void println(std::string out);
void startUp();
void menue();
void generateField(int x,int y);
void printField();
void printCost();
void printbuildingMaterialCost();
void deleteField(int x, int y);
void setField(int x, int y, Building* value);
void buildBuilding(int startX, int startY, int endX, int endY, Building* value);
int setDimensionX();
int setDimensionY();
int setPositionX();
int setPositionY();
int setDeletePositionX();
int setDeletePositionY();
int setEndX(int startX);
int setEndY(int startY);
int getSizeTolerance();
bool wannaBuild(double cost);
Building* setValue();
std::string formate(double cost);
};