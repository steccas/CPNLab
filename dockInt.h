//
// Created by steccas on 25/06/17.
//

#ifndef CONTNET_DOCKINT_H
#define CONTNET_DOCKINT_H

#include <string>

using namespace std;

class dockInt {
private:
    string execCmd(string command);
    bool isInvalid(string str);
    bool isInvalidU(string str);
    bool isConflict(string str);
    bool isAlready(string str);
    bool isOverlapping(string str);
public:
    dockInt() {}
    void startDocker();
    void stopDocker();
    string getDockerStatus();
    void addCont(string name, string netId, bool isRouter);
    string addCont(string name, string netId);
    void delCont(string id);
    string addNet(string name, string subnet, string gw);
    string delNet(string id);
    void connect(string contId, string netId);
    void disconnect(string contId, string netId);
    void deleteAllConts();
    void prune();
    string ifconfig(string contId);
    string routeAdd(string contId, string ip, string via);
    string routeDel(string contId, string ip);
    string route(string contId);
    string inspect(string id);
    string inspect(string id, string format);
    string ps(string mode, bool started);
    string getContImg(string id);
    string getContStatus(string id);
    string lsNet(string mode);
    string start(string id);
    string stop(string id);
    string ifconfig(string contId, string param);
};


#endif //CONTNET_DOCKINT_H

