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

#include "Window.h"


using namespace opgtk;


Window::Window() :
        freezeDispatcher(), unfreezeDispatcher(), closeDispatcher() {

    //Connect dispatchers
    freezeDispatcher.connect(sigc::mem_fun(*this, &Window::freezeNotify));
    unfreezeDispatcher.connect(sigc::mem_fun(*this, &Window::unfreezeNotify));
    closeDispatcher.connect(sigc::mem_fun(*this, &Window::closeWindowNotify));
}

void Window::setTitle(std::string newTitle) { set_title(newTitle); }

void Window::closeWindow() { close(); }

void Window::freeze() { get_child()->set_sensitive(false); }

void Window::unfreeze() { get_child()->set_sensitive(true); }


void Window::freezeNotify() { get_child()->set_sensitive(false); }

void Window::unfreezeNotify() { get_child()->set_sensitive(true); }

void Window::closeWindowNotify() { close(); }

void Window::on_hide() {
    onClose();
    Gtk::Window::on_hide();
}