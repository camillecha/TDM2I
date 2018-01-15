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


#include "Image3D.h"

#include <QFileInfo>

// include generated components headers
#include "Component3D.h"
#include "Component2D.h"

using namespace camitk;


// --------------- GetFileExtensions -------------------
QStringList Image3D::getFileExtensions() const { 
    QStringList ext;
    ext << "polo";
    ext << "polo";
    
    return ext;
}

// --------------- Open -------------------
Component * Image3D::open(const QString & fileName) throw (AbortException) {
    Component * component;
    QStringList ext;
    ext << "polo";
    ext << "polo";
    
    // Get the fileName suffix
    QFileInfo fileInfo(fileName);
    QString suffix = fileInfo.suffix();
    
    // Open the right component according to the suffix
    switch (ext.indexOf(suffix))
    {
    case  0: 
        component = new Component3D(fileName);
        break;
    case  1: 
        component = new Component3D(fileName);
        break;
    default:
        std::cout << "The file extension" << suffix.toStdString() << " is not handled by Image3D extension, sorry... " << std::endl;
        component = NULL;
        break;
    }
    return component;
}

// --------------- Save --------------------
bool Image3D::save(Component * component) const { 
    // depending on the components managed by Image3D, use
    // component->getPointSet() (for a MeshComponent derived class)
    // or component->getImageData() (for a ImageComponent derived class)
    // and save the data in the managed format in the file component->getFileName()

    return false;
}

