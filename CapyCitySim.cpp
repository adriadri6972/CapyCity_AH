#include "CapyCitySim.h"

using namespace std;

//statische Variblen um überall die Blueprintanzahl und die aktuelle Nummer zur Verfügung zu haben
static int blueprintCount = 0;
static int currentBlueprintNumber=0;


//erzeugen eines neuen Blueprints und erweitern der map um diesen Blueprint mit dem zugehörigen index als pair
//aktueller Blueprint und Blueprintnummer = der gerade erzeugte
//hohzählen der gesamt Blueprintanzahl
//ich weiß nicht genau was es mit dem stack/heap fehler auf sich hat der hier markiert ist???
//bitte um Feedback was ich hier anders machen kann um das zu vermeiden
void CapyCity::addBlueprint() {
	Blueprint x =  Blueprint();
	blueprintList.insert(std::pair<int, Blueprint>(blueprintCount, x));
	currentBlueprint = &blueprintList.find(blueprintList.size()-1)->second;
	currentBlueprintNumber=blueprintCount;
	blueprintCount++;
	//delete &x;
}

//Blueprintmenü um alle Blueprints zu verwalten
//Eingabebeschränkung durch regex auf die zahlen 1-4
//wenn mindesten ein Blueprint existiert wird nach diesem Menü die flag gesetzt die dafür sorgt das im main script das Hauptmenü
//aufgerufen wird
void CapyCity::blueprintMenue() {
	cout <<""<<endl;
	cout <<"|----------- Blueprints -----------|"<<endl;
	cout <<"|                                  |"<<endl;
	cout <<"|        neuer Blueprint (1)       |"<<endl;
	cout <<"|      Blueprint wechseln (2)      |"<<endl;
	cout <<"|          alle Drucken (3)        |"<<endl;
	cout <<"|       Programm Beenden (4)       |"<<endl;
	cout <<"|                                  |"<<endl;
	cout <<"|__________________________________|"<<endl;
	cout <<"\nEingabe: ";

	string input = "";
	regex test("^([1-4]{0,1})$");
	cin >> input;

	if (regex_match(input, test)) {
		switch (stoi(input)) {
		case 1: addBlueprint();break;
		case 2: switchBlueprint();break;
		case 3: printAll();break;
		case 4: exit(0);break;
		default:
			cout<<" Fehler!\tEingabe ist nicht erlaubt!";
		}
	}
	else {
		cout<<"\nEingabe ist nicht erlaubt!\n"<<endl;
	}
	if (!blueprintList.empty()) {
		currentBlueprint->setInBlue(true);
	}
}

//Ordnen der Blueprints nach ihrer index Nummer (garnicht so leicht in einer ungeordneten map) + ausgabe auf der Konsole
//Eingabebeschränkung mit regex und prüfen ob die eingabe kleiner ist als die Menge aller Blueprints
//rekursiver aufruf bis eine valide eingabe erfolgt
void CapyCity::switchBlueprint() {
	int count = 0;
	//prüfen
	if (blueprintList.empty()) {
		cout << "\nkeine Blueprints vorhanden" << endl;
		return;
	}
	cout << "\n" << endl;
	//ordnen
	while (count < blueprintList.size()) {
		cout << "Blueprint #" + to_string(count) +"   Effizienzberechnung(Kennzahl): "+to_string(blueprintList.find(count)->second.getKennzahl()) << endl;
		count++;
	}
	cout << "\nBlueprint waehlen: #";
	string y = "";
	regex test("^([0-9][0-9]{0,1})$");
	cin >> y;
	if (regex_match(y, test) && stoi(y) < blueprintList.size()) {
		currentBlueprint = &blueprintList.find(stoi(y))->second;
		currentBlueprintNumber = blueprintList.find(stoi(y))->first;
	}
	else {
		cin.clear();
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		cout << "\nEingabe ungueltig!\n"<<endl;
		switchBlueprint();
	}
}


//kopiere die ganze Blueprintmap in einen dreiteiligen Vektor	
//Vektor besteht aus double Kennzahl,int index,Blueprint Objekt
//merken des aktuellen Blueprints in "currentBlueprint2"
//solange der dreiteilige Vektor nicht leer ist:
//-> iteriere in einer for-Schleife über alle paare 
//-> merke das mit der größten Kennzahl und an welchem index dieses im vektor steht
//-> größtest dreierpaar wird zum aktuellen Blueprint und wird auf der Konsole ausgegeben 
//-> entferne das größte dreierpaar aus dem Vektor (am gemerkter index)
//wenn der Vektor leer ist wird der aktuelle Bauplan durch den gemerkten "currentBlueprint2" wieder korrigiert
//auch hier entsteht ein stack/heap Problem???
void CapyCity::printAll() {
	if (!blueprintList.empty()) {
		cout << "\nSortiere Blueprints absteigend nach Kennzahl:" << endl;

		vector<pair<double, pair<int, Blueprint*>>> list;
		Blueprint* currentBlueprint2=currentBlueprint;

		for (pair<int, Blueprint> x : blueprintList) {
			list.push_back(make_pair(x.second.getKennzahl(), make_pair(x.first,&x.second)));
		}
		while(!list.empty()) {
			pair<double, pair<int, Blueprint*>> highest = make_pair(list.at(0).first, make_pair(list.at(0).second.first, list.at(0).second.second));
			int position = 0;
			for (int i = 0;i < list.size();i++) {
				if (list.at(i).first > highest.first) {
					highest.first = list.at(i).first;
					highest.second.first = list.at(i).second.first;
					highest.second.second = list.at(i).second.second;
					position = i;
				}
			}
			currentBlueprint = &blueprintList.find(highest.second.first)->second;
			cout << "\nBlueprint #" + to_string(highest.second.first) +" ("+to_string(currentBlueprint->getWidth())+"x"+ to_string(currentBlueprint->getHeight()) +") ----- Kennzahl: "+ to_string(currentBlueprint->getKennzahl()) << endl;
			currentBlueprint->printField();
			list.erase(list.begin() + position, list.begin() + position + 1);
		}
		currentBlueprint = currentBlueprint2;
	}
	else {
		cout<<"\n keine Blueprints vorhanden"<<endl;
	}
}

//kopiere die Blueprintmap in einen zweiteiligen Vektor
//beim kopieren wird gleichzeitig der aktuell gültige Blueprint nicht mit in diese Liste aufgenommen
//for-SChleife: vergleiche den aktuellen Bauplan mit allen elementen im Vektor
//wenn ein dreierpaar des Vektors alle Tests bestanden ist dieses mit dem aktuellen Plan identisch und es wird 
//gefragt ob einer gelöscht werden soll
//wenn n bleiben beide bestehen es wird beim nächsten Testen erneut gefragt
//wenn j wird die map mit allen Blueprints gelöscht und mit den Blueprints aus dem kopierten Vektor 
//wieder aufgefüllt (zu löschender Blueprint gibt es ja hier nicht)
//die index Nummer wird hierbei neu vergeben und alle index die größer als das zu löschende Element waren rutschen eins runter um 
//die entstandene Lücke zu schließen
void CapyCity::vergleichen() {

	vector<pair<int, Blueprint>> testList;

	for (int i = 0;i < blueprintList.size();i++) {
		if (currentBlueprint == nullptr || &blueprintList.find(i)->second != currentBlueprint) {
			testList.push_back(make_pair(blueprintList.find(i)->first, blueprintList.find(i)->second));

		}
	}
	for (pair<int, Blueprint> x : testList) {
		if (currentBlueprint->getKennzahl() == x.second.getKennzahl()) {
			if (currentBlueprint->getWidth() == x.second.getWidth()) {
				if (currentBlueprint->getHeight() == x.second.getHeight()) {
					for (int i = 0;i < currentBlueprint->getWidth();i++) {
						for (int j = 0;j < currentBlueprint->getHeight();j++) {
							if (currentBlueprint->getField().at(i + j) != x.second.getField().at(i + j)) {
								return;
							}
						}
					}
					if (wannaDelete(x.first)) {
						blueprintList.clear();
						blueprintCount = 0;
						for (pair<int, Blueprint> z : testList) {
							blueprintList.insert(std::pair<int, Blueprint>(blueprintCount, z.second));
							blueprintCount++;
						}
						currentBlueprint = &blueprintList.find(x.first)->second;
						currentBlueprintNumber = blueprintList.find(x.first)->first;
						return;
					}
					else {
						return;
					}
				}
			}
		}
	}
	currentBlueprint->setletsTest(false);
}

//rekursive abfrage ob objekt gelöscht werden soll
bool CapyCity::wannaDelete(int x) {
	cout << "\nder aktuelle Bauplan(#" + to_string(currentBlueprintNumber) + ") ist identisch mit Bauplan #" + to_string(x) + " moechten Sie den aktuellen Bauplan loeschen und zu Bauplan #" + to_string(x) + " wechseln? [j/n]\n";
	string quest = "";
	regex j("[j]");
	regex n("[n]");
	cin >> quest;
	if (regex_match(quest, j)) {
		cout << "Loesche Bauplan #" + to_string(currentBlueprintNumber) + "...\n";
		if (currentBlueprintNumber != blueprintList.size()-1) {
			cout << "Hinweis: die Nummern aller hoeheren Bauplaene werden um 1 veringer um die entstandene Luecke zu fuellen.\n";
		}
		return true;
	}
	else if (regex_match(quest, n)) {
		return false;
	}
	else {
		cin.clear();
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		cout<<"\nEingabe darf nur j oder n sein\n";
		return wannaDelete(x);
	}
}

//zum anzeigen der deraktuellen Nummer im Hauptmenü
int CapyCity::getcurrentBlueprintNumber() {
	return currentBlueprintNumber;
}

//formatirung von double auf 2 nachkomma
string CapyCity::formate(double cost) {
	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << cost;
	std::string strCost = stream.str();
	return strCost;
}
