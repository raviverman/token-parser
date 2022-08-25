/*
 * File: expression_parser.h
 * Project: token-parser
 * File Created: Tuesday, 23rd August 2022 9:45:22 pm
 * Author: Ravi Verman (raviverman@hotmail.com)
 * -----
 * Last Modified: Tuesday, 23rd August 2022 9:47:16 pm
 * Modified By: Ravi Verman (raviverman@hotmail.com)
 * -----
 * SPDX-License-Identifier: GPL-2.0-only
 * Copyright 2022 - 2022 Ravi Verman, Ravi Verman
 */

#include "expression.h"
#include "parser.h"
#include <functional>
#include <vector>

using namespace Expression;

namespace Parser {
class ExpressionParser : public ParserBase {
    std::vector<ExpressionBase*> m_allocated_expression;

public:
    ExpressionParser(std::string input)
        : ParserBase(input) {};
    std::optional<OperatorType> parseOperator();
    std::optional<ExpressionBase*> parseExpression();
    ~ExpressionParser()
    {
        // delete allocated sub-expressions during parsing
        for (auto ref : m_allocated_expression) {
            delete ref;
        }
    }
};
}; // namespace Parser
