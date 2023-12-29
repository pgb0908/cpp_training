//
// Created by bont on 23. 12. 29.
//
#include <string>
#include <iostream>
#include <functional>

using namespace std;

int add(int a, int b){
    cout << a << " + " << b << " = " << a+b << endl;
    return a+b;
}

class SomeClass{
public:
    SomeClass(int val):val_(val){
    }

    int val_;

    void do_something(){
        cout << "value : " << val_ << endl;
    }
};

void do_something(SomeClass& s1, SomeClass& s2){
    s1.val_ = s2.val_ +5;
}

int main(){

    // sample 1
    auto add_func1 = bind(add, 2, 3);
    auto rtn1 = add_func1(1, 2);
    auto rtn2 = add_func1(4, 5);
    cout << "rtn1 is " << rtn1 << endl;
    cout << "rtn2 is " << rtn2 << endl << endl;

    auto add_func2 = bind(add, placeholders::_1, placeholders::_2);
    auto rtn3 = add_func2(1, 2);
    auto rtn4 = add_func2(4, 5);
    cout << "rtn3 is " << rtn3 << endl;
    cout << "rtn4 is " << rtn4 << endl << endl;


    // sample 2
    auto func1 = bind(do_something,  placeholders::_1, placeholders::_2);
    SomeClass someClass1(0);
    SomeClass someClass2(1);
    func1(someClass1, someClass2);

    cout << "someClass1 value : " << someClass1.val_ << endl;

    return 0;
}