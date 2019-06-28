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

#ifndef ENTSGTK_APP_H
#define ENTSGTK_APP_H


#include <gtkmm/application.h>
#include "Includes.h"
#include "Explorer.h"
#include "EntryWindow.h"
#include "Controller.h"
#include <thread>

namespace ents_explorer_gtk {

    //TODO Add a template here so we can code for different types of Explorer and keep pointers to it.
    class App : public Controller {

    protected:

        App();

    public:

        //ents_interface::get_string_return getStringFromUser(std::string &&message, std::string &input) override;

        static Glib::RefPtr<App> create();

        /**
         * Subclasses of Controller are required to
         */
        void init() override;

    private:

    };


}

#endif //ENTSGTK_APP_H
