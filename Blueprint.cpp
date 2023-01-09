
#include "Blueprint.h"
#include "CapyCitySim.h"

//ich verwende fast überall den import von regex um die Nutzereingabe auf Zahlen zu beschränken


//Konstruktor
Blueprint::Blueprint(){
	startUp();
};

//Methoden

//print ist schöner als cout
void Blueprint::print(string out) {
	cout << out;
}
void Blueprint::println(string out) {
	cout << out << endl;
}

// Begrüßungstext beim erzeugen eines Blueprints
void Blueprint::startUp() {
	println("Willkommen in CapyCity buildertool!");
	println("Mit diesem Tool kann eine Bauflaeche von bis zu " + to_string(getSizeTolerance()) + "x" + to_string(getSizeTolerance()) + " Feldern bebaut werden.");
	println("\nAktuelle unterstuetze Bauvorhaben sind:\nWasserkarftwerk (als A markiert)\nWindkraftwerk (als W markiert)\nSolarpanele (als S markiert)");
	println("\nInfo: Positionskoordinaten beziehen sich auf die linke obere Ecke des jeweiligen Gebauedes");
	println("\nBitte verwenden sie diese Anwendung im Vollbildmodus");
	println("\nInitialisiere Blueprint...\n");
	generateField(setDimensionY(), setDimensionX());
}

// Hauptmenü mit switch case für die jeweilige Methode
//Eingabebeschränkung durch regex auf die zahlen 1-6
void Blueprint::menue() {
	println("");
	println("|----------- Hauptmenue -----------|");
	println("|                                  |");
	println("|       aktuell Blueprint #"+ to_string(CapyCity::getcurrentBlueprintNumber())+"       |");
	println("|                                  |");
	println("|----------------------------------|");
	println("|                                  |");
	println("|  aktuellen Bauplan ausgeben (1)  |");
	println("|     Gebaeude platzieren (2)      |");
	println("|     Gebaeude entfernen (3)       |");
	println("|   Gebaeude/Material kosten (4)   |");
	println("|     Blueprintverwaltung (5)      |");
	println("|       Programm Beenden (6)       |");
	println("|                                  |");
	println("|__________________________________|");
	print("\nEingabe: ");

	string input = "";
	regex regexBetweenOneAndSix("^([1-6]{0,1})$");
	cin >> input;

	if (regex_match(input, regexBetweenOneAndSix)) {
		switch (stoi(input)) {
		case 1: printField();printCost();break;
		case 2: setField(setPositionX(), setPositionY());break;
		case 3: deleteField(setDeletePositionX(), setDeletePositionY());break;
		case 4: printbuildingMaterialCost();break;
		case 5: inBlue=false;break;
		case 6: exit(0);break;
		default:
			println("Menue Fehler!\tEingabe ist nicht erlaubt!");
		}
	}
	else {
		println("\nEingabe ist nicht erlaubt!\n");
	}
}

// flag die in der main entscheidet ob Hauptmenü oder Blueprintmenü gezeigt wird
bool Blueprint::getInBlue() {
	return inBlue;
}
void Blueprint::setInBlue(bool x) {
	inBlue = x;
}

// flag die in der main entscheidet ob Blueprints verglichen werden sollen
bool Blueprint::getwannaTest() {
	return letsTest;
}
void Blueprint::setletsTest(bool x) {
	letsTest = x;
}

// löschen eines einzelnen Feldes, die aufgabe war etwas unklar (Gebäude sollen nur verkleinert werden) 
// deswegen kann man mit der Option löschen nur einzelne Felder entfernen 
void Blueprint::deleteField(int x, int y) {
	Building* a = new AquaEnergie();
	Building* w = new WindEnergie();
	Building* s = new SolarEnergie();
	if (field[y][x] == "A") {
		currentAquaCost -= a->getGroundPrice() + a->sumMaterialCosts();
		currentTotalCost -= a->getGroundPrice() + a->sumMaterialCosts();
		currentAquaMW -= a->getMegaWatt();
		currentTotalMW -= a->getMegaWatt();
	}
	if (field[y][x] == "W") {
		currentWindCost -= w->getGroundPrice() + w->sumMaterialCosts();
		currentTotalCost -= w->getGroundPrice() + w->sumMaterialCosts();
		currentWindMW -= w->getMegaWatt();
		currentTotalMW -= w->getMegaWatt();
	}
	if (field[y][x] == "S") {
		currentSolaCost -= s->getGroundPrice() + s->sumMaterialCosts();
		currentTotalCost -= s->getGroundPrice() + s->sumMaterialCosts();
		currentSolaMW -= s->getMegaWatt();
		currentTotalMW -= s->getMegaWatt();
	}
	kennzahl = (currentTotalMW / (currentTotalCost * rows * columns));
	field[y][x] = BLANK;
	delete a;
	delete w;
	delete s;
}

//wird beim erzeugen aufgerufen um die höhe und breite des neuen Blueprints anzulegen und mit einem 
//Leerzeichen (ASKII) zu befüllen
void Blueprint::generateField(int x, int y) {
	for (int height = 0;height < sizeTolerance;height++) {
		for (int width = 0;width < sizeTolerance;width++) {
			this->field[width][height] = BLANK;
		}
	}
	setletsTest(true);
}

//(grafische) Ausgabe des aktuellen Blueprints, farbiges gestalten von A,W und S mit printf
void Blueprint::printField() {
	if (rows <= 0 && columns <= 0) {
		print("kein Feld gefunden");
		return;
	}
	for (int x = 0;x < (rows * 2) + 1;x++) {
		for (int y = 0;y < columns;y++) {
			if (y == 0) {
				print("|");
			}
			if (x % 2 == 1) {
				if (field[(x / 2)][y] == "A") {
					printf(" \033[36mA\033[0m |");
				}
				else if (field[(x / 2)][y] == "W") {
					printf(" \033[91mW\033[0m |");
				}
				else if (field[(x / 2)][y] == "S") {
					printf(" \033[93mS\033[0m |");
				}
				else {
					print(" " + field[(x / 2)][y] + " |");
				}
			}
			else {
				print("---|");
			}
		}
		println("");
	}

	
}

//(grafische) Ausgabe der aktuellen Kosten
void Blueprint::printCost() {
	println("\n");
	println("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$");
	println("                                                                              ");
	println("                          aktuelle Kostenuebersicht:                          ");
	println("                                                                              ");
	println("                  Wasserkraftwerke (A): " + formate(currentAquaCost) + " Euro ");
	println("                  Windkraftwerke (W):   " + formate(currentWindCost) + " Euro ");
	println("                  Solarkraftwerke (S):  " + formate(currentSolaCost) + " Euro ");
	println("______________________________________________________________________________");
	println("                          Gesamtkosten: " + formate(currentTotalCost) + " Euro");
	println("                                                                              ");
	println("                                                                              ");
	println("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$");
	println("                                                                              ");
	println("                          aktuell erzeugte MegaWatt:                          ");
	println("                                                                              ");
	println("                  Wasserkraftwerke (A): " + formate(currentAquaMW) + " MW     ");
	println("                  Windkraftwerke (W):   " + formate(currentWindMW) + " MW     ");
	println("                  Solarkraftwerke (S):  " + formate(currentSolaMW) + " MW     ");
	println("______________________________________________________________________________");
	println("                                Gesamt: " + formate(currentTotalMW) + " MW    ");
	println("                                                                              ");
	println("                                                                              ");
	println("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$");
	println("                                                                              ");
	println("                   Aktuelle Kennzahl: " + to_string(kennzahl) + "             ");
	println("                                                                              ");
	println("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$");
	println("\n");
}

//(grafische) Ausgabe der Ressourcenkosten
void Blueprint::printbuildingMaterialCost() {
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
	println("|                       " + wood->getName() + ":       " + formate(wood->getPrice()) + " Euro                          |");
	println("|                       " + iron->getName() + ":      " + formate(iron->getPrice()) + " Euro                          |");
	println("|                       " + plas->getName() + ": " + formate(plas->getPrice()) + " Euro                          |");
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

//Test ob übergebene xy-Koordinate schon belegt ist, wenn nein weiter mit buildBuilding()
void Blueprint::setField(int x, int y) {
	if ((field[y][x] == "A" || field[y][x] == "W") || field[y][x] == "S") {
		print("\nBauplatz ist schon belegt! Bau woanders!\n");
	}
	else {
		buildBuilding(x, y, setEndX(x), setEndY(y), setBuilding());
	}
}

//übergeben Start- und Endpunkt vom Gebäude in x und y Richtung
//Iteriere mit zwei for-Schleifen über die Karte und schreibe die xy-Koordinaten an dennen etwas stehen soll in zwei 
//Integer Arrays, solange bis das Ende erreicht ist. Dabei wird geprüft ob jede Koordinate die beschrieben werden soll
//frei ist
//sind alle Plätze frei werden die aktuellen Kosten/MW berechnet und der Nutzer gefragt ob das Gebäude gebaut werden soll
//bei n wird das Gebäude verworfen und alles zurückgesetzt
//bei j werden alle gemerkten Koordinaten auf den aktuellen Blueprint angewand
//es wird ermittelt welches Gebäude gebaut wird und die gesamt Kosten/MW für diese Gebäudeart werden 
//aktualisiert (wird in printCost() benutzt)
void Blueprint::buildBuilding(int startX, int startY, int endX, int endY, Building* value) {
	int* xKoordinates = new int[sizeTolerance * sizeTolerance];
	int* yKoordinates = new int[sizeTolerance * sizeTolerance];
	int zaehler = 0;

	for (int height = startY;height <= endY;height++) {
		for (int width = startX;width <= endX;width++) {
			yKoordinates[zaehler] = width;
			xKoordinates[zaehler] = height;
			zaehler++;
			if (field[height][width] == "A" || field[height][width] == "W" || field[height][width] == "S") {
				println("\nEs steht nicht der komplette Bauplatz zur verfuegung! Bauvorhaben abgebrochen!\n");
				delete[] xKoordinates;
				delete[] yKoordinates;
				return;
			}
		}
	}

	currentBuildingCost = (value->getGroundPrice() + value->sumMaterialCosts()) * zaehler;
	currentBuildingMW = value->getMegaWatt() * zaehler;

	if (wannaBuild(currentBuildingCost, currentBuildingMW)) {
		for (int i = 0;i < zaehler;i++) {
			field[xKoordinates[i]][yKoordinates[i]] = value->getLabel();
		}
		if (value->getLabel() == "A") {
			currentAquaCost += currentBuildingCost;
			currentAquaMW += currentBuildingMW;
		}
		else if (value->getLabel() == "W") {
			currentWindCost += currentBuildingCost;
			currentWindMW += currentBuildingMW;
		}
		else if (value->getLabel() == "S") {
			currentSolaCost += currentBuildingCost;
			currentSolaMW += currentBuildingMW;
		}
		setletsTest(true);
	}
	else {
		println("\nBau wurde abgebrochen.\n");
	}
	delete[] xKoordinates;
	delete[] yKoordinates;
}

//Abfrage für die zu löschende x-Koordinate für die übergabe an deleteField()
//Eingabebeschränkung mit regex und kontrolle ob die auswahl im Feld liegt
//bei falscher eingabe rekursiver Aufruf
//ruft sich solange rekursiv selbst auf bis eine valide eingabe getätigt wurde
int Blueprint::setDeletePositionX() {
	print("zu loeschende Breitenkoordinate: ");
	string xD = "";
	regex zeroToNine("^([0-9][0-9]{0,1})$");
	cin >> xD;
	if (regex_match(xD, zeroToNine) && stoi(xD) < columns) {
		return stoi(xD);
	}
	else {
		cin.clear();
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		println("Breite muss zwischen -1 und " + to_string(columns) + " liegen!");
		return setDeletePositionX();
	}
}

//Abfrage für die zu löschende y-Koordinate für die übergabe an deleteField()
//Eingabebeschränkung mit regex und kontrolle ob die auswahl im Feld liegt
//bei falscher eingabe rekursiver Aufruf
//ruft sich solange rekursiv selbst auf bis eine valide eingabe getätigt wurde
int Blueprint::setDeletePositionY() {
	print("zu loeschende Tiefenkoordinate: ");
	string yD = "";
	regex zeroToNine("^([0-9][0-9]{0,1})$");
	cin >> yD;
	if (regex_match(yD, zeroToNine) && stoi(yD) < rows) {
		return stoi(yD);
	}
	else {
		cin.clear();
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		println("Tiefe muss zwischen -1 und " + to_string(rows) + " liegen!");
		return setDeletePositionY();
	}
}

//Abfrage der breite des zu bauenden Gebäudes und errechnen des Endpunktes(x) anhand des Startpunktes(x) 
//Eingabebeschränkung mit regex und kontrolle ob die auswahl im Feld liegt
//bei falscher eingabe rekursiver Aufruf
//ruft sich solange rekursiv selbst auf bis eine valide eingabe getätigt wurde
int Blueprint::setEndX(int startX) {
	print("\nWie breit soll das Gebauede werden?\nBreite: ");
	string x = "";
	regex width("^([1-9][0-9]{0,1})$");
	cin >> x;
	if (regex_match(x, width) && startX + stoi(x) - 1 < columns) {
		return ((startX + stoi(x)) - 1);
	}
	else {
		cin.clear();
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		println("Breite muss zwischen 0 und " + to_string((columns - startX) + 1) + " liegen!");
		return setEndX(startX);
	}
}

//Abfrage der tiefe des zu bauenden Gebäudes und errechnen des Endpunktes(x) anhand des Startpunktes(x) 
//Eingabebeschränkung mit regex und kontrolle ob die auswahl im Feld liegt
//bei falscher eingabe rekursiver Aufruf
//ruft sich solange rekursiv selbst auf bis eine valide eingabe getätigt wurde
int Blueprint::setEndY(int startY) {
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

//Abfrage wie hoch die Baufläche des neu erzeugnten Blueprints sein soll, für die übergabe an generateField()
//Eingabebeschränkung mit regex und kontrolle ob die auswahl kleiner ist als die festgelegte maximale Größe
//speichern der rows variable um in anderen Methoden die höhe abfragen zu können
//ruft sich solange rekursiv selbst auf bis eine valide eingabe getätigt wurde
int Blueprint::setDimensionY() {
	print("Grundstueckstiefe: ");
	string n = "";
	regex test("^([1-9][0-9]{0,1})$");
	cin >> n;
	if (regex_match(n, test) && stoi(n) <= sizeTolerance) {
		rows = stoi(n);
		return stoi(n);
	}
	else {
		cin.clear();
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		println("Tiefe muss zwischen 0 und " + to_string(sizeTolerance + 1) + " liegen!");
		return setDimensionY();
	}
}

//Abfrage wie breit die Baufläche des neu erzeugnten Blueprints sein soll, für die übergabe an generateField()
//Eingabebeschränkung mit regex und kontrolle ob die auswahl kleiner ist als die festgelegte maximale Größe
//speichern der columns variable um in anderen Methoden die breite abfragen zu können
//ruft sich solange rekursiv selbst auf bis eine valide eingabe getätigt wurde
int Blueprint::setDimensionX() {
	print("Grundstuecksbreite: ");
	string m = "";
	regex test("^([1-9][0-9]{0,1})$");
	cin >> m;
	if (regex_match(m, test) && stoi(m) <= sizeTolerance) {
		columns = stoi(m);
		return stoi(m);
	}
	else {
		cin.clear();
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		println("Breite muss zwischen 0 und " + to_string(sizeTolerance + 1) + " liegen!");
		return setDimensionX();
	}
}

//Abfrage der x-Koordinate für den Startpunkt eines neuen Gebäude, zur übergabe an setField()
//Eingabebeschränkung mit regex und kontrolle ob die auswahl im feld liegt
//ruft sich solange rekursiv selbst auf bis eine valide eingabe getätigt wurde
int Blueprint::setPositionX() {
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

//Abfrage der y-Koordinate für den Startpunkt eines neuen Gebäude, zur übergabe an setField()
//Eingabebeschränkung mit regex und kontrolle ob die auswahl im feld liegt
//ruft sich solange rekursiv selbst auf bis eine valide eingabe getätigt wurde
int Blueprint::setPositionY() {
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

//get-Methode um die maximale Feldgröße in der CapyCitySim Klasse benutzen zu können
int Blueprint::getSizeTolerance() {
	return sizeTolerance;
}

//get-Methode um die aktuelle Bleuprint-feldbreite in der CapyCitySim Klasse benutzen zu können
int Blueprint::getWidth() {
	return columns;
}

//get-Methode um die aktuelle Bleuprint-feldhöhe in der CapyCitySim Klasse benutzen zu können
int Blueprint::getHeight() {
	return rows;
}

//get-Methode um die aktuelle Blueprint-kennzahl in der CapyCitySim Klasse benutzen zu können
double Blueprint::getKennzahl() {
	return kennzahl;
}

//Abfrage ob ein gebäude mit den übergebenen Kosten und MW werten gebaut werden soll
//Eingabebeschränkung mit regex auf j und n
//bei j werden die Gesamtkosten des aktuellen Blueprints aktualisiert und true an buildBuilding() übergeben
//bei einer nicht zulässigen eingabe ruft sich di Methode rekursiv immer wieder selbst auf, bis eine valide eingabe erfolg
bool Blueprint::wannaBuild(double cost,double megaWatt) {
	print("Das Gebaeude kostet " + formate(cost) + " Euro und erzeugt "+ formate(megaWatt)+" Mega Watt.\nsoll das Gebaeude gebaut werden? j/n\n");
	string quest = "";
	regex j("[j]");
	regex n("[n]");
	cin >> quest;
	if (regex_match(quest, j)) {
		currentTotalCost += cost;
		currentTotalMW += megaWatt;
		kennzahl = currentTotalMW / (currentTotalCost * rows * columns);
		return true;
	}
	else if (regex_match(quest, n)) {
		return false;
	}
	else {
		cin.clear();
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		println("\nEingabe darf nur j oder n sein\n");
		return wannaBuild(cost,megaWatt);
	}
}

//Hilfsmethode um eine double variable auf 2 Nachkomma zu formatieren und als String zurück zu geben
//wird bei berechnungen von Geldbeträgen verwendet
string Blueprint::formate(double cost) {
	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << cost;
	std::string strCost = stream.str();
	return strCost;
}

//get-Methode um das bebaute Feld des Bauplanes in der CapyCitySim Klasse verwenden zu können
//wird in vergleichen() verwendet, um Baupläne zu vergleichen
vector<string> Blueprint::getField() {
	vector<string> list;
	for (int y = 0;y <= rows;y++) {
		for (int x = 0;x <= columns;x++) {
			list.push_back(field[x][y]);
		}
	}
	return list;
}

//Abfrage welches Gebäude gebaut werden soll
//Eingabebeschränkung ohne regex, da hier Buchstaben erwartet werden wird alles als String eingelesen und kann ohne Probleme
//mit allen Zeichen verglichen werden
//Beschränkung auf A,W und S, bei falscher eingabe ruft sich die Methode rekursiv selbst wieder auf
//übergibt zu bauendes Gebäude an buildBuilding()
Building* Blueprint::setBuilding() {
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
			return setBuilding();
		}
	}

	else if (!cin.bad() && !cin.eof()) {
		cin.clear();
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		println("Eingabe ist nicht erlaubt!");
		return setBuilding();
	}
	return setBuilding();
}
