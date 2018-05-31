/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ID = 258,
     INTVAL = 259,
     DBLVAL = 260,
     FLTVAL = 261,
     STRVAL = 262,
     CHARVAL = 263,
     VOID = 264,
     SHORT = 265,
     CHAR = 266,
     INT = 267,
     LONG = 268,
     FLOAT = 269,
     DOUBLE = 270,
     RETURN = 271,
     DO = 272,
     WHILE = 273,
     FOR = 274,
     SWITCH = 275,
     CASE = 276,
     DEFAULT = 277,
     IF = 278,
     ELSE = 279,
     CONTINUE = 280,
     BREAK = 281,
     GOTO = 282,
     UNSIGNED = 283,
     STRUCT = 284,
     CONST = 285,
     EXTERN = 286,
     REGISTER = 287,
     TYPEDEF = 288,
     UNION = 289,
     STATIC = 290,
     AUTO = 291,
     SIZEOF = 292,
     EQ = 293,
     LE = 294,
     ADD = 295,
     DIV = 296,
     AND = 297,
     BITXOR = 298,
     LSH = 299,
     SETADD = 300,
     SETDIV = 301,
     SETAND = 302,
     SETRSH = 303,
     NE = 304,
     GT = 305,
     SUB = 306,
     MOD = 307,
     BITOR = 308,
     NOT = 309,
     RSH = 310,
     BITAND = 311,
     COM = 312,
     SET = 313,
     SETMUL = 314,
     SETOR = 315,
     SETLSH = 316,
     SETSUB = 317,
     SETMOD = 318,
     SETXOR = 319,
     GE = 320,
     LT = 321,
     MUL = 322,
     OR = 323,
     PREPROC = 324
   };
#endif
/* Tokens.  */
#define ID 258
#define INTVAL 259
#define DBLVAL 260
#define FLTVAL 261
#define STRVAL 262
#define CHARVAL 263
#define VOID 264
#define SHORT 265
#define CHAR 266
#define INT 267
#define LONG 268
#define FLOAT 269
#define DOUBLE 270
#define RETURN 271
#define DO 272
#define WHILE 273
#define FOR 274
#define SWITCH 275
#define CASE 276
#define DEFAULT 277
#define IF 278
#define ELSE 279
#define CONTINUE 280
#define BREAK 281
#define GOTO 282
#define UNSIGNED 283
#define STRUCT 284
#define CONST 285
#define EXTERN 286
#define REGISTER 287
#define TYPEDEF 288
#define UNION 289
#define STATIC 290
#define AUTO 291
#define SIZEOF 292
#define EQ 293
#define LE 294
#define ADD 295
#define DIV 296
#define AND 297
#define BITXOR 298
#define LSH 299
#define SETADD 300
#define SETDIV 301
#define SETAND 302
#define SETRSH 303
#define NE 304
#define GT 305
#define SUB 306
#define MOD 307
#define BITOR 308
#define NOT 309
#define RSH 310
#define BITAND 311
#define COM 312
#define SET 313
#define SETMUL 314
#define SETOR 315
#define SETLSH 316
#define SETSUB 317
#define SETMOD 318
#define SETXOR 319
#define GE 320
#define LT 321
#define MUL 322
#define OR 323
#define PREPROC 324




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 15 "fcg.y"
{
    char* id;
}
/* Line 1529 of yacc.c.  */
#line 191 "fcg.yacc.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

