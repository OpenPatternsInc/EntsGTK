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

#ifndef ENTSINTERFACE_SNAPSHOT_H
#define ENTSINTERFACE_SNAPSHOT_H


#include <vector>
#include "Ent.h"
#include "List.h"

namespace ents_interface {


    class Snapshot {


    public:

        List parents, siblings, children;

        Ent focus;

        Snapshot() = default;

        static Snapshot generate(Ent focus);


    };


}

#endif //ENTSINTERFACE_SNAPSHOT_H
