# Les composants de la SFML
SET(SFML_COMPONENTS audio graphics window system network)

# On lie la SFML de façon dynamique ou pas
OPTION(SFML_STATIC_LIBRARIES "Lier la SFML de façon statique" OFF)

IF(WIN32)
    LIST(APPEND SFML_COMPONENTS main)
    
    # On ajoute quelques chemins au dossier où findSFML va chercher
    # selon que la SFML soit liée statiquement ou non
    IF(SFML_STATIC_LIBRARIES)
        LIST(APPEND SFML_ROOT
            "C:/SFML-Static"
            "C:/Program Files/SFML-Static"
            "C:/Program Files (x86)/SFML-Static"
            "D:/SFML")
    ELSE()
        LIST(APPEND SFML_ROOT
            "C:/SFML"
            "C:/Program Files/SFML"
            "C:/Program Files (x86)/SFML"
            "D:/SFML")
    ENDIF()
endif()

# On tente de trouver la SFML
FIND_PACKAGE(SFML 2 COMPONENTS ${SFML_COMPONENTS})

# Si elle est trouvée
IF(SFML_FOUND)
    # On inclut les headers
    INCLUDE_DIRECTORIES(${SFML_INCLUDE_DIR})
    # On inclut les librairies
    LINK_DIRECTORIES(${SFML_LIBRARY_DIRS})
ENDIF()