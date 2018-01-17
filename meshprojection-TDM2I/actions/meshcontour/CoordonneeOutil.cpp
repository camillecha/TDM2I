#include "CoordonneeOutil.h"

CoordoneeOutil::CoordoneeOutil(std::string path):a_file(path, std::ios::in)
{
	if (!a_file) {
		std::cout << "unreacheable file" << std::endl;
	}
	else {
		std::string line;
		std::string timer;
		std::vector<double> vec(6, -1);
		while (getline(a_file, line)) {
			std::istringstream iss(line);
			iss >> timer >> vec[0] >> vec[1] >> vec[2] >> vec[3] >> vec[4] >> vec[5];
			coordonnee.push_back(vec);
			temps.push_back(timer);
		}
	}
}

CoordoneeOutil::~CoordoneeOutil()
{
}


double* CoordoneeOutil::getCoordonnees(int i)
{
	return coordonnee[i].data();
}

int CoordoneeOutil::getTime(int i) {
	/*int resultat = processTimer(temps[i])[2];*/
	int resultat = 0;
	if (i < getSize() - 1) {
		int *t1 = processTimer(temps[i]);
			int *t2 = processTimer(temps[i+1]);
			//Calcule du temps en milliseconde
			resultat = resultat + t2[3] - t1[3];//milliseconde
			resultat = resultat + (t2[2] - t1[2]) * 1000;//seconde -> milliseconde
			resultat = resultat + (t2[1] - t1[1]) * 1000 * 60;//minute
			resultat = resultat + (t2[0] - t1[0]) * 1000 * 60 * 60;//heure
			return resultat;
	}
	else {
		return 0;
	}
	
}

int CoordoneeOutil::getSize() {
	return coordonnee.size();
}

int* CoordoneeOutil::processTimer(std::string s) {
	int *resultat = new int[4];
	int i = 0;
	std::istringstream iss(s);
	std::string parsed;
	while(getline(iss, parsed, ':')) {
		resultat[i] = stoi(parsed);
		i++;
	}

	return resultat;
}



