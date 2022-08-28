#include "../src/number_parser.h"
#include <bitset>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <optional>
#include <random>
#include <sstream>
#include <string>

#define TIME(call, type)                                                         \
    do {                                                                         \
        auto start_##type = high_resolution_clock::now();                        \
        value_##type = call;                                                     \
        auto end_##type = high_resolution_clock::now();                          \
        duration_##type = duration_cast<nanoseconds>(end_##type - start_##type); \
    } while (0);

// some test numbers
std::string input[] = {
    "1",
    "-9223372036854775808",
    "9223372036854775807",
    "1.0",
    "1e1",
    "1.23456",
    "2.22507e-306",
    "1e-307",
    "1.7976931348623157E+307",
};

union DoubleBytes {
    char bytes[8];
    double value;
};

DoubleBytes nextRandom()
{
    DoubleBytes db;
    for (int i = 0; i < 8; i++) {
        db.bytes[i] = std::rand();
    }
    return db;
}

using namespace std::chrono;
int main(int argc, char const* argv[])
{

    Parser::NumberParser("10").parseNumber(); // trick to avoid extra delay due to dynamic linking
    std::cout << std::setw(25) << "String Representation"
              << std::setw(15) << "std::stod"
              << std::setw(15) << "Value"
              << std::setw(15) << "NumberParser"
              << std::setw(15) << "Value"
              << std::setw(25) << "Conversion Error"
              << std::endl;
    for (auto i : input) {
        double value_stnd, value_custom;
        nanoseconds duration_stnd, duration_custom;
        auto parser = Parser::NumberParser(i);
        TIME(parser.parseNumber().value(), custom);
        TIME(std::stod(i), stnd);
        std::cout << std::setw(25) << i
                  << std::setw(15) << duration_stnd.count() << "ns "
                  << std::setw(15) << value_stnd
                  << std::setw(15) << duration_custom.count() << "ns "
                  << std::setw(15) << value_custom
                  << std::setw(25) << (value_custom - value_stnd)
                  << std::endl;
    }
    std::stringstream ss;
    double avgTime = 0;
    int MAX = 50;
    for (int i = 0; i < MAX; i++) {
        double value_stnd, value_custom;
        nanoseconds duration_stnd, duration_custom;
        auto random = nextRandom();
        ss << random.value; // convert double into string
        auto parser = Parser::NumberParser(ss.str());
        TIME(parser.parseNumber().value(), custom);
        TIME(std::stod(ss.str()), stnd);
        // std::cout << duration_custom.count() << " " << duration_stnd.count() << std::endl;
        avgTime += ((double)duration_custom.count() / duration_stnd.count());
        ss.str(""); // reset string stream
    }
    avgTime /= MAX;
    std::cout << "Custom parser is " << avgTime << "x slower than standard parser" << std::endl;
    return 0;
}
