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

#ifndef OPGUI_WINDOW_H
#define OPGUI_WINDOW_H


#include <string>

namespace opgui {

/**
 * This class provides the common interface for a Window
 */
    class Window {


    public:

        virtual void closeWindow() = 0;

        virtual void freeze() = 0;

        virtual void unfreeze() = 0;

        virtual void setTitle(std::string newTitle) = 0;

        virtual void redraw() = 0;

        virtual void onClose() = 0;

        /**
         * Force the user to initialize the Window using implementations of virtual functions we can't call in the constructor.
         *
         * This should be overridden in the abstract GUI layer.
         */
        virtual void init() = 0;

    };


}

#endif //OPGUI_WINDOW_H
