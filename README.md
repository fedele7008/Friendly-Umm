# Friendly Umm...

## Requirements

* `cmake` > 3.11
* `g++` or any other c++ compiler
* `make` or any other build tool
* `git`
* `python3`

## Optional

* `doxygen` if you want to create documentation
* `graphviz` if you want to create documentation with UML diagram (requires `doxygen` too)

## How to configure

Run `cmake -B build` from project root directory to generate build directory

* If you also want to create documentation, run `cmake -B build -D BUILD_DOC=ON`
* If you also want to create documentation with UML diagram, run `cmake -B build -D BUILD_DOC=ON -D UML=ON`

Then run `cmake --build build` to compile the project

* Additionally, run `cmake --build build --target doc` to generate documentation

Now you will have `artifact` directory in project root.

* `artifact/bin/` directory contains executable binaries of the project (compiled from `apps` directory)
* `artifact/lib/` directory contains c++ libraries for the project (compiled from `modules` directory)
* `artifact/test/` directory contains unit tests for the project
* `artifact/doc/` directory contains documentation for the project (only if you generated documentation).

To see the documentation, open `artifact/doc/html/index.html`.

## Friendly Umm... programming language specification

### Lexical Syntax
* ID: a string consist of a letter(a-zA-Z) followed by zero or more letters and digits(0-9), but not equal to other characters designated by the language specification (e.g. "main", "int", "if", etc.)
* NUM: a string consisting of list of digits(0-9), the first of which is not 0.
* LPAREN: "("
* RPAREN: ")"
* LBRACE: "{"
* RBRACE: "}"
* RETURN: "return"
* IF: "if"
* ELSE: "else"
* WHILE: "while"
* PRINT: "print"
* PRINTLN: "println"
* INPUT: "scan"
* MAIN: "main"
* ASSIGN: "="
* INT: "int"
* CHAR: "char"
* EQ: "=="
* NE: "!="
* PLUS: "+"
* MINUS: "-"
* STAR: "*"
* SLASH: "/"
* COMMA: ","
* SEMI: ";"
* LBRACK: "["
* RBRACK: "]"
* STR: starting with " and followed by letters and digits and closing with quote character

#### Raw Lexical Syntax
* SPACE: space character
* TAB: tab character
* NEWLINE: newline character
* COMMENT: "//" followed by all characters upto newline character

#### Special Lexical Syntax
* BEGF: beginning of file indicator
* ENDF: end of file indicator

### Context-free Syntax (context-free grammar)
* start -> BEGF procedures ENDF
* procedures -> procedure procedures
* procedures -> main
* procedure -> type ID LPAREN params RPAREN LBRACE statements RETURN expr SEMI RBRACE
* main -> INT ID LPAREN RPAREN LBRACE statements RETURN expr SEMI RBRACE
* params ->
* params -> paramlist
* paramlist -> dcl
* paramlist -> dcl COMMA paramlist
* type -> INT
* type -> CHAR
* dcls ->
* dcls -> dcls dcl ASSIGN rvalue SEMI
* dcls -> dcls dcl SEMI
* dcl -> type ID
* statements ->
* statements -> statements statement
* statement -> dcls
* statement -> lvalue ASSGIN expr SEMI
* statement -> IF LPAREN test RPAREN LBRACE statements RBRASE
* statement -> IF LPAREN test RPAREN LBRACE statements RBRACE ELSE LBRACE statements RBRACE
* statement -> WHILE LPAREN test RPAREN LBRACE statements RBRACE
* statement -> PRINT LPAREN expr RPAREN SEMI
* statement -> PRINTLN LPAREN expr RPAREN SEMI
* statement -> ID LPAREN RPAREN SEMI
* statement -> ID LPAREN arglist SEMI
* test -> expr EQ expr
* test -> expr NE expr
* expr -> term
* expr -> expr PLUS term
* expr -> expr MINUS term
* term -> factor
* term -> term STAR factor
* term -> term SLASH factor
* factor -> ID
* factor -> NUM
* factor -> LPAREN expr RPAREN
* factor -> ID LPAREN RPAREN
* factor -> ID LPAREN arglist RPAREN
* arglist -> ID
* arglist -> expr COMMA arglist
* lvalue -> ID
* lvalue -> LPAREN lvalue RPAREN
* rvalue -> NUM
* rvalue -> STR
* rvalue -> INPUT
