//------------------------------------------------------------
//
// This file is part of HAPLOS availabe off the website at
// <http://pc2lab.cec.miamiOH.edu/haplos>
//
// Human  Population  and   Location  Simulator (HAPLOS)  is
// free software: you can  redistribute it and/or  modify it
// under the terms of the GNU  General Public License  (GPL)
// as published  by  the   Free  Software Foundation, either
// version 3 (GPL v3), or  (at your option) a later version.
//
// HAPLOS is distributed in the hope that it will  be useful,
// but   WITHOUT  ANY  WARRANTY;  without  even  the IMPLIED
// WARRANTY of  MERCHANTABILITY  or FITNESS FOR A PARTICULAR
// PURPOSE.
//
// Miami University and the HAPLOS  development team make no
// representations  or  warranties  about the suitability of
// the software,  either  express  or implied, including but
// not limited to the implied warranties of merchantability,
// fitness  for a  particular  purpose, or non-infringement.
// Miami  University and  its affiliates shall not be liable
// for any damages  suffered by the  licensee as a result of
// using, modifying,  or distributing  this software  or its
// derivatives.
//
// By using or  copying  this  Software,  Licensee  agree to
// abide  by the intellectual  property laws,  and all other
// applicable  laws of  the U.S.,  and the terms of the  GNU
// General  Public  License  (version 3).  You  should  have
// received a  copy of the  GNU General Public License along
// with HAPLOS.  If not, you may  download copies  of GPL V3
// from <http://www.gnu.org/licenses/>.
//
//-----------------------------------------------------------
#include "Daycare.h"
#include "Building.h"

Daycare::Daycare(int i, int x, int y, int capacity, int visitorCapacity, int childCapacity) : Building('D', i, x, y, capacity, visitorCapacity){
    this->maxChildCapacity=childCapacity;
    this->childCapacity=0;
}

int Daycare::getChildCapacity(){
    return childCapacity;
}

int Daycare::getMaxChildCapacity(){
    return maxChildCapacity;
}

void Daycare::removeChild(Person *p){
    currentChildren.erase(p->getID());
}

void Daycare::addChild(Person *p){
    currentChildren[p->getID()] = p;
}

std::unordered_map<int, Person *>Daycare::getChildren(){
    return currentChildren;
    
}

int Daycare::getTotalNumberOfPeople(){
    return currentChildren.size()+Building::getTotalNumberOfPeople();
}


void Daycare::setChildCapacity(int c){
    childCapacity=c;
}

Daycare::~Daycare(){
    
}