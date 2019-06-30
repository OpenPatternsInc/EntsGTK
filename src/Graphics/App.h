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

#ifndef ENTSGUI_APP_H
#define ENTSGUI_APP_H

#include "Explorer.h"

namespace ents_gui {

    //TODO Add a template to App so it can easily hold pointers to subclasses of Explorer.

/**
 * The abstract class App is an interface which handles the common tasks of all GUI
 * implementations of the EntsDatabase, as designed by OpenPatterns.
 *
 * Subclasses must implement certain functions, which allow for UI flow to be determined
 * in this library, rather than the implementation itself, which should be concerned strictly
 * with how the chosen GUI library links with this library.
 */
    class App : public AppInterface {

        //TODO Turn this into a vector so we can have multiple TreeExplorers open at once!
        /**
         * m_explorer is a private pointer to the instance of ents_gui::Explorer. Subclasses can get a pointer to the
         * implementation as the subclass by calling explorer().
         */
        Explorer* m_explorer;


    public:

        /**
         * Defining a default constructor.
         */
        App() : m_explorer(nullptr) {

        };

        /**
         * Default destructor. We don't want to delete the data on m_explorer because we might use it somewhere else.
         */
        ~App() override = default;

        /**
         * Here we can implement the quit function, which will destroy this app and thus everything else.
         */
        void quit() override {

            delete this;

        }

    private:



    protected:

        /**
         * Set the private explorer pointer.
         * Make this function protected, because we only want subclasses to call it.
         *
         * It may make some sense to just set m_explorer from the constructor, but that will make
         * it difficult later when there are multiple Explorers open at once, or different windows.
         */
        void setExplorer(Explorer* ptr) {
            m_explorer = ptr;
        }

    };

}

#endif //ENTSGUI_APP_H
