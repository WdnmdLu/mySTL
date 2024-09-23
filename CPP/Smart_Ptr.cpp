#include <iostream>
#include <memory>
using namespace std;
class Test {
public:
	Test() { cout << "Test的构造函数..." << endl; }
	~Test() { cout << "Test的析构函数..." << endl; }

	int getDebug() { return this->debug; }

private:
	int debug = 20;
};

int main(){

    Test *t = new Test();
    auto_ptr<Test> test(t);

	cout << "test->debug：" << test->getDebug() << endl;
	cout << "(*test).debug：" << (*test).getDebug() << endl;

    int *a = new int(10);
    unique_ptr<int> ptr1(a);
    cout<<*ptr1<<endl;

    int *b = new int(30);
    shared_ptr<int> ptr2(b);
    shared_ptr<int> ptr3(std::move(ptr2));
    cout<<"Ptr2: "<<ptr2.use_count()<<" Ptr3: "<<ptr3.use_count()<<endl;
}