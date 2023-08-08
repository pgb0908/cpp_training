#include <iostream>
#include <vector>
#include <memory>

class Filter{
public:
    Filter(int a, int b, int c){
        a_ = a;
        b_ = b;
        c_ = c;

    }

    void show() const{
        std::cout << a_ << " " << b_ << " " << c_ << std::endl;
    }

private:
    int a_;
    int b_;
    int c_;

};

class Chain {
public:
    template<typename T, typename ...Args>
    Chain& add(Args&&... args){
        chain_.push_back(std::make_unique<Filter>(std::forward<Args>(args)...));
        return *this;
    }

    std::vector<std::unique_ptr<Filter>> get() {
        return std::move(chain_);
    }

private:
    std::vector<std::unique_ptr<Filter>> chain_;

};

int main() {
    Chain chain;
    chain.add<Filter>(1,2,3);

    auto item = chain.get();

    for(auto& temp : item){
        temp->show();
    }

    return 0;
}
