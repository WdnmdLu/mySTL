#include <iostream>
#include <string>
class Complex{
    public:
        Complex(int real = 1,int image = 2):real(real),image(image){}
        int real;
        int image;
        Complex operator+(Complex& C1) {
            Complex C2;
            C2.real = this->real + C1.real;
            C2.image = this->image + C1.image; // 使用 C1.image
            return C2;
        }

        Complex& operator=(Complex& C1){
            this->image = C1.image;
            this->real = C1.real;
            return *this;
        }

        bool operator==(Complex& C1){
            return ((C1.image == this->image) && (C1.real == this->real));
        }

        Complex& operator+=(Complex& C1){
            this->image += C1.image;
            this->real += C1.real;
            return *this;
        }

        Complex& operator-=(Complex& C1){
            this->image -= C1.image;
            this->real -= C1.real;
            return *this;
        }

        Complex& operator*=(Complex& C1){
            this->image *= C1.image;
            this->real *= C1.real;
            return *this;
        }
};

std::ostream &operator<<(std::ostream &cout, const Complex& C1) {
    cout << C1.real << " " << C1.image;
    return cout;
}

std::istream &operator>>(std::istream &cin, Complex& C1) {
    cin>>C1.real>>C1.image;
    return cin;
}

class Mail{
    public:
        Mail(const char* Ctx,const char* Til):Context(Ctx),Title(Til)
        {}
        std::string Context;
        std::string Title;
};

class Sender{
    public:
        void operator<<(Mail &mail){
            std::cout<<mail.Title<<"  "<<mail.Context<<std::endl;
            return;
        }

    private:
        Sender(){}
};


int main(){
    Sender *sender = new Sender();
}