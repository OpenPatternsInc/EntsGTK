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

#ifndef ENTS_ROOT_ENT_H
#define ENTS_ROOT_ENT_H

#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <unordered_set>
#include <algorithm>

namespace ents_root {

    /**
     * Ent is a class which represents an entity within a taxonomic hierarchy.
     * It is essentially a collection of pointers to other Ent instances that
     * are related to it.
     */
    class Ent {

    protected:
        /**
         * A name is required to display to the user so that the tree makes
         * sense. Names don't necessarily have to be unique, because that would
         * be limiting to the user. Different Ent instances with the same name
         * are differentiated with context by the user by looking at the other
         * Ent instances it is related to.
         */
        std::string m_name;
        /**
         * Collection of pointers to this Ent's direct parents.
         */
        std::vector<Ent*> m_parents;
        /**
         * Collection of pointers to this Ent's direct children.
         */
        std::vector<Ent*> m_children;
        /**
         * Collection of pointers to this Ent's direct overlaps.
         */
        std::vector<Ent*> m_overlaps;
        /**
         * Collection of pointers to this Ent's direct disjoints.
         */
        std::vector<Ent*> m_disjoints;


    public:

        /**
         * Constant to easily change how many characters the UID is.
         */
        static const int UID_LENGTH = 10;
        /**
         * A unique char array of numbers.
         */
        std::array<char, UID_LENGTH> UID {};

        /**
         * Create a new Ent with default non-initialized state. Has a UID automatically, but nothing else.
         */
        Ent();


        Ent(std::string name, std::array<char, UID_LENGTH> UID);

        /**
         * We do not destroy any other Ents automatically from this destructor.
         */
        virtual ~Ent() = default;

        /**
         * This function recursively destroys every descendent of the given Ent.
         * Call this instead of using the delete keyword individually to ensure
         * every node is deleted.
         *
         * First it calls this function on each of its children. After each of
         * the calls return, delete that Ent.
         */
        void destroyDescendents();





        /**
         * Allow access to data members directly via public methods.
         * 
         * We can delete these in subclasses, and provide new better ones
         * that are type-safe for those subclasses.
         * 
         * We don't need setters, because the getters return references.
         */

        std::string& name() {
            return m_name;
        }

        std::vector<Ent*>& parents() {
            return m_parents;
        }

        std::vector<Ent*>& children() {
            return m_children;
        }

        std::vector<Ent*>& overlaps() {
            return m_overlaps;
        }

        std::vector<Ent*>& disjoints() {
            return m_disjoints;
        }

        Ent& addParent(Ent* newParent) {
            m_parents.push_back(newParent);
            return *this;
        }

        Ent& addChild(Ent* newChild) {
            m_children.push_back(newChild);
            return *this;
        }

        Ent& addDisjoint(Ent* newDisjoint) {
            m_disjoints.push_back(newDisjoint);
            return *this;
        }

        Ent& addOverlap(Ent* newOverlap) {
            m_overlaps.push_back(newOverlap);
            return *this;
        }

        Ent& removeParent(Ent* p);

        Ent& removeChild(Ent* c);

        Ent& removeOverlap(Ent* o);

        Ent& removeDisjoint(Ent* d);

        static void parentChild(Ent* parent, Ent* child) {
            parent->addChild(child);
            child->addParent(parent);
        }

        static void overlap(Ent* a, Ent* b) {
            a->addOverlap(b);
            b->addOverlap(a);
        }

        static void disjoint(Ent* a, Ent* b) {
            a->addDisjoint(b);
            b->addDisjoint(a);
        }

        /**
         * Siblings are Ents which are neither parents nor children of this one.
         * A true sibling will either be an overlap or disjoint, but sometimes we may not know yet.
         * There may be another ent with the same direct parent that has no known relation to this one,
         * and so the user must provide this additional information to sort it properly.
         *
         * This function returns all of such ents.
         */
        std::unordered_set<Ent*> getUnsortedSiblings();


        std::unordered_set<Ent*> getDescendants();

        std::string toSave();

        std::string getUIDString();

        void generateUID();


    };

}

#endif /* ENTS_ROOT_ENT_H */