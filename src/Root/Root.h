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

#ifndef ENTS_ROOT_ROOT_H
#define ENTS_ROOT_ROOT_H

#include "Ent.h"

namespace ents_root {

    class Root : public Ent {

        /** Lets assume that an Ent has parents, because all Ents do except root.
         * That means that when we get the parents of an Ent, if the list is
         * empty, then it must be root. We can be sure of this with its UID.
         *
         * If we assume that there are parents, then we can skip checking for
         * them.
         *
         * We still have the power to add parents to Root, but we will not use
         * that power, simply for simplicity of the class. Whenever we add a
         * parent to an Ent, we don't want to be checking that the Ent is not
         * Root. That is a waste, because Root is only one Ent.
         *
         * But when we know the Ent is Root, and we use a Root instance, THEN
         * we limit our usage to how a Root would behave.
         */


    public:


        Root();

        ~Root() override = default;


        /**
         * If we're sure the Ent is Root, we do not need to allow the user to
         * change its name. There is no case where this would help speed the
         * program up.
         * @return
         */
        //std::string& name() = delete;

        //std::string& info() = delete;

        //std::vector<Ent&>& parents() = delete;

        //Ent& addParent(Ent*) = delete;

        //Ent& removeParent(Ent*) = delete;

        /**
         * Allow the user to query Root's name, but the name will be const now.
         * @return
         */
        inline const std::string& getName() const {
            return m_name;
        }









    };





}

#endif /* ENTS_ROOT_ROOT_H */

