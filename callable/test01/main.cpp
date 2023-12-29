//
// Created by bont on 23. 12. 29.
//

#include <string>
#include <iostream>
#include <functional>

using namespace std;

int some_function(const string& str){
    cout << "some_function : " << str << endl;
    return 0;
}

class SomeClass {
public:
    SomeClass():a_(0){};
    explicit SomeClass(int some):a_(some){}

    int func(){
        cout << "inner value : " << a_ << endl;
        return 0;
    }

private:
    int a_;
};

int main(){

    std::function<int(const std::string&)> f1 = some_function;
    f1("hello");


    std::function<int(SomeClass&)> f2 = &SomeClass::func;
    SomeClass someClass;
    f2(someClass);

    std::function<void()> f3 = [](){
                        cout << "function3 : this" << endl;
                        return; };

    f3();

    return 0;
}