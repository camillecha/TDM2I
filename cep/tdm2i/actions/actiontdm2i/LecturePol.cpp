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
#include "LecturePol.h"
#include <Property.h>
#include <Application.h>

// Qt includes
#include <QString>
#include <QMessageBox>
#include <QTextStream>


using namespace camitk;


// --------------- Constructor -------------------
LecturePol::LecturePol(ActionExtension * extension) : Action(extension) {
    // Setting name, description and input component
    setName("lecturePol");
    setDescription("Lit le fichier pol et déplace l'objet");
    setComponent("Component3D");

    // Setting classification family and tags
    setFamily("TDM2I Family");
    // Tags allow the user to search the actions trhough themes
    // You can add tags here with the method addTag("tagName");

    // Setting the action's parameters
    addParameter(new Property(tr("filePath"), "", tr("Chemin du fichier"), ""));
    

}

// --------------- destructor -------------------
LecturePol::~LecturePol() {
    // Do not do anything yet.
    // Delete stuff if you create stuff
    // (except if you use smart pointers of course !!)
}

// --------------- apply -------------------
Action::ApplyStatus LecturePol::apply() {

    foreach (Component *comp, getTargets()) {
        Component3D * input = dynamic_cast<Component3D *> ( comp );
        process(input);
    }

    return SUCCESS;
}

void Affichage2D::process(Component3D * comp) {
    // Get the parameters
    String filePath = property("filePath").toString();
    
    // For this example, the action just pops up a message.
    QString msg;
    QTextStream in(&msg);
    in << "Action lecturePol called on " << comp->getName()  << endl;
    in << "With parameters: " << endl;
    in << "xfilePath: " << filePath << endl;
    
    QMessageBox::warning(NULL, "Action Called", msg);


}


