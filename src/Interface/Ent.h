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

#ifndef ENTS_INTERFACE_ENT_H
#define ENTS_INTERFACE_ENT_H

#include "Includes.h"
#include <iostream>


namespace ents_interface {


    class Ent {

    public:

        ents_interface::RELATION relationToFocus;

        ents_root::Ent* raw;

        explicit Ent(ents_root::Ent* ent);

        Ent() : raw(nullptr), relationToFocus(ents_interface::RELATION::UNKNOWN) {}

        virtual ~Ent() = default;


        std::vector<Ent> getParents() {
            return wrap(raw->parents());
        }

        std::vector<Ent> getChildren() {
            return wrap(raw->children());
        }

        std::vector<Ent> getOverlaps() {
            return wrap(raw->overlaps());
        }

        std::vector<Ent> getDisjoints() {
            return wrap(raw->disjoints());
        }

        std::vector<Ent> getDescendants() {
            return wrap(raw->getDescendants());
        }

        std::vector<Ent> getUnorderedSiblings();

        std::vector<Ent> wrap(const std::vector<ents_root::Ent*>& ents);

        std::vector<Ent> wrap(const std::unordered_set<ents_root::Ent*>& ents);


    };


}

#endif /* ENTS_INTERFACE_ENT_H */
