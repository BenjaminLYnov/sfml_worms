project(Worms)

# Ajoutez tous les fichiers source et en-tête spécifiques à la bibliothèque  (de manière récursive)
file(GLOB_RECURSE WORMS_SOURCES
    *.cpp
    *.h
)

add_executable(Worms ${WORMS_SOURCES})

# Ajoutez le chemin vers les entêtes
target_include_directories(Worms PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/)

# Lier la bibliothèque SfmlEngine
target_link_libraries(Worms PRIVATE SfmlEngine)

# Inclure le chemin d'inclusion des bibliothèques externe
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib)

# Organisez l'architecture virtuelle pour refléter la structure des fichiers
foreach(_source IN ITEMS ${WORMS_SOURCES})
    get_filename_component(_source_path "${_source}" PATH)
    file(RELATIVE_PATH _source_path_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()

########################################################################################################################
# Dépendances

########################################################################################################################
# SFML
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

target_link_libraries(Worms PRIVATE sfml-graphics)
target_compile_features(Worms PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET Worms
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:Worms>
        VERBATIM)
endif()

install(TARGETS Worms)
########################################################################################################################

