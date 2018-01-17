#ifndef DEPLACEMENT3D_H
#define DEPLACEMENT3D_H

#include <Action.h>

#include <MeshComponent.h>
#include <ImageComponent.h>
#include <Slice.h>
#include <InteractiveViewer.h>

//--vtk
#include <vtkPlane.h>
#include <vtkPolyDataMapper.h>


class Deplacement3D : public camitk::Action {
Q_OBJECT

public: 

    /// Default Constructor 
    Deplacement3D (camitk::ActionExtension *);

    /// Default Destructor
    virtual ~Deplacement3D ();
    
    /// method called when the action when the action is triggered (i.e. started)
//    virtual QWidget* getWidget();
    
public slots:
    /** this method is automatically called when the action is triggered.
      * Call getTargets() method to get the list of components to use.
      * \note getTargets() is automatically filtered so that it only contains compatible components, 
      * i.e., instances of ShowMeshIn2DSlice (or a subclass).
      */
    virtual ApplyStatus apply();
    
    
}; 

#endif // DEPLACEMENT3D_H





