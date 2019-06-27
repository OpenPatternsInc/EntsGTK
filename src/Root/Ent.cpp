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

#include <utility>
#include "Ent.h"
#include "Root.h"
#include <iostream>
#include <random>

using namespace std;

namespace ents_root {

    Ent::Ent() : m_parents(), m_children(), m_overlaps(), m_disjoints() {
        generateUID();
    }

    Ent::Ent(string name, array<char, UID_LENGTH> UID) :
            m_parents(), m_children(), m_overlaps(), m_disjoints(), m_name(move(name)), UID(UID)
    {}

    void Ent::destroyDescendents() {

        for (auto child : m_children) {
            child->destroyDescendents();
            delete child;
        }
    }

    Ent& Ent::removeParent(Ent* p) {

        for (auto it = m_parents.begin(); it != m_parents.end(); it++) {
            if (*it == p) {
                m_parents.erase(it);
                break;
            }
        }
        return *this;
    }

    Ent& Ent::removeChild(Ent* c) {

        for (std::size_t i = 0; i < m_children.size(); i++) {

            if (c == m_children[i]) {
                m_children.erase(m_children.begin() + i);
                break;
            }
        }
        return *this;
    }

    Ent& Ent::removeOverlap(Ent* o) {

        for (auto it = m_overlaps.begin(); it != m_overlaps.end(); it++) {
            if (*it == o) {
                m_overlaps.erase(it);
                break;
            }
        }

        return *this;
    }

    Ent& Ent::removeDisjoint(Ent* d) {

        for (auto it = m_disjoints.begin(); it != m_disjoints.end(); it++) {
            if (*it == d) {
                m_disjoints.erase(it);
                break;
            }
        }

        return *this;
    }

    std::unordered_set<Ent*> Ent::getUnsortedSiblings() {

        std::unordered_set<Ent*> siblings;

        for (auto &parent : m_parents) {

            auto children = parent->m_children;

            for (auto &child : children) {

                if (this != child
                    && std::find(m_disjoints.begin(), m_disjoints.end(), child) == m_disjoints.end()
                    && std::find(m_overlaps.begin(), m_overlaps.end(), child) == m_overlaps.end())
                {
                    siblings.insert(child);
                }
            }

            //Also, unordered siblings of the parent are unordered siblings of this Ent.
            auto siblingsOfParent = parent->getUnsortedSiblings();
            for (auto sib : siblingsOfParent)
                siblings.insert(sib);

        }

        return siblings;

    }

    std::unordered_set<Ent*> Ent::getDescendants() {

        auto out = std::unordered_set<Ent*>();

        for (auto child : children()) {

            out.insert(child);

            auto grands = child->getDescendants();

            for (auto grand : grands) {

                out.insert(grand);
            }
        }
        return out;
    }

    std::string Ent::toSave() {

        auto str = m_name + "\n";

        str += getUIDString();

        //We only need to store the children, because we can then deduce the parent connections needed later...
        //for (auto p : m_parents)
        //    str += 'p' + p->getUIDString();
        for (auto c : m_children)
            str += 'c' + c->getUIDString();
        //TODO We only need to store one of these as well, as we can deduce the other of the pair... but not a priority.
        for (auto o : m_overlaps)
            str += 'o' + o->getUIDString();
        for (auto d : m_disjoints)
            str += 'd' + d->getUIDString();

        return str;

    }

    std::string Ent::getUIDString() {
        return std::string(UID.begin(), UID.end());
    }

    void Ent::generateUID() {

        static const char chars[] = "0123456789";

        const size_t sz = (sizeof(chars) - 1);

        //TODO Make these static variables so we don't need to instantiate them over and over...
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, sz);

        for (auto &c : UID)
            c = chars[dis(gen) % sz];

    }



}