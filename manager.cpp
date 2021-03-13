//
// Created by steccas on 24/06/17.
//

#include <sstream>
#include <iostream>
#include <vector>
#include <random>
#include "manager.h"

using namespace std;

//private

void manager::addMan(string id, string tp) {
    managed toAdd(id, tp);
    //toAdd= new managed(id, tp);
    this->mged.push_back(toAdd);
}

void manager::delMan(string id) {
    for (list<managed>::iterator it=mged.begin(); it!=mged.end(); ++it){
        string _id = it->getId();
        if (_id == id) {mged.erase(it);}
    }
}



//public

manager::manager() {
    docker= new dockInt();
    routerImg = "debian:networkR";
    hostImg = "debian:networkH";
}

bool manager::isRouter(string id) {
    if(docker->getContImg(id) == routerImg) return true;
    else return false;
}

int manager::connectC(string id1, string id2) { //Ho realizzato che è meglio conservarsi le cose in una struttura dati propria
    bool r1, r2 = false;
    r1 = isRouter(id1);
    r2 = isRouter(id2);
    if (r1 || r2) {
        //vedi chi è il router
        string router, host;
        if (r1 == 1 && r2 == 0) {
            router = id1;
            host = id2;

            //usa readContainerNetworks e poi prendi l'ip del router in base alla rete interessata
            //docker->routeAdd(id2, "default", )
        }
        if (r1 == 0 && r2 == 1) {
            router = id2;
            host = id1;
        }
        if (r1 == 1 && r2 == 1) {

        }
        //controlla se r1 e r2 sono sulla stessa rete
        //aggiungi il router nel def gw dell'host
        //aggiungili vicendevolmente (metti la route per la rete/i dietro ogni router)

    }
    else return 1;
}

dockInt *manager::getDocker() {
    return docker;
}

vector <string> manager::readContainersId() {
    string tmp;
    string out;
    out = (docker->ps("id", 0));
    //cout << "call1 : "+ out << endl;
    vector<string> ret;

    ret = splitString(out, "\n");

    return ret;
}

vector <string> manager::readContainersStatus() {
    string out;
    out = (docker->ps("status", 0));
    //cout << "call1 : "+ out << endl;
    vector<string> ret;

    ret = splitString(out, "\n");

    return ret;
}

vector <string> manager::readContainersNames() {
    string out;
    out = (docker->ps("names", 0));
    //cout << "call1 : "+ out << endl;
    vector<string> ret;

    ret = splitString(out, "\n");

    return ret;
}


vector <string> manager::readContainerNetworks(string id) {
    string tmp;
    string out;
    out = docker->inspect(id, "'{{range $key, $value := .NetworkSettings.Networks}}{{printf \"%s\\n\" $key}}{{end}}'");
    vector<string> ret;

    ret = splitString(out, "\n");

    return ret;
}


vector <string> manager::readNetworksId() {
    string out;
    out = (docker->lsNet("id"));
    vector<string> ret;
    ret = splitString(out, "\n");
    return ret;
}

vector <string> manager::readNetworksNames() {
    string out;
    out = (docker->lsNet("name"));
    vector<string> ret;
    ret = splitString(out, "\n");
    return ret;
}

list <string> manager::readNetworkConts(string id) {
    string tmp;
    stringstream out;
    out.str(docker->inspect(id, "'{{range $key, $value := .Containers}}{{printf \"%s\n\" $key}}{{end}}'"));
    list<string> ret;
    while ( getline(out, tmp) ) {
        if (tmp.empty())                  // be careful: an empty line might be read
            continue;
        ret.push_back(tmp);
    }
    return ret;
}

vector<string> manager::splitString(const std::string& str,
                                 const std::string& delim)
{
    try {
        std::vector<std::string> strings;

        std::string::size_type pos = 0;
        std::string::size_type prev = 0;
        while ((pos = str.find(delim, prev)) != std::string::npos)
        {
            strings.push_back(str.substr(prev, pos - prev));
            prev = pos + 1;
        }

        // To get the last substring (or only, if delimiter is not found)
        strings.push_back(str.substr(prev));

        return strings;
    } catch(int e) {
        vector<string> err;
        err[0] = "unsplittable " + e;
        return err;
    }

}

bool manager::isNotWhiteSpace(string str) {
    auto it = str.begin();
    do {
        if (it == str.end()) return false;
    } while (*it >= 0 && *it <= 0x7f && std::isspace(*(it++)));
    // one of these conditions will be optimized away by the compiler,
    // which one depends on whether char is signed or not
    return true;
}

string manager::getNetSubnet(string id) {
    //string str = execCmd("docker inspect " + id + " -f '{{ .IPAM.Config}}'");
    string str;
    str = this->docker->inspect(id, "'{{ .IPAM.Config}}'");

    unsigned first = str.find("[{");
    unsigned last = str.find("  ");
    string strNew = str.substr (first,last - first);
    strNew.erase (0,2);
    //cout << strNew << endl;
    return strNew;
}

string manager::getNetName(string id) {
    string ret;
    ret = docker->inspect(id, "{{.Name}}");
    return ret;
}

string manager::createGwForExam(string sub) {
    vector<string> ip = splitString(sub, ".");
    string gw;
    if(ip.size() == 4){
        ip[3] = "60";
         gw = ip[0] + "." + ip[1] + "." + ip[2] + "." + ip[3];
    }
    else gw = "error";
    return gw;
}

string manager::createSubNetForExam() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, 254);
    int i3 = dist(mt);
    string s3 = to_string(i3);
    string ip = "10.0." + s3 + ".0/24";
    cout << ip;
    return ip;
}

string manager::addNetExam(string name) {
    bool ok = false;
    string res;
    while (!ok){
        string sub = createSubNetForExam();
        string gw = createGwForExam(sub);
        res = docker->addNet(name, sub, gw);
        if (res != "overlapping") ok = true;
    }
    return res;
}

vector<string> manager::readContIfs(string id) {
    string out;
    out = (docker->ifconfig(id, "| grep \"eth\" | awk -F'[: ]+' '{ print $1 }'"));
    cout << out;
    vector<string> ret;
    ret = splitString(out, "\n");
    return ret;
}

bool manager::dockerService() {
    string status = docker->getDockerStatus();
    if (status == "active\n") return 1;
    else {
        docker->startDocker();
        status = docker->getDockerStatus();
        if (status == "active\n") return 1;
        else return 0;
    }
}
