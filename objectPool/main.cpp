#include "iostream"
#include "c++/objectPool.h"
void testLongLifeFactory();
void testShortLifeFactory();

int main(int argc, char *argv[]){
    testLongLifeFactory();
    testShortLifeFactory();
    return 0;
}

void testLongLifeFactory(){
    std::shared_ptr<ObjectFactory> factory = std::make_shared<ObjectFactory>();
    {
        std::shared_ptr<Object> o0 = factory->get("IBM");
        std::shared_ptr<Object> o1 = factory->get("IBM");
        if(o0 == o1){
            std::cout << "o0 == o1" << std::endl;
        }
    }
}

void testShortLifeFactory(){
    std::shared_ptr<Object> o0;
    {
        std::shared_ptr<ObjectFactory> factory = std::make_shared<ObjectFactory>();
        o0 = factory->get("IBM");
        std::shared_ptr<Object> o1 = factory->get("IBM");
        if(o0 == o1){
            std::cout << "o0 == o1" << std::endl;
        }
    }
}