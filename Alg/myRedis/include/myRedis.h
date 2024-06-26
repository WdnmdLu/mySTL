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

class myRedis{
public:
    static myRedis &GetInstance(){
        static myRedis Instance;
        return Instance;
    }
    ~myRedis(){}
    const char* Parse(std::string line);
private:
    unordered_map Map;
};