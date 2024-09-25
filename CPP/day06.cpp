#include <iostream>

class Animal{
    public:
        ~Animal(){
            std::cout<<"Animal的析构函数调用"<<std::endl;
        }

        Animal(){
            std::cout<<"Animal的构造函数调用"<<std::endl;
        }

        virtual void Speak(){
            std::cout<<"动物在说话"<<std::endl;
        }
};

class Cat : public Animal{
    public:
        Cat(){
            std::cout<<"Cat的构造函数调用"<<std::endl;
        }

        ~Cat(){
            std::cout<<"Cat的析构函数调用"<<std::endl;
        }

        void Speak(){
            std::cout<<"小猫在说话"<<std::endl;
        }
};

void doSpeak(Animal& animal){
    animal.Speak();
}

int main(){
    Cat cat;
    doSpeak(cat);
}