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

#ifndef ENTSGTK_EXPLORER_H
#define ENTSGTK_EXPLORER_H


#include <gtkmm/window.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/listviewtext.h>
#include <gtkmm/listbox.h>
#include <gtkmm/box.h>
#include <glibmm.h>
#include <gtkmm/menubar.h>
#include "Includes.h"
#include "List.h"

namespace ents_explorer_gtk {


    //TODO Add a template here for the List subclass, so we can program generically from ents_gui.
    class Explorer : public ents_gui::Explorer, public opgtk::Window {

    public:

        //*********************************************
        //std::promise<std::string> entryPromise;
        //std::unique_ptr<std::string> entryMessage;
        //*********************************************

        Gtk::MenuBar menuBar;
        Gtk::Menu subMenuTree, subMenuFocus;
        //Items for the Tree menu.
        Gtk::MenuItem treeItem, newTreeItem, openTreeItem, saveTreeItem, saveAsTreeItem, closeTreeItem;
        //Items for the Focus menu.
        Gtk::MenuItem focusItem, newChildItem, deleteFocusItem;
        //The box which contains all of the contents of the window, including the lists and the menu bar.
        Gtk::VBox mainBox;
        //The box which contains the 3 lists.
        Gtk::HBox listBox;

        /**
         * Construct the Explorer and get its state ready with the basic functionality.
         * @param app
         * @param tree
         */
        explicit Explorer(ents_gui::App& app);

        ~Explorer() override = default;

        void setupMenuBar();

        Gtk::MenuItem createMenuItem(const std::string &text, Gtk::Menu &subTree, void (Explorer::*callback)() = nullptr);

        /**
         * Prepare the state so that it is ready by using the implemented interface.
         */
        void init() override;

        ents_gui::List* initializeNewList() override;

        void closeTree() override;

        void createEntryWindow(const std::string& message, void (ents_interface::Interface:: *afterFunction)(const ents_interface::EntryResult&)) override;

        bool chooseFolder(std::string message, std::filesystem::path &newPath) override;

        bool chooseFile(std::string message, std::filesystem::path &fileToOpen, std::filesystem::path startingDirectory) override;

    };


}

#endif //ENTSGTK_EXPLORER_H
