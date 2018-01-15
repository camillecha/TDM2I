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
#include "Deplacement3D.h"
#include <Property.h>
#include <Application.h>

// Qt includes
#include <QString>
#include <QMessageBox>
#include <QTextStream>


using namespace camitk;


// --------------- Constructor -------------------
Deplacement3D::Deplacement3D(ActionExtension * extension) : Action(extension) {
    // Setting name, description and input component
    setName("deplacement3D");
    setDescription("permet d'afficher en 3D sur le maillage su cerveau l'outil");
    setComponent("Component3D");

    // Setting classification family and tags
    setFamily("TDM2I family");
    // Tags allow the user to search the actions trhough themes
    // You can add tags here with the method addTag("tagName");

    // Setting the action's parameters
    addParameter(new Property(tr("tx"), 0, tr("translation x"), ""));
    addParameter(new Property(tr("ty"), 0, tr("translation y"), ""));
    addParameter(new Property(tr("tz"), 0, tr("translation z"), ""));
    addParameter(new Property(tr("rx"), 0, tr("rotation x "), ""));
    addParameter(new Property(tr("ry"), 0, tr("rotation y"), ""));
    addParameter(new Property(tr("rz"), 0, tr("rotation z"), ""));

}

// --------------- destructor -------------------
Deplacement3D::~Deplacement3D() {
    // Do not do anything yet.
    // Delete stuff if you create stuff
    // (except if you use smart pointers of course !!)
}

// --------------- apply -------------------
Action::ApplyStatus Deplacement3D::apply() {

    foreach (Component *comp, getTargets()) {
        Component3D * input = dynamic_cast<Component3D *> ( comp );
        process(input);
    }

    return SUCCESS;
}

void Deplacement3D::process(Component3D * comp) {
    // Get the parameters
    int tx = property("tx").toInt();
    int ty = property("ty").toInt();
    int tz = property("tz").toInt();
    int rx = property("rx").toInt();
    int ry = property("ry").toInt();
    int rz = property("rz").toInt();

    // For this example, the action just pops up a message.
    QString msg;
    QTextStream in(&msg);
    in << "Action deplacement3D called on " << comp->getName()  << endl;
    in << "With parameters: " << endl;
    in << "tx: " << tx << endl;
    in << "ty: " << ty << endl;
    in << "tz: " << tz << endl;
    in << "rx: " << rx << endl;
    in << "ry: " << ry << endl;
    in << "rz: " << rz << endl;
    QMessageBox::warning(NULL, "Action Called", msg);


}


