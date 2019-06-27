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

#include <chrono>
#include "Ent.h"

using rEnt = ents_root::Ent;

using RELATION = ents_interface::RELATION;

using namespace std::chrono;

namespace ents_interface {

    Ent::Ent(rEnt* ent) : raw(ent), relationToFocus(RELATION::UNKNOWN) {

        //UID(randomString());

    }

    std::vector<Ent> Ent::getUnorderedSiblings() {

        auto list = std::vector<Ent>();

        auto siblings = raw->getUnsortedSiblings();

        for (auto ent : siblings) {
            Ent temp = Ent(ent);
            list.push_back(temp);
        }
        return list;
    }


    std::vector<Ent> Ent::wrap(const std::vector<ents_root::Ent*>& ents) {

        auto list = std::vector<Ent>();

        for (auto ent : ents) {
            Ent temp = Ent(ent);
            list.push_back(temp);
        }
        return list;
    }

    std::vector<Ent> Ent::wrap(const std::unordered_set<ents_root::Ent*>& ents) {

        auto list = std::vector<Ent>();

        for (auto ent : ents) {
            Ent temp = Ent(ent);
            list.push_back(temp);
        }
        return list;
    }


}