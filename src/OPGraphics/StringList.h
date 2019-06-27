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

#ifndef OPGUI_STRINGLIST_H
#define OPGUI_STRINGLIST_H

#include <vector>
#include <iostream>
#include "ListItem.h"
#include "Point.h"
#include "MenuInterface.h"

namespace opgui {


/**
 * This class provides the common interface for a Window
 */
    template <typename Interface, typename Thing>
    class StringList : public StringListInterface, public MenuInterface {

        std::vector<ListItem<Thing>> items;

    public:

        StringList() = default;

        ~StringList() = default;


        void setItems(std::vector<ListItem<Thing>> in) {

            items = in;

            redraw();
        }


        void redraw() override {

            this->clearItems();

            for (auto item : items) {

                addRow(item.getLabel());
            }
        }


        ListItem<Thing> getItem(int index) {
            return items[index];
        }



        virtual void onItemLeftClick(Thing thing) = 0;

        virtual void onItemRightClick(Thing thing) = 0;




        virtual PopupMenu* getMenuToShow(Thing thing) = 0;




    };


}


#endif //OPGUI_STRINGLIST_H
