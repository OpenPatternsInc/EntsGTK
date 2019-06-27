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

#include <gtkmm/frame.h>
#include <gtkmm/filechooserdialog.h>
#include "Explorer.h"
#include "App.h"

using namespace ents_gtkgui;

Explorer::Explorer(ents_gui::App& app)
        :
        ents_gui::Explorer(app),
        mainBox(),
        listBox()
{
    set_default_size(700, 400);
    set_position(Gtk::WIN_POS_CENTER);
    set_border_width(5);

    setupMenuBar();
};

void Explorer::setupMenuBar() {

    //Create the MenuBar at the top of the window.
    menuBar = Gtk::MenuBar();
    //Do stuff for the "Tree" menu.
    subMenuTree = Gtk::Menu();
    treeItem = Gtk::MenuItem("Tree");
    menuBar.append(treeItem);
    treeItem.set_submenu(subMenuTree);

    newTreeItem = createMenuItem("New...", subMenuTree, &Explorer::createNewTree);
    openTreeItem = createMenuItem("Open...", subMenuTree, &Explorer::selectAndOpenTree);
    saveTreeItem = createMenuItem("Save", subMenuTree, &Explorer::saveTree);
    saveAsTreeItem = createMenuItem("Save as...", subMenuTree);
    closeTreeItem = createMenuItem("Close", subMenuTree);

    //Do stuff for the "Focus" menu.
    subMenuFocus = Gtk::Menu();
    focusItem = Gtk::MenuItem("Focus");
    menuBar.append(focusItem);
    focusItem.set_submenu(subMenuFocus);

    newChildItem = createMenuItem("Create new Ent as child...", subMenuFocus, &Explorer::newEntUnderFocus);
    deleteFocusItem = createMenuItem("Delete", subMenuFocus);

    //Now add the MenuBar to the window.
    mainBox.pack_start(menuBar, Gtk::PACK_SHRINK);
}

Gtk::MenuItem Explorer::createMenuItem(const std::string &text, Gtk::Menu &subTree, void(Explorer::*callback)()) {

    auto temp = Gtk::MenuItem(text);

    if (callback)
        temp.signal_activate().connect(std::bind(callback, this));

    subTree.append(temp);

    return temp;
}


void Explorer::init()  {

    set_title(tree.getName());

    ents_gui::Explorer::init();
    //Now add box to the mainBox
    //Gtk::manage(mainBox);
    mainBox.pack_end(listBox);
    //and add that
    add(mainBox);
    //Now show everything.
    show_all_children();
    show();
    //TODO One list element is always selected at the start... that's not necessary.
}

ents_gui::List* Explorer::initializeNewList() {

    //Create a new ScrollWindow to hold the ListViewText in.
    auto newScrolledWindow = Gtk::manage(new Gtk::ScrolledWindow());
    //Only show the scroll bars when needed.
    newScrolledWindow->set_policy(Gtk::PolicyType::POLICY_AUTOMATIC, Gtk::PolicyType::POLICY_AUTOMATIC);
    /* Create a new List in dynamic memory. They will automatically be deleted when the vector of ScrolledWindows
     * is destroyed, because they will be owned by that parent widget. */
    List* newList = Gtk::manage(new List(*this));
    //Add the List widget to the ScrolledWindow.
    newScrolledWindow->add(*newList);
    //Create a frame to outline the list and scrollWindows
    auto newFrame = Gtk::manage(new Gtk::Frame());
    //Add the ScrolledWindow to the Frame.
    newFrame->add(*newScrolledWindow);
    //Add the ScrolledWindow to the Box so we can show multiple within the Explorer Window.
    listBox.pack_start(*newFrame, true, true);
    //Now return a pointer to the ents_gui::List subclass.
    return newList;
}

void Explorer::closeTree() {

}

void Explorer::createEntryWindow(const std::string& message, void (ents_interface::Interface:: *afterFunction)(const ents_interface::EntryResult&)) {

    //Do not use Gtk::manage to manage lifetimes of windows.
    auto entryWindow = new EntryWindow(*this, message, afterFunction);

    entryWindow->init();

    dynamic_cast<App&>(getApp()).add_window(*entryWindow);
}


bool Explorer::chooseFolder(std::string message, std::filesystem::path &newPath) {

    Gtk::FileChooserDialog dialog(message, Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER);

    dialog.set_transient_for(*this);

    dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
    dialog.add_button("Select", Gtk::RESPONSE_OK);

    int result = dialog.run();

    if (result == Gtk::RESPONSE_OK) {

        newPath = std::filesystem::path(dialog.get_filename());

        return true;
    }
    return false;
}


bool Explorer::chooseFile(std::string message, std::filesystem::path &fileToOpen, std::filesystem::path startingDirectory) {

    auto filter = Gtk::FileFilter::create();

    filter->set_name("Ents Tree");
    filter->add_pattern("*.ents");

    Gtk::FileChooserDialog dialog(message, Gtk::FILE_CHOOSER_ACTION_OPEN);

    dialog.set_filter(filter);
    dialog.set_transient_for(*this);
    dialog.set_current_folder(startingDirectory.string());

    dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
    dialog.add_button("Open", Gtk::RESPONSE_OK);

    int result = dialog.run();

    if (result == Gtk::RESPONSE_OK) {

        fileToOpen = std::filesystem::path(dialog.get_filename());

        return true;
    }
    return false;
}
