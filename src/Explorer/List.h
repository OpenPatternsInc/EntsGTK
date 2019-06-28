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

#ifndef ENTSGTK_LIST_H
#define ENTSGTK_LIST_H

#include <gtkmm/treeview.h>
#include <memory>
#include <gtkmm/listviewtext.h>
#include "Includes.h"
#include "EntryWindow.h"
#include "EntContextMenu.h"

namespace ents_explorer_gtk {

    class List : public ents_gui::List, public opgtk::StringList<ents_interface::Interface, ents_interface::Ent> {

    public:


        explicit List(ents_gui::ExplorerInterface& ex);

        opgtk::PopupMenu* getMenuToShow(ents_interface::Ent ent) override {

            auto menu = new EntContextMenu(ent, &(this->explorer));

            menu->init();

            menu->show_all();

            return menu;

        }

    };


}

#endif //ENTSGTK_LIST_H
