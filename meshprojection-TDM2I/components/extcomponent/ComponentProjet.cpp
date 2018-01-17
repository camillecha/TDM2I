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
    // Read the input file...

    // Set the properties with their default values
    addProperty(new Property(tr("nomFichier"), "Hello World !", tr("Description"), ""));
    addProperty(new Property(tr("timeStart"), QTime(15, 55, 2), tr("Description"), ""));
    addProperty(new Property(tr("timeEnd"), QTime(15, 55, 2), tr("Description"), ""));

    // Add sub-components using the following code lines
    // Create a component (can be a component of your Component extension:
    // Component * subComp = new .....
    // add it as sub-component:
    // addChild(subComp);

    
}

// --------------- destructor -------------------
ComponentProjet::~ComponentProjet() {

}

