#include <iostream>
using namespace std;
//引用是一种声明关系，声明的时候必须初始化。引用不开辟内存空间
//此种声明关系，一经声明，不可变更

// 指针引用
void Swap(char* &p,char* &q){
    char *t;
    t = p;
    p = q;
    q = t;
}

void test01(){
    int a = 500; // <===> *(int*)0xb0002345 = 500  变量名实质是一段内存空间的别名  

    int &ra = a;
    printf("Sizeof(a): %ld  Sizeof(ra): %ld\n",sizeof(a),sizeof(ra));
    printf("Add: a: %p   Add: ra: %p\n",&a,&ra);
    
    char *aa = "Hello";
    char *bb = "World";
    printf("AA: %s BB: %s\n",aa,bb);
    Swap(aa,bb);
    printf("AA: %s BB: %s\n",aa,bb);

    // 数组引用
    int arr[]={1,2,3,4,5};
    // 为什么这样可以
    int (&ar)[5] = arr;

    return;
}
/*
 * 优点：避免调用时的额外开销（入栈与出栈操作）
 * 代价：由于内联函数的函数体在代码段中会出现多个“副本”，因此会增加代码段的空间。
 * 本质：以牺牲代码段空间为代价，提高程序的运行时间的效率。
 * 适用场景：函数体很“小”，且被“频繁”调用。
 */
inline int Add(int &a,int &b){
    return a+b;
}

void test02(){
    // 开辟空间
    int *a = new int(10);
    // 开辟数组空间
    int *p = new int[5]{1,2,3,4,5};
    int i;
    printf("a: %d\n",*a);

    for(i = 0 ; i < 5 ; i++){
        printf("p[%d]:%d   ",i,p[i]);
    }
    printf("\n");

    delete a;
    delete[] p;
}

void test03(){
    int a=10,b=20;
    std::cout<<Add(a,b)<<std::endl;

    int arr[]={1,2,3};
    int *p = arr;
    //cout<<*p++<<endl;
    cout<<(*p)++<<endl;
}

class Base {
public:
    virtual ~Base() {}  // 虚析构函数，启用多态
};

class Derived : public Base {
public:
    void func() {
        printf("Func is running\n");
    }
};

void Cast(const int &data){
    cout<<data<<endl;
}

void test04(){
    float a = 3.14;
    int b = static_cast<int>(a);
    cout<<"B: "<<b<<" A: "<<a<<endl;

    Base* c = new Derived();
    Derived* d = dynamic_cast<Derived*>(c);
    if (d) {
        d->func();  // 安全的向下转型
    }

    delete c;

    Cast(b);
}

int main(){
    test04();

    return 0;
}