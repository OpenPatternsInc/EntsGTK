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

#ifndef ENTS_INTERFACE_INTERFACE_H
#define ENTS_INTERFACE_INTERFACE_H

#include "Includes.h"
#include "Ent.h"
#include "Root.h"
#include "Tree.h"
#include "Snapshot.h"
#include "IO.h"
#include "EntryResult.h"
#include "AbstractInterface.h"
#include "Loader.h"
#include <vector>
#include <string>
#include <memory>
#include <future>

namespace ents_interface {

    enum class get_string_return {GOT_STRING, NO_INPUT};

    enum class create_tree_exception {CREATE_SUCCESS, USER_CANCEL_CREATE, NO_NAME, CREATE_UNKNOWN_ERROR};

    class Interface : public AbstractInterface {

        //Do we make ents_interface::Tree to have private constructors?
        //Then we can make ents_interface::Interface a friend class.
        //Then the derived subclass won't be able to create them without going
        //through the protected functions of this class.

    private:

        //Don't keep a copy of the Tree instances here.
        //Instead, we will use a unique_ptr to hold the instances and pass them
        //to the UI elements which will own them.

        /**
         * This is a temporary way to store an Ent which may be renamed later... spaghetti code...
         */
        Ent renameCandidate;

        //Make all this stuff public for now...
    public:

        Tree tree;

        Snapshot snapshot;

        Interface();

        // Virtual Destructor

        virtual ~Interface() = default;

        void initializeIO();


        /* Virtual functions that are implementation-specific.
         * Therefore, the idea is to interface with a Tree by deriving a class
         * from the given class Interface. This derivation comes with pure
         * virtual functions which must be implemented by the Interface subclass.
         *
         *
         */


        virtual void getStringFromUser(const std::string& message, void (Interface:: *afterFunction)(const EntryResult&)) = 0;

        void createNewTree();

        void saveTree();

        void selectAndOpenTree();

        //void saveTreeWithHandle(EntryResult entryResult);

        void newTreeFromName(const EntryResult& entryResult);


        void newEntUnderFocus();

        void addParentToFocus(const Ent& ent);

        void addChildToFocus(Ent ent);

        void addOverlapToFocus(const Ent& ent);

        void addDisjointToFocus(const Ent& ent);

        void newEntUnderFocusCallback(const EntryResult& entryResult);

        virtual void openTree(Tree&& treeToOpen) = 0;

        void renameFocus();

        void renameEnt(Ent ent);

        void rename(const EntryResult& entryResult);

        Ent getFocus() {
            return snapshot.focus;
        }

        void setFocus(const ents_interface::Ent& newFocus);

        void reloadSnapshot() {

            snapshot = Snapshot::generate(getFocus());

        }


        /**
         * Called when something has changed. Perhaps the UI would like to redraw or something.
         */
        void notifyChange();

        virtual void notifyUIChange() = 0;


    };



}



#endif /* ENTS_INTERFACE_INTERFACE_H */

