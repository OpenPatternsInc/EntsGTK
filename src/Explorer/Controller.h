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

#ifndef ENTSGTK_CONTROLLER_H
#define ENTSGTK_CONTROLLER_H

#include <gtkmm/application.h>
#include <glibmm.h>
#include <thread>
#include "OpenerHelper.h"
#include "Explorer.h"

namespace ents_explorer_gtk {

/**
* Class to handle the GTK-related stuff in controlling the opening and closing
* of windows and doing that all right.
*/
    class Controller : public Gtk::Application, public ents_gui::App {

    private:

        std::vector<Gtk::Window*> mainWindows;

        void threadRun();

    public:

        void requestOpenNewExplorer(std::shared_ptr<ents_interface::Tree> treeToExplore) override;

        void requestOpenNewEntry(Gtk::Window& parent, std::promise<std::string> entryPromise);

        void onEntryComplete();

        Controller();

    protected:







    };


}

#endif //ENTSGTK_CONTROLLER_H
