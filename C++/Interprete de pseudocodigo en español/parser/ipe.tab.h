/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

#ifndef YY_YY_IPE_TAB_H_INCLUDED
# define YY_YY_IPE_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    SEMICOLON = 258,
    COMMA = 259,
    LETFCURLYBRACKET = 260,
    RIGHTCURLYBRACKET = 261,
    PRINT = 262,
    STRINGPRINT = 263,
    STRINGREAD = 264,
    READ = 265,
    CLEAN = 266,
    PLACE = 267,
    IF = 268,
    ELSE = 269,
    WHILE = 270,
    THEN = 271,
    ENDIF = 272,
    DO = 273,
    ENDWHILE = 274,
    REPEAT = 275,
    UNTIL = 276,
    FOR = 277,
    ENDFOR = 278,
    FROM = 279,
    STEP = 280,
    SWITCH = 281,
    ENDSWITCH = 282,
    ASSIGNMENT = 283,
    PLUSASSIGNMENT = 284,
    MINUSASSIGNMENT = 285,
    DIVIASSIGNMENT = 286,
    MULTASSIGNMENT = 287,
    NUMBER = 288,
    STRING = 289,
    VARIABLE = 290,
    NUMERICVARIABLE = 291,
    ALPHANUMERICVARIABLE = 292,
    UNDEFINED = 293,
    CONSTANT = 294,
    NUMERICCONSTANT = 295,
    BUILTIN = 296,
    OR = 297,
    AND = 298,
    GREATER_OR_EQUAL = 299,
    LESS_OR_EQUAL = 300,
    GREATER_THAN = 301,
    LESS_THAN = 302,
    EQUAL = 303,
    NOT_EQUAL = 304,
    PLUS = 305,
    MINUS = 306,
    CONCATENATION = 307,
    MULTIPLICATION = 308,
    DIVISION = 309,
    INTDIVISION = 310,
    MODULO = 311,
    INCREMENT = 312,
    DECREMENT = 313,
    NOT = 314,
    UNARY = 315,
    LPAREN = 316,
    RPAREN = 317,
    POWER = 318
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 122 "ipe.y" /* yacc.c:1909  */

	int integer;
	bool binary;
	double number;
	char * name;					/* NEW in example 7 */
	lp::ExpNode *expNode;	/* NEW in IPE */
	lp::NumericExpNode *numericExpNode;	/* NEW in IPE */
	lp::LogicExpNode *logicExpNode;		/* NEW in IPE */
	lp::AlphanumericExpNode *alphanumericExpNode;	/* NEW in IPE */
	std::list<lp::Statement *> *stmts;	/* NEW in example 16 */
	lp::Statement *st;					/* NEW in example 16 */
	lp::AST *prog;						/* NEW in example 16 */

#line 132 "ipe.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_IPE_TAB_H_INCLUDED  */
