/*****************************************************************************
 * $CAMITK_LICENCE_BEGIN$
 *
 * CamiTK - Computer Assisted Medical Intervention ToolKit
 * (c) 2001-2017 Univ. Grenoble Alpes, CNRS, TIMC-IMAG UMR 5525 (GMCAO)
 *
 * Visit http://camitk.imag.fr for more information
 *
 * This file is part of CamiTK.
 *
 * CamiTK is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * CamiTK is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with CamiTK.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $CAMITK_LICENCE_END$
 ****************************************************************************/

// CamiTK includes
#include "ComponentProjet.h"
#include <Property.h>

#include <QFileInfo>

#include <QString>
#include <QTime>

using namespace camitk;

// --------------- Constructor -------------------
ComponentProjet::ComponentProjet(const QString & file) throw(AbortException)
:
Component(file, QFileInfo(file).baseName())
{
    std::ifstream a_file(file.toStdString(), std::ios::in);
    // Read the input file...
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
		
		a_file.close();
	}
	
	
    QString name = file.split('/').back();
    
    // Set the properties with their default values
    addProperty(new Property(tr("nomFichier"), name, tr("Nom du fichier"), ""));
    addProperty(new Property(tr("timeStart"), QTime::fromString(QString::fromStdString(temps[0]),"h:m:s:z"), tr("Heure de début du tracking"), ""));
    addProperty(new Property(tr("timeEnd"), QTime::fromString(QString::fromStdString(temps.back()),"hh:mm:ss:z"), tr("Heure de fin du tracking"), ""));

    // Add sub-components using the following code lines
    // Create a component (can be a component of your Component extension:
    // Component * subComp = new .....
    // add it as sub-component:
    // addChild(subComp);

    
}

// --------------- destructor -------------------
ComponentProjet::~ComponentProjet() {

}

//---------------------Method--------------------

double* ComponentProjet::getCoordonnees(int i)
{
	return coordonnee[i].data();
}

int ComponentProjet::getTime(int i) {
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

int ComponentProjet::getSize() {
	return coordonnee.size();
}

int* ComponentProjet::processTimer(std::string s) {
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
