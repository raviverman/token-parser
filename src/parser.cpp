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

#include "parser.h"

namespace Parser {
int ParserBase::pos()
{
    return m_current_pos;
}

std::string ParserBase::input()
{
    return m_input;
}

std::string ParserBase::parseInfo()
{
    return m_parse_info.str();
}

void ParserBase::next(int n)
{
    m_current_pos += n;
}

// returns true if end of input has been reached
bool ParserBase::eoi(int index)
{
    if (m_current_pos + index >= m_input.size()) {
        return true;
    }
    return false;
}

bool ParserBase::isNext(const char& character)
{
    if (eoi()) {
        return false;
    }
    return m_input[m_current_pos] == character;
}

bool ParserBase::isAny(const std::string chars)
{
    if (eoi()) {
        return false;
    }
    auto next = peek().value();
    for (auto& element : chars) {
        if (element == next) {
            return true;
        }
    }
    return false;
}

std::optional<char> ParserBase::consumeSpecific(const char& character)
{
    if (ParserBase::eoi()) {
        return std::nullopt;
    }
    if (m_input[m_current_pos] != character) {
        return std::nullopt;
    }
    m_current_pos++;
    return m_input[m_current_pos - 1];
}

// consume any of the given characters.
// one of the characters must be present, do precheck
// consumes next character anyway
std::optional<char> ParserBase::consumeAny(const std::string characters)
{
    if (eoi()) {
        return std::nullopt;
    }
    auto next = peek().value();
    for (auto& ch : characters) {
        if (ch == next) {
            break;
        }
    }
    m_current_pos++;
    return m_input[m_current_pos - 1];
}

std::string ParserBase::consumeUntil(const char& character)
{
    if (eoi()) {
        return "";
    }
    std::stringstream ss;
    while (!eoi() && m_input[m_current_pos] != character) {
        ss << m_input[m_current_pos++];
    }
    return ss.str();
}

// look at a character ahead and returns it if within bounds
std::optional<char> ParserBase::peek(int index)
{
    if (!eoi(index)) {
        return m_input[m_current_pos + index];
    }
    return std::nullopt;
}

std::string ParserBase::consumeAll(const char& character)
{
    int curr_pos = m_current_pos;
    while (!eoi() && character == m_input[m_current_pos]) {
        m_current_pos++;
    }
    return m_input.substr(curr_pos, m_current_pos - curr_pos);
}

}; // namespace Parser
