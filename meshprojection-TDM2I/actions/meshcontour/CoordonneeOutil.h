#pragma once
#ifndef COORDONEEOUTIL_H
#define COORDONEEOUTIL_H
#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <string>
#include <sstream>


class CoordoneeOutil
{
public:
	CoordoneeOutil(std::string path);
	~CoordoneeOutil();
	//Retourne les coordonnée de la ligne i (commence à 0) : double[6] : tx,ty,tz,rx,ry,rz
	double* getCoordonnees(int i);
	//Retourne le temps à attendre avant de passer de la ligne i à i+1, en milliseconde
	int getTime(int i);
	//Retourne la taille du tableau de coordonnée
	int getSize();
private:
	//Attribut
	std::ifstream a_file;
	std::vector<std::vector<double>> coordonnee;
	std::vector<std::string> temps;
	//Fonction
	//Transforme un string type hh:mm:ss:ms en int en ms
	int* processTimer(std::string s);
};
#endif
