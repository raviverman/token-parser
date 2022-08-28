/*
 * File: main.cpp
 * Project: token-parser
 * File Created: Sunday, 21st August 2022 7:52:51 pm
 * Author: Ravi Verman (raviverman@hotmail.com)
 * -----
 * Last Modified: Sunday, 21st August 2022 10:16:19 pm
 * Modified By: Ravi Verman (raviverman@hotmail.com)
 * -----
 * SPDX-License-Identifier: GPL-2.0-only
 * Copyright 2022 - 2022 Ravi Verman, Ravi Verman
 */

#include "src/expression_parser.h"
#include "src/number_parser.h"
#include <iostream>
#include <string>

using namespace Parser;

class Cli {
public:
    Cli()
    {
        std::cout << "=token-parser v0.0.1=" << std::endl;
    }
    std::string displayPrompt()
    {
        std::cout << ">>> ";
        std::string input;
        getline(std::cin, input);
        return input;
    };
};

int main(int argc, char const* argv[])
{
    // loop till stdin is open (ctrl+D closes the stdin)
    Cli cli;
    while (std::cin) {
        std::string input = cli.displayPrompt();
        if (input.empty()) {
            continue; // no input at prompt, continue
        }
        // parse integer
        auto p = NumberParser(input);
        auto result = p.parseNumber();
        // parsed output
        if (result.has_value()) {
            std::cout << "Result: " << result.value() << std::endl
                      << p.parseInfo() << std::endl;
            continue;
        }
        auto pp = ExpressionParser(input);
        auto exp = pp.parseExpression();
        if (exp.has_value()) {
            std::cout << "Expression: " << exp.value()->expand() << std::endl;
            exp.value()->printTree(std::cout, 0);
            std::cout<< "Solution: "<< exp.value()->solve()<<std::endl;
            continue;
        } else {
            std::cout << "Error: " << pp.parseInfo() << std::endl;
        }
    }
    std::cout << std::endl; // shell prompt at newline
    return 0;
}
