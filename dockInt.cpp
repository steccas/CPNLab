//
// Created by steccas on 25/06/17.
//

#include "dockInt.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <array>
#include <memory>
#include <QtCore/QProcess>

using namespace std;

void dockInt::addCont(string name, string netId, bool isRouter) {
    execCmd("docker run --name " + name + " --cap-add=NET_ADMIN --network=" + netId + " -d -it debian:network /bin/bash");
    //addMan(netId, "cont");
}

string dockInt::addCont(string name, string netId) {
    string str = execCmd("docker run --name " + name + " --cap-add=NET_ADMIN --network=" + netId + " -d -it debian:CPNLab /bin/bash");
    if (isAlready(str)) return "already";
    if (isInvalid(str) || isInvalidU(str)) return "invalid";
    return str;
    //addMan(netId, "cont");
}

void dockInt::delCont(string id) {
    execCmd("docker rm " + id);
    //delMan(id);
}

string dockInt::addNet(string name, string subnet, string gw) {
    string str = execCmd("docker network create -d bridge --gateway " + gw + " --subnet " + subnet + " " + name);
    if (isAlready(str)) return "already";
    if (isInvalid(str)) return "invalid";
    if (isOverlapping(str)) return "overlapping";
    return str;
}

string dockInt::delNet(string id) {
    string ret = execCmd("docker network rm " + id);
    ret.erase(std::remove(ret.begin(), ret.end(), '\n'), ret.end());
    return ret;
}

void dockInt::connect(string contId, string netId) {
    execCmd("docker network connect "+ netId + " " + contId);
}

void dockInt::disconnect(string contId, string netId) {
    execCmd("docker network disconnect "+ netId + " " + contId);
}

string dockInt::execCmd(string command){
    command = command + " 2>&1";
    //cout << command << endl;

    const char* cmd = command.c_str();

    //int r=system (cmd);

    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), 128, pipe.get()) != NULL)
            result += buffer.data();
    }
    //cout << "CmdRes: " + result + "\n";
    return result;
    //printf ("The value returned was: %d.\n",r);

    //cout << getCmdOutput() << endl;
}



string dockInt::ifconfig(string contId) {
    return execCmd("docker exec " + contId + " ifconfig");
}

string dockInt::ifconfig(string contId, string param) {
    return execCmd("docker exec " + contId + " ifconfig " + param);
}

string dockInt::routeAdd(string contId, string ip, string via) {
    return execCmd("docker exec " + contId + " ip route add " + ip + " via " + via);
}

string dockInt::route(string contId) {
    return execCmd("docker exec " + contId + " ip route");
}

string dockInt::inspect(string id) {
    return execCmd("docker inspect " + id);
}

string dockInt::inspect(string id, string format) {
    return execCmd("docker inspect " + id + " -f " + format);
}

string dockInt::ps(string mode, bool started) {
    if(started == 0){
        if (mode == "all"){
            return execCmd("docker ps -a");
        }

        if(mode == "id"){
            return execCmd("docker ps -a -q");
            //return getCmdOutput();
        }

        if(mode == "status"){
            return execCmd("docker ps -a -q --format '{{.Status}}'");
        }

        if(mode == "names"){
            return execCmd("docker ps -a -q --format '{{.Names}}'");
        }
    }
    if(started == 1){
        if (mode == "all"){
            return execCmd("docker ps");
        }

        if(mode == "id"){
            if (mode == "all"){
                return execCmd("docker ps -q");
            }
        }

        if(mode == "status"){
            return execCmd("docker ps -q --format '{{.Status}}'");
        }

        if(mode == "names"){
            return execCmd("docker ps -q --format '{{.Names}}'");
        }
    }
}

string dockInt::getContImg(string id) {
    return execCmd("docker inspect " + id + " -f\"{{ .Config.Image }}\"");
}

string dockInt::lsNet(string mode) {
    if (mode == "all"){
        return execCmd("docker network ls");
    }

    if(mode == "id"){
        return execCmd("docker network ls -q");
    }

    if(mode == "name"){
        return execCmd("docker network ls --format '{{.Name}}'");
    }
}

string dockInt::start(string id) {
    return execCmd("docker start " + id);
}

string dockInt::stop(string id) {
    return execCmd("docker stop " + id);
}

void dockInt::startDocker() {
    execCmd("systemctl start docker");
}


void dockInt::stopDocker() {
    execCmd("systemctl stop docker");
}

string dockInt::getContStatus(string id) {
    string ret = execCmd("docker inspect " + id + " -f\"{{ .State.Status }}\"");
    ret.erase(std::remove(ret.begin(), ret.end(), '\n'), ret.end());
    return ret;
}

string dockInt::routeDel(string contId, string ip) {
    return execCmd("docker exec " + contId + " ip route delete " + ip);
}

bool dockInt::isInvalid(string str) {
    std::size_t found = str.find("invalid");
    if (found!=std::string::npos)
        return true;
    else
        return false;
}

bool dockInt::isConflict(string str) {
    std::size_t found = str.find("Conflict");
    if (found!=std::string::npos)
        return true;
    else
        return false;
}

bool dockInt::isAlready(string str) {
    std::size_t found = str.find("already");
    if (found!=std::string::npos)
        return true;
    else
        return false;
}

bool dockInt::isInvalidU(string str) {
    std::size_t found = str.find("Invalid");
    if (found!=std::string::npos)
        return true;
    else
        return false;
}

bool dockInt::isOverlapping(string str) {
    std::size_t found = str.find("overlapping");
    if (found!=std::string::npos)
        return true;
    else
        return false;
}

void dockInt::prune() {
    execCmd("docker betwork prune -f");
}

void dockInt::deleteAllConts() {
    execCmd("docker stop $(docker ps -a -q)");
    execCmd("docker rm $(docker ps -a -q)");
}

string dockInt::getDockerStatus() {
    return execCmd("systemctl status docker | grep active | awk -F'[: ]+' '{ print $3 }'");
}
