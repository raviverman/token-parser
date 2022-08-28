#include "operator.h"

namespace Operator {

double AddOperator::operate(double operand1, double operand2)
{
    return operand1 + operand2;
}
double SubtractOperator::operate(double operand1, double operand2)
{
    return operand1 - operand2;
}
double MultiplyOperator::operate(double operand1, double operand2)
{
    return operand1 * operand2;
}
double DivideOperator::operate(double operand1, double operand2)
{
    return operand1 / operand2;
}

OperatorBase*
OperatorFactory::BinaryOperatorFactory(OperatorType op_type)
{
    switch (op_type) {
    case OperatorType::ADD:
        return new AddOperator();
    case OperatorType::SUBTRACT:
        return new SubtractOperator();
    case OperatorType::MULTIPLY:
        return new MultiplyOperator();
    case OperatorType::DIVIDE:
        return new DivideOperator();
    };
}
};