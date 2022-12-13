#include "CapyCitySim.h"

int main()
{
	println("Willkommen in CapyCity buildertool!");
	println("Mit diesem Tool kann eine Bauflaeche von bis zu " + to_string(getSizeTolerance()) + "x" + to_string(getSizeTolerance()) + " Feldern bebaut werden.");
	println("\nAktuelle unterstuetze Bauvorhaben sind:\nWasserkarftwerk (als A markiert)\nWindkraftwerk (als W markiert)\nSolarpanele (als S markiert)");
	println("\nInfo: Positionskoordinaten beziehen sich auf die linke obere Ecke des jeweiligen Gebauedes");
	println("\nBitte verwenden sie diese Anwendung im Vollbildmodus");
	println("\nInitialisiere Grundstueck...\n");
	generateField(setDimensionX(), setDimensionY());
	while (menue()) {
		menue();
	}
	return 0;
}