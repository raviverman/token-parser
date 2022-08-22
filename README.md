# token-parser
Parses tokens from a CLI.

## Supported Parsers
 * Number parser
    > 3.14, 33e+2, 1.1e-3, -13.22 etc

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
>>> 34.22e12
Result: 3.422e+13
Integer: 34 Fraction: 0.22 Exponent: 1e+12
```

## Future Additions
* Parser Additions
    * Expression parser
* Usage Examples
* Parser Benchmarks
* Test infrastructure
