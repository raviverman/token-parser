/*
 * File: expression_parser.cpp
 * Project: token-parser
 * File Created: Tuesday, 23rd August 2022 9:45:14 pm
 * Author: Ravi Verman (raviverman@hotmail.com)
 * -----
 * Last Modified: Tuesday, 23rd August 2022 10:43:18 pm
 * Modified By: Ravi Verman (raviverman@hotmail.com)
 * -----
 * SPDX-License-Identifier: GPL-2.0-only
 * Copyright 2022 - 2022 Ravi Verman, Ravi Verman
 */

#include "expression_parser.h"
#include "number_parser.h"
// Expression Grammar
// expression -> enclosed | operand | expression operator expression
// enclosed -> "(" expression ")"
// operator -> "+" | "-" | "*" | "/"
// operand -> number | ...<string extension>

using namespace Expression;
namespace Parser {

std::optional<OperatorType> ExpressionParser::parseOperator()
{
    if (eoi()) {
        return {};
    }
    switch (peek().value()) {
    case '+':
        next();
        return Operator::ADD;
    case '-':
        next();
        return Operator::SUBTRACT;
    case '*':
        next();
        return Operator::MULTIPLY;
    case '/':
        next();
        return Operator::DIVIDE;
    }
    return {};
}
std::optional<ExpressionBase*> ExpressionParser::parseExpression()
{
    // skip the whitespace first
    consumeAll(' ');
    if (eoi())
        return {};

    // first part of expression ( either an expression or an operand )
    ExpressionBase* firstExp = nullptr;
    if (isNext('(')) {
        // enclosed function
        consumeSpecific('(');
        auto expression = parseExpression();
        if (!expression.has_value()) {
            // error in parsing expression
            return expression;
        }
        firstExp = expression.value();
        firstExp->setEnclosed();

        consumeAll(' '); // remove all whitespace
        auto closingBracket = consumeSpecific(')');
        if (!closingBracket.has_value()) {
            m_err_msg << "Closing bracket not found at position " << pos();
            return {};
        }
    } else if (NumberParser::isDigit(peek().value()) || isAny("+-")) {
        // non-enclosed expression begins with a number of a signed number
        auto parser = NumberParser(input(), pos(), FIRST);
        auto parsedNumber = parser.parseNumber();
        if (!parsedNumber.has_value()) {
            m_err_msg << "Error in parsing \"" << consumeUntil('\n') << "\" as number";
            return {};
        }
        // move cursor to the position after the parsed number
        next(parser.pos() - pos());
        auto newExp = new Operand(parsedNumber.value());
        m_allocated_expression.push_back(newExp);
        firstExp = newExp;
    }

    if (firstExp) {
        consumeAll(' '); // skip any whitespace
        // search for an operator
        auto op = parseOperator();
        if (!op.has_value()) {
            return firstExp;
        }
        // op is a binary operator
        auto secondExp = parseExpression();
        if (!secondExp.has_value()) {
            if (m_err_msg.str().empty())
                m_err_msg << "Expected second operand after operator " << OpString[op.value()];
            return secondExp;
        }
        auto newExp = new BinaryExpression(firstExp, secondExp.value(), op.value());
        m_allocated_expression.push_back(newExp);
        return newExp;
    }
    m_err_msg << "Error in parsing \"" << consumeUntil('\n') << "\" as expression";
    return {};
}
}; // namespace Parser
