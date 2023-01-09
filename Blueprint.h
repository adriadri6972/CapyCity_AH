#pragma once
#include <iostream>
#include <list>
#include <regex>
#include <iomanip>
#include <sstream>
#include "Building.h"

using namespace std;

class Blueprint{
	//variablen

	//höhe und breite des Feldes
	int rows = 0, columns = 0; 

	//maximale Bauplangröße (auf 50 festgelegt um das Feld auf der Konsole im Vollbildmodus grafisch gut ausgeben zu können)
	const static int sizeTolerance = 50;

	//Kosten und MegaWatt Variablen
	double currentTotalCost = 0, currentBuildingCost = 0, currentAquaCost = 0, currentWindCost = 0, currentSolaCost = 0;
	double currentTotalMW = 0, currentBuildingMW = 0, currentAquaMW = 0, currentWindMW = 0, currentSolaMW = 0;
	
	// 32 ist ASCII-Code und erzeugt ein leeres Feld
	const char BLANK = 32;

	//flags für die Kommunikation zwischen Blueprint und CapyCitySim Klassen
	bool inBlue = false;
	bool letsTest = false;

	//es ist bewusst ein 2D String Array geworden um die Ausgabe zu vereinfachen und die Gebäudelable (A,W,S) 
	//farbig darstellen zu können
	string field[sizeTolerance][sizeTolerance];

	
public:
	//Kennzahl varibale
	double kennzahl = 0;
	Blueprint();


//Methoden
void print(std::string out);
void println(std::string out);
void startUp();
void menue();
void generateField(int x,int y);
void printField();
void printCost();
void printbuildingMaterialCost();
void deleteField(int x, int y);
void setField(int x, int y);
void buildBuilding(int startX, int startY, int endX, int endY, Building* value);
int setDimensionY();
int setDimensionX();
int setPositionX();
int setPositionY();
int setDeletePositionX();
int setDeletePositionY();
int setEndX(int startX);
int setEndY(int startY);
int getSizeTolerance();
int getWidth();
int getHeight();
double getKennzahl();
bool wannaBuild(double cost,double megaWatt);
bool getInBlue();
void setInBlue(bool);
bool getwannaTest();
void setletsTest(bool);
Building* setBuilding();
vector<string> getField();
string formate(double cost);
};