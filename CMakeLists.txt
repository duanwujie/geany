cmake_minimum_required(VERSION 3.14)
project(geany)

set(CMAKE_C_STANDARD 99)



# Use the package PkgConfig to detect GTK+ headers/library files
FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTK3 REQUIRED gtk+-3.0)

# Setup CMake to use GTK+, tell the compiler where to look for headers
# and to the linker where to look for libraries
INCLUDE_DIRECTORIES(${GTK3_INCLUDE_DIRS})
LINK_DIRECTORIES(${GTK3_LIBRARY_DIRS})

# Add other flags to the compiler
ADD_DEFINITIONS(${GTK3_CFLAGS_OTHER})


add_subdirectory(scintilla)

add_subdirectory(ctags)

add_subdirectory(src/tagmanager)

INCLUDE_DIRECTORIES(src/tagmanager)
INCLUDE_DIRECTORIES(scintilla/include)
INCLUDE_DIRECTORIES(scintilla)

ADD_DEFINITIONS(-DGTK)
ADD_DEFINITIONS(-DGEANY_PRIVATE)
ADD_DEFINITIONS(-DG_LOG_DOMAIN="MacEdit")


#pacakge define
ADD_DEFINITIONS(-DPACKAGE="macedit")
ADD_DEFINITIONS(-DVERSION="1.0")
ADD_DEFINITIONS(-DREVISION="326a754")
ADD_DEFINITIONS(-DGEANY_PREFIX="/usr/local")
ADD_DEFINITIONS(-DGEANY_DATADIR="/usr/local/share")
ADD_DEFINITIONS(-DGEANY_LIBDIR="/usr/local/lib")
ADD_DEFINITIONS(-DGEANY_LOCALEDIR="/usr/local/share/locale")
ADD_DEFINITIONS(-DGEANY_DOCDIR="/usr/local/share/doc/geany")
ADD_DEFINITIONS(-DGEANY_LIBEXECDIR="/usr/local/libexec/")


ADD_DEFINITIONS(-DHAVE_SOCKET=1)
ADD_DEFINITIONS(-DUSE_STDBOOL_H=1)


#ADD_DEFINITIONS(-DGEANY_EXPORT_SYMBOL="__attribute__((visibility(\"default\")))")
ADD_DEFINITIONS(-DGEANY_EXPORT_SYMBOL=__attribute__\(\(visibility\(\"default\"\)\)\))
ADD_DEFINITIONS(-DGEANY_API_SYMBOL=GEANY_EXPORT_SYMBOL)

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fvisibility=hidden -Wno-deprecated-declarations")

SET(FlexOutput ${CMAKE_SOURCE_DIR}/src/signallist.i)



ADD_CUSTOM_COMMAND(
        OUTPUT ${FlexOutput}
        COMMAND sh ${CMAKE_SOURCE_DIR}/gen-signal.sh ${CMAKE_SOURCE_DIR}
        COMMENT "signallist.i")


#sed -n 's/^.*handler="\([^"]\{1,\}\)".*$/ITEM(\1)/p' data/geany.glade




set(LIBGEANY_SOURCES src/about.c src/about.h
    src/app.h
    src/build.c src/build.h
    src/callbacks.c src/callbacks.h
    src/dialogs.c src/dialogs.h
    src/document.c src/document.h
    src/editor.c src/editor.h
    src/encodings.c src/encodings.h
    src/filetypes.c src/filetypes.h
    src/geanyentryaction.c src/geanyentryaction.h
    src/geanymenubuttonaction.c src/geanymenubuttonaction.h
    src/geanyobject.c src/geanyobject.h
    src/geanywraplabel.c src/geanywraplabel.h
    src/gtkcompat.h
    src/highlighting.c src/highlighting.h
    src/highlightingmappings.h
    src/keybindings.c src/keybindings.h
    src/keyfile.c src/keyfile.h
    src/log.c src/log.h
    src/libmain.c src/main.h src/geany.h
    src/msgwindow.c src/msgwindow.h
    src/navqueue.c src/navqueue.h
    src/notebook.c src/notebook.h
    src/plugins.c src/plugins.h
    src/pluginutils.c src/pluginutils.h
    src/prefs.c src/prefs.h
    src/printing.c src/printing.h
    src/project.c src/project.h
    src/sciwrappers.c src/sciwrappers.h
    src/search.c src/search.h
    src/socket.c src/socket.h
    src/spawn.c src/spawn.h
    src/stash.c src/stash.h
    src/support.h
    src/symbols.c src/symbols.h
    src/templates.c src/templates.h
    src/toolbar.c src/toolbar.h
    src/tools.c src/tools.h
    src/sidebar.c src/sidebar.h
    src/ui_utils.c src/ui_utils.h
    src/utils.c src/utils.h)


add_library(libgeany STATIC ${LIBGEANY_SOURCES} ${FlexOutput})
target_link_libraries(libgeany scintilla tagmanager)


# Add an executable compiled from hello.c
add_executable(geany src/main.c ${LIBGEANY_SOURCES} ${FlexOutput})
#target_link_libraries(geany libgeany)


# Link the target to the GTK+ libraries
TARGET_LINK_LIBRARIES(geany libgeany m  ${GTK3_LIBRARIES} gmodule-2.0)