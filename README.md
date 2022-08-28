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
Our parser is 10x slower on average.
```
  String Representation   std::stod         Value   NumberParser        Value         Conversion Error   
                      1         875ns              1           2208ns             1                  0   
   -9223372036854775808        1666ns   -9.22337e+18           6417ns  -9.22337e+18                  0   
    9223372036854775807         667ns    9.22337e+18           5333ns   9.22337e+18                  0   
                    1.0         125ns              1           2292ns             1                  0   
                    1e1         125ns             10           3167ns            10                  0   
                1.23456         167ns        1.23456           3542ns       1.23456                  0   
           2.22507e-306        2584ns   2.22507e-306           7750ns  2.22507e-306       4.74303e-321   
                 1e-307        1000ns         1e-307           5833ns        1e-307       2.17389e-322   
1.7976931348623157E+307        1333ns   1.79769e+307           8917ns  1.79769e+307                  0   
Custom parser is 10.7652x slower than standard parser
```

## Future Additions
* Parser Additions
* Usage Examples
* Parser Benchmarks
* Test infrastructure
* Expression Solver