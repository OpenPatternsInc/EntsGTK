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

#include "Tree.h"

using namespace std;

namespace ents_root {

    Tree::Tree() : m_root(new Ent("root", rootNum)), m_name("Unnamed") {

        m_root->name() = "root";

        entMap.insert(pair(m_root->UID, m_root));

        auto animals = newEnt("animals");

        auto landAnimals = newEnt("land animals", animals);
        auto aquaticAnimals = newEnt("aquatic animals", animals);

        auto reptiles = newEnt("reptiles", animals);
        auto mammals = newEnt("mammals", animals);

        auto snakes = newEnt("snakes", reptiles);
        Ent::overlap(reptiles, landAnimals);
        Ent::overlap(mammals, landAnimals);
        Ent::overlap(reptiles, aquaticAnimals);
        Ent::overlap(mammals, aquaticAnimals);

        auto molecules = newEnt("molecules");
        Ent::disjoint(molecules, animals);
        auto fats = newEnt("fats", molecules);
        auto proteins = newEnt("proteins", molecules);
        auto carbohydrates = newEnt("carbohydrates", molecules);
        auto omega3s = newEnt("omega 3s", fats);

        auto EPA = newEnt("EPA", omega3s);
        auto DHA = newEnt("DHA", omega3s);
        Ent::disjoint(EPA, DHA);

        auto birds = newEnt("birds", landAnimals);
        auto fish = newEnt("fish", aquaticAnimals);
        Ent::disjoint(fish, mammals);

        auto finches = newEnt("finches", birds);

        auto sharks = newEnt("sharks", fish);

        auto whales = newEnt("whales", mammals);
        Ent::parentChild(aquaticAnimals, whales);

        auto dogs = newEnt("dogs", mammals);
        Ent::parentChild(landAnimals, dogs);
        auto apes = newEnt("apes", mammals);
        Ent::parentChild(landAnimals, apes);

        auto gorillas = newEnt("gorillas", apes);
        auto humans = newEnt("humans", apes);

        auto americans = newEnt("americans", humans);
        auto you = newEnt("you", humans);


    }


    Tree::~Tree() {

        //Destroy each child, then this one will be destroyed automatically.
        //m_root->destroyDescendents();

        delete m_root;
    }



    void Tree::setName(string newName) {

        m_name = move(newName);

    }



    Ent* Tree::newEnt(string name, Ent* firstParent) {

        Ent* newEnt = new Ent;
        newEnt->name() = move(name);

        //TODO check to make sure the UID isn't already taken... not high priority...
        entMap.insert(pair<array<char, Ent::UID_LENGTH>, Ent*>(newEnt->UID, newEnt));

        if (firstParent)
            Ent::parentChild(firstParent, newEnt);
        else
            Ent::parentChild(m_root, newEnt);

        return newEnt;

    }


    string Tree::toSave() {

        string out;

        for (auto ent : entMap) {

            out += ent.second->toSave() + '\n';

        }

        return out;

    }



}