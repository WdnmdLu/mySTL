#include <iostream>
#include <string>
#include <list>
#include <set>
#include "md5.h"
using namespace std;

// Forward declaration
class PhysicalNode;

// 虚拟节点
class VirtualNode {
public:
    VirtualNode(string ip, PhysicalNode* node) : ip_(ip), Node(node) {
        md5_ = getMD5(ip.c_str());
    }

    bool operator<(const VirtualNode& host) const {
        return md5_ < host.md5_;
    }

    bool operator==(const VirtualNode& host) const {
        return md5_ == host.md5_;
    }

    uint getMd5_() const {
        return md5_;
    }

    const PhysicalNode* getPhysicalHost() const {
        return Node;
    }

private:
    string ip_;             // IP address of the virtual node
    uint md5_;              // MD5 value of the IP address
    PhysicalNode* Node;     // Pointer to the physical node
};

// 物理节点
class PhysicalNode {
public:
    PhysicalNode(string ip, int vNumber) : ip_(ip) {
        for (int i = 0; i < vNumber; i++) {
            virtualNodes_.emplace_back(ip + "#" + to_string(i), this);
        }
    }

    string getIp() const {
        return ip_;
    }

    const list<VirtualNode>& getVirtualList() const {
        return virtualNodes_;
    }

private:
    string ip_;                     // IP address of the physical node
    list<VirtualNode> virtualNodes_; // List of virtual nodes
};

// Consistent Hashing class
class ConsistentHash {
public:
    // Add a physical node to the hash circle
    void addHost(PhysicalNode& pHost) {
        const list<VirtualNode>& vNodes = pHost.getVirtualList();
        for (const auto& vNode : vNodes) {
            hashCircle_.insert(vNode);
        }
    }

    // Remove a physical node from the hash circle
    void delHost(PhysicalNode& pHost) {
        const list<VirtualNode>& vNodes = pHost.getVirtualList();
        for (const auto& vNode : vNodes) {
            auto it = hashCircle_.find(vNode);
            if (it != hashCircle_.end()) {
                hashCircle_.erase(it);
            }
        }
    }

    // Get the physical node corresponding to a client IP address
    string getHost(string clientIp) {
        uint md5 = getMD5(clientIp.c_str());
        auto it = hashCircle_.upper_bound(VirtualNode(clientIp, nullptr));
        if (it == hashCircle_.end()) {
            return hashCircle_.begin()->getPhysicalHost()->getIp();
        }
        return it->getPhysicalHost()->getIp();
    }

private:
    set<VirtualNode> hashCircle_;   // Set to store virtual nodes in the hash circle
};

// Main function
int main() {
    PhysicalNode host1("10.127.123.2", 10);
    PhysicalNode host2("10.127.123.5", 10);
    PhysicalNode host3("10.127.123.11", 10);

    ConsistentHash chash;
    chash.addHost(host1);
    chash.addHost(host2);
    chash.addHost(host3);

    // Example usage: finding the host for a client IP
    string clientIp = "192.168.0.3";
    string selectedHost = chash.getHost(clientIp);
    cout << "Client IP " << clientIp << " maps to host " << selectedHost << endl;

    return 0;
}