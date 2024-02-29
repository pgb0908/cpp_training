//
// Created by bong on 23. 12. 29.
//


#include <vector>
#include <iostream>
#include <functional>

class A{
public:
    A(int a):value_(a){

    }

    int value_;
    void print(){
        std::cout << value_ << std::endl;
    }


};

int main() {
    A a1(5);
    A a2(3);

    std::vector<std::reference_wrapper<A>> vector;

    vector.push_back(std::ref(a1));
    vector.push_back(std::ref(a2));


    for(auto item : vector){
        item.get().print();
    }

    return 0;
}