#include <iostream>
#include "log4cpp/NDC.hh"

using namespace log4cpp;

int main(int argc, char** argv) {
    std::cout << "1. empty NDC: " << NDC::get() << std::endl;

    NDC::push("context1");
    std::cout << "2. push context1: " << NDC::get() << std::endl;
    
    NDC::push("context2");
    std::cout << "3. push context2: " << NDC::get() << std::endl;
    std::cout << "4. get depth: " << NDC::getDepth() << std::endl;

    std::cout << "5. pop: " << NDC::pop() << std::endl;

    NDC::clear();
    std::cout << "6. clear: " << NDC::get() << std::endl;

    return 0;
}
    
    
