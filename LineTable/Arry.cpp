#include <iostream>
#include <string.h>
#include <time.h>
void Reverse(char str[],int size){
    char temp;
    for(int i=0,j=size-1;i++,j--;){
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        if(i>=j){
            return;
        }
    }
    return;
}
//偶数在左，奇数在右
void Adjust(int arry[],int size){
    int i=0,j=size-1;
    int temp;
    while(i<j)
    {
        if(arry[i]%2 == 0 ){
            i++;
            continue;
        }
        if(arry[j]%2 != 0){
            j--;
            continue;
        }
        temp = arry[i];
        arry[i] = arry[j];
        arry[j] = temp;
        i++,j--;
    }
}


class Array{
public:
    Array(int size = 10): mCap_(size),mCur(0)
    {
        mpArr = new int[size]();
    }
    ~Array(){
        delete []mpArr;
        mpArr = nullptr;
    }
public:
    void push_back(int val){
        if(mCur == mCap_){
            expand(2*mCap_);
        }
        mpArr[mCur++]=val;
    }
    void pop_back(){
        if(mCur == 0){
            return;
        }
        mCur--;
    }
    void insert(int pos,int val){
        if(pos < 0 || pos > mCur){
            return;
        }
        if (mCur == mCap_){
            expand(2 * mCap_);
        }
        for (int i = mCur - 1; i>=pos;i--){
            mpArr[i+1] = mpArr[i];
        }
        mpArr[pos] = val;
        mCur++;
    }
    // 删除指定位置元素
    void erase(int pos){
        if(pos<0 || pos>mCur){
            return;
        }
        for(int i = pos +1;i<mCur;i++){
            mpArr[i - 1] = mpArr[i];
        }
        mCur--;
    }
    int find(int val){
        for(int i = 0;i<mCur;i++){
            if(mpArr[i] == val){
                return i;
            }
        }
        return -1;
    }
    void Show() const{
        for (int i=0;i<mCur;i++){
            std::cout<<mpArr[i]<<" ";
        }
        printf("\n");
    }
private:
    // 扩容到size大小
    void expand(int size){
        int *p = new int[size]();
        memcpy(p,mpArr,sizeof(int)*mCur);
        delete []mpArr;
        mpArr = p;
        mCap_ = size;
    }
private:
    int* mpArr;// 指向可扩容的数组
    int mCap_;// 数组容量
    int mCur;// 数组有效元素个数
};

int main(){
    Array array;
    srand(time(0));
    for(int i=0;i<10;i++){
        array.push_back(rand()%100);
    }
    array.Show();
    array.pop_back();
    array.Show();
    array.insert(2,199);
    array.Show();
    std::cout<<"Find: "<<array.find(199)<<std::endl;
    array.erase(6);
    array.Show();

    char str[]={"Hello World"};
    std::cout<<"Str:"<<str<<std::endl;
    Reverse(str,strlen(str));
    std::cout<<"Str:"<<str<<std::endl;

    int arr[20];
    for(int i=0;i<20;i++){
        arr[i] = rand()%100;
    }
    Adjust(arr,20);
    for(int i=0;i<20;i++){
        std::cout<<arr[i]<<" ";
    }
    printf("\n");
}