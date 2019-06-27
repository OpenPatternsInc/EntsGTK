cmake_minimum_required(VERSION 3.14)
project(Ents VERSION 0.1.0 DESCRIPTION "Ents Hierarchy Database C++ project with GTK UI" HOMEPAGE_URL "http://www.openpatterns.net/" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(Ents src/main.cpp src/Root/Ent.cpp src/Root/Ent.h src/Root/Root.cpp src/Root/Root.h src/Root/Tree.cpp src/Root/Tree.h src/Root/Leaf.cpp src/Root/Leaf.h src/Root/Headers.h src/Interface/Ent.cpp src/Interface/Ent.h src/Interface/Includes.h src/Interface/AbstractInterface.cpp src/Interface/AbstractInterface.h src/Interface/EntryResult.cpp src/Interface/EntryResult.h src/Interface/Headers.h src/Interface/Interface.cpp src/Interface/Interface.h src/Interface/IO.cpp src/Interface/IO.h src/Interface/List.cpp src/Interface/List.h src/Interface/Loader.cpp src/Interface/Loader.h src/Interface/Root.cpp src/Interface/Root.h src/Interface/Snapshot.cpp src/Interface/Snapshot.h src/Interface/Tree.cpp src/Interface/Tree.h src/OPGraphics/ListItem.cpp src/OPGraphics/ListItem.h src/OPGraphics/MenuInterface.cpp src/OPGraphics/MenuInterface.h src/OPGraphics/Point.cpp src/OPGraphics/Point.h src/OPGraphics/PopupItem.cpp src/OPGraphics/PopupItem.h src/OPGraphics/PopupMenu.cpp src/OPGraphics/PopupMenu.h src/OPGraphics/StringList.cpp src/OPGraphics/StringList.h src/OPGraphics/StringListInterface.h src/OPGraphics/Window.cpp src/OPGraphics/Window.h src/OPGTK/PopupMenu.cpp src/OPGTK/PopupMenu.h src/OPGTK/StringList.cpp src/OPGTK/StringList.h src/OPGTK/Window.cpp src/OPGTK/Window.h src/OPGTK/Includes.h src/OPGraphics/Headers.h src/OPGTK/Headers.h src/Graphics/App.cpp src/Graphics/App.h src/Graphics/EntContextMenu.cpp src/Graphics/EntContextMenu.h src/Graphics/EntryWindow.cpp src/Graphics/EntryWindow.h src/Graphics/Explorer.cpp src/Graphics/Explorer.h src/Graphics/ExplorersHandler.cpp src/Graphics/ExplorersHandler.h src/Graphics/List.cpp src/Graphics/List.h src/Graphics/Headers.h src/Graphics/Includes.h src/Graphics/Interfaces.h src/Explorer/App.cpp src/Explorer/App.h src/Explorer/Controller.cpp src/Explorer/Controller.h src/Explorer/EntContextMenu.cpp src/Explorer/EntContextMenu.h src/Explorer/EntryWindow.cpp src/Explorer/EntryWindow.h src/Explorer/Explorer.cpp src/Explorer/Explorer.h src/Explorer/Includes.h src/Explorer/List.cpp src/Explorer/List.h src/Explorer/OpenerHelper.cpp src/Explorer/OpenerHelper.h)

##Need to add the C++ Standard Library FileSystem manually.
target_link_libraries(${CMAKE_PROJECT_NAME} stdc++fs)

##Add support for gtkmm (GTK with C++ bindings)
find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)
include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})
target_link_libraries(${CMAKE_PROJECT_NAME} ${GTKMM_LIBRARIES})

##Multithread support from pthread style threads in Standard Library
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")