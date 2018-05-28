%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcg.yacc.h>

#ifndef NDEBUG
#    define DEBUGF(...) printf(__VA_ARGS__)
#else
#    define DEBUGF(...)
#endif
%}

%option       noyywrap nounput yylineno
%x            COMMENT

whitesp       [ \t\n\r]
nonwhitesp    [^ \t\n\r]
ident         [a-zA-Z][a-zA-Z0-9_]*
digit         [0-9]
hexdigit      [0-9a-fA-F]
octdigit      [0-7]

DECIMAL [0-9]+

HEX [0x][0-9A-Fa-f]+

DOUBLE [0-9]+[\.][0-9]+

FLOAT [0-9]+[\.][0-9]+[f]

STRING \".*\"

CHARVAL "'"(\\)?."'"

%%

{DECIMAL} {
return INTVAL;
}

{HEX} {
return INTVAL;
}

{DOUBLE} {
return DBLVAL;
}

{FLOAT} {
return FLTVAL;
}

{STRING} {
return STRVAL;
}

{CHARVAL} {
return CHARVAL;
}

"void"  {
return VOID;
}

"short" {
return SHORT;
}

"char"  {
return CHAR;
}

"int"  {
return INT;
}

"long"  {
return LONG;
}

"float"  {
return FLOAT;
}

"double"  {
return DOUBLE;
}

"return" {
return RETURN;
}

"do" {
return DO;
}

"while" {
return WHILE;
}

"for" {
return FOR;
}

"switch" {
return SWITCH;
}

"case" {
return CASE;
}

"default" {
return DEFAULT;
}

"if" {
return IF;
}

"else" {
return ELSE;
}

"continue" {
return CONTINUE;
}

"break" {
return BREAK;
}

"goto" {
return GOTO;
}

"unsigned" {
return UNSIGNED;
}

"struct" {
return STRUCT;
}

"const" {
return CONST;
}

"extern" {
return EXTERN;
}

"register" {
return REGISTER;
}

"typedef" {
return TYPEDEF;
}

"union" {
return UNION;
}

"static" {
return STATIC;
}

"auto" {
return AUTO;
}

"sizeof" {
return SIZEOF;
}

"==" {
return EQ;
}

"<=" {
return LE;
}

"+" {
return ADD;
}

"/" {
return DIV;
}

"&&" {
return AND;
}

"^" {
return BITXOR;
}

"<<" {
return LSH;
}

"+=" {
return SETADD;
}

"/=" {
return SETDIV;
}

"&=" {
return SETAND;
}

">>=" {
return SETRSH;
}

"!=" {
return NE;
}

">" {
return GT;
}

"-" {
return SUB;
}

"%" {
return MOD;
}

"|" {
return BITOR;
}

"!" {
return NOT;
}

">>" {
return RSH;
}

"&" {
return BITAND;
}

"~" {
return COM;
}

"=" {
return SET;
}

"*=" {
return SETMUL;
}

"|=" {
return SETOR;
}

"<<=" {
return SETLSH;
}

"-=" {
return SETSUB;
}

"%=" {
return SETMOD;
}

"^=" {
return SETXOR;
}

">=" {
return GE;
}

"<" {
return LT;
}

"*" {
return MUL;
}

"||" {
return OR;
}



%{ 
 /**************************************************************************
  * Scan miscellaneous C punctuation. 
  *************************************************************************/
%}

"("         { DEBUGF( "(\n" ); return '('; }
")"         { DEBUGF( ")\n" ); return ')'; }
"{"         { DEBUGF( "{\n" ); return '{'; }
"}"         { DEBUGF( "}\n" ); return '}'; }
"["         { DEBUGF( "[\n" ); return '['; }
"]"         { DEBUGF( "]\n" ); return ']'; }
","         { DEBUGF( ",\n" ); return ','; }
";"         { DEBUGF( ";\n" ); return ';'; }

%{ 
 /**************************************************************************
  * Scan C identifiers.
  *************************************************************************/
%}

{ident}         { DEBUGF( "ID\n" ); yylval.id = strdup(yytext); return ID; }

%{ 
 /**************************************************************************
  * Scan C literal values including strings, character literals, integer
  * literals, and floating point literals.
  *************************************************************************/
%}


%{
 /**************************************************************************
  * Scan a multi-line C comment using left context or a C single line
  * comment to the end of the line.
  *************************************************************************/
%}

"//".*                      { /* ignored */ }

"/*"                        { BEGIN COMMENT; }
<COMMENT>"*/"               { BEGIN 0; }
<COMMENT>([\n](\r)?)|.      { /* ignored */ } 

%{
 /**************************************************************************
  * Scan white space in-between tokens and ignore it.
  *************************************************************************/
%}

{whitesp}+ { /* ignored */  }

%{
 /**************************************************************************
  * Anything else that matches is unexpected so print an error.
  *************************************************************************/
%}

. {
    fprintf( stderr, "Unexpected input at line %d: '%s'\n", yylineno, yytext );
    exit( 1 );
}
