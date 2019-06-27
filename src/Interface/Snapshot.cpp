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

#include "Snapshot.h"

using namespace ents_interface;

Snapshot Snapshot::generate(Ent focus) {

    focus.relationToFocus = RELATION::FOCUS;

    Snapshot snap;

    snap.focus = focus;

    std::vector<Ent> parents, siblings, children;


    //parents
    for (auto &parent : focus.getParents()) {
        parent.relationToFocus = RELATION::PARENT;
        parents.emplace_back(parent);
        //Go deeper...
        for (auto &parent2 : parent.getParents()) {
            parent2.relationToFocus = RELATION::PARENT;
            parents.emplace_back(parent2);
            //Go deeper...
            for (auto &parent3 : parent2.getParents()) {
                parent3.relationToFocus = RELATION::PARENT;
                parents.emplace_back(parent3);
                //Go deeper...
                for (auto &parent4 : parent3.getParents()) {
                    parent4.relationToFocus = RELATION::PARENT;
                    parents.emplace_back(parent4);
                    //Go deeper...
                    for (auto &parent5 : parent4.getParents()) {
                        parent5.relationToFocus = RELATION::PARENT;
                        parents.emplace_back(parent5);
                    }
                }
            }
        }
        snap.parents.setEnts(parents);
    }
    //children
    //*
    auto desc = focus.getDescendants();
    for (auto &d : desc) {
        d.relationToFocus = RELATION::CHILD;
    }
    snap.children.setEnts(desc);
    //*/
    /*
    for (auto &child : focus.getChildren()) {
        child.relationToFocus = RELATION::CHILD;
        children.emplace_back(child);
        //Go Deeper...
        for (auto child2 : child.getChildren()) {
            child2.relationToFocus = RELATION::CHILD;
            children.emplace_back(child2);
            //Go Deeper...
            for (auto child3 : child2.getChildren()) {
                child3.relationToFocus = RELATION::CHILD;
                children.emplace_back(child3);
                //Go Deeper...
                for (auto child4 : child3.getChildren()) {
                    child4.relationToFocus = RELATION::CHILD;
                    children.emplace_back(child4);
                    //Go Deeper...
                    for (auto child5 : child4.getChildren()) {
                        child5.relationToFocus = RELATION::CHILD;
                        children.emplace_back(child5);
                    }
                }
            }
        }
        snap.children.setEnts(children);
    }
    //*/
    //siblings
    siblings.emplace_back(focus);
    for (auto &disjoint : focus.getDisjoints()) {
        disjoint.relationToFocus = RELATION::DISJOINT;
        siblings.emplace_back(disjoint);
    }
    for (auto &overlap : focus.getOverlaps()) {
        overlap.relationToFocus = RELATION::OVERLAP;
        siblings.emplace_back(overlap);
    }
    for (auto &unsorted : focus.getUnorderedSiblings()) {
        unsorted.relationToFocus = RELATION::UNKNOWN;
        siblings.emplace_back(unsorted);
    }
    snap.siblings.setEnts(siblings);

    return snap;


}