# Les composants de la SFML
set(SFML_COMPONENTS audio graphics window system network)

# On lie la SFML de façon dynamique ou pas
option(SFML_STATIC_LIBRARIES "Lier la SFML de façon statique" OFF)

if(WIN32)
    list(APPEND SFML_COMPONENTS main)
    
    # On ajoute quelques chemins au dossier où findSFML va chercher
    # selon que la SFML soit liée statiquement ou non
    if(SFML_STATIC_LIBRARIES)
        list(APPEND SFML_ROOT
            "C:/SFML-Static"
            "C:/Program Files/SFML-Static"
            "C:/Program Files (x86)/SFML-Static"
            "D:/SFML")
    else()
        list(APPEND SFML_ROOT
            "C:/SFML"
            "C:/Program Files/SFML"
            "C:/Program Files (x86)/SFML"
            "D:/SFML")
    endif()
endif()

# On tente de trouver la SFML
find_package(SFML 2 COMPONENTS ${SFML_COMPONENTS})

# Si elle est trouvée
if(SFML_FOUND)
    # On inclut les headers
    include_directories(${SFML_INCLUDE_DIR})
endif()