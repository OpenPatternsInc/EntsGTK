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

#ifndef ENTS_ROOT_TREE_H
#define ENTS_ROOT_TREE_H

#include "Ent.h"
#include <string>
#include <unordered_set>
#include <map>


namespace ents_root {


    class Tree {

        /*
         * Is there really a reason for each Ent to have a unique ID? Not really
         * when it comes to algorithms, which are relative. If we want to look
         * up an Ent, we will do it via questioning from Root. That is most
         * efficient anyways.
         */

    public:

        std::string m_name;

        /**
         * The root of the tree is the "owner" of all Ents within the tree.
         * When it destroys itself, it will also destroy all Ents by going down
         * the child lists. This is problematic because you can get to the same
         * Ent in multiple ways going down the tree. If we destroy all children,
         * and those children remove the connections between themselves and all
         * of their parents, then their parents no longer have a connection to
         * them and they won't be reached again.
         */
        Ent* m_root;

        /**
         * Each Ent must have a unique identifying number. Root is zeroed out.
         */
        static constexpr std::array<char, Ent::UID_LENGTH> rootNum = {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0'};

        std::map<std::array<char, Ent::UID_LENGTH>, Ent*> entMap;

        Tree();

        ~Tree();

        Tree(Tree&& oldTree) = default;

        Tree& operator=(Tree&& oldTree) = default;

        Tree(Tree&) = delete;

        Tree& operator=(Tree&) = delete;

        void setName(std::string newName);

        Ent* newEnt(std::string name, Ent* firstParent = nullptr);

        std::string toSave();


    };



}


#endif /* ENTS_ROOT_TREE_H */

