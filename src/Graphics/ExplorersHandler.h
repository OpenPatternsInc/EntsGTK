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

#ifndef ENTSGUI_EXPLORERSHANDLER_H
#define ENTSGUI_EXPLORERSHANDLER_H

#include <vector>
#include <atomic>
#include "Explorer.h"

namespace ents_gui {

/**
* This is an abstract class which encapsulates the functions and data relating
* to having multiple Explorer instances running at the same time.
*/
    class ExplorersHandler {

        std::vector<ExplorerInterface*> explorers;

        std::mutex mutex;

        std::atomic<bool> closing;


        /**
         * When the Explorer's destructor is called, that will remove the pointer here from the list.
         *
         * If subclasses of this abstract class want to destroy or close an explorer, we will call that Explorer's
         * destructor, which will in turn remove the pointer from the vector.
         */




        ExplorersHandler() : explorers(), mutex(), closing(false) {

        }


        ~ExplorersHandler() {

            std::lock_guard<std::mutex> lock(mutex);

        }



        void openNewExplorer() {





        }





    };


}

#endif //ENTSGUI_EXPLORERSHANDLER_H
