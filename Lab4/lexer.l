%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define ID 256
#define INTVAL 257
#define DECIMAL 258
#define HEX 259
#define STRING 260
#define PUNCTUATION 261
#define VOID 262
#define SHORT 263
#define LONG 264
#define DOUBLE 265
#define CHAR 266
#define INT 267
#define FLOAT 268
#define RETURN 269
#define WHILE 270
#define SWITCH 271
#define DEFAULT 272
#define ELSE 273
#define BREAK 274
#define DO 275
#define FOR 276
#define CASE 277
#define IF 278
#define CONTINUE 279 
#define GOTO 280
#define UNSIGNED 281 
#define STRUCT 282
#define CONST 283
#define EXTERN 284
#define REGISTER 285
#define TYPEDEF 286
#define UNION 287
#define STATIC 288
#define AUTO 289
#define SIZEOF 290
#define CHARVAL 291
#define PRIMITIVETYPES 292


int list_type;
int incomment = 0;
%}

%option noyywrap nounput yylineno

ID [a-zA-Z][a-zA-Z0-9_]*

PRIMITIVETYPES void|short|long|double|char|int|float

CONTROLFLOW return|while|switch|default|else|break|do|for|case|if|continue|goto

KEYWORDS unsigned|struct|const|extern|register|typedef|union|static|auto|sizeof

DECIMAL [0-9]+

HEX [0x][0-9A-Fa-f]+

DOUBLE [0-9]+[\.][0-9]+

FLOAT [0-9]+[\.][0-9]+[f]

STRING \".*\"

CHARVAL "'"(\\)?."'"

PUNCTUATION \{|\}|\[|\]|\(|\)|\,|\;




%x COMMENT PREPROC 


%%
"//" {

BEGIN COMMENT;
}

\/\* {

BEGIN COMMENT;
}

\*\/ {

BEGIN 0;
}

"**" {

BEGIN COMMENT;
}

<COMMENT>[\n](\r)? {


BEGIN 0;
}

<COMMENT>[ \t] {

}


<COMMENT>. {
}


"void"  {
printf("VOID\n");
return VOID;
}

"short" {
printf("SHORT\n");
return SHORT;
}

"long"  {
printf("LONG\n");
return LONG;
}

"double"  {
printf("DOUBLE\n");
return DOUBLE;
}

"char"  {
printf("CHAR\n");
return CHAR;
}

"int"  {
printf("INT\n");
return INT;
}

"float"  {
printf("FLOAT\n");
return FLOAT;
}

"return" {
printf("RETURN\n");
return RETURN;
}

"while" {
printf("WHILE\n");
return WHILE;
}

"switch" {
printf("SWITCH\n");
return SWITCH;
}

"default" {
printf("DEFAULT\n");
return DEFAULT;
}

"else" {
printf("ELSE\n");
return ELSE;
}

"break" {
printf("BREAK\n");
return BREAK;
}

"do" {
printf("DO\n");
return DO;
}

"for" {
printf("FOR\n");
return FOR;
}

"case" {
printf("CASE\n");
return CASE;
}

"if" {
printf("IF\n");
return IF;
}

"continue" {
printf("CONTINUE\n");
return CONTINUE;
}

"goto" {
printf("GOTO\n");
return GOTO;
}

"unsigned" {
printf("UNSIGNED\n");
return UNSIGNED;
}

"struct" {
printf("STRUCT\n");
return STRUCT;
}

"const" {
printf("CONST\n");
return CONST;
}

"extern" {
printf("EXTERN\n");
return EXTERN;
}

"register" {
printf("REGISTER\n");
return REGISTER;
}

"typedef" {
printf("TYPEDEF\n");
return TYPEDEF;
}

"union" {
printf("UNION\n");
return UNION;
}

"static" {
printf("STATIC\n");
return STATIC;
}

"auto" {
printf("AUTO\n");
return AUTO;
}

"sizeof" {
printf("SIZEOF\n");
return SIZEOF;
}

{ID} {
printf("ID\n");
return ID;
}

{DECIMAL} {
printf("INTVAL\n");
return DECIMAL;
}

{HEX} {
printf("INTVAL\n");
return HEX;
}

{DOUBLE} {
printf("DBLVAL\n");
return DOUBLE;
}

{FLOAT} {
printf("FLTVAL\n");
return FLOAT;
}

{STRING} {
printf("STRVAL\n");
return STRING;
}

{CHARVAL} {
printf("CHARVAL\n");
return CHARVAL;
}

{PUNCTUATION} {
printf("%s\n", yytext);
return PUNCTUATION;
}

[ \t] {

}

"\n" {

}

^#.* {
printf("PREPROC\n");
}

"==" {
printf("EQ\n");
}

"<=" {
printf("LE\n");
}

"+" {
printf("ADD\n");
}

"/" {
printf("DIV\n");
}

"&&" {
printf("AND\n");
}

"^" {
printf("BITXOR\n");
}

"<<" {
printf("LSH\n");
}

"+=" {
printf("SETADD\n");
}

"/=" {
printf("SETDIV\n");
}

"&=" {
printf("SETAND\n");
}

">>=" {
printf("SETRSH\n");
}

"!=" {
printf("NE\n");
}

">" {
printf("GT\n");
}

"-" {
printf("SUB\n");
}

"%" {
printf("MOD\n");
}

"|" {
printf("BITOR\n");
}

"!" {
printf("NOT\n");
}

">>" {
printf("RSH\n");
}

"-=" {
printf("SETSUB\n");
}

"%=" {
printf("SETMOD\n");
}

"^=" {
printf("SETXOR\n");
}

">=" {
printf("GE\n");
}

"<" {
printf("LT\n");
}

"*" {
printf("MUL\n");
}

"||" {
printf("OR\n");
}

"&" {
printf("BITAND\n");
}

"~" {
printf("COM\n");
}

"=" {
printf("SET\n");
}

"*=" {
printf("SETMUL\n");
}

"|=" {
printf("SETOR\n");
}

"<<=" {
printf("SETLSH\n");
}


%%



int main(int argc, const char* argv[])
{
while (yylex()){}
return 0;
}
