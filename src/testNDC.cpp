#include "log4cpp/NDC.hh"

using namespace log4cpp;

int main(int argc, char** argv) {
    cout << "1. empty NDC: " << NDC::get() << endl;

    NDC::push("context1");
    cout << "2. push context1: " << NDC::get() << endl;
    
    NDC::push("context2");
    cout << "3. push context2: " << NDC::get() << endl;
    cout << "4. get depth: " << NDC::getDepth() << endl;

    cout << "5. pop: " << NDC::pop() << endl;

    NDC::clear();
    cout << "6. clear: " << NDC::get() << endl;
}
    
    
