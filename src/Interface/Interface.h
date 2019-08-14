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

namespace ents_interface {

    /**
     * Return values describing the result of asking the user for a string.
     */
    enum class get_string_return {GOT_STRING, NO_INPUT};

    /**
     * Return values for describing the result of creating a new tree.
     */
    enum class create_tree_exception {CREATE_SUCCESS, USER_CANCEL_CREATE, NO_NAME, CREATE_UNKNOWN_ERROR};

    /**
     * An Interface object implementation is an object which can interact with the user. By implementing virtual functions
     * common to all user interfaces, we can program its behavior abstractly.
     */
    class Interface : public AbstractInterface {

        //Do we make ents_interface::Tree to have private constructors?
        //Then we can make ents_interface::Interface a friend class.
        //Then the derived subclass won't be able to create them without going
        //through the protected functions of this class.

    private:

        //Don't keep a copy of the Tree instances here.
        //Instead, we will use a unique_ptr to hold the instances and pass them
        //to the UI elements which will own them.

        //TODO Remove spaghetti code here
        /**
         * This is a temporary way to store an Ent which may be renamed later...
         */
        Ent renameCandidate;

        //Make all this stuff public for now...
    public:

        /**
         * This is the Tree instance which is being interfaced with through this instance of Interface.
         */
        Tree tree;

        /**
         * When we display information to the user, we take a snapshot of the tree to a certain accuracy. We can
         * then retrieve more information. Temporary snapshot can be used to synchronize access to the tree which may
         * undergo alterations before the next user-request.
         */
        Snapshot snapshot;

        /**
         * Initialize the simple data members.
         *
         * Does nothing at the moment. Most initialization is done in
         */
        Interface();

        /**
         * This virtual destructor will clean up what's needed because it is designed to be used in such a way.
         */
        virtual ~Interface() = default;

        /**
         * Initialize the IO object if needed. Reserved for things which can not be initialized within the constructor.
         */
        void initializeIO();

        /* Virtual functions that are implementation-specific.
         * Therefore, the idea is to interface with a Tree by deriving a class
         * from the given class Interface. This derivation comes with pure
         * virtual functions which must be implemented by the Interface subclass.
         *
         *
         */

        /**
         * Virtual function called when the program needs input from the user.
         * It takes a reference to a string which tells the user what the input is for, and then it will call a function
         * after successful input.
         * @param message
         * @param afterFunction
         */
        virtual void getStringFromUser(const std::string& message, void (Interface:: *afterFunction)(const EntryResult&)) = 0;

        /**
         * Tells the interface to create a new tree. Can be called inside or outside the Interface module.
         */
        void createNewTree();

        /**
         * Saves the current tree being explored to file. Can be called from wherever.
         */
        void saveTree();

        /**
         * Has the user select an existing tree to open.
         */
        void selectAndOpenTree();

        //void saveTreeWithHandle(EntryResult entryResult);

        /**
         * Tells the interface to create a new tree from a certain name and then open it up.
         * @param entryResult
         */
        void newTreeFromName(const EntryResult& entryResult);

        /**
         * Creates a new Ent which is the child of the current focus.
         */
        void newEntUnderFocus();

        /**
         * Takes the selected Ent and connects it as a parent to the current focus.
         * @param ent
         */
        void addParentToFocus(const Ent& ent);

        /**
         * Takes the selected Ent and connects it as a child to the focus.
         * @param ent
         */
        void addChildToFocus(Ent ent);

        /**
         * Takes the selected Ent and connects it as an overlap to the focus.
         * @param ent
         */
        void addOverlapToFocus(const Ent& ent);

        /**
         * Takes the selected Ent and connects it as a disjoint to the focus.
         * @param ent
         */
        void addDisjointToFocus(const Ent& ent);

        //TODO Refactor this all. Callback functions are not needed. Just call a function with a reference as a parameter and return to the calling function.
        /**
         * Called when the user input text for a new Ent to be created with the current focus as a parent.
         * @param entryResult
         */
        void newEntUnderFocusCallback(const EntryResult& entryResult);

        /**
         * Opens a given Tree in the explorer.
         * @param treeToOpen
         */
        virtual void openTree(Tree&& treeToOpen) = 0;

        /**
         * Called when the user needs to rename the current focus.
         */
        void renameFocus();

        /**
         * Called when the user needs to rename a certain ent.
         * @param ent
         */
        void renameEnt(Ent ent);

        //TODO Remove spaghetti code here.
        /**
         * Renames the ent which is saved in renameCandidate.
         * @param entryResult
         */
        void rename(const EntryResult& entryResult);

        /**
         * Returns the current focus.
         * @return
         */
        Ent getFocus() {
            return snapshot.focus;
        }

        /**
         * Sets the new current focus to be the given Ent.
         */
        void setFocus(const ents_interface::Ent& newFocus);

        /**
         * Takes a new snapshot of the tree currently for use later. We save a copy of things so that if the tree changes
         * we don't get any errors.
         */
        void reloadSnapshot() {
            snapshot = Snapshot::generate(getFocus());
        }

        /**
         * Called when something has changed. Perhaps the UI would like to redraw or something.
         */
        void notifyChange();

        /**
         * Pure virtual function. May be implemented if the UI needs to be updated. Not useful for instance for
         * command line interfaces though.
         */
        virtual void notifyUIChange() = 0;

    };

}

#endif /* ENTS_INTERFACE_INTERFACE_H */

