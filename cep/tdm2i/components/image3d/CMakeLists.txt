# Call CamiTK CMake Macro to define the component
camitk_extension(   COMPONENT_EXTENSION
                    DEFAULT
                    INSTALL_ALL_HEADERS
                    DESCRIPTION "Coordonnees de point permettant l'affichage en 3D."
                    
                    NEEDS_CEP_LIBRARIES librarytdm2i 
                    
                    
                )

