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

#include "Controller.h"
#include "Explorer.h"

using namespace ents_explorer_gtk;

using namespace std;


Controller::Controller() :
        Application("net.openpatterns.ents.gtkgui")
{

}

void Controller::requestOpenNewExplorer(std::shared_ptr<ents_interface::Tree> treeToExplore) {
    //Construct a new Explorer on the heap
    auto * explorer = new Explorer(dynamic_cast<ents_gui::App&>(*this));
    //Explorer *explorer = new Explorer(*this, nullptr);

    explorer->init();

    add_window(*explorer);

}


void Controller::threadRun() {

    std::promise<std::string> entryPromise;

    auto entryFuture = entryPromise.get_future();






}