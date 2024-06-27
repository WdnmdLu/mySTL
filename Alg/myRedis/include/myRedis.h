#pragma once
#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <vector>
#include <sstream>
#include <algorithm>
#include "stringhash.h"
#include "unordered_map.h"
#include "ReactorV2.h"
#include "Bst.h"

class myRedis{
public:
    static myRedis &GetInstance(){
        static myRedis Instance;
        return Instance;
    }
    
    void Parse(std::string line,char *Res);
    void Hash(std::string &cmd,std::vector<std::string> &args,std::istringstream &iss,char *Res);
    void Tree(std::string &cmd,std::vector<std::string> &args,std::istringstream &iss,char *Res);
    void RBTree(std::string &cmd,std::vector<std::string> &args,std::istringstream &iss,char *Res);
    void SKlist(std::string &cmd,std::vector<std::string> &args,std::istringstream &iss,char *Res);
private:
    ~myRedis(){}
    myRedis();
    unordered_map Map;
    BST tree;
    //所有的命令都存储在这里
    unordered_map cmd;
};