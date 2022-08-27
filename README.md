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
## Benchmark Results

These are first benchmark results. Parser can be improved and this can be optimised. There is a coversion
error because the coversion doesn't do caveats possibly in IEEE754 double precision floating point standard. 
The error is minimal and should have same precision as double (precise upto 15 decimal places).
Our parser is 5x slower on average.
```
    String Representation     std::stod          Value       NumberParser         Value  Conversion Error
                        1           2us               1               2us             1                 0
     -9223372036854775808           2us    -9.22337e+18               7us  -9.22337e+18                 0
      9223372036854775807           0us     9.22337e+18               6us   9.22337e+18                 0
                      1.0           0us               1               2us             1                 0
                      1e1           0us              10               3us            10                 0
                  1.23456           0us         1.23456               4us       1.23456                 0
             2.22507e-306           3us    2.22507e-306               8us  2.22507e-306      4.74303e-321
                   1e-307           1us          1e-307               6us        1e-307      2.17389e-322
  1.7976931348623157E+307           1us    1.79769e+307               9us  1.79769e+307                 0
```

## Future Additions
* Parser Additions
* Usage Examples
* Parser Benchmarks
* Test infrastructure
* Expression Solver