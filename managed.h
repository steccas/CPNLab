//
// Created by steccas on 22/06/17.
//

#ifndef CONTNET_MANAGED_H
#define CONTNET_MANAGED_H

#include <string>

using namespace std;

class managed {
private:
    string id;
    string type;
public:
    managed(string id, string tp);
    string getId();
    string getType();
};


#endif //CONTNET_MANAGED_H
