/*
 * File: expression.cpp
 * Project: token-parser
 * File Created: Wednesday, 24th August 2022 8:44:40 pm
 * Author: Ravi Verman (raviverman@hotmail.com)
 * -----
 * Last Modified: Wednesday, 24th August 2022 8:44:50 pm
 * Modified By: Ravi Verman (raviverman@hotmail.com)
 * -----
 * SPDX-License-Identifier: GPL-2.0-only
 * Copyright 2022 - 2022 Ravi Verman, Ravi Verman
 */

#include "expression.h"
#include <sstream>

namespace Expression {
double Operand::solve()
{
    return m_value;
}

std::string Operand::expand()
{
    std::stringstream ss;
    std::string en_open = "";
    std::string en_close = "";
    if (isEnclosed()) {
        en_open = "( ";
        en_close = " )";
    }
    ss << en_open << "OPRAND(" << m_value << ")" << en_close;
    return ss.str();
}

double BinaryExpression::solve()
{
    // Instantiate Operator based on type
    // and call with the operator
    return 123;
}

std::string BinaryExpression::expand()
{
    std::stringstream ss;
    std::string en_open = "";
    std::string en_close = "";
    if (isEnclosed()) {
        en_open = "( ";
        en_close = " )";
    }
    ss << en_open << m_operand1->expand() << " "
       << "OPERATOR(" << Operator::OpSign[m_op_type] << ") "
       << m_operand2->expand()
       << en_close;
    return ss.str();
}
}; // namespace Expression
