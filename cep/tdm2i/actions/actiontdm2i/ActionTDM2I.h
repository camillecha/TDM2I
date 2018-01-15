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


#ifndef ACTIONTDM2I_H
#define ACTIONTDM2I_H

#include <ActionExtension.h>

class ActionTDM2I : public camitk::ActionExtension {
    Q_OBJECT
    Q_INTERFACES(camitk::ActionExtension);
    Q_PLUGIN_METADATA(IID "fr.imag.camitk.wizardgenerated.action.ActionTDM2I")

public:
    /// Constructor
    ActionTDM2I() : ActionExtension() {};

    /// Destructor
    virtual ~ActionTDM2I() {};

    /// Method returning the action extension name
    virtual QString getName() {
        return "actionTDM2I";
    };

    /// Method returning the action extension descrption
    virtual QString getDescription() {
        return "differentes methodes pour la realisation des differents affichage des objets en 3D et 2D.";
    };

    /// initialize all the actions
    virtual void init();

};

#endif // ACTIONTDM2I_H


