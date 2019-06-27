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

#include "EntContextMenu.h"

using namespace ents_gui;

void EntContextMenu::init() {

    auto relation = ent.relationToFocus;

    if (relation == RELATION::FOCUS) {

        this->addItem("Create new Ent as child...", &EntContextMenu::onNewEntAsChildSelected);

    } else if (relation == RELATION::PARENT) {

        this->addItem("Not a parent", nullptr);

    } else if (relation == RELATION::CHILD) {

        this->addItem("Not a child", nullptr);

    } else if (relation == RELATION::UNKNOWN) {

        this->addItem("Add as parent", &EntContextMenu::onAddSelectedAsParent);
        this->addItem("Add as child", &EntContextMenu::onAddSelectedAsChild);
        this->addItem("Add as disjoint", &EntContextMenu::onAddSelectedAsDisjoint);
        this->addItem("Add as overlap", &EntContextMenu::onAddSelectedAsOverlap);

    } else {

        std::cout << "ERROR in ents_gui::EntContextMenu: unsupported relationship type...\n";

    }

    this->addItem("Rename", &EntContextMenu::onRenameSelected);
    this->addItem("Delete", &EntContextMenu::onDeleteSelected);


}