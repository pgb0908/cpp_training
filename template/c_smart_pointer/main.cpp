//
// Created by bont on 24. 2. 29.
//

#include <memory>
#include <iostream>


template<class T>
class CuniquePtr : public std::unique_ptr<T>{
public:
    CuniquePtr() : std::unique_ptr<T>(){
        std::cout << "counstructor" << std::endl;
    }
    explicit CuniquePtr(T* object) : std::unique_ptr<T>(object){
        object->print();
    }
};

template <class T, void (*deleter)(T*)>
class CSmartPtr : public std::unique_ptr<T, void (*)(T*)> {
public:
    CSmartPtr() : std::unique_ptr<T, void (*)(T*)>(nullptr, deleter) {}
    CSmartPtr(T* object) : std::unique_ptr<T, void (*)(T*)>(object, deleter) {}
};

class TEST_A{
public:
    TEST_A(std::string ss){
        ss_ = ss;
    };

    ~TEST_A(){
      std::cout << "Destructor activate!!!" << std::endl;
    };

    void print(){
        std::cout << "ss : "  << ss_ << std::endl;
    }

private:
    std::string ss_;
};

void deleteTest(TEST_A* a){
    delete a;
};


int main() {
    auto aa = new TEST_A("hello");
    auto ss = CSmartPtr<TEST_A, deleteTest>(aa);
    //ss->print();

    auto bb = new TEST_A("hi");
    auto sss = CuniquePtr<TEST_A>(bb);

    return 0;
}