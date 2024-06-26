#pragma once
#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <vector>
#include <sstream>
#include <algorithm>
#include "stringhash.h"
struct Node{
    std::string Key;
    std::string Value;
    int flag;// 这个用于说明我的value值是数字还是字符串  value=0 数字 value=1 字符串
    Node *next;
};

struct List{
    Node *head;
    int Curr=0;
};

// 寻找下一个素数
int SuNum(int value);



int stringToInt(const std::string& str);

bool checkArguments(std::istringstream& iss, int expectedArgs, std::vector<std::string>& args);

class unordered_map{
public:
    unordered_map();

    ~unordered_map();

    void Insert(std::string Key, std::string value);
    int Delete(std::string Key);
    const char* Find(std::string Key);
    bool ChangValue(std::string Key,std::string value);

private:
    void Expand();

    int HashFunction(std::string key);

    int Size;
    int Cap;
    List* arr;
    double status;
};