#include <iostream>
#include "log4cpp/Priority.hh"

using namespace log4cpp;

int main(int argc, char** argv) {
    
    std::cout << "priority debug(700): " << Priority::getPriorityName(700) << endl;
    std::cout << "priority debug(700): " << Priority::getPriorityValue("DEBUG") << endl;
    std::cout << "priority debug(700): " << Priority::getPriorityValue("700") << endl;
    try {
	std::cout << "priority debug(700): " << Priority::getPriorityValue("700arghh") << endl;
    } catch(std::invalid_argument& e) {
	std::cout << "caught " << e.what() << endl;
    }
    return 0;
}
