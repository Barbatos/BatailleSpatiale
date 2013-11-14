# Dossier où copier les ressources
SET(RESSOURCE_DIR ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})

# On supprime l'éventuel dossier ressources existant
FILE(REMOVE_RECURSE ${RESSOURCE_DIR}/ressources)

# On copie le dossier ressources
FILE(COPY ressources DESTINATION ${RESSOURCE_DIR})