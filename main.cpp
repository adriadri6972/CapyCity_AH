#include "CapyCitySim.h"

// in dem Skript CapyCitySim.cpp kommt es in einigen Methoden zu stack/heap Problemen
// ich konnte nicht herrausfinden was es damit aufsich hat, muss ich hier noch irgendetwas an erzeugten Objekten löschen?
// wenn ich versuche die objekte zu löschen entstehen Exceptions, so wie das Programm aktuell ist gibt es im ablauf keine Probleme.
// könnte ich bitte ein Feedback bekommen was ich hier falsch gemacht habe und anders lösen kann?

// der Wert der Kennzahl ist im ganzen Programm etwas komisch, ich führe die Berechnung laut der gegebenen Formel durch aber die werte
// sind sehr klein und definieren nicht wirklich wie effizient der Bauplan ist.
// ich schätze das Problem liegt bei den MW- und Preiswerten (die in den Konstruktoren definiert werden) weshalb die Rechnung 
// keinen richtigen Sinn ergibt
// es sollte mehr Sinn ergeben wenn die Kosten richtig aufeinander abgestimmt sind, allerdings habe ich diese Werte nicht gefunden

// das main Skript erzeugt einen simulator vom Typ CapyCity
int main()
{
	CapyCity simulator = CapyCity();
	// schleife durch das Blueprintmenü
	while (true) {
		simulator.blueprintMenue();
		//solange im aktuellen blueprint ein flag gesetzt ist -> schleife durch das Hauptmenü
		while (!simulator.blueprintList.empty()&&simulator.currentBlueprint->getInBlue()) {
			// wenn im aktuellen Blueprint ein flag gesetzt ist werden die Blueprints miteinander verglichen
			if (simulator.currentBlueprint->getwannaTest()) {
				simulator.vergleichen();
			}
			simulator.currentBlueprint->menue();
		}
	};
	return 0;
}