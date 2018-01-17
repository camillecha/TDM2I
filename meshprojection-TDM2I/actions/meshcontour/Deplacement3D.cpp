// CamiTK includes
#include "Deplacement3D.h"
#include <Property.h>
#include <Application.h>
#include <InteractiveViewer.h>
#include "ComponentProjet.h"

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

#include <chrono>
#include <thread>

using namespace camitk;

// --------------- Constructor -------------------
Deplacement3D::Deplacement3D(ActionExtension * extension) : Action(extension) {
    // Setting name, description and input component
    setName("Deplacement 3D");
    setFamily("TDM2I");
    setDescription("Project the mesh in the 2D slice viewer");
    setComponent("Component");
    
    /*
    double coordonnees[6]; //tableau contenant 6 doubles
    int temps;
    double tx, ty, tz, rx, ry, rz;
    
    for (int i = 0; i < getSize(); i++){
        coordonnees = getCoordonnees(i);
        tx = coordonnees[0];
        ty = coordonnees[1];
        tz = coordonnees[2];
        rx = coordonnees[3];
        ry = coordonnees[4];
        rz = coordonnees[5];      
        temps = getTime(i);
        //Component->setTransformTranslationVTK(tx, ty, tz);
       // Component->setTransformRotationVTK(rx, ry, rz);
        sleep_for(nanoseconds(temps));
    }
    */

}


// --------------- destructor -------------------
Deplacement3D::~Deplacement3D() {
    // Do not do anything yet.
    // Delete stuff if you created stuff
    // (except if you use smart pointers of course !!)
}


// --------------- getWidget -------------------
/*
QWidget* Deplacement3D::getWidget() {
    MeshComponent * inputMesh = nullptr;
    MeshComponent * inputMesh2 = nullptr;

    QListIterator<Component*> it(getTargets());
    // start from the end
    it.toBack();

    // update target data
    Component *inputComponent;
    while (it.hasPrevious() || (!inputMesh2 && !inputComponent)) {
        inputComponent = it.previous();
        if (!inputMesh && dynamic_cast<MeshComponent *>(inputComponent)) {
            inputMesh = dynamic_cast<MeshComponent *>(inputComponent);
        }
        else {
            if (!inputMesh2 && dynamic_cast<MeshComponent*>(inputComponent)) {
                inputMesh2 = dynamic_cast<MeshComponent*>(inputComponent);
            }
        }
    }

    if (!inputMesh || !inputMesh2) {
        CAMITK_WARNING("ShowMeshIn2DSlice", "getWidget", "Cannot apply action: please select at least two meshes");
        Application::showStatusBarMessage("ShowMeshIn2DSlice: cannot apply action: please select at least two meshes");
        return nullptr;
    }

    // check if the current image is still the same
    if (inputMesh != mesh) {
        targetMesh = inputMesh2;
        if (mesh!=nullptr && isVisible) {
            // hide
            toggleShowContour();
        }
        // update mesh
        mesh = inputMesh;
        // make sure to remove the contour of the renderer screen if the components die
        connect(mesh, SIGNAL(destroyed()), this, SLOT(cleanUp()));
        connect(targetMesh, SIGNAL(destroyed()), this, SLOT(cleanUp()));
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
        label->setText(QString("Mesh: ") + mesh->getName() + QString(", Mesh2: ") + targetMesh->getName());
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
*/

Action::ApplyStatus Deplacement3D::apply()
{
    return SUCCESS;
}
