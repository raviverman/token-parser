# token-parser
Parses tokens from a CLI.

## Supported Parsers
 * Number parser
    > 3.14, 33e+2, 1.1e-3, -13.22 etc
 * Expression parser
    > ( 5 - 34 * (23 / 5))

## Dependencies
Requires `gcc`/`clang`  (C++17 or above). Will possibly switch to C++20 later.
Needs `cmake` to compile the code.

## How to run
```
cd token-parser 
cmake .
cmake --build .
bld/main
```
It will bring the parser prompt where it can be tested
```
=token-parser v0.0.1=
>>> ( 4 - ( 9 * 4 ))
Expression: ( OPRAND(4) OPERATOR(-) ( OPRAND(9) OPERATOR(*) OPRAND(4) ) )
>>> 45.3e10
Result: 4.53e+11
Integer: 45 Fraction: 0.3 Exponent: 1e+10
>>> 
```

## Future Additions
* Parser Additions
* Usage Examples
* Parser Benchmarks
* Test infrastructure
* Expression Solver