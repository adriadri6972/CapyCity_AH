#pragma once

#include <iostream>
#include <list>
#include <regex>
#include <iomanip>
#include <sstream>
#include "Building.h"

using namespace std;

void print(std::string out);
void println(std::string out);
void menue();
void generateField(int x, int y);
void printField();
void printCost();
void printbuildingMaterialCost();
void deletePlot(int x, int y);
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
