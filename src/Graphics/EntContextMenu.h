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

#ifndef ENTSGUI_ENTCONTEXTMENU_H
#define ENTSGUI_ENTCONTEXTMENU_H


#include "Includes.h"

namespace ents_gui {


//Forward declaration.
    class Explorer;

/**
 * This class is an abstract PopupMenu which will appear when an Ent in an Explorer is right-clicked.
 *
 * It is currently generated as needed and then discarded.
 */
    class EntContextMenu : virtual public opgui::PopupMenu {

        using RELATION = ents_interface::RELATION;

    public:

        ents_interface::Ent ent;

        ents_interface::Interface *explorer;

        EntContextMenu(const ents_interface::Ent &ent, ents_interface::Interface *explorerInstance) : explorer(explorerInstance), ent(ent) { }

        /**
         * What should happen when the expendable menu is created?
         */
        void init();

        virtual void addItem(std::string text, void (EntContextMenu::*callbackFunction)()) = 0;

        void onRenameSelected() { explorer->renameEnt(ent); }

        void onDeleteSelected() {  }

        void onNewEntAsChildSelected() { explorer->newEntUnderFocus(); }

        void onAddSelectedAsParent() { explorer->addParentToFocus(ent); }

        void onAddSelectedAsChild() { explorer->addChildToFocus(ent); }

        void onAddSelectedAsOverlap() { explorer->addOverlapToFocus(ent); }

        void onAddSelectedAsDisjoint() { explorer->addDisjointToFocus(ent); }

    };


}

#endif //ENTSGUI_ENTCONTEXTMENU_H
