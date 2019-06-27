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

#include "Explorer.h"

using namespace ents_gui;

void Explorer::init() {

    ents_interface::Interface::initializeIO();

    //Create a new list, initialize it, and save a pointer to it for later.
    m_lists.push_back(dynamic_cast<List*>(initializeNewList()));
    m_lists.push_back(dynamic_cast<List*>(initializeNewList()));
    m_lists.push_back(dynamic_cast<List*>(initializeNewList()));

    //ents_interface::Tree newTree;

    //newTree.setName("DemoTree");

    //openTree(std::move(newTree));
}


void Explorer::openTree(ents_interface::Tree&& treeToOpen) {

    //unfreeze just to make sure... maybe move this somewhere else later...
    //unfreeze();

    tree = std::move(treeToOpen);

    setTitle(tree.getName());

    setFocus(tree.getRoot());

}


void Explorer::redraw() {

    m_lists[0]->update(snapshot.parents);
    m_lists[1]->update(snapshot.siblings);
    m_lists[2]->update(snapshot.children);
}


void Explorer::notifyUIChange() {

    redraw();

    //TODO We might not necessarily need unfreeze the window, but it will for now.
    unfreeze();

}