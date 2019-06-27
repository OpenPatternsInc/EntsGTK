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

#include <memory>
#include "Tree.h"
#include "IO.h"
#include <utility>

using namespace std;

using namespace ents_interface;

using rEnt = ents_root::Ent;


Tree::Tree() : tree(new ents_root::Tree()) {

}


//Move constructor.
Tree::Tree(Tree&& oldTree) noexcept : tree(move(oldTree.tree)) {

}


//Move assignment
Tree& Tree::operator=(Tree&& oldTree) noexcept {

    tree = move(oldTree.tree);
    //TODO make a special "empty" constructor which will be destroyed immediately because it was moved from.
    oldTree.tree = make_shared<ents_root::Tree>();

    return *this;
}


set_name_return Tree::setName(string newName) {

    //No checks yet...
    tree->setName(move(newName));

    return set_name_return::SUCCESS;

}


Ent Tree::getRoot() {

    rEnt &ref = *tree->m_root;
    rEnt* ptr = &ref;
    Ent ret(ptr);
    return ret;
}


string Tree::getName() {

    return tree->m_name;
}


void Tree::newEnt(std::string name, ents_interface::Ent firstParent) {

    tree->newEnt(move(name), firstParent.raw);


}

void Tree::save() {

    IO::saveString(fileHandle + '.' + EXTENSION, tree->toSave());


}