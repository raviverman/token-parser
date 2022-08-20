/*
 * File: parser.cpp
 * Project: token-parser
 * File Created: Saturday, 20th August 2022 5:39:01 pm
 * Author: Ravi Verman (raviverman@hotmail.com)
 * -----
 * Last Modified: Sunday, 21st August 2022 12:32:27 am
 * Modified By: Ravi Verman (raviverman@hotmail.com)
 * -----
 * SPDX-License-Identifier: GPL-2.0-only 
 * Copyright 2022 - 2022 Ravi Verman, Ravi Verman
 */

#include<iostream>
#include<string>
#include<sstream>
#include<optional>

namespace CLI {
    std::string displayPrompt() {
        std::cout<<">>> ";
        std::string input;
        getline(std::cin, input);
        return input;
    }
}

// Number Grammar (picked from JSON grammar https://www.json.org/json-en.html)

// number -> integer fraction exponent
// integer -> digit | onenine digits | '-' digit | '-' onenine digits
// digits -> digit | digit digits
// digit -> 0 | onenine
// onenine -> 1-9
// fraction -> "" | '.' digits
// exponent -> 'e' sign digits | 'E' sign digits | ""
// sign -> + | - | ""

class Parser {
    std::string m_input;
    int m_current_pos;
    std::string m_err_msg;
    std::stringstream m_parse_info;
    public:
        Parser(std::string input) {
            m_input = input;
            m_current_pos = 0;
        }

        std::string parseInfo() {
            return m_parse_info.str();
        }

        void next() {
            m_current_pos++;
        }

        // returns true if end of input has been reached
        bool eoi(int index = 0) {
            if (m_current_pos + index >= m_input.size()) {
                return true;
            }
            return false;
        }

        bool isNext(const char& character ) {
            if (eoi()) {
                return false;
            }
            return m_input[m_current_pos] == character;
        }

        bool isAny(const std::string chars) {
            if (eoi()) {
                return false;
            }
            auto next = peek().value();
            for(auto &element : chars ) {
                if ( element == next ) {
                    return true;
                }
            }
            return false;
        }

        std::optional<char> consumeSpecific(const char& character) {
            if (eoi()) {
                return std::nullopt;
            }
            if (m_input[m_current_pos] != character) {
                return std::nullopt;
            }
            m_current_pos++;
            return m_input[m_current_pos-1];
        }

        // consume any of the given characters.
        // one of the characters must be present, do precheck
        // consumes next character anyway
        std::optional<char> consumeAny(const std::string characters) {
            if (eoi()) {
                return std::nullopt;
            }
            auto next = peek().value();
            for(auto &ch : characters) {
                if (ch == next) {
                    break;
                }
            }
            m_current_pos++;
            return m_input[m_current_pos-1];
        }

        std::string consumeUntil(const char& character) {
            if (eoi()) {
                return "";
            }
            std::stringstream ss;
            while(!eoi() && m_input[m_current_pos] != character) {
                ss<<m_input[m_current_pos++];
            }
            return ss.str();
        }

        // look at a character ahead and returns it if within bounds
        std::optional<char> peek(int index = 0) {
            if (!eoi(index)) {
                return m_input[m_current_pos+index];
            }
            return std::nullopt;
        }

        std::string consumeAll(const char& character) {
            int curr_pos = m_current_pos;
            while(!eoi() && character == m_input[m_current_pos++]);
            return m_input.substr(curr_pos, m_current_pos - curr_pos);
        }

        bool isDigit(char character) {
            return (character >= '0' && character <= '9');
        }

        std::optional<int64_t> parseDigit() {
            if (eoi()) {
                return std::nullopt;
            }
            auto value = peek().value();
            if (!isDigit(value)) {
                return std::nullopt;
            }
            return consumeSpecific(value).value() - '0';
        }

        std::optional<int64_t> parseDigits() {
            if (eoi()) {
                return std::nullopt;
            }
            auto digit = parseDigit();
            int64_t result = 0;
            while(digit.has_value()) {
                result = result * 10 + digit.value();
                digit = parseDigit();
            }
            return result;

        }

        std::optional<int64_t> parseInteger() {
            if (eoi()) {
                return std::nullopt;
            }
            int64_t result = 0;
            if (peek().value() == '-') {
                // is a negative number
                consumeSpecific('-');
                auto integer = parseInteger();
                if (!integer.has_value()) {
                    return std::nullopt;
                }
                result = -1 * integer.value();
            } else if (eoi(1)) {
                // is just a single digit
                return parseDigit();
            } else {
                // is more than single digit
                return parseDigits();
            }
            return result;
        }
        
        std::optional<double> parseFraction() {
            if (eoi() || !isNext('.') ) {
                return 0; // no fraction present
            }
            next(); // decimal is already checked to be present
            // count the zeros succeeding the decimal point
            double zeros = 1.0;
            while(consumeSpecific('0').has_value()) {
                zeros /= 10;
            }

            // non-zero digits
            auto integers = parseDigits();
            // if . present, it has to be followed by atleast one int
            if (!integers.has_value()) {
                return std::nullopt;
            }
            int64_t int_result = integers.value();
            double fraction = 0.0;
            fraction = int_result;
            while(int_result) {
                fraction /= 10;
                int_result /= 10;
            }
            // move fraction by number of zeros succeeding decimal point
            fraction = fraction * zeros; 
            return fraction;
        }

        // consumes only if next character is a sign
        char parseSign() {
            if (eoi() || !isAny("+-")) {
                return '+';
            }
            return consumeAny("+-").value();
        }

        std::optional<double> parseExponent() {
            if (eoi() || !isAny("eE") ) {
                return 1; // no exponent present
            }
            next(); // consumes next e/E
            bool isPositive = parseSign() == '+';
            double exponent = 1;
            // non-zero digits
            auto integers = parseDigits();
            if (!integers.has_value()) {
                return std::nullopt;
            }
            int powerOf10 = integers.value();
            while(powerOf10--) {
                if(isPositive) {
                    exponent *= 10;
                } else {
                    exponent /= 10;
                }
            }
            return exponent;
        }

        // returns a parsed number
        std::optional<double> parseNumber() {
            if (eoi()){
                return std::nullopt;
            }
            double result = 0.0;
            auto integer = parseInteger();
            if (!integer.has_value()) {
                return std::nullopt;
            }
            auto fraction = parseFraction();
            if (!fraction.has_value()) {
                return std::nullopt;
            }
            auto exponent = parseExponent();
            if (!exponent.has_value()) {
                return std::nullopt;
            }
            result += integer.value();
            result += fraction.value();
            result *= exponent.value();
            m_parse_info<< "Integer: " << integer.value()
                        << " Fraction: " << fraction.value()
                        << " Exponent: " << exponent.value();

            consumeAll(' '); // consume all whitespace ( only ' '  for now )
            if (!eoi()) {
                // 
                return std::nullopt;
            }
            return result;
        }
};

int main(int argc, char const *argv[])
{
    // loop till stdin is open (ctrl+D closes the stdin)
    while(std::cin) {
        std::string input = CLI::displayPrompt();
        // parse integer
        auto p = Parser(input);
        auto result = p.parseNumber();
        // parsed output
        if (result.has_value()) {
            std::cout<<"Result: "<<result.value()<<std::endl<<p.parseInfo()<<std::endl;
        } else {
            std::cout<<"Not a number"<<std::endl;
        }
    }
    return 0;
}