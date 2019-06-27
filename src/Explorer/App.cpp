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

#include <gtkmm/messagedialog.h>
#include "App.h"

using namespace ents_gtkgui;


App::App() = default;


Glib::RefPtr<App> App::create() {
    return Glib::RefPtr<App>(new App());
}

/*
ents_interface::get_string_return App::getStringFromUser(std::string &&message, std::string &input) {

    std::promise<std::string> inputPromise;
    auto inputFuture = inputPromise.get_future();

    //std::thread thread(&App::runEntryWindow, this, std::move(message), std::move(inputPromise));

    //thread.join();

    //add_window(*entry);

    //signal(37, getStringFromUser, )

    inputFuture.wait();

    input = inputFuture.get();

    return ents_interface::get_string_return::GOT_STRING;
}

void App::runEntryWindow(std::string&& message, std::promise<std::string> inputPromise) {

    EntryWindow* entry = new EntryWindow(&explorer(), message, std::move(inputPromise));

}
*/

void App::init() {
    /*
     * TODO Create a loop of run() calls. We call run(Window) and it returns when the window is hidden.
     * That means the function will return back to after the run when the window is quit or hidden, and we
     * can go from there, and maybe run a different window.
     */
    //Lets open one Explorer window to start with and start it in the main Application function.
    auto newExplorer = new Explorer(*this);
    newExplorer->init();

    run(*newExplorer);
    //If we get here, that means all windows have been closed, which is when run() returns.

}