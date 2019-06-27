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

#ifndef ENTSGUI_ENTRYWINDOW_H
#define ENTSGUI_ENTRYWINDOW_H

#include "Interfaces.h"
#include <utility>

namespace ents_gui {

/**
 * This abstract class provides the common functionality of a user inputting text into a window.
 */
    class EntryWindow : public EntryWindowInterface {

    public:

        ExplorerInterface& explorer;

        std::string message;

        void (ents_interface::Interface:: *afterFunction)(const ents_interface::EntryResult&);

        EntryWindow(ExplorerInterface& explorer, std::string message,
                    void (ents_interface::Interface:: *afterFunction)(const ents_interface::EntryResult&)) :
                explorer(explorer), message(std::move(message)), afterFunction(afterFunction) {

            explorer.freeze();

        }

        ~EntryWindow() = default;

        void init() override { setTitle("Text Entry"); }

        void onOkButtonClicked() { onComplete(); }

        void onCancelButtonClicked();

        void onComplete();

        void redraw() override { }

        void onClose() override { explorer.unfreeze(); }

    };


}

#endif //ENTSGUI_ENTRYWINDOW_H
