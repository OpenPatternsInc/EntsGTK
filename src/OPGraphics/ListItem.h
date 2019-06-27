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

#ifndef OPGUI_LISTITEM_H
#define OPGUI_LISTITEM_H

#include <string>
#include <memory>
#include <iostream>
#include "StringListInterface.h"
#include "PopupMenu.h"

namespace opgui {


    template<typename T>
    class ListItem {

        /**
         * The string labeling this item.
         */
        std::string m_label;

        /**
         * The object which this item corresponds to.
         */
        T m_thing;

        /**
         * Reference back to the StringList that contains this item.
         */
        StringListInterface* m_list;

    public:

        /**
         * Constructor for creating a new ListItem.
         */
        ListItem(StringListInterface* list, std::string text, T thing) :
                m_list(list), m_label(text), m_thing(thing) {

        }

        /**
         * Trivial constructor so we can create an empty one if we need to.
         */
        ListItem() {}

        virtual ~ListItem() {

            /**
             * TODO Need to figure out who is the owner of this... if we make copies of this instance, the old constructors
             * are called.
             */
            //delete m_menu;
        }

        //We can't have a constructor with no arguments because we need to set the reference.
        //ListItem() : m_list(nullptr) {}

        void setLabel(std::string&& text);

        const std::string getLabel() {
            return m_label;
        }



        T getThing() {
            return m_thing;
        }


    };


}

#endif //OPGUI_LISTITEM_H
