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

#ifndef OPGTK_WINDOW_H
#define OPGTK_WINDOW_H

#include <gtkmm/window.h>
#include <glibmm/dispatcher.h>

#include "Includes.h"

namespace opgtk {

/**
 * This class links up the window API from opgui::Window with the Gtk::Window library.
 */
    class Window : public Gtk::Window, public virtual opgui::Window {

        Glib::Dispatcher freezeDispatcher, unfreezeDispatcher, closeDispatcher;

        /**
         * Called by the main thread via freezeDispatcher.
         */
        void freezeNotify();
        /**
         * Called by the main thread via unfreezeDispatcher.
         */
        void unfreezeNotify();
        /**
         * Called by the main thread via closeDispatcher.
         */
        void closeWindowNotify();

    protected:

        Window();

    public:

        void setTitle(std::string newTitle) override;
        /**
         * Tells the window to close, destroying all sub-components.
         */
        void closeWindow() override;
        /**
         * Call this function even from another thread to asynchronously prevent the user from doing actions.
         */
        void freeze() override;
        /**
         * Call this function from any thread to unfreeze the window asynchronously.
         */
        void unfreeze() override;

        void on_hide() override;

    };


}

#endif //OPGTK_WINDOW_H
