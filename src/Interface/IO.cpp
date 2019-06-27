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

#include "IO.h"

using namespace ents_interface;

using namespace std;

namespace fs = std::filesystem;


bool IO::init(AbstractInterface *inter) {

    SETTINGS_PATH = fs::path("ents.settings");
    interface = inter;

    try {

        if (fs::exists(SETTINGS_PATH)) {

            fs::path wd;

            if (getWorkingDirectory(wd)) {

                workingDirectory = move(wd);

                cout << "Working directory found: \"" << workingDirectory.string() << "\"\n";

                return true;

            } else {

                return newWorkingDirectory();
            }
        } else {

            return newWorkingDirectory();
        }
    } catch (exception &e) {
        std::cout << e.what() << "\n";
    }
    return false;
}


bool IO::newWorkingDirectory() {

    fs::path wd;

    auto result = interface->chooseFolder("Please select where to save Ents Tree files...", wd);

    if (result) {

        ofstream stream;

        stream.open(SETTINGS_PATH);

        stream << wd.string();

        workingDirectory = fs::path(wd);

        return true;

    }

    return false;

}


bool IO::getWorkingDirectory(std::filesystem::path &pathToDir) {

    try {

        ifstream stream;

        stream.open(SETTINGS_PATH);

        string directory;

        std::getline(stream, directory);

        pathToDir = fs::path(directory);

        return fs::exists(pathToDir);


    } catch (exception &e) {
        cout << e.what() << "\n";
    }

    return false;

}

void IO::saveString(const std::string& fileName, std::string &&data) {

    try {

        auto fileString = workingDirectory.string() + fs::path::preferred_separator + fileName;

        cout << "File name: " << fileString << "\n";

        auto filePath = fs::path(fileString);

        ofstream stream;

        stream.open(filePath);

        stream << data;

        cout << "Saved?\n";

    } catch (exception &e) {
        cout << e.what() << "\n";
    }
}