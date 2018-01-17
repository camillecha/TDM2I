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

// CamiTK includes
#include "ShowMeshIn2DSlice.h"
#include <Property.h>
#include <Application.h>
#include <InteractiveViewer.h>

// Qt includes
#include <QBoxLayout>
#include <QFrame>
#include <QLabel>
#include <QListIterator>
#include <QMessageBox>
#include <QMap>

// VTK includes
#include <vtkCutter.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkGeometryFilter.h>
#include <vtkVector.h>
#include <QThread>

#include <thread>
#include <chrono>

using namespace camitk;

// --------------- Constructor -------------------
ShowMeshIn2DSlice::ShowMeshIn2DSlice(ActionExtension * extension) : Action(extension) {
    // Setting name, description and input component
    setName("Show Mesh in 2D Slice");
    setDescription("Project the mesh in the 2D slice viewer");
    setComponent("Component");

    // Setting classification family and tags
    setFamily("TDM2I");
    addTag("Projection");
    addTag("Contour");
    addTag("Cutter");

    // size of the contour
    Property *contourSize = new Property("Contour Line Width", 1.0, "Line width of the contour", "mm");
    contourSize->setAttribute("minimum", 0.0);
    contourSize->setAttribute("singleStep",0.25);
    contourSize->setAttribute("decimals", 2);
    addParameter(contourSize);

    // init the status
    isVisible = false;
    mesh = nullptr;
    targetImage = nullptr;
    informationFrame = nullptr;
    

}


// --------------- destructor -------------------
ShowMeshIn2DSlice::~ShowMeshIn2DSlice() {
    // Do not do anything yet.
    // Delete stuff if you created stuff
    // (except if you use smart pointers of course !!)
}

// --------------- getWidget -------------------
QWidget* ShowMeshIn2DSlice::getWidget() {
    MeshComponent * inputMesh = nullptr;
    ImageComponent * inputImage = nullptr;

    QListIterator<Component*> it(getTargets());
    // start from the end
    it.toBack();

    // update target data
    Component *inputComponent;
    while (it.hasPrevious() || (!inputImage && !inputComponent)) {
        inputComponent = it.previous();
        if (!inputMesh && dynamic_cast<MeshComponent *>(inputComponent)) {
            inputMesh = dynamic_cast<MeshComponent *>(inputComponent);
            inputMesh->setTransformTranslation(50, 130, 90);
        }
        else {
            if (!inputImage && dynamic_cast<ImageComponent*>(inputComponent)) {
                inputImage = dynamic_cast<ImageComponent*>(inputComponent);
               // inputImage->setTransformTranslation(-80, 130, 1160);
            }
        }
    }

    if (!inputMesh || !inputImage) {
        CAMITK_WARNING("ShowMeshIn2DSlice", "getWidget", "Cannot apply action: please select at least one mesh and one image.");
        Application::showStatusBarMessage("ShowMeshIn2DSlice: cannot apply action: please select at least one mesh and one image.");
        return nullptr;
    }

    // check if the current image is still the same
    if (inputMesh != mesh) {
        targetImage = inputImage;
        if (mesh!=nullptr && isVisible) {
            // hide
            toggleShowContour();
        }
        // update mesh
        mesh = inputMesh;
        // make sure to remove the contour of the renderer screen if the components die
        connect(mesh, SIGNAL(destroyed()), this, SLOT(cleanUp()));
        connect(targetImage, SIGNAL(destroyed()), this, SLOT(cleanUp()));
        // show the contour
        toggleShowContour();
    }

    
        // create widget
    if (!informationFrame) {
        //-- the frame
        informationFrame = new QFrame();
        informationFrame->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
        informationFrame->setLineWidth(3);

        //-- the vertical layout, put every GUI elements in it
        QVBoxLayout* informationFrameLayout = new QVBoxLayout();

        // add the default action widget
        informationFrameLayout->addWidget(Action::getWidget());

        QLabel* label = new QLabel();
        label->setText(QString("Mesh: ") + mesh->getName() + QString(", image: ") + targetImage->getName());
        informationFrameLayout->addWidget(label);

        QPushButton* toggleButton = new QPushButton("Toggle Contour");
        informationFrameLayout->addWidget(toggleButton);
        toggleButton->setCheckable(true);
        toggleButton->setChecked(true);
        QObject::connect(toggleButton, SIGNAL(toggled(bool)), this, SLOT(toggleShowContour()));

        //-- set the layout for the action widget
        informationFrame->setLayout(informationFrameLayout);
    }

    return informationFrame;
}

// --------------- apply -------------------
Action::ApplyStatus ShowMeshIn2DSlice::apply() {

    // update the property of all actors
    foreach (vtkSmartPointer<vtkActor> contourActor, contourActorMap) {
        contourActor->GetProperty()->SetLineWidth(property("Contour Line Width").toDouble());
    }
    foreach (vtkSmartPointer<vtkActor> contourActorIn2DViewer, contourActorIn2DViewerMap) {
        contourActorIn2DViewer->GetProperty()->SetLineWidth(property("Contour Line Width").toDouble());
    }
    deplacer();
    Application::refresh();

    return SUCCESS;
}

// --------------- cleanUp -------------------
void ShowMeshIn2DSlice::cleanUp() {
    if (isVisible)
        toggleShowContour();
}

// --------------- getNewPlane -------------------
vtkSmartPointer< vtkPlane > ShowMeshIn2DSlice::getNewPlane(Slice::SliceOrientation orientation) {
    //-- Create a plane to cut
    vtkSmartPointer<vtkPlane> cuttingPlane = vtkSmartPointer<vtkPlane>::New();

    // Compute orientation of the image volume
    double normalVector[3];
    normalVector[0] = normalVector[1] = normalVector[2] = 0.0;
    double originVector[3];
    targetImage->getTransformFromWorld()->TransformPoint(normalVector, originVector);

    // Correct the normal vector
    // For instance, axial slices are the XY direction -> XY direction has a plan normal = (0,0,1)
    normalVector[getOrientationIndex(orientation)] = 1.0;

    // transform XY plane from world to image frame
    double normalVectorInWorldFrame[3];
    targetImage->getTransformFromWorld()->TransformPoint(normalVector, normalVectorInWorldFrame);

    // remove origin translation to only get the new orientation
    for (int i=0; i<3; i++) {
        normalVectorInWorldFrame[i] -= originVector[i];
    }
    cuttingPlane->SetNormal(normalVectorInWorldFrame);

    return cuttingPlane;
}

// --------------- getOrientationIndex -------------------
int ShowMeshIn2DSlice::getOrientationIndex(Slice::SliceOrientation orientation) {
    switch(orientation) {
    case Slice::SAGITTAL:
        return 0;
        break;
    case Slice::CORONAL:
        return 1;
        break;
    case Slice::AXIAL:
    default:
        return 2;
        break;
    }
}

// --------------- getVoxelSize -------------------
double ShowMeshIn2DSlice::getVoxelSize(Slice::SliceOrientation orientation) {
    double voxelSize[3];
    targetImage->getImageData()->GetSpacing(voxelSize);
    return voxelSize[getOrientationIndex(orientation)];
}

// --------------- getNewActor -------------------
vtkSmartPointer<vtkActor> ShowMeshIn2DSlice::getNewActor(Slice::SliceOrientation orientation) {
    vtkSmartPointer<vtkActor> newActor = vtkSmartPointer<vtkActor>::New();
    // set rgb components to mach the color of the current orientation (blue=axial, green=coronal, red=sagittal)
    double color[3];
    color[0] = color[1] = color[2] = 0.3;
    color[getOrientationIndex(orientation)] = 1.0;
    newActor->GetProperty()->SetColor(color);
    // width of the contour is defined by the user
    newActor->GetProperty()->SetLineWidth(property("Contour Line Width").toDouble());
    // set the input mapper
    newActor->SetMapper(cutterMapperMap.value(orientation));
    // remove lightning effect for better visibility
    newActor->GetProperty()->LightingOff();
    return newActor;
}




// -----------------------------------------------------



// --------------- toggleShowContour -------------------
void ShowMeshIn2DSlice::toggleShowContour() {

    if (!isVisible) {

        //-- create the cutting planes
        cuttingPlaneMap.insert(Slice::AXIAL, getNewPlane(Slice::AXIAL));
        cuttingPlaneMap.insert(Slice::SAGITTAL, getNewPlane(Slice::SAGITTAL));
        cuttingPlaneMap.insert(Slice::CORONAL, getNewPlane(Slice::CORONAL));
        // TODO
        
        // TODO
        

        //-- set the position of the plane depending on the current slice
        updateCuttingPlane();

        //-- Always use the mesh surface (i.e., a vtkPolyData)
        // A mesh can be a vtkUnstructuredGrid, vtkPolyData or vtkStructuredGrid
        // If the mesh is an unstructured or structured grid, the outside surface is needed to
        // get the contour. In this cases a convertion to polydata is needed
        vtkSmartPointer<vtkGeometryFilter> geometryFilter;
        bool convertedToPolyData = mesh->getPointSet()->IsA("vtkUnstructuredGrid") || mesh->getPointSet()->IsA("vtkStructuredGrid");
        if (convertedToPolyData) {
            geometryFilter = vtkSmartPointer<vtkGeometryFilter>::New();
            geometryFilter->SetInputData(mesh->getPointSet());
        }

        //-- Transform the mesh to the world frame
        vtkSmartPointer<vtkTransformPolyDataFilter> transformPolyDataFilter = vtkTransformPolyDataFilter::New();
        transformPolyDataFilter->SetTransform(mesh->getTransformFromWorld());
        if (convertedToPolyData) {
            transformPolyDataFilter->SetInputConnection(geometryFilter->GetOutputPort());
        }
        else {
            transformPolyDataFilter->SetInputData(mesh->getPointSet());
        }

        //-- create the actual cutters mappers and actors for each plane
        QMapIterator<camitk::Slice::SliceOrientation, vtkSmartPointer<vtkPlane>> it(cuttingPlaneMap);
        while (it.hasNext()) {
            it.next();
            //-- Create the contour using a cutter
            // the cutter filter is the algorithm that build the contour from two inputs: the mesh and cuttingPlane
            vtkSmartPointer<vtkCutter> cutter = vtkSmartPointer<vtkCutter>::New();
            cutter->SetCutFunction(cuttingPlaneMap.value(it.key()));
            // use the position +/- 1% of the voxelSize
            cutter->SetValue(0.0,0.0);
            cutter->SetInputConnection(transformPolyDataFilter->GetOutputPort());
            cutter->Update();

            //-- create a 3D representation (actor)
            vtkSmartPointer<vtkPolyDataMapper> cutterMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
            cutterMapper->SetInputConnection(cutter->GetOutputPort());
            // add the mapper to the corresponding map
            cutterMapperMap.insert(it.key(),cutterMapper);

            // create a new actor
            vtkSmartPointer<vtkActor> contourActor = getNewActor(it.key());
            // add the actor to the corresponding map
            contourActorMap.insert(it.key(), contourActor);

            //-- add the actor to the 3D viewer in order to see the actual contour position
            InteractiveViewer::get3DViewer()->getRendererWidget()->addProp(contourActor,true);

            //-- for the 2D slice viewer, the contour needs to be transformed back to the world frame
            //   otherwise, if the image is not in the same frame, it won't be visible
            // NOTE : the 2D actor ALSO needs to be translated a little bit offside the slice plane
            // otherwise it won't be visible (this is a display trick and does not change
            // the inner data)
            // Get a new contour actor
            vtkSmartPointer<vtkActor> contourActorIn2DViewer = getNewActor(it.key());
            // add the actor to the corresponding map
            contourActorIn2DViewerMap.insert(it.key(), contourActorIn2DViewer);
            // Compute the transform
            vtkSmartPointer<vtkMatrix4x4> displayTranformIn2D = vtkSmartPointer<vtkMatrix4x4>::New();
            // get the transform from the image to the world (inverse of what getTransformFromWorld gives)
            targetImage->getTransformFromWorld()->GetInverse(displayTranformIn2D);
            double offsetFactor = 0.0;
            switch(it.key()) {
            case Slice::SAGITTAL:
                // for sagittal, more tricky: add 0.1*getVoxelSize()
                offsetFactor = 1.0;
                break;
            case Slice::CORONAL:
            case Slice::AXIAL:
                // for coronal and axial, remove 0.1*getVoxelSize() in the orientation direction
                offsetFactor = -1.0;
                break;
            default:
                break;
            }
            int orientationIndex = getOrientationIndex(it.key());
            // compute the "slightly" out of plane transform
            double translationInSlice = displayTranformIn2D->GetElement(orientationIndex,3) + offsetFactor*getVoxelSize(it.key())/10.0;
            displayTranformIn2D->SetElement(orientationIndex,3,translationInSlice);
            contourActorIn2DViewer->SetUserMatrix(displayTranformIn2D);

            //-- finally add this actor to the 2D viewer
            getViewer(it.key())->getRendererWidget()->addProp(contourActorIn2DViewer,true);
            //@DEBUG show the displaced actor in 3D
            //InteractiveViewer::get3DViewer()->getRendererWidget()->addProp(contourActorIn2DViewer,true);
        }

        //-- make sure to be notified when the user change the slice
        QObject::connect(InteractiveViewer::getAxialViewer(), SIGNAL(selectionChanged()), this, SLOT(updateCuttingPlane()));
        QObject::connect(InteractiveViewer::getCoronalViewer(), SIGNAL(selectionChanged()), this, SLOT(updateCuttingPlane()));
        QObject::connect(InteractiveViewer::getSagittalViewer(), SIGNAL(selectionChanged()), this, SLOT(updateCuttingPlane()));

        // @DEBUG this can be an option (get the contour as a mesh)
        //new MeshComponent(cutter->GetOutput(), mesh->getName()+"contour");

        // @DEBUG check where is the axial camera
        //#include <vtkCameraActor.h>
        //vtkSmartPointer<vtkCameraActor> cameraActor = vtkSmartPointer<vtkCameraActor>::New();
        //cameraActor->SetCamera(InteractiveViewer::getAxialViewer()->getRendererWidget()->getActiveCamera());
        //InteractiveViewer::get3DViewer()->getRendererWidget()->addProp(cameraActor);
    }
    else {
        //-- do not notify this action anymore
        QObject::disconnect(InteractiveViewer::getAxialViewer(), SIGNAL(selectionChanged()), this, SLOT(updateCuttingPlane()));
        QObject::disconnect(InteractiveViewer::getCoronalViewer(), SIGNAL(selectionChanged()), this, SLOT(updateCuttingPlane()));
        QObject::disconnect(InteractiveViewer::getSagittalViewer(), SIGNAL(selectionChanged()), this, SLOT(updateCuttingPlane()));

        //-- remove the actors from the viewers
        foreach (vtkSmartPointer<vtkActor> contourActor, contourActorMap) {
            InteractiveViewer::get3DViewer()->getRendererWidget()->removeProp(contourActor);
        }
        QMapIterator<camitk::Slice::SliceOrientation, vtkSmartPointer<vtkActor>> it(contourActorIn2DViewerMap);
        while (it.hasNext()) {
            it.next();
            getViewer(it.key())->getRendererWidget()->removeProp(it.value());
        }

    }

    // toggle state and refresh
    isVisible = !isVisible;
    Application::refresh();

}

void ShowMeshIn2DSlice::deplacer(){
        
        
    int x = 0;
    int y = 30;
    int z = 0;
    
    double x1 = 0;
    double y1 = 0;
    double z1 = -42.12;
    
    mesh->translate(x,y,z);
    mesh->rotate(x1,y1,z1);
    
}




// --------------- updateCuttingPlane -------------------
void ShowMeshIn2DSlice::updateCuttingPlane(Slice::SliceOrientation orientation) {
    // Note: Image origin convention indicates that the origin of the image is centered
    // on the first top left corner pixel
    // -> therefore image slices are displayed with a little shift of 0.5*voxelSize[i]
    // BUT that is only for the planar coordinates (the slice 0 is still at 0, not at 0.5*voxelSize[getOrientationIndex()]
    // Nothing has to be done in the direction perpendicular to the orientation
    //
    // The position of the current slice plane in the image frame (positionInImageFrame) is:
    // position of the image origin (0,0,0) + translation to the current slice
    //
    // The translation to the current slice is equal to:
    // index of the current slice in the considered orientation * slice thickness in this direction
    //
    // The translation to the current slice therefore depends on the current orientation

    //-- Starts at origin
    double positionInImageFrame[3];
    positionInImageFrame[0] = positionInImageFrame[1] = positionInImageFrame[2] = 0.0;

    //-- Add the proper translation to the current selected slice plane
    // Get the current slice from the proper orientation
    SingleImageComponent *orientationSlices = nullptr;
    switch(orientation) {
    case Slice::SAGITTAL:
        orientationSlices = targetImage->getSagittalSlices();
        break;
        // TODO
        
    case Slice::CORONAL:
        orientationSlices = targetImage->getCoronalSlices();
        break;
        // TODO
        
    case Slice::AXIAL:
    default:
        orientationSlices = targetImage->getAxialSlices();
        break;
    }

    if (orientationSlices) {
        positionInImageFrame[getOrientationIndex(orientation)] += orientationSlices->getSlice()*getVoxelSize(orientation);

        //-- transform this position from the image frame in world coordinates
        double currentSlicePos[3];
        targetImage->getTransformFromWorld()->TransformPoint(positionInImageFrame, currentSlicePos);

        //-- update the cutting plane
        cuttingPlaneMap.value(orientation)->SetOrigin(currentSlicePos);
    }
}

void ShowMeshIn2DSlice::updateCuttingPlane() {
    if (isVisible) {
        // -- update all orientation planes
        updateCuttingPlane(Slice::AXIAL);
        updateCuttingPlane(Slice::SAGITTAL);
        updateCuttingPlane(Slice::CORONAL);
        // TODO
        
        // TODO
        
    }
}

// --------------- getViewer -------------------
InteractiveViewer* ShowMeshIn2DSlice::getViewer(Slice::SliceOrientation orientation) {
    switch(orientation) {
    case Slice::SAGITTAL:
        return InteractiveViewer::getSagittalViewer();
        break;
        // TODO
        
    case Slice::CORONAL:
        return InteractiveViewer::getCoronalViewer();
        break;
        // TODO
        
    case Slice::AXIAL:
        return InteractiveViewer::getAxialViewer();
        break;
    default:
        break;
    }
    return nullptr;
}
