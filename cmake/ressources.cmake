# Dossier où copier les ressources
set(RESSOURCE_DIR "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}")

# On supprime l'éventuel dossier ressources existant
file(REMOVE_RECURSE "${RESSOURCE_DIR}/ressources")

# On copie le dossier ressources
file(COPY "ressources" DESTINATION "${RESSOURCE_DIR}")