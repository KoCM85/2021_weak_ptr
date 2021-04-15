#include <iostream>
#include <memory>

// std::weak_ptr break reference cycles

class POP;

class dre {
    std::weak_ptr<POP> sha_dre; // if replace std::weak_ptr<POP> sha_dre; to std::shared_ptr<POP> sha_dre; will be memory leak

public:
    dre() { std::cout << "dre() \n"; }
    dre(std::shared_ptr<POP> ptr_in) : sha_dre(ptr_in) { std::cout << "dre(std::shared_ptr<POP>) \n"; }
    ~dre() { std::cout << "~dre() \n"; }
};

class POP : public std::enable_shared_from_this<POP> {
    std::shared_ptr<dre> ini;

public:
    POP() { std::cout << "POP() \n"; }
    ~POP() { std::cout << "~POP() \n"; }

    inline void set();
};

void POP::set() {
    ini = std::make_shared<dre>(shared_from_this());
}


int main() {
    {
        std::shared_ptr<POP> pop_1 = std::make_shared<POP>();
        pop_1->set();
    }

    return 0;
}