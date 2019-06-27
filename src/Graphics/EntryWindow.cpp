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

using namespace ents_gui;

void EntryWindow::onCancelButtonClicked() {

    auto result = ents_interface::EntryResult();

    result.status = ents_interface::EntryResultStatus::CANCEL;

    ((&explorer)->*afterFunction)(result);

    closeWindow();

}

void EntryWindow::onComplete() {

    if (getText().empty())
        return;

    auto result = ents_interface::EntryResult(getText());
    //TODO actually check to make sure the entry is valid...
    result.status = ents_interface::EntryResultStatus::SUCCESS;

    ((&explorer)->*afterFunction)(result);

    closeWindow();

}