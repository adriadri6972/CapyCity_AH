// CapyCity_AH.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <list>
#include <regex>
#include <iomanip>
#include <sstream>
#include "Building.h"
#include "CapyCitySim.h"

using namespace std;

int rows = 0, columns = 0, sizeToleranz = 40;
double currentTotalCost = 0, currentBuildingCost = 0, currentAquaCost = 0, currentWindCost = 0, currentSolaCost = 0;
string** field;

int main();

void print(string out);
void println(string out);
void menue();
void generateField(int x, int y);
void printField();
void setField(int x, int y, Building* value);
int setDimensionX();
int setDimensionY();
int setPositionX();
int setPositionY();
int setDeletePositionX();
int setDeletePositionY();
void deletePlot(int x, int y);
Building* setValue();
void buildBuilding(int startX, int startY, int endX, int endY, Building* value);
int setEndX(int startX);
int setEndY(int startY);
bool wannaBuild(double cost);
string formate(double cost);
void printCost();
void printbuildingMaterialCost();

int main()
{
	println("Willkommen in CapyCity buildertool!");
	println("Mit diesem Tool kann eine Bauflaeche von bis zu " + to_string(sizeToleranz) + "x" + to_string(sizeToleranz) + " Feldern bebaut werden.");
	println("\nAktuelle unterstuetze Bauvorhaben sind:\nWasserkarftwerk (als A markiert)\nWindkraftwerk (als W markiert)\nSolarpanele (als S markiert)");
	println("\nInfo: Positionskoordinaten beziehen sich auf die linke obere Ecke des jeweiligen Gebauedes");
	println("\nBitte verwenden sie diese Anwendung im Vollbildmodus");
	println("\nInitialisiere Grundstueck...\n");
	generateField(setDimensionX(), setDimensionY());
	while (true) {
		menue();
	}
	return 0;
}

void print(string out) {
	cout << out;
}
void println(string out) {
	cout << out << endl;
}

void menue() {
	println("");
	println("|---------- Hauptmenue ------------|");
	println("|                                  |");
	println("|  aktuellen Bauplan ausgeben (1)  |");
	println("|     Gebaeude platzieren (2)      |");
	println("|     Gebaeude entfernen (3)       |");
	println("|   Gebaeude/Material kosten (4)   |");
	println("|       Programm Beenden (5)       |");
	println("|                                  |");
	println("|__________________________________|");
	print("\nEingabe: ");

	string input = "";
	regex test("^([1-5]{0,1})$");
	cin >> input;
	if (regex_match(input, test)) {
		switch (stoi(input)) {
		case 1: printField();break;
		case 2: setField(setPositionX(), setPositionY(), setValue());break;
		case 3: deletePlot(setDeletePositionX(), setDeletePositionY());break;
		case 4: printbuildingMaterialCost();break;
		case 5:
			for (int i = 0; i < rows; i++) {
				delete[] field[i];
			}
			delete[] field;
			exit(0);break;
		default:
			println("Menue Fehler!\tEingabe ist nicht erlaubt!");
			menue();
		}
	}
	else {
		println("\nEingabe ist nicht erlaubt!\n");
		menue();
	}
}

void deletePlot(int x, int y) {
	field[x][y] = 32;
}

void generateField(int x, int y) {
	field = new string * [x];
	for (int i = 0;i <= x;i++) {
		field[i] = new string[y];
	}
	for (int height = 0;height < columns;height++) {
		for (int width = 0;width < rows;width++) {
			field[width][height] = 32;		// 32 ist ASCII-Code und erzeugt ein leeres Feld
		}
	}
}

void printField() {
	if (rows <= 0 && columns <= 0) {
		print("kein Feld gefunden");
		return;
	}
	for (int x = 0;x < (rows * 2) + 1;x++) {
		for (int y = 0;y < columns;y++) {
			if (x % 2 == 1) {
				if (field[(x / 2)][y] == "A") {
					printf("| \033[36mA\033[0m |");
				}
				else if (field[(x / 2)][y] == "W") {
					printf("| \033[91mW\033[0m |");
				}
				else if (field[(x / 2)][y] == "S") {
					printf("| \033[93mA\033[0m |");
				}
				else {
					print("| " + field[(x / 2)][y] + " |");
				}
			}
			else {
				print("|---|");
			}
		}
		println("");
	}

	printCost();
}

void printCost() {
	println("\n");
	println("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$");
	println("                                                                              ");
	println("                          aktuelle Kostenuebersicht:                          ");
	println("                                                                              ");
	println("                      Wasserkraftwerke: " + formate(currentAquaCost) + " Euro ");
	println("                      Windkraftwerke:   " + formate(currentWindCost) + " Euro ");
	println("                      Solarkraftwerke:  " + formate(currentSolaCost) + " Euro ");
	println("______________________________________________________________________________");
	println("                          Gesamtkosten: " + formate(currentTotalCost) + " Euro");
	println("                                                                              ");
	println("                                                                              ");
	println("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$");
	println("\n");
}

void printbuildingMaterialCost() {
	Building* aqua = new AquaEnergie();
	Building* wind = new WindEnergie();
	Building* sola = new SolarEnergie();
	Material* wood = new Wood();
	Material* iron = new Iron();
	Material* plas = new Plastic();
	println("\n");
	println("|----------------------------------------------------------------------|");
	println("|                               CapaCity                               |");
	println("|======================================================================|");
	println("|                                                                      |");
	println("|                        Basispreis Gebauede:                          |");
	println("|                                                                      |");
	println("|                  " + aqua->getName() + " (" + aqua->getLabel() + "): " + formate(aqua->getGroundPrice()) + " Euro                    |");
	println("|                  " + wind->getName() + "   (" + wind->getLabel() + "): " + formate(wind->getGroundPrice()) + " Euro                    |");
	println("|                  " + sola->getName() + "  (" + sola->getLabel() + "): " + formate(sola->getGroundPrice()) + " Euro                    |");
	println("|                                                                      |");
	println("|                                                                      |");
	println("|                        Basispreis Material:                          |");
	println("|                                                                      |");
	println("|                       " + wood->getName() + ":       " + formate(wood->getPrice()) + " Euro                         |");
	println("|                       " + iron->getName() + ":      " + formate(iron->getPrice()) + " Euro                         |");
	println("|                       " + plas->getName() + ": " + formate(plas->getPrice()) + " Euro                         |");
	println("|                                                                      |");
	println("|                                                                      |");
	println("|                       Benoetigte Rescourcen:                         |");
	println("|                                                                      |");
	println("|     " + aqua->getName() + " (" + aqua->getLabel() + "): " + aqua->listMaterials() + "    |");
	println("|     " + wind->getName() + "   (" + wind->getLabel() + "): " + wind->listMaterials() + "    |");
	println("|     " + sola->getName() + "  (" + sola->getLabel() + "): " + sola->listMaterials() + "    |");
	println("|                                                                      |");
	println("|                                                                      |");
	println("|______________________________________________________________________|");
	println("|______________________________________________________________________|");
	println("\n");

	delete aqua;
	delete wind;
	delete sola;
	delete wood;
	delete iron;
	delete plas;
}

void setField(int x, int y, Building* value) {
	if (field[x][y] == "A" || field[x][y] == "W" || field[x][y] == "S") {
		print("\nBauplatz ist schon belegt! Bau woanders!\n");
		return menue();
	}
	buildBuilding(x, y, setEndX(x), setEndY(y), value);
}

void buildBuilding(int startX, int startY, int endX, int endY, Building* value) {
	int* xKoordinates = new int[sizeToleranz * sizeToleranz];
	int* yKoordinates = new int[sizeToleranz * sizeToleranz];
	int zaehler = 0;

	for (int height = startY;height <= endY;height++) {
		for (int width = startX;width <= endX;width++) {
			//if ((height >= startY && height <= endY) && (width >= startX && width <= endX)) {
			yKoordinates[zaehler] = width;
			xKoordinates[zaehler] = height;
			zaehler++;
			if (field[height][width] == "A" || field[height][width] == "W" || field[height][width] == "S") {
				println("\nEs steht nicht der komplette Bauplatz zur verfuegung! Bauvorhaben abgebrochen!\n");
				delete[] xKoordinates;
				delete[] yKoordinates;
				return;
				//	}
					//field[height][width] = value;
			}
		}
	}

	currentBuildingCost = value->getGroundPrice() + (value->sumMaterialCosts() * zaehler);

	if (wannaBuild(currentBuildingCost)) {
		for (int i = 0;i < zaehler;i++) {
			field[xKoordinates[i]][yKoordinates[i]] = value->getLabel();
		}
		if (value->getLabel() == "A") {
			currentAquaCost += currentBuildingCost;
		}
		else if (value->getLabel() == "W") {
			currentWindCost += currentBuildingCost;
		}
		else if (value->getLabel() == "S") {
			currentSolaCost += currentBuildingCost;
		}
	}
	else {
		println("\nBau wurde abgebrochen.\n");
	}
	delete[] xKoordinates;
	delete[] yKoordinates;
}

int setDeletePositionX() {
	print("zu loeschende Tiefenkoordinate: ");
	int xD;
	if (cin >> xD) {
		if (xD < 0 || xD > columns) {
			println("Tiefenkoordinate muss zwischen 0 und " + to_string(columns) + " liegen!");
			setDeletePositionX;
		}
		return xD;
	}
	else if (!cin.bad() && !cin.eof()) {
		cin.clear();
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		println("Eingabe ist nicht erlaubt!");
		return setDeletePositionX();
	}
	return 0;
}

int setDeletePositionY() {
	print("zu loeschende Breitenkoordinate: ");
	int yD;
	if (cin >> yD) {
		if (yD < 0 || yD > rows) {
			println("Breitenkoordinate muss zwischen 0 und " + to_string(rows) + " liegen!");
			setDeletePositionX;
		}
		return yD;
	}
	else if (!cin.bad() && !cin.eof()) {
		cin.clear();
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		println("Eingabe ist nicht erlaubt!");
		return setDeletePositionY();
	}
	return 0;
}

int setEndX(int startX) {
	print("\nWie breit soll das Gebauede werden?\nBreite: ");
	string x = "";
	regex test("^([1-9][0-9]{0,1})$");
	cin >> x;
	if (regex_match(x, test) && startX + stoi(x) - 1 < columns) {
		return ((startX + stoi(x)) - 1);
	}
	else {
		cin.clear();
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		println("Breite muss zwischen 0 und " + to_string((columns - startX) + 1) + " liegen!");
		return setEndX(startX);
	}
}

int setEndY(int startY) {
	print("\nWie tief soll das Gebauede werden?\nTiefe: ");
	string y = "";
	regex test("^([1-9][0-9]{0,1})$");
	cin >> y;
	if (regex_match(y, test) && startY + stoi(y) - 1 < rows) {
		return ((startY + stoi(y)) - 1);
	}
	else {
		cin.clear();
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		println("Tiefe muss zwischen 0 und " + to_string(rows - startY + 1) + " liegen!");
		return setEndY(startY);
	}
}

int setDimensionX() {
	print("Grundstueckstiefe: ");
	string n = "";
	regex test("^([1-9][0-9]{0,1})$");
	cin >> n;
	if (regex_match(n, test) && stoi(n) <= sizeToleranz) {
		rows = stoi(n);
		return stoi(n);
	}
	else {
		cin.clear();
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		println("Tiefe muss zwischen 0 und " + to_string(sizeToleranz + 1) + " liegen!");
		return setDimensionX();
	}
}

int setDimensionY() {
	print("Grundstuecksbreite: ");
	string m = "";
	regex test("^([1-9][0-9]{0,1})$");
	cin >> m;
	if (regex_match(m, test) && stoi(m) <= sizeToleranz) {
		columns = stoi(m);
		return stoi(m);
	}
	else {
		cin.clear();
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		println("Breite muss zwischen 0 und " + to_string(sizeToleranz + 1) + " liegen!");
		return setDimensionY();
	}
}

int setPositionX() {
	print("Breitenposition: ");
	string x = "";
	regex test("^([0-9][0-9]{0,1})$");
	cin >> x;
	if (regex_match(x, test) && stoi(x) < columns) {
		return stoi(x);
	}
	else {
		cin.clear();
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		println("Breite muss zwischen -1 und " + to_string(columns) + " liegen!");
		return setPositionX();
	}
}

int setPositionY() {
	print("Tiefenposition: ");
	string y = "";
	regex test("^([0-9][0-9]{0,1})$");
	cin >> y;
	if (regex_match(y, test) && stoi(y) < rows) {
		return stoi(y);
	}
	else {
		cin.clear();
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		println("Tiefe muss zwischen -1 und " + to_string(rows) + " liegen!");
		return setPositionY();
	}
}

bool wannaBuild(double cost) {
	print("Das Gebaeude kostet " + formate(cost) + " Euro.\nsoll das Gebaeude gebaut werden? j/n\n");
	string quest = "";
	regex j("[j]");
	regex n("[n]");
	cin >> quest;
	if (regex_match(quest, j)) {
		currentTotalCost += cost;
		return true;
	}
	else if (regex_match(quest, n)) {
		return false;
	}
	else {
		cin.clear();
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		println("\nEingabe darf nur j oder n sein\n");
		return wannaBuild(cost);
	}
}

string formate(double cost) {
	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << cost;
	std::string strCost = stream.str();
	return strCost;
}

Building* setValue() {
	println("\nWelcher Energieerzeuger soll platziert werden?\nWasserkraftwerk (A), Windkraftwerk (W), Soloarpannel (S)");
	string value = "";

	if (cin >> value) {
		if (value == "A") {
			return new AquaEnergie();
		}
		else if (value == "W") {
			return new WindEnergie();
		}
		else if (value == "S") {
			return new SolarEnergie();
		}
		else {
			println("Eingabe ist nicht erlaubt!");
			return setValue();
		}
	}

	else if (!cin.bad() && !cin.eof()) {
		cin.clear();
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		println("Eingabe ist nicht erlaubt!");
		return setValue();
	}
	return setValue();
}
