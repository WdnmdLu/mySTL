#include "myRedis.h"
#include <string.h>

void myRedis::Parse(std::string line,char *Res){

    // 创建字符串流以解析命令和参数
    std::istringstream iss(line);
    std::string cmd;
    iss >> cmd;
    std::vector<std::string> args;
    // 将命令转换为大写
    std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::toupper);
    // 解析命令，根据命令去选择底层的数据结构进行操作
    if(cmd == "QUIT" || cmd == "EXIT"){
        strcpy(Res,"OUT");
        return;
    }
    // 对命令进行判断，看底层是想使用哪种数据结构进行存储
    // SET GET DEL(哈希表/默认) RBSET RBGET RBDEL(红黑树) SKSET SKGET SKDEL(跳表)
    // BSET BGET BDEL(平衡二叉树)
    // 需要进行命令的解析，根据命令决定使用哪种数据结构进行操作
    std::string str(this->cmd.Find(cmd));
    int Value = std::stoi(str);
    switch (Value)
    {
    case 0:{
            Hash(cmd,args,iss,Res);
        }
        break;
    case 1:
        Tree(cmd,args,iss,Res);
        break;
    case 2:
        
        break;
    case 3:
        
        break;
    default:
        break;
    }
}

//哈希表
void myRedis::Hash(std::string &cmd,std::vector<std::string> &args,std::istringstream &iss,char *Res){
    if (cmd == "SET") {
        if (!checkArguments(iss, 2, args)) {
            strcpy(Res,"Error: SET command requires two arguments (key and value). Please input again.");
            return;
        }
        std::string key = args[0];
        std::string value = args[1];
        int num = stringToInt(args[0]);
        Map.Insert(key,value);
        strcpy(Res,"OK");
    } 
    else if(cmd == "GET"){
        if (!checkArguments(iss, 1, args)) {
            strcpy(Res,"Error: GET command requires one arguments (key). Please input again.");
            return;
        }
        std::string key = args[0];
        std::cout << cmd << " Key " << key << std::endl;
        const char *R = Map.Find(key);
        if(R == nullptr){
            strcpy(Res,"nil");
            return;
        }
        strcpy(Res,R);
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
        std::string str = "(integer)" + std::to_string(Num);
        strcpy(Res,str.c_str());
    }
    else{
        std::cerr << "Input Error: Invalid command! Please input again." << std::endl;
        strcpy(Res,"Input Error: Invalid command! Please input again.");
    }
}

//二叉树
void myRedis::Tree(std::string &cmd,std::vector<std::string> &args,std::istringstream &iss,char *Res){
    if (cmd == "BSET") {
        if (!checkArguments(iss, 2, args)) {
            strcpy(Res,"Error: SET command requires two arguments (key and value). Please input again.");
            return;
        }
        std::string key = args[0];
        std::string value = args[1];
        int num = stringToInt(args[0]);
        printf("Tree Insert Key: %s  Value: %s\n",key.c_str(),value.c_str());
        tree.Insert(key,value);
        strcpy(Res,"OK");
    } 
    else if(cmd == "BGET"){
        if (!checkArguments(iss, 1, args)) {
            strcpy(Res,"Error: GET command requires one arguments (key). Please input again.");
            return;
        }
        std::string key = args[0];
        std::cout << cmd << " Key " << key << std::endl;
        tree.Find(key,Res);
        if(Res == nullptr || strlen(Res) == 0){
            printf("Find Error 1111\n");
            strcpy(Res,"nil");
            return;
        }
        printf("Find Ok 1111\n");
    }
    else if(cmd == "BDEL"){
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
        std::string str = "(integer)" + std::to_string(Num);
        strcpy(Res,str.c_str());
    }
    else{
        std::cerr << "Input Error: Invalid command! Please input again." << std::endl;
        strcpy(Res,"Input Error: Invalid command! Please input again.");
    }
}
// 红黑树
void myRedis::RBTree(std::string &cmd,std::vector<std::string> &args,std::istringstream &iss,char *Res){
    
}
// 跳表
void myRedis::SKlist(std::string &cmd,std::vector<std::string> &args,std::istringstream &iss,char *Res){
    
}

myRedis::myRedis(){
    // 命令初始化，将所有的命令都放入到cmd这个map中，然后再从这里进行调用查看就可
    // 哈希
    this->cmd.Insert("GET","0");
    this->cmd.Insert("SET","0");
    this->cmd.Insert("DEL","0");
    // 平衡二叉树
    this->cmd.Insert("BSET","1");
    this->cmd.Insert("BGET","1");
    this->cmd.Insert("BDEL","1");
    // 红黑树
    this->cmd.Insert("RBSET","2");
    this->cmd.Insert("RBGET","2");
    this->cmd.Insert("RBDEL","2");
    // 跳表
    this->cmd.Insert("SKSET","3");
    this->cmd.Insert("SKGET","3");
    this->cmd.Insert("SKDEL","3");
}