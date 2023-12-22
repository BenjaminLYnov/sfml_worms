cmake_minimum_required(VERSION 3.10)

# Nom du projet
project(Worms)

# Inclure les sous-dossiers
add_subdirectory(Worms)
add_subdirectory(SfmlEngine)

# Définir Worms comme projet de démarrage
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Worms)