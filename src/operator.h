/*
 * File: operator.h
 * Project: token-parser
 * File Created: Tuesday, 23rd August 2022 10:03:09 pm
 * Author: Ravi Verman (raviverman@hotmail.com)
 * -----
 * Last Modified: Tuesday, 23rd August 2022 10:03:15 pm
 * Modified By: Ravi Verman (raviverman@hotmail.com)
 * -----
 * SPDX-License-Identifier: GPL-2.0-only
 * Copyright 2022 - 2022 Ravi Verman, Ravi Verman
 */

#pragma once
#include <string>
namespace Operator {
enum OperatorType {
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE
};

char OpString[][25] = {
    "ADD",
    "SUBTRACT",
    "MULTIPLY",
    "DIVIDE",
};

char OpSign[][3] = {
    "+",
    "-",
    "*",
    "/",
};

class OperatorBase {
protected:
    OperatorType m_op_type;

public:
    // implemented by derieved classes
    OperatorType operatorType() { return m_op_type; }
    virtual double operate(double operand1, double operand2) = 0;
};
};
