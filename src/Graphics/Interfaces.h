/*
 * This file is part of the Ents Hierarchy Database Project.
 * Copyright (C) 2019 OpenPatterns and Jason Stockwell.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ENTSGUI_INTERFACES_H
#define ENTSGUI_INTERFACES_H

#include "Includes.h"

/**
 * This Header creates the basic prototypes for the GUI components, and extends them with public interfaces.
 */

namespace ents_gui {



    class AppPrototype {};

    class ExplorerPrototype : public ents_interface::Interface, public virtual opgui::Window {};

    class ListPrototype : public ents_interface::List, public virtual opgui::StringList<ents_interface::Interface, ents_interface::Ent> {};

    class EntryWindowPrototype : public virtual opgui::Window {};




    class ListInterface : public ListPrototype {

    public:

        virtual void update(ents_interface::List list) = 0;

    };


    /**
     * This is a pure virtual class containing the functions which need to be implemented by the
     * derived subclasses for the particular GUI library.
     *
     * By declaring this interface first, we allow all areas of source code to access these functions of derived classes.
     */
    class ExplorerInterface : public ExplorerPrototype {


    public:

        //virtual void openTree(std::shared_ptr<ents_interface::Tree> treeToOpen) = 0;

        virtual void closeTree() = 0;

        virtual void createEntryWindow(const std::string& message, void (ents_interface::Interface:: *afterFunction)(const ents_interface::EntryResult&)) = 0;

        /**
         * Force the subclass to implement the code to set up a new List, and return a pointer to it.
         */
        virtual ListInterface* initializeNewList() = 0;

    };


    class EntryWindowInterface : public EntryWindowPrototype {

    public:

        virtual std::string getText() = 0;

        virtual void setMessage(std::string message) = 0;

    };


    /**
     * This public interface is for the App class.
     */
    class AppInterface : public AppPrototype {

    public:

        virtual ~AppInterface() = default;

        virtual void quit() = 0;

        //TODO Change the raw Tree pointer to unique?
        virtual void requestOpenNewExplorer(std::shared_ptr<ents_interface::Tree> treeToExplore) = 0;
        /**
         * Force the derived class to define how to initialize itself. It must initialize the Explorer
         * implementation, and get it running.
         */
        virtual void init() = 0;
    };


}







#endif //ENTSGUI_INTERFACES_H
