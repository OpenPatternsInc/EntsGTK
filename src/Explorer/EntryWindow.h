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

#ifndef ENTSGTK_ENTRYWINDOW_H
#define ENTSGTK_ENTRYWINDOW_H


#include <gtkmm/window.h>
#include <gtkmm/label.h>
#include <gtkmm/entry.h>
#include <gtkmm/button.h>
#include <gtkmm/box.h>
#include <gtkmm/frame.h>
#include <future>
#include <gtkmm/dialog.h>
#include "Includes.h"
//#include "List.h"

namespace ents_gtkgui {

//Forward declaration.
//class Explorer;

    class EntryWindow : public opgtk::Window, public ents_gui::EntryWindow {

    public:

        EntryWindow(ents_gui::Explorer& explorer, const std::string& message, void (ents_interface::Interface:: *afterFunction)(const ents_interface::EntryResult&));

        ~EntryWindow() override;

        std::atomic<bool> set;

        Gtk::Label messageLabel;
        Gtk::Entry entry;
        Gtk::Button okButton, cancelButton;

        Gtk::Box mainBox, buttonBox;
        Gtk::Frame frame;

        std::string getText() override;

        void setMessage(std::string message) override;

        bool on_key_press_event(GdkEventKey* event) override;





    };


}


#endif //ENTSGTK_ENTRYWINDOW_H
