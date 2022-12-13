// CapyCity_AH.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <list>
#include <regex>

using namespace std;

int rows = 0, columns = 0, sizeToleranz = 40;
string** field;

int main();

void print(string out);
void println(string out);
void menue();
void generateField(int x, int y);
void printField();
void setField(int x, int y, string value);
int setDimensionX();
int setDimensionY();
int setPositionX();
int setPositionY();
int setDeletePositionX();
int setDeletePositionY();
void deletePlot(int x, int y);
string setValue();
void buildBuilding(int startX, int startY, int endX, int endY, string value);
int setEndX(int startX);
int setEndY(int startY);

enum MyEnum
{
	LEER = 0,
	WASSER = 1,
	WIND = 2,
	SONNE = 3
};

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
	println("|       Programm Beenden (4)       |");
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
		case 4:
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
	println("");
}

void setField(int x, int y, string value) {
	if (field[x][y] == "A" || field[x][y] == "W" || field[x][y] == "S") {
		print("\nBauplatz ist schon belegt! Bau woanders!\n");
		return menue();
	}
	buildBuilding(x, y, setEndX(x), setEndY(y), value);
}

void buildBuilding(int startX, int startY, int endX, int endY, string value) {
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
	for (int i = 0;i < zaehler;i++) {
		field[xKoordinates[i]][yKoordinates[i]] = value;
	}
	delete[] xKoordinates;
	delete[] yKoordinates;
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

string setValue() {
	println("\nWelcher Energieerzeuger soll platziert werden?\nWasserkraftwerk (A), Windkraftwerk (W), Soloarpannel (S)");
	string value = "";
	MyEnum eNum = LEER;

	if (cin >> value) {
		if (value == "A") {
			eNum = WASSER;
		}
		else if (value == "W") {
			eNum = WIND;
		}
		else if (value == "S") {
			eNum = SONNE;
		}
		else {
			eNum = LEER;
		}
		switch (eNum) {
		case WASSER: return "A";break;
		case WIND: return "W";break;
		case SONNE: return "S";break;
		default: 
			println("Eingabe ist nicht erlaubt!");
			return setValue();break;
		}
		//if (value == "A" || value == "W" || value == "S") {
		//	return value;
		//}
		//else {
		//	println("Eingabe ist nicht erlaubt!");
		//	return setValue();
		//}
	}
	else if (!cin.bad() && !cin.eof()) {
		cin.clear();
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		println("Eingabe ist nicht erlaubt!");
		return setValue();
	}
	return setValue();
}