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

#ifndef ENTS_INTERFACE_TREE_H
#define ENTS_INTERFACE_TREE_H

#include "Includes.h"
#include "Ent.h"
#include "Root.h"
#include <memory>

namespace ents_interface {

    enum class set_name_return {SUCCESS, NO_STRING, OTHER_FAILURE};


    class Tree {

        friend class Interface;

    private:

        std::shared_ptr<ents_root::Tree> tree;

        const std::string EXTENSION = "ents";

    public:

        std::string fileHandle = "test";

        //Default constructor. Private so it is only available to friend classes.
        Tree();

        //Move constructor.
        Tree(Tree&& oldTree) noexcept;
        //Move assignment.
        Tree& operator=(Tree&& oldTree) noexcept;
        //Copy construction and assignment are automatically deleted... but do it manually anyways.

        Tree(Tree& oldTree) = delete;
        Tree&operator=(Tree& oldTree) = delete;


        set_name_return setName(std::string newName);

        //Destructor.
        ~Tree() = default;
        //Returns an interface handle to the tree's root Ent.
        Ent getRoot();
        //Returns the current name of the tree.
        std::string getName();

        //TODO check for name validity.
        void newEnt(std::string name, Ent firstParent = Ent());

        void save();





    };

}


#endif /* ENTS_INTERFACE_TREE_H */

