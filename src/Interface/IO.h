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

#ifndef ENTSINTERFACE_IO_H
#define ENTSINTERFACE_IO_H

#include <filesystem>
#include <iostream>
#include <string>
#include <fstream>
#include <mutex>
#include "AbstractInterface.h"

namespace ents_interface {

    class IO {

    private:

        //static std::mutex mu;

        inline static std::filesystem::path SETTINGS_PATH;

        inline static std::filesystem::path workingDirectory;

        inline static AbstractInterface* interface;

    public:

        IO() = default;

        ~IO() = default;





        /**
         * Must call this when the Interface is being initialized.
         */
        bool init(AbstractInterface *inter);

        /**
         * Ask the user to choose a new working directory.
         */
        static bool newWorkingDirectory();


        static bool getWorkingDirectory(std::filesystem::path &pathToDir);

        static void saveString(const std::string& fileName, std::string &&data);

    };


}

#endif //ENTSINTERFACE_IO_H
