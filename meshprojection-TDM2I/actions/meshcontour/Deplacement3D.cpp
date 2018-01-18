// CamiTK includes
#include "Deplacement3D.h"
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
#include <QTimer>

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
    setDescription("Move a mesh  following coordonnees give in a .pol file");
    setComponent("Component");
    
    informationFrame = nullptr;
    actualLine = 0;
    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(moveTool()));

}


// --------------- destructor -------------------
Deplacement3D::~Deplacement3D() {
    // Do not do anything yet.
    // Delete stuff if you created stuff
    // (except if you use smart pointers of course !!)
}


// --------------- getWidget -------------------

QWidget* Deplacement3D::getWidget() {
    MeshComponent * inputMesh = nullptr;
    ComponentProjet * inputPol = nullptr;

    QListIterator<Component*> it(getTargets());
    // start from the end
    it.toBack();

    // update target data
    Component *inputComponent;
    while (it.hasPrevious() || (!inputPol && !inputComponent)) {
        inputComponent = it.previous();
        if (!inputMesh && dynamic_cast<MeshComponent *>(inputComponent)) {
            inputMesh = dynamic_cast<MeshComponent *>(inputComponent);
        }
        else {
            if (!inputPol && dynamic_cast<ComponentProjet*>(inputComponent)) {
                inputPol = dynamic_cast<ComponentProjet*>(inputComponent);
            }
        }
    }

    if (!inputMesh || !inputPol) {
        CAMITK_WARNING("Déplacement 3D", "getWidget", "Cannot apply action: please select at least one mesh and one .pol");
        Application::showStatusBarMessage("Déplacement 3D : cannot apply action: please select at least one mesh and one .pol");
        return nullptr;
    }

    // check if the current image is still the same
    if (inputMesh != mesh) {
        targetPol = inputPol;
        // update mesh
        mesh = inputMesh;
        
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
        label->setText(QString("Mesh: ") + mesh->getName() + QString(", Image: ") + targetPol->getName());
        informationFrameLayout->addWidget(label);

        //-- set the layout for the action widget
        informationFrame->setLayout(informationFrameLayout);
    }

    return informationFrame;
}

void Deplacement3D::moveTool()
{
    double *coordonnees; //tableau contenant 6 doubles
    double tx, ty, tz, rx, ry, rz;
    if(actualLine<targetPol->getSize()){
        coordonnees = targetPol->getCoordonnees(actualLine);
        tx = coordonnees[0];
        ty = coordonnees[1];
        tz = coordonnees[2];
        rx = coordonnees[3];
        ry = coordonnees[4];
        rz = coordonnees[5];      
        mesh->setTransformTranslation(tx, ty, tz);
        mesh->setTransformRotation(rx, ry, rz);
        Application::refresh();
        timer->start(targetPol->getTime(actualLine));
        actualLine = actualLine+1;
    }else{
        timer->stop();
        actualLine = 0;
    }
}


Action::ApplyStatus Deplacement3D::apply()
{
    timer->start(0);
    return SUCCESS;
}



       
