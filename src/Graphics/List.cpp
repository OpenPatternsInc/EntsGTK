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

#include "List.h"

using namespace ents_gui;

void List::update(ents_interface::List list) {

    auto items = std::vector<opgui::ListItem<ents_interface::Ent>>();

    auto ents = list.getEnts();

    for (ents_interface::Ent ent : ents) {

    std::string display;
    std::string name = ent.raw->name();

    if (ent.relationToFocus == ents_interface::RELATION::FOCUS)
    display = name + " (Focus)";
    else if (ent.relationToFocus == ents_interface::RELATION::UNKNOWN)
    display = name + " (Unknown relationship)";
    else if (ent.relationToFocus == ents_interface::RELATION::OVERLAP)
    display = name + " (Overlap)";
    else if (ent.relationToFocus == ents_interface::RELATION::DISJOINT)
    display = name + " (Disjoint)";
    else
    display = name;

    items.emplace_back(std::move(opgui::ListItem<ents_interface::Ent>(this, display, ent)));

    }

    setItems(items);

}