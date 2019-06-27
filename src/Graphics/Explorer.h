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

#ifndef ENTSGUI_EXPLORER_H
#define ENTSGUI_EXPLORER_H

#include "EntryWindow.h"
#include "List.h"
#include <memory>
#include <vector>

namespace ents_gui {

/**
* TreeExplorer is an abstract class which represents and handles the common
* functionality of a window which has 3 lists for exploring a Tree of Ents.
 *
 * Must call init after the construction is complete in order to utilize
 * implementations of pure virtual functions.
*/
    class Explorer : public ExplorerInterface {

        /**
         * A vector of pointers to ents_gui::List.
         */
        std::vector<List*> m_lists;

    public:

        AppInterface& app;


        explicit Explorer(AppInterface& mApp) : app(mApp) {




        };

        //Deletion of the lists and their related widgets will be handled by the derived class.
        ~Explorer() override = default;



        void getStringFromUser(const std::string& message, void (ents_interface::Interface:: *afterFunction)(const ents_interface::EntryResult&)) override {

            createEntryWindow(message, afterFunction);

        }

        void init() override;



    protected:

        void openTree(ents_interface::Tree&& treeToOpen) override;


        void redraw() override;


        void notifyUIChange() override;

        AppInterface& getApp() {

            return app;

        }

        void onClose() override {}


    };


}

#endif //ENTSGUI_EXPLORER_H
