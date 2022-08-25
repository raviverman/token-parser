/*
 * File: number_parser.h
 * Project: token-parser
 * File Created: Sunday, 21st August 2022 9:14:20 pm
 * Author: Ravi Verman (raviverman@hotmail.com)
 * -----
 * Last Modified: Sunday, 21st August 2022 9:18:25 pm
 * Modified By: Ravi Verman (raviverman@hotmail.com)
 * -----
 * SPDX-License-Identifier: GPL-2.0-only
 * Copyright 2022 - 2022 Ravi Verman, Ravi Verman
 */

#include "parser.h"

namespace Parser {
class NumberParser : public ParserBase {
public:
    NumberParser(std::string input, int pos = 0, ParserOption parse_opt = ALL)
        : ParserBase(input, pos, parse_opt)
    {
    }
    // returns if the given char is a digit
    static bool isDigit(char character);
    // consumes only if next character is a sign
    char parseSign();
    // parses single integer.g. "3"
    std::optional<int64_t> parseDigit();
    // parses unsigned integer.g. "314"
    std::optional<int64_t> parseDigits();
    // parses signed integer.g. "-314"
    std::optional<int64_t> parseInteger();
    // parses fraction part of a number e.g. ".14159"
    std::optional<double> parseFraction();
    // parses exponent part of a number e.g. "e13"
    std::optional<double> parseExponent();
    // returns a parsed number
    std::optional<double> parseNumber();
};
static bool isDigit(char character);
} // namespace Parser
