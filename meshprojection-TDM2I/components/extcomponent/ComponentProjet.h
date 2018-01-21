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


#ifndef COMPONENTPROJET_H
#define COMPONENTPROJET_H

#include <QObject>

#include <Component.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <string>
#include <sstream>



class ComponentProjet : public camitk::Component {

    Q_OBJECT

public:
    /// Default Constructor
    ComponentProjet(const QString & file) throw(camitk::AbortException);

    /// Default Destructor
    virtual ~ComponentProjet();

    /// do nothing to init the representation, as all representation are done in the sub-component
    virtual void initRepresentation() {};
    
    //Retourne les coordonnée de la ligne i du fichier(commence à 0) : double[6] : tx,ty,tz,rx,ry,rz
	double* getCoordonnees(int i);
    
	//Retourne le temps à attendre avant de passer de la ligne i à i+1, en milliseconde
	int getTime(int i);
    
	//Retourne la taille du tableau de coordonnée
	int getSize();
    
private:
    //Attribut
	std::vector<std::vector<double>> coordonnee;//Contient tout les coordonées trouvé dans le fichier
	std::vector<std::string> temps;//Contient tout les temps trouvé dans le fichier
	//Fonction
	//Transforme un string type hh:mm:ss:ms en int[4] : hh,mm,ss,ms 
	int* processTimer(std::string s);

};

#endif // COMPONENTPROJET_H

