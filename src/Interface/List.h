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

#ifndef ENTSINTERFACE_LIST_H
#define ENTSINTERFACE_LIST_H

#include <vector>
#include <mutex>
#include <set>
#include "Root.h"

namespace ents_interface {

    /**
     * List is a convenience class where a vector of Ents is stored atomically.
     */
    class List {

        std::vector<Ent> ents;

        //std::mutex mutex;

    public:

        List() = default;

        virtual ~List() = default;

        //TODO Do we make this class move-only?

        List& setEnts(std::vector<Ent> newEnts);

        std::vector<Ent> getEnts();

    };


}


#endif //ENTSINTERFACE_LIST_H
