# Very Small Compiler

Very Small Compiler is a simple compiler written in C++ that translates Teeny Tiny Code (TTC) into Python code. This project serves as a hands-on exploration of compiler construction principles, inspired by the walkthrough provided by Austin Henley in his blog post: [Teeny Tiny Compiler](https://austinhenley.com/blog/teenytinycompiler3.html).

## Overview

The compiler follows the steps outlined in the blog post to transform Teeny Tiny Code, a minimalistic language, into Python code. It includes a lexer, parser, and emitter, providing insights into lexical analysis, parsing, and code generation.

## HowTo
- **1: lexer:** Reads the source code and breaks it into tokens (smallest units of meaning like keywords and operators).

- **2: tokenizer:** Converts raw input into tokens by following the language's rules.

- **3 parser:** Takes tokens and builds a syntax tree, checking the code's structure.

- **4 emitter:** Generates the final output code from the syntax tree.

- **5 linter:** Analyzes the code for errors and stylistic issues, providing feedback.

- **6 main:** Coordinates the entire process, running the lexer, parser, and emitter in sequence.
