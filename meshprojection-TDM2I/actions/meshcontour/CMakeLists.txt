# Call CamiTK CMake Macro to define the action
camitk_extension(ACTION_EXTENSION
                 DEFAULT
                 INSTALL_ALL_HEADERS
                 DESCRIPTION "Show the contour of the mesh in a given orientation slice"
                 NEEDS_COMPONENT_EXTENSION extcomponent
#                 AUTO_TEST
                 # all files but .frame
#                 TEST_FILES DisplacedMesh.vtk polydata.vtk sinus_skin_decimated_located.obj structuredGrid.vtk
#                            sinus_skin_decimated_located1.vtk sinus_skin_decimated.vtk unstructuredGrid.vtk
)

