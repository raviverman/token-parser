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
    ss << en_open << "OPERAND(" << m_value << ")" << en_close;
    return ss.str();
}

void Operand::printTree(std::ostream& out, int tabs)
{
    std::string tab;
    tab.append("|", 1);
    for (int i = 0; i < tabs; i++) {
        tab.append("---", 3);
        tab.append("|", 1);
    }
    tab[tab.length() - 1] = '>';
    out << tab << m_value << std::endl;
}

double BinaryExpression::solve()
{
    OperatorBase* op = OperatorFactory::BinaryOperatorFactory(m_op_type);
    auto result = op->operate(m_operand1->solve(), m_operand2->solve());
    delete op;
    return result;
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

void BinaryExpression::printTree(std::ostream& out, int tabs)
{
    std::string tab;
    tab.append("|", 1);
    for (int i = 0; i < tabs; i++) {
        tab.append("---", 3);
        tab.append("|", 1);
    }
    out << tab << Operator::OpString[m_op_type] << std::endl;
    m_operand1->printTree(out, tabs + 1);
    m_operand2->printTree(out, tabs + 1);
}
}; // namespace Expression
