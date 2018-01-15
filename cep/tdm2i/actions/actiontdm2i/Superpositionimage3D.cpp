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
#include "Superpositionimage3D.h"
#include <Property.h>
#include <Application.h>

// Qt includes
#include <QString>
#include <QMessageBox>
#include <QTextStream>


using namespace camitk;


// --------------- Constructor -------------------
Superpositionimage3D::Superpositionimage3D(ActionExtension * extension) : Action(extension) {
    // Setting name, description and input component
    setName("superpositionimage3D");
    setDescription("permet de superposer le maillage de l'objet et du cerveau.");
    setComponent("Component3D");

    // Setting classification family and tags
    setFamily("TDM2I Family");
    // Tags allow the user to search the actions trhough themes
    // You can add tags here with the method addTag("tagName");

    // Setting the action's parameters
    addParameter(new Property(tr("cerveau"), 0.0, tr("maillage du cerveau "), ""));
    addParameter(new Property(tr("outil"), 0.0, tr("maillage de l'outil "), ""));

}

// --------------- destructor -------------------
Superpositionimage3D::~Superpositionimage3D() {
    // Do not do anything yet.
    // Delete stuff if you create stuff
    // (except if you use smart pointers of course !!)
}

// --------------- apply -------------------
Action::ApplyStatus Superpositionimage3D::apply() {

    foreach (Component *comp, getTargets()) {
        Component3D * input = dynamic_cast<Component3D *> ( comp );
        process(input);
    }

    return SUCCESS;
}

void Superpositionimage3D::process(Component3D * comp) {
    // Get the parameters
    double cerveau = property("cerveau").toDouble();
    double outil = property("outil").toDouble();

    // For this example, the action just pops up a message.
    QString msg;
    QTextStream in(&msg);
    in << "Action superpositionimage3D called on " << comp->getName()  << endl;
    in << "With parameters: " << endl;
    in << "cerveau: " << cerveau << endl;
    in << "outil: " << outil << endl;
    QMessageBox::warning(NULL, "Action Called", msg);


}


