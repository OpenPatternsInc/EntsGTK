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

#ifndef ENTS_INTERFACE_ROOT_H
#define ENTS_INTERFACE_ROOT_H

#include "Ent.h"
#include <string>

namespace ents_interface {


    class Root  {

        friend class Tree;

    public:

        Root() = delete;

        Root(Ent& copyFrom);

        ~Root();

        const std::string& getName() const;

    private:
        ents_root::Ent *m_root;

        Root(ents_root::Ent* rawRoot);

    };



}


#endif /* ENTS_INTERFACE_ROOT_H */

