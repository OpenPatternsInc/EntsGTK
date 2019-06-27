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

#ifndef ENTSINTERFACE_ABSTRACTINTERFACE_H
#define ENTSINTERFACE_ABSTRACTINTERFACE_H


#include <filesystem>

class AbstractInterface {

public:

    virtual bool chooseFolder(std::string message, std::filesystem::path &newPath) = 0;

    virtual bool chooseFile(std::string message, std::filesystem::path &fileToOpen, std::filesystem::path startingDirectory) = 0;

};


#endif //ENTSINTERFACE_ABSTRACTINTERFACE_H
