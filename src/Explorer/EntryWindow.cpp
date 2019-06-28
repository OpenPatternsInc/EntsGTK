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

#include "EntryWindow.h"
#include "App.h"

using namespace ents_explorer_gtk;
using namespace std;

EntryWindow::EntryWindow(ents_gui::Explorer& explorer, const std::string& message, void (ents_interface::Interface:: *afterFunction)(const ents_interface::EntryResult&))
        :
        ents_gui::EntryWindow(explorer, message, afterFunction),
        set(false),
        okButton("OK"),
        cancelButton("Cancel"),
        buttonBox(Gtk::ORIENTATION_HORIZONTAL, 5),
        mainBox(Gtk::ORIENTATION_VERTICAL, 5),
        messageLabel(message),
        entry()
{
    set_default_size(400, 200);
    set_border_width(5);

    buttonBox.pack_start(cancelButton, true, false, 5);
    buttonBox.pack_start(okButton, true, false, 5);

    mainBox.pack_start(messageLabel, false, false, 5);
    mainBox.pack_start(entry, false, false, 5);
    mainBox.pack_start(buttonBox, false, false, 5);

    add(mainBox);

    okButton.signal_clicked().connect(sigc::mem_fun(*this, &ents_gui::EntryWindow::onOkButtonClicked));
    cancelButton.signal_clicked().connect(sigc::mem_fun(*this, &EntryWindow::onCancelButtonClicked));
    //entry.signal_key_press_event().connect(sigc::mem_fun(*this, &EntryWindow::onKeyPress));

    set_events(Gdk::KEY_PRESS_MASK);

    set_transient_for(dynamic_cast<Explorer&>(explorer));
    set_position(Gtk::WIN_POS_CENTER_ON_PARENT);

    show_all_children();
    show();

}


EntryWindow::~EntryWindow() = default;


std::string EntryWindow::getText() {

    return entry.get_text();

}

void EntryWindow::setMessage(std::string message) {

    messageLabel.set_label(message);

}

bool EntryWindow::on_key_press_event(GdkEventKey* event) {


    auto key = event->keyval;

    auto keyName = std::string(gdk_keyval_name(key));

    //TODO Replace this with something not using a string literal.
    if (std::string(keyName) == "Return") {
        onComplete();
        return false;
    }

    return Gtk::Window::on_key_press_event(event);

}