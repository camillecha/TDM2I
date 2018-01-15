project(librarytdm2i)

# Call CamiTK CMake Macro to define LibraryTDM2I library
gather_headers_and_sources(LIBRARYTDM2I)

camitk_library( STATIC
		SOURCES ${LIBRARYTDM2I_HEADERS} ${LIBRARYTDM2I_SOURCES} 
                
                
                
                
                DESCRIPTION "Brainshift Navigator librairie"
)

