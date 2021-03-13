//
// Created by steccas on 22/06/17.
//

#include "managed.h"

managed::managed(string id, string tp) {
    this->id = id;
    type=tp;
}

string managed::getId() {return id; }

string managed::getType() { return type; }
