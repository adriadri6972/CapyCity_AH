//#pragma once
//
//#include <iostream>
//#include <list>
//#include <regex>
//#include <iomanip>
//#include <sstream>
//#include "Building.h"
//
//using namespace std;
//
//class CapyCitySim {
//	int rows, columns, sizeToleranz;
//	double currentTotalCost, currentBuildingCost, currentAquaCost, currentWindCost, currentSolaCost;
//	std::string** field;
//
//	int main();
//	void print(std::string out);
//	void println(std::string out);
//	void menue();
//	void generateField(int x, int y);
//	void printField();
//	void setField(int x, int y, Building* value);
//	int setDimensionX();
//	int setDimensionY();
//	int setPositionX();
//	int setPositionY();
//	int setDeletePositionX();
//	int setDeletePositionY();
//	void deletePlot(int x, int y);
//	Building* setValue();
//	void buildBuilding(int startX, int startY, int endX, int endY, Building* value);
//	int setEndX(int startX);
//	int setEndY(int startY);
//	bool wannaBuild(double cost);
//	std::string formate(double cost);
//	void printCost();
//	void printbuildingMaterialCost();
//};