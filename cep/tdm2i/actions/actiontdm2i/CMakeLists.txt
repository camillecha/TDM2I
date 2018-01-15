# Call CamiTK CMake Macro to define the action
camitk_extension(   ACTION_EXTENSION
                    DEFAULT
                    INSTALL_ALL_HEADERS
                    DESCRIPTION "differentes methodes pour la realisation des differents affichage des objets en 3D et 2D."
                    
                    NEEDS_CEP_LIBRARIES librarytdm2i 
                    NEEDS_COMPONENT_EXTENSION image3d 
                    
                )

