/*
 * File: parser.h
 * Project: token-parser
 * File Created: Sunday, 21st August 2022 7:54:16 pm
 * Author: Ravi Verman (raviverman@hotmail.com)
 * -----
 * Last Modified: Sunday, 21st August 2022 8:42:42 pm
 * Modified By: Ravi Verman (raviverman@hotmail.com)
 * -----
 * SPDX-License-Identifier: GPL-2.0-only
 * Copyright 2022 - 2022 Ravi Verman, Ravi Verman
 */

#include <iostream>
#include <optional>
#include <sstream>
#include <string>

namespace Parser {
class ParserBase {
    std::string m_input;
    int m_current_pos;
    std::string m_err_msg;

protected:
    std::stringstream m_parse_info;

public:
    ParserBase(std::string input)
    {
        m_input = input;
        m_current_pos = 0;
    }
    // function that returns additional (debug) info about parsing
    // can be overridden by derieved classes to provide specific functionality
    std::string parseInfo();
    // moves one position to the right
    void next();
    // returns true if end of input has been reached
    bool eoi(int index = 0);
    // returns true if the next element is the given character
    bool isNext(const char& character);
    // returns true if the next element is an of the given characters
    bool isAny(const std::string chars);
    // consumes and returns if the next element is the given characters
    std::optional<char> consumeSpecific(const char& character);
    // consume any of the given characters.
    // one of the characters must be present, do precheck
    // consumes next character anyway
    std::optional<char> consumeAny(const std::string characters);
    // consumes all elements until the given character is found
    std::string consumeUntil(const char& character);
    // look at a character ahead and returns it if within bounds
    std::optional<char> peek(int index = 0);
    // consume all subsequent element that match the character
    std::string consumeAll(const char& character);
};
} // namespace Parser