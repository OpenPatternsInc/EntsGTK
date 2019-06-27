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

#ifndef ENTSGUI_LIST_H
#define ENTSGUI_LIST_H

#include "Interfaces.h"
#include "EntContextMenu.h"
#include <vector>
#include <mutex>

namespace ents_gui {


/**
 * An abstract interface class that forces subclasses to implement certain functions.
 * Takes care of basic stuff a list of Ents would need to do.
 *
 * This class extends ents_interface::List which is just a vector of ents_interface::Ent objects.
 */
    class List : public ListInterface {

    protected:

        /**
         * explorer is a reference to the ExplorerInterface subclass instance which owns this list.
         * We can call abstract virtual functions of the instance, without being dependent
         * upon Explorer.
         */
        ExplorerInterface& explorer;


    public:

        explicit List(ExplorerInterface& ex) : explorer(ex) {

        }

        void update(ents_interface::List list) override;


        void onItemLeftClick(ents_interface::Ent ent) override {

            explorer.setFocus(ent);

        }

        void onItemRightClick(ents_interface::Ent ent) override {

            //this->showMenu();

        }

    };


}

#endif //ENTSGUI_LIST_H
