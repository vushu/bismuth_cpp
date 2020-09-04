#pragma once
#include <string>
namespace bi {

    extern bool isLogging;
    void log(std::string message);
    void log(std::string from, std::string message);
    void log(float message);
    void log(int message);

}
