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
#include "Affichage2D.h"
#include <Property.h>
#include <Application.h>

// Qt includes
#include <QString>
#include <QMessageBox>
#include <QTextStream>


using namespace camitk;


// --------------- Constructor -------------------
Affichage2D::Affichage2D(ActionExtension * extension) : Action(extension) {
    // Setting name, description and input component
    setName("affichage2D");
    setDescription("affichage de l'outil sur les coupes 2D");
    setComponent("Component2D");

    // Setting classification family and tags
    setFamily("TDM2I Family");
    // Tags allow the user to search the actions trhough themes
    // You can add tags here with the method addTag("tagName");

    // Setting the action's parameters
    addParameter(new Property(tr("x"), 0, tr("coordonnee en x"), ""));
    addParameter(new Property(tr("y"), 0, tr("coordonnee en y"), ""));
    addParameter(new Property(tr("z"), 0, tr("coordonnee en z"), ""));

}

// --------------- destructor -------------------
Affichage2D::~Affichage2D() {
    // Do not do anything yet.
    // Delete stuff if you create stuff
    // (except if you use smart pointers of course !!)
}

// --------------- apply -------------------
Action::ApplyStatus Affichage2D::apply() {

    foreach (Component *comp, getTargets()) {
        Component2D * input = dynamic_cast<Component2D *> ( comp );
        process(input);
    }

    return SUCCESS;
}

void Affichage2D::process(Component2D * comp) {
    // Get the parameters
    int x = property("x").toInt();
    int y = property("y").toInt();
    int z = property("z").toInt();

    // For this example, the action just pops up a message.
    QString msg;
    QTextStream in(&msg);
    in << "Action affichage2D called on " << comp->getName()  << endl;
    in << "With parameters: " << endl;
    in << "x: " << x << endl;
    in << "y: " << y << endl;
    in << "z: " << z << endl;
    QMessageBox::warning(NULL, "Action Called", msg);


}


