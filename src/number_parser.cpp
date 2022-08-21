/*
 * File: number_parser.cpp
 * Project: token-parser
 * File Created: Sunday, 21st August 2022 8:44:56 pm
 * Author: Ravi Verman (raviverman@hotmail.com)
 * -----
 * Last Modified: Sunday, 21st August 2022 10:16:41 pm
 * Modified By: Ravi Verman (raviverman@hotmail.com)
 * -----
 * SPDX-License-Identifier: GPL-2.0-only
 * Copyright 2022 - 2022 Ravi Verman, Ravi Verman
 */

#include "number_parser.h"

// Number Grammar (picked from JSON grammar https://www.json.org/json-en.html)

// number -> integer fraction exponent
// integer -> digit | onenine digits | '-' digit | '-' onenine digits
// digits -> digit | digit digits
// digit -> 0 | onenine
// onenine -> 1-9
// fraction -> "" | '.' digits
// exponent -> 'e' sign digits | 'E' sign digits | ""
// sign -> + | - | ""

namespace Parser {
bool NumberParser::isDigit(char character)
{
    return (character >= '0' && character <= '9');
}

std::optional<int64_t> NumberParser::parseDigit()
{
    if (eoi()) {
        return std::nullopt;
    }
    auto value = peek().value();
    if (!isDigit(value)) {
        return std::nullopt;
    }
    return consumeSpecific(value).value() - '0';
}

std::optional<int64_t> NumberParser::parseDigits()
{
    if (eoi()) {
        return std::nullopt;
    }
    auto digit = parseDigit();
    int64_t result = 0;
    while (digit.has_value()) {
        result = result * 10 + digit.value();
        digit = parseDigit();
    }
    return result;
}

std::optional<int64_t> NumberParser::parseInteger()
{
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

std::optional<double> NumberParser::parseFraction()
{
    if (eoi() || !isNext('.')) {
        return 0; // no fraction present
    }
    next(); // decimal is already checked to be present
    // count the zeros succeeding the decimal point
    double zeros = 1.0;
    while (consumeSpecific('0').has_value()) {
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
    while (int_result) {
        fraction /= 10;
        int_result /= 10;
    }
    // move fraction by number of zeros succeeding decimal point
    fraction = fraction * zeros;
    return fraction;
}

char NumberParser::parseSign()
{
    if (eoi() || !isAny("+-")) {
        return '+';
    }
    return consumeAny("+-").value();
}

std::optional<double> NumberParser::parseExponent()
{
    if (eoi() || !isAny("eE")) {
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
    while (powerOf10--) {
        if (isPositive) {
            exponent *= 10;
        } else {
            exponent /= 10;
        }
    }
    return exponent;
}

std::optional<double> NumberParser::parseNumber()
{
    if (eoi()) {
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
    m_parse_info << "Integer: " << integer.value()
                 << " Fraction: " << fraction.value()
                 << " Exponent: " << exponent.value();

    consumeAll(' '); // consume all whitespace ( only ' '  for now )
    if (!eoi()) {
        //
        return std::nullopt;
    }
    return result;
}
} // namespace Parser
