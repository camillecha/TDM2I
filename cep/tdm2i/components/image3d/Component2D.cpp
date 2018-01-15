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
#include "Component2D.h"
#include <Property.h>


#include <QString>

using namespace camitk;

// --------------- Constructor -------------------
Component2D::Component2D(const QString & file) throw(AbortException)
:
ImageComponent(file)
{
    // Set the properties with their default values
    addProperty(new Property(tr("objet2D"), "null", tr("coordonnee de l'objet en 2D pour l'affichage sur les differentes coupes"), ""));


    // Read the image from the given input file
    if (!file.isNull()) {
        // Here is an example of image creation without reading a file
        //  to show how to use vtkImageData and ImageComponents.
        // Replace this code with real image creation using the input file.
        // Do not hesitate to read vtk documentation or tutorials to see how vtkImageData works

        // Create a vtkImageData
        vtkSmartPointer<vtkImageData> image = NULL;
        image = vtkSmartPointer<vtkImageData>::New();
        image->SetDimensions(3,3,3);
        image->AllocateScalars(VTK_UNSIGNED_CHAR, 1);
        // Here, we arbitrarily fill the image data
        int* dims = image->GetDimensions();

        for (int z = 0; z < dims[2]; z++) {
            for (int y=0; y<dims[1]; y++) {
                for (int x=0; x<dims[0]; x++) {
                    double val = ((x==1) && (y==1) && (z==1))? 1.0: 0.0;
                    image->SetScalarComponentFromDouble(x,y,z,0,val);
                }
            }
        }

        // Make this image the image of your component
        // (this method is already implemented in ImageComponent)
        setImageData(image, false);
    }
    else
    { // there is no file name, so we cannot open an image...
        throw (AbortException("No file found"));
    }

}

// --------------- destructor -------------------
Component2D::~Component2D() {

}

