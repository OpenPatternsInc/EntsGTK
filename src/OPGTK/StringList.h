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

#ifndef OPGTK_STRINGLIST_H
#define OPGTK_STRINGLIST_H

#include <gtkmm/listviewtext.h>
#include <iostream>
#include <exception>
#include "Includes.h"
#include "PopupMenu.h"

namespace opgtk {


    class NoSelectionException : public std::exception {};

    template <typename InterfaceT, typename Thing>
    class StringList : public virtual opgui::StringList<InterfaceT, Thing>, public Gtk::ListViewText {

        Gtk::TreeModelColumn<Glib::ustring> column;
        Gtk::TreeModel::ColumnRecord columnRecord;
        Glib::RefPtr<Gtk::ListStore> listModel;
        Glib::RefPtr<Gtk::TreeSelection> treeSelection;

        Gtk::CellRendererText* textRenderer;

        PopupMenu menu;

    public:

        StringList();

        void clearItems() override;

        void addRow(std::string text);

        bool on_button_press_event(GdkEventButton *event) override;

        std::unique_ptr<opgui::ListItem<Thing>> getSelected();

    };


    template <typename InterfaceT, typename Thing>
    StringList<InterfaceT, Thing>::StringList() :
            Gtk::ListViewText(1), column(), columnRecord(), textRenderer(manage(new Gtk::CellRendererText()))
    {

        set_headers_visible(false);

        set_hover_selection(true);

        columnRecord.add(column);

        listModel = Gtk::ListStore::create(columnRecord);

        this->set_model(listModel);

        treeSelection = get_selection();

        set_events(Gdk::BUTTON_PRESS_MASK);

        //TODO remove this
        menu.accelerate(*this);
    }

    template <typename InterfaceT, typename Thing>
    void StringList<InterfaceT, Thing>::clearItems() {
        listModel->clear();
    }

    template <typename InterfaceT, typename Thing>
    void StringList<InterfaceT, Thing>::addRow(std::string text)
    {
        //TODO Fix this workaround.
        //For some reason, listModel will be a nullptr when it gets here... so we just get another for the time being.
        if (!listModel)
        {
            listModel = Gtk::ListStore::create(columnRecord);
            set_model(listModel);
            treeSelection = get_selection();
        }

        auto row = listModel->append();
        row->set_value<Glib::ustring>(column, text);

        //Cell rendering stuff here...
        //row->set_value()
        //auto gtkListStore = listModel->gobj();
        //gtkListStore->
    }

    template <typename InterfaceT, typename Thing>
    bool StringList<InterfaceT, Thing>::on_button_press_event(GdkEventButton *event) {

        std::unique_ptr<opgui::ListItem<Thing>> selected;

        //If nothing has been selected, we will get back a unique_ptr with a blank list item, but this is easier to deal with for now.
        try {
            selected = getSelected();

        } catch (NoSelectionException& e) {
            return true;
        }


        auto thing = selected->getThing();

        //This makes sure we only accept single clicks, not double.
        if (event->type == GDK_BUTTON_PRESS) {

            if (event->button == GDK_BUTTON_PRIMARY) {
                this->onItemLeftClick(getSelected()->getThing());
                return true;
            } else if (event->button == GDK_BUTTON_SECONDARY) {


                this->onItemRightClick(getSelected()->getThing());
                //TODO Add the code here to make the menu popup.

                auto tMenu = this->getMenuToShow(getSelected()->getThing());

                auto pop = dynamic_cast<PopupMenu*>(tMenu);

                //if (pop == nullptr) {
                //   std::cout << "nullptr.....\n";
                //}

                pop->popup(event->button, event->time);

                //dynamic_cast<opgtk::PopupMenu<Interface>*>(this->getMenuToShow(getSelected()->getThing()))->popup(event->button, event->time);


                return true;
            }
        }
        //Stop propagation of the event to the parent Widget, because we will just handle it here.
        return true;

    }

    template <typename InterfaceT, typename Thing>
    std::unique_ptr<opgui::ListItem<Thing>> StringList<InterfaceT, Thing>::getSelected() {
        auto selected = treeSelection->get_selected();

        if (selected)
        {
            //auto pathString = listModel->get_path(selected).to_string().raw();

            auto index = std::stoi(listModel->get_path(selected).to_string());

            return std::make_unique<opgui::ListItem<Thing>>(this->getItem(index));
        }
        else
        {
            //TODO Fix this so we either don't return a unique_ptr, or can check that it is empty...
            //Nothing was selected, so throw an exception.
            throw NoSelectionException();
        }
    }


}


#endif //OPGTK_STRINGLIST_H
