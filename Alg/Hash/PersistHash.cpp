#include <iostream>
#include <string>
#include <list>
#include <set>
#include "md5.h"
using namespace std;
using uint = unsigned int;
class PhySicalNode;
// 虚拟节点
class VirtualNode{
public:
    VirtualNode(string ip,PhySicalNode* node):ip_(ip),Node(node){
        md5_ = getMD5(ip.c_str());
    }
    bool operator<(const VirtualNode& host) const 
    {
        return md5_ < host.md5_; 
    }
    bool operator==(const VirtualNode& host) const 
    {
        return md5_ == host.md5_;
    }
    uint getMd5_() const{
        return md5_;
    }
    const PhysicalNode *getPhysicalHost() const{
        return Node;
    }
private:
    string ip_;// 虚拟节点的ip
    uint md5_;// 虚拟节点的md5值
    PhySicalNode *Node;// 虚拟节点属于哪个物理节点的ip
};
// 物理节点
class PhysicalNode{
public:
    PhysicalNode(string ip,int vNumber):ip_(ip)
    {
        for(int i = 0;i < vNumber ; i++){
            virtualNodes_.emplace_back(
                ip + "#" + ::to_string(i),
                this
            )
        }
    }
    string getIp() const{
        return ip_;
    }
    list<virtualNodes_>& getVirtualList() const{
        return virtualNodes_;
    }

private:
    string ip_;
    list<VirtualNode> virtualNodes_;
};

class ConsistHash{
public:
    // 添加到哈希环上
    void addHost(PhysicalNode &pHost){
        //获取物理主机上的所有虚拟主机
        list<VirtualNode> &list = pHost.getVirtualList();
        for(auto host : list){
            hashCircle_.insert(host);
        }
    }
    void delHost(PhySicalNode &pHost){
        list<VirtualNode> &list = pHost.getVirtualList();
        for(auto host : list){
            auto it = hashCircle_.find(host);
            if(it != hashCircle_.end()){
                hashCircle_.erase(it);
            }
        }
    }
    string getHost(string clientIp){
        uint md5 = getMD5(clientIp.c_str());
        for(auto host : hashCircle_){
            if(host.getMd5_() > md5){
                return host.getPhysicalHost()->getIp();
            }
        }
        //返回从0开始的第一个节点
        return hashCircle_.begin()->getPhysicalHost()->getIp();
    }
private:
    set<VirtualNode> hashCircle_;
};

// 一致性哈希算法的实现
int main(){
    PhysicalNode host1("10.127.123.2",10);

    PhysicalNode host1("10.127.123.5",10);

    PhysicalNode host1("10.127.123.11",10);

    ConsistHash chash;
    chash.addHost(host1);
    chash.addHost(host2);
    chash.addHost(host3);
}