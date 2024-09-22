#include <iostream>

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

    int (&ar)[5] = arr;

    return;
}

int main(){
    test01();

    return 0;
}