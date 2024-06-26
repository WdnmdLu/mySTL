#include "myRedis.h"

const char* myRedis::Parse(std::string line){

    std::string Res;
    // 创建字符串流以解析命令和参数
    std::istringstream iss(line);
    std::string cmd;
    iss >> cmd;
    std::vector<std::string> args;
    // 将命令转换为大写
    std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::toupper);
    if(cmd == "QUIT" || cmd == "EXIT"){
        return "OUT";
    }
    // 对命令进行判断，看底层是想使用哪种数据结构进行存储
    // SET GET DEL(哈希表) RBSET RBGET RBDEL(红黑树) SKSET SKGET SKDEL(跳表)
    if (cmd == "SET") {
        if (!checkArguments(iss, 2, args)) {
            return "Error: SET command requires two arguments (key and value). Please input again.";
        }
        std::string key = args[0];
        std::string value = args[1];
        int num = stringToInt(args[0]);
        Map.Insert(key,value);
        return "Ok";
    } 
    else if(cmd == "GET"){
        if (!checkArguments(iss, 1, args)) {
            Res = cmd + " command requires one argument (key). Please input again.";
            return Res.c_str();
        }
        std::string key = args[0];
        std::cout << cmd << " Key " << key << std::endl;
        const char *R = Map.Find(key);
        if(R == nullptr){
            return "nil";
        }
        std::cout << "GET Res: " << Res<<std::endl;
        return R;
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
        Res = "(integer)" + std::to_string(Num);
        return Res.c_str();
    }
    else{
        std::cerr << "Input Error: Invalid command! Please input again." << std::endl;
        return "Input Error: Invalid command! Please input again.";
    }
    return nullptr;
}