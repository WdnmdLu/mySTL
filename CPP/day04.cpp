#include <iostream>
template <typename T>
class unique_ptr{
    public:
        explicit unique_ptr(T* p = nullptr) : ptr(p) {}

        // 析构函数
        ~unique_ptr() {
            delete ptr; // 释放资源
        }

        T &operator*(){
            return *ptr;
        }

        T *operator->(){
            return ptr;
        }
        
        unique_ptr(const unique_ptr&) = delete;

    private:
        

        T *ptr;
};

template <typename T>
class Share_ptr{
    public:
        Share_ptr(T* p = nullptr) : ptr(p), ref_count(p ? new int(1) : nullptr) {}

        Share_ptr(const Share_ptr& other) : ptr(other.ptr), ref_count(other.ref_count) {
            if (ptr) {
                ++(*ref_count);
            }
        }
        // 传入一个右值
        Share_ptr(Share_ptr&& other) noexcept : ptr(other.ptr), ref_count(other.ref_count) {
            other.ptr = nullptr;
            other.ref_count = nullptr;
        }
        // 赋值构造
        Share_ptr& operator=(const Share_ptr& other) {
            if (this != &other) {
                reset();
                ptr = other.ptr;
                ref_count = other.ref_count;
                if (ptr) {
                    ++(*ref_count);
                }
            }
            return *this;
        }
        // 对于右值的构造
        Share_ptr& operator=(Share_ptr&& other) noexcept {
            if (this != &other) {
                reset();
                ptr = other.ptr;
                ref_count = other.ref_count;
                other.ptr = nullptr;
                other.ref_count = nullptr;
            }
            return *this;
        }

        T& operator*() const {
            return *ptr;
        }

        // 重载 -> 操作符
        T* operator->() const {
            return ptr;
        }

        // 获取当前引用计数
        int use_count() const {
            return ref_count ? *ref_count : 0;
        }

        void reset(T* p = nullptr) {
            if (ptr != p) {
                delete_ptr();
                ptr = p;
                ref_count = p ? new int(1) : nullptr;
            }
        }

        // 删除当前管理的指针
        void delete_ptr() {
            if (ptr && --(*ref_count) == 0) {
                delete ptr;
                delete ref_count;
            }
        }

    private:
        int *ref_count;
        T *ptr;
};

class Test{
    public:
        int a;
        int b;

        void Func(){
            printf("Func is Running\n");
        }
};

int main(){
    unique_ptr<int> ptr(new int(20));

    unique_ptr<Test> test(new Test());
    test->Func();
    test->a = 10;
    test->b = 20;

}