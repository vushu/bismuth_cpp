#include <bismuth/logging.hpp>
#include <iostream>

bool bi::isLogging = true;

void bi::log(std::string message) {

    if (bi::isLogging) {
        std::cout << message << std::endl;
    }
}

void bi::log(std::string from,std::string message) {

    if (bi::isLogging) {
        std::cout << from << message << std::endl;
    }
}
