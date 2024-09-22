#include <iostream>
#include <string>
#include <map>
using namespace std;

class Animal{
    public:
        int a;
        int b;
};

/*
 * const的编译方式不同，C中，const就是当作一个变量来编译生成指令的。
 * C++中，所有出现const常量名字的地方，都被常量的初始化替代了，可以将其看作一个宏替换
*/
void Const(){
    const int a = 20;
    // 不同类型之间无法之间进行赋值
    // int * != const int *
    //int *p = &a;

    bool T = 0;
    if(T){
        printf("True  %d\n",T);
    }
    else{
        printf("False %d\n",T);
    }
}

void test(){
    int a;
    int b;
    int c = (a = 10) + (b = 20);
    printf("C: %d  A: %d  B: %d\n",c,a,b);

    map<Animal,int> Map;
    Animal a1;
    Animal a2;
    a1.a = 10,a1.b = 20;
    a2.a = 30,a2.b = 40;
}
/* ----------------------------------------- */
void test02(){
    int a,b;
    cin>>a>>b;
    cout<<a<<"  "<< b <<endl;
}
/* ---------------------------------------- */
// 函数重载，函数名相同，函数的参数类型不同就会构成重载
int func(int a){
    printf("func(int a)\n");

    return 0;
}

int func(int a,int b){
    printf("func(int a,int b)\n");
    return 0;
}

void test03(){
    func(10);
    func(10,20);
}

/* ---------------------------------- */

struct Complex{
    float real;
    float image;
};

Complex operator+(Complex a,Complex b){
    Complex c;
    c.real = a.real + b.real;
    c.image = a.image + b.image;
    return c;
}

void test04(){
    Complex a;
    Complex b;
    a.real = 1.11;
    a.image = 2.22;
    b.real = 3.33;
    b.image = 4.44;

    Complex c = a+b;
    printf("%.2f  %.2f\n",c.image,c.real);
}
/* ------------------------------ */

void Print(int a,int b = 10){

}

void Print(int a){

}

int main(){
    Print(10,20);
    Print(10);
}