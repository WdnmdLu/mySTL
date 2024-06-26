#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <vector>
#include <sstream>
#include <algorithm>
#include "stringhash.h"
#include "unordered_map.hpp"


int main() {
    unordered_map Map;
    std::string line;
    while (true) {
        // 输出提示符
        std::cout<<">> ";
        // 读取整行输入
        if (!std::getline(std::cin, line)) {
            break;  // 如果读取失败（例如遇到EOF），则退出循环
        }
        // 创建字符串流以解析命令和参数
        std::istringstream iss(line);
        std::string cmd;
        iss >> cmd;
        std::vector<std::string> args;
        // 将命令转换为大写
        std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::toupper);
        if(cmd == "QUIT" || cmd == "EXIT"){
            break;
        }
        if (cmd == "SET") {
            if (!checkArguments(iss, 2, args)) {
                std::cerr << "Error: SET command requires two arguments (key and value). Please input again." << std::endl;
                continue;
            }
            std::string key = args[0];
            std::string value = args[1];
            int num = stringToInt(args[0]);
            std::cout << "Set value " << value << " to key " << key << std::endl;
            Map.Insert(key,value);
        } 
        else if(cmd == "GET"){
            if (!checkArguments(iss, 1, args)) {
                std::cerr << "Error: " << cmd << " command requires one argument (key). Please input again." << std::endl;
                continue;
            }
            std::string key = args[0];
            std::cout << cmd << " Key " << key << std::endl;
            const char *Res = Map.Find(key);
            if(Res == nullptr){
                std::cout<<"nil"<<std::endl;
                continue;
            }
            std::cout << "GET Res: " << Res<<std::endl;
        }
        else if(cmd == "DEL"){
            std::string arg;
            int count = 0;
            while (iss >> arg) {
                args.push_back(arg);
                count++;
            }
            int Num = 0;
            for(int i = 0;i<count;i++){
                if(1 == Map.Delete(args[i])){
                    Num++;
                }
            }
            std::cout<<"(integer)"<<Num<<std::endl;
            
        }
        else{
            std::cerr << "Input Error: Invalid command! Please input again." << std::endl;
            continue;
        }
    }
    return 0;
}