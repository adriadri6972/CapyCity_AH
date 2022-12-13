#pragma once
class CapyCity {

	int rows, columns , sizeToleranz;
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
};