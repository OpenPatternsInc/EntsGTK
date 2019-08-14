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

#include <filesystem>
#include "Interface.h"

using namespace std;

using namespace ents_interface;



Interface::Interface() {



}

void Interface::initializeIO() {

    //Initialize the IO static class.
    IO io;
    if (io.init(this)) {
        std::cout << "Settings and working directory initialized.\n";
    } else {
        std::cout << "Settings and working directory could not be initialized...\n";
    }


}

//TODO combine EntryResult callback functions so they are combined and check for SUCCESS first, then go to custom.
void Interface::newTreeFromName(const EntryResult& entryResult) {

    if (entryResult.status == EntryResultStatus::SUCCESS) {

        Tree newTree;
        newTree.setName(entryResult.text);
        this->openTree(move(newTree));

    }

    //If it was not a success... just don't do anything.
}

void Interface::renameFocus() {

    renameEnt(snapshot.focus);

}


void Interface::renameEnt(Ent ent) {

    renameCandidate = ent;

    auto message = string("Rename \"").append(ent.raw->name()).append("\" to...");

    getStringFromUser(message, &Interface::rename);


}

void Interface::rename(const EntryResult& entryResult) {

    if (entryResult.status == EntryResultStatus::SUCCESS) {

        renameCandidate.raw->name() = entryResult.text;

        notifyChange();

    }
    //If it was not a success... do nothing.
}




void Interface::newEntUnderFocus() {

    auto message = "Please enter a name for the new Ent.";

    getStringFromUser(message, &Interface::newEntUnderFocusCallback);

}

void Interface::newEntUnderFocusCallback(const ents_interface::EntryResult& entryResult) {

    if (entryResult.status == EntryResultStatus::SUCCESS) {

        tree.newEnt(entryResult.text, snapshot.focus);

        notifyChange();

    }

    //If it was not a success, do nothing...

}

void Interface::addParentToFocus(const Ent& ent) {
    //Connect them as parent and child.
    ents_root::Ent::parentChild(ent.raw, snapshot.focus.raw);

    //Remove the redundant connections.
    auto parents = snapshot.focus.getParents();
    auto parentsToRemove = vector<Ent>();
    for (auto parent : parents) {
        auto children = parent.getChildren();
        for (const auto &child : children) {
            if (child.raw == ent.raw) {
                parentsToRemove.push_back(parent);
            }
        }
    }
    for (auto parent : parentsToRemove) {
        parent.raw->removeChild(snapshot.focus.raw);
        snapshot.focus.raw->removeParent(parent.raw);
    }
    notifyChange();
}

void Interface::addChildToFocus(Ent ent) {
    //Make the new connection.
    ents_root::Ent::parentChild(snapshot.focus.raw, ent.raw);

    //Remove the redundant connections.
    auto parents = ent.getParents();
    auto parentsToRemove = vector<Ent>();
    for (auto parent : parents) {
        auto children = parent.getChildren();
        for (const auto &child : children) {
            if (child.raw == snapshot.focus.raw) {
                parentsToRemove.push_back(parent);
            }
        }
    }
    for (auto parent : parentsToRemove) {
        parent.raw->removeChild(ent.raw);
        ent.raw->removeParent(parent.raw);
    }
    notifyChange();
}

void Interface::addOverlapToFocus(const Ent& ent) {

    ents_root::Ent::overlap(snapshot.focus.raw, ent.raw);
    notifyChange();
}

void Interface::addDisjointToFocus(const Ent& ent) {

    ents_root::Ent::disjoint(snapshot.focus.raw, ent.raw);
    notifyChange();

}



void Interface::createNewTree() {

    //We need a name to call this Tree. Query the user.

    auto message = "Enter a name for the new Tree.";

    getStringFromUser(message, &Interface::newTreeFromName);

}



void Interface::saveTree() {

    tree.save();

}


void Interface::setFocus(const ents_interface::Ent& newFocus) {

    if (snapshot.focus.raw == newFocus.raw)
        return;

    snapshot.focus.raw = newFocus.raw;

    reloadSnapshot();

    notifyChange();
}


void Interface::selectAndOpenTree() {

    auto message = "Choose Ents Tree to open.";

    std::filesystem::path workingDirectory;

    IO::getWorkingDirectory(workingDirectory);

    std::filesystem::path fileToOpen;

    auto result = chooseFile(message, fileToOpen, workingDirectory);

    //TODO FINISH THIS***************************************************************************************

    if (result) {

        Loader::loadTreeFile(fileToOpen);

    }

}

void Interface::notifyChange() {

    reloadSnapshot();

    notifyUIChange();

}