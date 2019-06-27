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

#ifndef ENTSGTK_ENTCONTEXTMENU_H
#define ENTSGTK_ENTCONTEXTMENU_H

#include "Includes.h"

namespace ents_gtkgui {

//class Explorer;

    class EntContextMenu : public ents_gui::EntContextMenu, public opgtk::PopupMenu {

    public:

        EntContextMenu(const ents_interface::Ent &ent, ents_interface::Interface *instance) : ents_gui::EntContextMenu(ent, instance) {


        }




        void addItem(std::string text, void (ents_gui::EntContextMenu::*callbackFunction)()) override {

            auto item = manage(new Gtk::MenuItem(text));

            if (callbackFunction) {

                item->signal_activate().connect(sigc::mem_fun(*this, callbackFunction));

            }

            //Should we save the items for later?
            //items.push_back(item);

            append(*item);

        }

    };


}

#endif //ENTSGTK_ENTCONTEXTMENU_H
