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

#include "List.h"

using namespace ents_interface;

List& List::setEnts(std::vector<Ent> newEnts) {


    //Remove duplicates
    //std::set<Ent> temp = std::set<Ent>(newEnts.begin(), newEnts.end());

    //TODO do this more efficiently with hashes and sets.
    ents = std::vector<Ent>();
    for (auto ent : newEnts) {
        bool found = false;
        for (const auto &in : ents)
            if (ent.raw == in.raw)
                found = true;
        if (!found)
            ents.emplace_back(ent);
    }

    return *this;
}


std::vector<Ent> List::getEnts() {

    //std::lock_guard<std::mutex> lock_guard(mutex);

    std::vector<Ent> copy = ents;

    return copy;

}