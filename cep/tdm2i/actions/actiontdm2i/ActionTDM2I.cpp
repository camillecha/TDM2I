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


#include "ActionTDM2I.h"

// include generated actions headers
#include "Deplacement3D.h"
#include "Affichage2D.h"
#include "Superpositionimage3D.h"

// --------------- getActions -------------------
void ActionTDM2I::init() {
    // Creating and registering the instance of Deplacement3D
    // Creating and registering the instance of Affichage2D
    // Creating and registering the instance of Superpositionimage3D
    registerNewAction(Deplacement3D);
    registerNewAction(Affichage2D);
    registerNewAction(Superpositionimage3D);
    registerNewAction(LecturePol);
}

