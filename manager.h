//
// Created by steccas on 24/06/17.
//

#ifndef CONTNET_MANAGER_H
#define CONTNET_MANAGER_H

#include "managed.h"
#include "dockInt.h"
#include <list>
#include <vector>

class manager {
private:
    list<managed> mged;
    void addMan(string id, string tp);
    void delMan(string id);
    dockInt* docker;
    string hostImg;
    string routerImg;
    vector<string> splitString(const std::string& str, const std::string& delim);
    string createSubNetForExam();

public:
    manager();
    dockInt* getDocker();
    vector<string> readContainersId();
    vector<string> readContainerNetworks(string id);

    vector <string> readNetworksId();
    list<string> readNetworkConts(string id);

    int connectC(string id1, string id2);
    bool isRouter(string id);

    vector <string> readContainersStatus();

    vector <string> readContainersNames();

    vector<string> readNetworksNames();

    vector<string> readContIfs(string id);

    bool isNotWhiteSpace (string str);

    string getNetSubnet(string id);

    string getNetName(string id);

    string createGwForExam(string sub);

    string addNetExam(string name);

    bool dockerService();
};


#endif //CONTNET_MANAGER_H
