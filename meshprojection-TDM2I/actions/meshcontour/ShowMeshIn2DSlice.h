/*****************************************************************************
 * $CAMITK_LICENCE_BEGIN$
 *
 * CamiTK - Computer Assisted Medical Intervention ToolKit
 * (c) 2001-2016 Univ. Grenoble Alpes, CNRS, TIMC-IMAG UMR 5525 (GMCAO)
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


#ifndef SHOWMESHIN2DSLICE_H
#define SHOWMESHIN2DSLICE_H

#include <Action.h>
#include <MeshComponent.h>
#include <ImageComponent.h>
#include <Slice.h>
#include <InteractiveViewer.h>

//--vtk
#include <vtkPlane.h>
#include <vtkPolyDataMapper.h>

/** Show the mesh contour in the Slice viewers.
 * 
 *  This action takes two inputs: a mesh component and an image component.
 * 
 *  The 2D contour of a mesh is displayed in each slice viewer (sagittal, coronal and axial)
 *  in respectively red, green and blue.
 * 
 *  This action takes into account the mesh and image frame.
 */
class ShowMeshIn2DSlice : public camitk::Action {
Q_OBJECT

public: 

    /// Default Constructor 
    ShowMeshIn2DSlice(camitk::ActionExtension *);

    /// Default Destructor
    virtual ~ShowMeshIn2DSlice();
    
    /// method called when the action when the action is triggered (i.e. started)
    virtual QWidget* getWidget();
    
public slots:
    /** this method is automatically called when the action is triggered.
      * Call getTargets() method to get the list of components to use.
      * \note getTargets() is automatically filtered so that it only contains compatible components, 
      * i.e., instances of ShowMeshIn2DSlice (or a subclass).
      */
    virtual ApplyStatus apply();

    /// this slots is called when the user changes the selected slice to update the contour
    void updateCuttingPlane();
    
private slots: 
    /// show/hide the contour in a viewer
    void toggleShowContour();
    
    /// remove the contour from the viewers if the mesh is closed / destroyed
    void cleanUp();
    
private:
    /// Apply show/hide the component, this is the current status
    bool isVisible;
    
    /// current target mesh component
    camitk::MeshComponent *mesh;
    
    /// current image component
    camitk::ImageComponent *targetImage;
    
    /// this action widget (to simplify, it is just a label that gives information + a button)
    QFrame* informationFrame;

    /// the contour mappers (input for both 3D and 2D actors)
    QMap<camitk::Slice::SliceOrientation, vtkSmartPointer<vtkPolyDataMapper>> cutterMapperMap;
    
    /// the mesh contours in the 3D view (where the mesh actually is), one for each orientation
    QMap<camitk::Slice::SliceOrientation, vtkSmartPointer<vtkActor>> contourActorMap;
    
    /// the mesh contours in the 2D views (with the proper transform that makes it appear in the slice viewer)
    QMap<camitk::Slice::SliceOrientation, vtkSmartPointer<vtkActor>> contourActorIn2DViewerMap;
    
    /// the cutting planes: the contour is the intersection between these planes and the mesh
    QMap<camitk::Slice::SliceOrientation, vtkSmartPointer<vtkPlane>> cuttingPlaneMap;
 
    /// get the dimension index corresponding to the current orientation
    /// 0 is the index for sagittal dimension, 1 for the coronal orientation and 2 is for the axial orientation
    int getOrientationIndex(camitk::Slice::SliceOrientation);
    
    /// get the voxel slice in the correct orientation
    double getVoxelSize(camitk::Slice::SliceOrientation);
    
    /// get the slice viewer corresponding to the orientation
    camitk::InteractiveViewer* getViewer(camitk::Slice::SliceOrientation);
    
    /// create an actor for the contour. The color of the new actor depends on the current orientation
    vtkSmartPointer<vtkActor> getNewActor(camitk::Slice::SliceOrientation);
    
    /// create a plane for a given orientation
    vtkSmartPointer<vtkPlane> getNewPlane(camitk::Slice::SliceOrientation);
    
    /// update the cutting plane position depending on the current slice and the given orientation
    void updateCuttingPlane(camitk::Slice::SliceOrientation);
    
    void deplacer();
    
//     void lireFichier();
//     
//     std::basic_ifstream<char> fichier;
//     
// 	std::vector<std::vector<double>> coordonnee;
//     
// 	std::vector<std::string> temps;
//     
//     //Retourne les coordonnées
//     double* getCoordonnees(int i);
// 	//Retourne le temps à attendre avant de passer de la ligne i à i+1, en milliseconde
// 	int getTime(int i);
// 	//Retourne la taille du tableau de coordonnée
// 	int getSize();
//     
//     //Transforme un string type hh:mm:ss:ms en int en ms
// 	int* processTimer(std::string s);
//     
//     int ligne = 0;

    
}; 

#endif // SHOWMESHIN2DSLICE_H

