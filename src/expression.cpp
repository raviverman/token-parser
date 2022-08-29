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

OperatorType Operand::opType()
{
    return OperatorType::NONE;
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
    // rearrange before solving so it solves the correct expression tree
    rearrange();
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

OperatorType BinaryExpression::opType()
{
    return m_op_type;
}

void BinaryExpression::swapOperand()
{
    std::swap(m_operand1, m_operand2);
}
ExpressionBase* BinaryExpression::changeOperand2(ExpressionBase* op)
{
    auto temp_op = m_operand2;
    m_operand2 = op;
    return temp_op;
}

OperatorType BinaryExpression::changeOperator(OperatorType op)
{
    auto temp_op = m_op_type;
    m_op_type = op;
    return temp_op;
}
void BinaryExpression::rearrange()
{
    if (Operator::OpPrecedence[m_op_type] > Operator::OpPrecedence[m_operand2->opType()]
        && !m_operand2->isEnclosed()) {
        // Operand has operator of type NONE (highest precedence), will never enter here.
        // No problem in casting to binary expression.
        BinaryExpression* exp2 = (BinaryExpression*)m_operand2;
        m_op_type = exp2->changeOperator(m_op_type);
        m_operand1 = exp2->changeOperand2(m_operand1);
        exp2->swapOperand();
        swapOperand();
    }
}

void BinaryExpression::printTree(std::ostream& out, int tabs)
{
    // rearrange before printing so it prints the correct expression tree
    rearrange();
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
