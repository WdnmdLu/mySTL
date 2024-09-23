#include <iostream>
#include <string>
#include <string.h>
#include <time.h>
#include <unistd.h>
using namespace std;
class list{
    public:
        list(){
            head = (Node*)malloc(sizeof(Node));
            head->next = NULL;
            size = 0;
        }
        // 头插
        void InsertByHead(int data){
            Node *newNode = (Node*)malloc(sizeof(Node));
            newNode->next = NULL;
            newNode->data = data;
            if(size == 0){
                tail = newNode;
            }

            newNode->next = head->next;
            head->next = newNode;
            size++;
        }
        // 尾插
        void InsertByTail(int data){
            Node* newNode = (Node*)malloc(sizeof(Node));
            newNode->next = NULL;
            newNode->data = data;
            if(size == 0){
                tail = newNode;
                head->next = newNode;
            }
            else{
                tail->next = newNode;
                tail = newNode;
            }
        }
        // 数据删除，删除指定的数据data
        void Delete(int data){
            Node *pMove = head->next;
            Node *pre = head;
            while(pMove != NULL){
                if(pMove->data == data){
                    pre->next = pMove->next;
                    if(pMove == tail){
                        if(size == 1){
                            delete(pMove);
                            pMove = NULL;
                        }
                        else{
                            tail = pre;
                            delete(pMove);
                        }
                    }
                    else{
                        delete(pMove);
                    }
                    size--;
                }
            }
        }
        //
    private:
        struct Node{
            struct Node *next;
            int data;
        };
        struct Node *head;
        struct Node *tail;
        int size;
};

class Complex{
    public:
        Complex():a(10),b(20),Name("Ok"){
            c = new char[5];
            strcpy(c,"Hello");
            printf("Complex的构造函数\n");
        }
        
        // 拷贝构造，深拷贝
        Complex(const Complex &other){
            this->c = new char[5];
            strcpy(this->c,other.c);
            this->a = other.a;
            this->b = other.b;
            this->Name = other.Name;
            printf("Complex的拷贝构造调用\n");
        }

        Complex &operator=(const Complex &c1){
            this->a = c1.a;
            this->b = c1.b;
            this->Name = c1.Name;
            strcpy(this->c,c1.c);
            return *this;
            printf("Complex的 = 重载调用\n");
        }

        Complex &operator+(const Complex &c1){
            this->a = this->a + c1.a;
            this->b = this->b + c1.b;
            return *this;
            printf("Complex的 + 重载调用\n");
        }
        
        int a;
        int b;
        char *c;
        string Name;
        ~Complex(){
            delete[] c;
            printf("Complex的析构函数\n");
        }
};

Complex &AA(Complex &other){
    printf("AA Running\n");
    return other;
}

void test(){
    Complex c1;
    c1.a = 3;
    c1.b = 4;
    Complex c2(c1);

    Complex c3;
    c3 = c2+c1;
    printf("C3: a: %d b: %d  Name: %s  c: %s\n",c3.a,c3.b,c3.Name.c_str(),c3.c);

    Complex c4;
    c4 = AA(c3);

    printf("C4: a: %d b: %d  Name: %s  c: %s\n",c3.a,c3.b,c3.Name.c_str(),c3.c);
}

void test01(){
    Complex C1;
    printf("%p\n",&C1);
    printf("%p\n",&AA(C1));
    Complex C2 = AA(C1);
}

class Clock{
    public:
        void Show(){
            system("clear");
            cout<<Hour<<" : "<<Minutes<<" : "<<Seconds<<endl;
        }
        void Trick(){
            sleep(1);
            Seconds += 1;
            if(Seconds == 60){
                Seconds = 0;
                Minutes += 1;
                if(Minutes == 60){
                    Minutes = 0;
                    Hour += 1;
                    if(Hour == 24){
                        Hour = 0;
                    }
                }
            }
        }

        void Run(){
            while(1){
                Trick();
                Show();
            }
        }

        Clock()
        {
            time_t t = time(NULL);
            tm local = * localtime(&t);
            Hour = local.tm_hour;
            Minutes = local.tm_min;
            Seconds = local.tm_sec;
        }

    private:
        // 时
        int Hour;
        // 分
        int Minutes;
        // 秒
        int Seconds;
};

void ClockRun(){
    Clock clock;
    clock.Run();
}

class AAA{
    public:
        void Speak(int a){
            printf("Do Speaking\n");
        }

        void Doing(int b)const {


        }

        int aa = 10;
};

class Student
{
    public:
    Student(string n, int nu):name(n),num(nu){}
    void dis()
    {
    cout<<"name "<<name<<" num "<<num<<endl;
    }
    private:
    string name;
    int num;
};

void test04(){

    Student s("zhangsan",1002);
    Student s2("lisi",1001);
    Student *ps = new Student("wangwu",1003);
    void (Student::*pf)() = &Student::dis;
    (s.*pf)();
    (s2.*pf)();
    (ps->*pf)();

    AAA *aaa = nullptr;
    aaa->Speak(10);

}

int main(){
    test01();
}