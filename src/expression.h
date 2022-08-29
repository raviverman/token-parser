/*
 * File: expression.h
 * Project: token-parser
 * File Created: Tuesday, 23rd August 2022 9:51:42 pm
 * Author: Ravi Verman (raviverman@hotmail.com)
 * -----
 * Last Modified: Tuesday, 23rd August 2022 9:52:26 pm
 * Modified By: Ravi Verman (raviverman@hotmail.com)
 * -----
 * SPDX-License-Identifier: GPL-2.0-only
 * Copyright 2022 - 2022 Ravi Verman, Ravi Verman
 */

#pragma once
#include "operator.h"
#include <iostream>

using namespace Operator;

namespace Expression {
enum ExpressionType {
    UNARY,
    BINARY,
};

class ExpressionBase {
    bool m_enclosed = false;

protected:
    ExpressionType m_exp_type;

public:
    // set expression as enclosed in bracket.
    void setEnclosed()
    {
        m_enclosed = true;
    }
    bool isEnclosed()
    {
        return m_enclosed;
    }
    ExpressionType expType() { return m_exp_type; }
    virtual OperatorType opType() = 0;
    // rearranges expression based on precedence of operator
    virtual void rearrange() = 0;
    virtual double solve() = 0;
    // returns expanded expression
    virtual std::string expand() = 0;
    // prints expression tree
    virtual void printTree(std::ostream&, int) = 0;
    // destructing the child using parent's pointer
    // fully deletes it
    virtual ~ExpressionBase() = default;
};

// Expression -> Operand
class Operand : public ExpressionBase {
    double m_value;

public:
    Operand(double value)
    {
        m_value = value;
        m_exp_type = UNARY;
    }
    OperatorType opType();
    void rearrange() {};
    double solve();
    void negate();
    std::string expand();
    void printTree(std::ostream&, int);
};

// Used with binary operators
// BinaryExpression -> Expression Operator Expression
class BinaryExpression : public ExpressionBase {
    ExpressionBase *m_operand1, *m_operand2;
    OperatorType m_op_type;

public:
    BinaryExpression(ExpressionBase* opd1, ExpressionBase* opd2, OperatorType op_type)
    {
        m_operand1 = opd1;
        m_operand2 = opd2;
        m_op_type = op_type;
        m_exp_type = BINARY;
    }
    OperatorType changeOperator(OperatorType);
    ExpressionBase* changeOperand2(ExpressionBase*);
    void negateFirst();
    void swapOperand();
    OperatorType opType();
    double solve();
    void rearrange();
    std::string expand();
    void printTree(std::ostream&, int);
};

};
