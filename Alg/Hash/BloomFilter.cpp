#include "stringhash.h"
#include <iostream>
#include <vector>

using namespace std;
// 布隆过滤器实现
class BloomFilter{

public:
    BloomFilter(int size = 1471)
        : bitSize_(size){
            bitMap_.resize(bitSize_ / 32 + 1);
        }

    void SetBit(const char *str){
        int idx1 = BKDRHash(str) % bitSize_;
        int idx2 = SDBMHash(str) % bitSize_;
        int idx3 = RSHash(str) % bitSize_;

        //把相应的idx1  idx2  idx3这几位全部置1
        int index = 0;
        int offset = 0;

        index = idx1 / 32;
        offset = idx1 % 32;
        bitMap_[index] |= (1 << offset);

        index = idx2 / 32;
        offset = idx2 % 32;
        bitMap_[index] |= (1 << offset);

        index = idx3 / 32;
        offset = idx3 % 32;
        bitMap_[index] |= (1 << offset);
    }

    bool getBit(const char *Key){
        int idx1 = BKDRHash(str) % bitSize_;
        int idx2 = SDBMHash(str) % bitSize_;
        int idx3 = RSHash(str) % bitSize_;

        int index = 0;
        int offset = 0;

        index = idx1 / 32;
        offset = idx1 % 32;
        if(0 == (bitMap_[index] & (1 << offset))){
            return false;
        }
        index = idx2 / 32;
        offset = idx2 % 32;
        if(0 == (bitMap_[index] & (1 << offset))){
            return false;
        }
        index = idx3 / 32;
        offset = idx3 % 32;
        if(0 == (bitMap_[index] & (1 << offset))){
           return false;
        }
        return true;
    }
private:
    int bitSize_;// 位图长度
    vector<int> bitMap_;// 位图数组
};

int main(){

}