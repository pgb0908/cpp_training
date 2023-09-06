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
    Chain& add(Args&&... args){  // R-value 인자들로 넘겨줌
        chain_.push_back(std::make_unique<T>(std::forward<Args>(args)...)); // forward를 통해 args는 r-value라는 것을 앎
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

    for(const auto& temp : item){
        temp->show();
    }

    return 0;
}
