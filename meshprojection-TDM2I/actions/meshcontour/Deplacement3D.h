#ifndef DEPLACEMENT3D_H
#define DEPLACEMENT3D_H

#include <Action.h>
#include "ShowMeshIn2DSlice.h"
#include <MeshComponent.h>
#include <ImageComponent.h>
#include <Slice.h>
#include <InteractiveViewer.h>
#include "ComponentProjet.h"


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
    virtual QWidget* getWidget();
    
public slots:
    /** this method is automatically called when the action is triggered.
      * Call getTargets() method to get the list of components to use.
      * \note getTargets() is automatically filtered so that it only contains compatible components, 
      * i.e., instances of ShowMeshIn2DSlice (or a subclass).
      */
    virtual ApplyStatus apply();
    
    /// move tool to actialLine coordinate in tagetPol
    void moveTool();
    
private :
    /// current target mesh component
    camitk::MeshComponent *mesh;
    
    ///current target image
    camitk::ImageComponent *targetImage;
    
    /// current ComponentProjet component
    ComponentProjet *targetPol;
    
    /// this action widget (to simplify, it is just a label that gives information + a button)
    QFrame* informationFrame;
    
    ///The line actualy used to set coordinate of the tools
    int actualLine;
    
    ///The timer that called mvoeTool when time between two coordinate have elapsed
    QTimer *timer;
    
}; 

#endif // DEPLACEMENT3D_H





