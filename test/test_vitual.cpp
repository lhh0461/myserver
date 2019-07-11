#include <iostream>
#include <string>

using namespace std;

namespace XEngine  {

template<typename T>
class CMemoryPool {
public:
    CMemoryPool() = default;
    virtual ~A() { cout << "a destruct" <<endl;};
private:
    int a;
};

class B : public A {
public:
    B() = default;
    ~B() {cout << "b destruct" <<endl;};
private:
    int b;
};

}

int main()
{
    A *a = new B();
    delete a;
}

