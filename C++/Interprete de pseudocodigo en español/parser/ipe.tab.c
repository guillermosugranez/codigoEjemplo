/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 6 "ipe.y" /* yacc.c:339  */

#include <iostream>
#include <string>

/*******************************************/
/* NEW in example 5 */
/* pow */
#include <math.h>
/*******************************************/

/*******************************************/
/* NEW in example 6 */
/* Use for recovery of runtime errors */
#include <setjmp.h>
#include <signal.h>
/*******************************************/

/* Error recovery functions */
#include "../error/error.hpp"

/* Macros for the screen */
#include "../includes/macros.hpp"
#include "../includes/util.hpp"

/*******************************************/
/* NEW in example 7 */
/* Table of symbol */
#include "../table/table.hpp"

/*******************************************/

/*******************************************/
/* 
  NEW in example 16
  AST class
  IMPORTANT: this file must be before init.hpp
*/
#include "../ast/ast.hpp"

/*******************************************/
/* NEW in example 10 */
#include "../table/init.hpp"
/*******************************************/


/*******************************************/
/* NEW in example 11 */
#include "../table/numericConstant.hpp"
/*******************************************/


/*******************************************/
/* NEW in example 13 */
#include "../table/builtinParameter1.hpp"
/*******************************************/

/*******************************************/
/* NEW in example 14 */
#include "../table/builtinParameter0.hpp"
#include "../table/builtinParameter2.hpp"
/*******************************************/



/*! 
	\brief  Lexical or scanner function
	\return int
	\note   C++ requires that yylex returns an int value
	\sa     yyparser
*/
int yylex();

extern int lineNumber; //!< External line counter


/***********************************************************/
/* NEW in example 2 */
extern std::string progname; //!<  Program name
/***********************************************************/

/*******************************************/
/* NEW in example 6 */
/*
 jhmp_buf
	This is an array type capable of storing the information of a calling environment to be restored later.
   This information is filled by calling macro setjmp and can be restored by calling function longjmp.
*/
jmp_buf begin; //!<  It enables recovery of runtime errors 
/*******************************************/


/*******************************************/
/* NEW in example 7 */
extern lp::Table table; //!< Externa Table of Symbols

/*******************************************/
/* NEW in example 16 */
extern lp::AST *root; //!< External root of the abstract syntax tree AST

extern int modoFichero; // Sirve para diferenciar el modo interprete y el modo fichero

int control = 1;

std::list<lp::Statement *> * nodeRoot = NULL; // Nodo Raiz


#line 173 "ipe.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "ipe.tab.h".  */
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
#line 122 "ipe.y" /* yacc.c:355  */

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

#line 291 "ipe.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_IPE_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 308 "ipe.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   621

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  64
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  21
/* YYNRULES -- Number of rules.  */
#define YYNRULES  76
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  165

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   318

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   219,   219,   235,   265,   285,   296,   302,   308,   314,
     320,   327,   334,   340,   346,   352,   359,   366,   376,   383,
     390,   397,   405,   412,   418,   426,   432,   438,   444,   450,
     456,   462,   471,   478,   484,   491,   498,   507,   514,   524,
     529,   536,   542,   548,   555,   581,   587,   593,   601,   607,
     613,   619,   625,   631,   637,   643,   649,   655,   661,   667,
     673,   679,   685,   700,   706,   712,   719,   724,   729,   735,
     740,   746,   751,   756,   761,   766,   771
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SEMICOLON", "COMMA", "LETFCURLYBRACKET",
  "RIGHTCURLYBRACKET", "PRINT", "STRINGPRINT", "STRINGREAD", "READ",
  "CLEAN", "PLACE", "IF", "ELSE", "WHILE", "THEN", "ENDIF", "DO",
  "ENDWHILE", "REPEAT", "UNTIL", "FOR", "ENDFOR", "FROM", "STEP", "SWITCH",
  "ENDSWITCH", "ASSIGNMENT", "PLUSASSIGNMENT", "MINUSASSIGNMENT",
  "DIVIASSIGNMENT", "MULTASSIGNMENT", "NUMBER", "STRING", "VARIABLE",
  "NUMERICVARIABLE", "ALPHANUMERICVARIABLE", "UNDEFINED", "CONSTANT",
  "NUMERICCONSTANT", "BUILTIN", "OR", "AND", "GREATER_OR_EQUAL",
  "LESS_OR_EQUAL", "GREATER_THAN", "LESS_THAN", "EQUAL", "NOT_EQUAL",
  "PLUS", "MINUS", "CONCATENATION", "MULTIPLICATION", "DIVISION",
  "INTDIVISION", "MODULO", "INCREMENT", "DECREMENT", "NOT", "UNARY",
  "LPAREN", "RPAREN", "POWER", "$accept", "program", "stmtlist", "stmt",
  "block", "if", "switch", "while", "repeat", "for", "cond", "asgn",
  "print", "read", "esp", "alphanumeric_exp", "logic_exp", "numeric_exp",
  "identifier", "exp", "relational", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318
};
# endif

#define YYPACT_NINF -55

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-55)))

#define YYTABLE_NINF -67

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -55,    12,   168,   -55,   -55,   -55,   -55,   -54,   -48,   -46,
     -37,   -55,   -20,    -2,    -2,   -55,     9,   493,   -55,   -55,
     -55,    11,   -55,   -55,   -55,   -55,   -55,   -55,   -55,    39,
      63,    64,    66,    46,   242,   500,     1,    96,   150,   500,
     455,    55,    72,   279,    58,   -55,   -55,   -55,   -55,   -55,
      33,   500,   500,   500,    43,   558,   -55,   500,   -55,   -55,
     -55,   -55,   474,   500,   500,   500,   500,   -55,   502,   -19,
      29,    37,    44,    45,    47,   455,   -22,   151,   -55,   -55,
      -2,   500,   -25,    49,    49,   516,     1,   500,   500,   500,
     500,   500,   500,   -55,   -55,   500,   316,   558,    88,     0,
      11,   -55,   -55,   558,   558,   558,   558,   -55,   -55,   -55,
     -55,   -55,   -55,   500,   -55,   455,   455,   -55,   -55,   -55,
     -55,   -55,   -55,   -55,   493,   205,   353,   -55,   109,   -55,
      30,   -55,   -55,   465,   465,     7,     7,     7,     7,    49,
     -55,   530,    70,   -55,   -55,   -55,   -55,   -55,   500,   500,
     -55,   -55,   390,    71,   544,   -55,   -55,   500,   -55,   427,
      90,   -55,   -55,   464,   -55
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     1,     5,     6,     3,     0,     0,     0,
       0,    39,     0,     0,     0,     3,     0,     0,    68,    66,
      67,     0,     4,    16,    11,    15,    12,    13,    14,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    48,    41,    61,    42,    62,
       0,     0,     0,     0,    70,    69,     3,     0,     7,     8,
       9,    10,     0,     0,     0,     0,     0,    17,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,     3,
       0,     0,     0,    55,    56,     0,     0,     0,     0,     0,
       0,     0,     0,    58,    57,     0,     0,    31,    61,    67,
      62,    32,    26,    27,    28,    30,    29,    33,    34,    38,
      37,    36,    35,     0,    47,     0,     0,    25,    71,    72,
      73,    74,    75,    76,     0,     0,     0,    22,     0,    64,
       0,    49,    43,    50,    51,    52,    53,    54,    59,    60,
      20,     0,    46,    45,    44,     3,    18,    21,     0,     0,
      63,    40,     0,     0,     0,    19,     3,     0,    65,     0,
       0,    24,     3,     0,    23
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -55,   -55,    -6,   -55,   -55,   -55,   -55,   -55,   -55,   -55,
     -12,    74,   -55,   -55,   -55,   -26,   -53,   -34,   -10,   -13,
     -55
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,    22,    23,    24,    25,    26,    27,    28,
      41,    29,    30,    31,    32,    54,    76,    55,    33,    77,
     124
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      34,    68,    42,   -42,    56,    74,    44,    35,    45,    43,
      69,    47,     3,    36,    49,    37,    50,    83,    84,    85,
     115,   116,   114,    97,    38,    51,    52,    71,    73,   103,
     104,   105,   106,    86,   149,    46,    53,   129,    48,    57,
     117,    39,    58,   108,    18,    19,    20,   128,   130,   102,
      96,   113,   -42,   133,   134,   135,   136,   137,   138,    40,
     132,   139,   142,   143,    93,    94,    59,    60,   127,    61,
      95,    78,   125,   126,    62,    63,    64,    65,    66,   141,
      87,    88,    81,    89,    90,    91,    92,    93,    94,   156,
      79,   109,   150,    95,    82,    86,   157,    87,    88,   110,
      89,    90,    91,    92,    93,    94,   111,   112,   162,     0,
      95,   144,    95,   116,   153,   154,   -66,   -66,   -66,   -66,
     -66,    87,    88,   160,    89,    90,    91,    92,    93,    94,
     148,    18,    19,    20,    95,    70,   101,     0,     0,   152,
      87,    88,     0,    89,    90,    91,    92,    93,    94,     0,
     159,     0,     0,    95,     0,     0,   163,     0,     0,    87,
      88,     0,    89,    90,    91,    92,    93,    94,    -2,     4,
       0,     5,    95,     6,     0,     7,     8,     9,    10,    11,
      12,    13,     0,    14,     0,    18,    19,    20,    15,    72,
      16,     0,     0,     0,    17,   118,   119,   120,   121,   122,
     123,     0,     0,    18,    19,    20,     4,    21,     5,     0,
       6,     0,     7,     8,     9,    10,    11,    12,    13,   145,
      14,     0,   146,     0,     0,    15,     0,    16,     0,     0,
       0,    17,     0,     0,     0,     0,     0,     0,     0,     0,
      18,    19,    20,     4,    21,     5,     0,     6,    67,     7,
       8,     9,    10,    11,    12,    13,     0,    14,     0,     0,
       0,     0,    15,     0,    16,     0,     0,     0,    17,     0,
       0,     0,     0,     0,     0,     0,     0,    18,    19,    20,
       4,    21,     5,     0,     6,     0,     7,     8,     9,    10,
      11,    12,    13,     0,    14,     0,     0,     0,     0,    15,
      80,    16,     0,     0,     0,    17,     0,     0,     0,     0,
       0,     0,     0,     0,    18,    19,    20,     4,    21,     5,
       0,     6,     0,     7,     8,     9,    10,    11,    12,    13,
       0,    14,     0,     0,     0,     0,    15,     0,    16,     0,
       0,     0,    17,   140,     0,     0,     0,     0,     0,     0,
       0,    18,    19,    20,     4,    21,     5,     0,     6,     0,
       7,     8,     9,    10,    11,    12,    13,     0,    14,     0,
       0,     0,   147,    15,     0,    16,     0,     0,     0,    17,
       0,     0,     0,     0,     0,     0,     0,     0,    18,    19,
      20,     4,    21,     5,     0,     6,     0,     7,     8,     9,
      10,    11,    12,    13,     0,    14,     0,   155,     0,     0,
      15,     0,    16,     0,     0,     0,    17,     0,     0,     0,
       0,     0,     0,     0,     0,    18,    19,    20,     4,    21,
       5,     0,     6,     0,     7,     8,     9,    10,    11,    12,
      13,     0,    14,     0,     0,     0,     0,    15,     0,    16,
     161,     0,     0,    17,     0,     0,     0,     0,     0,     0,
       0,     0,    18,    19,    20,     4,    21,     5,     0,     6,
       0,     7,     8,     9,    10,    11,    12,    13,     0,    14,
       0,     0,     0,     0,    15,     0,    16,   164,    45,    46,
      17,    47,    48,     0,    49,     0,    50,     0,     0,    18,
      19,    20,     0,    21,     0,    51,    52,    45,    46,    18,
      98,    99,     0,   100,    75,    50,    53,     0,    89,    90,
      91,    92,    93,    94,    51,    52,    45,    46,    95,    47,
      48,     0,    49,    45,    50,    53,    47,     0,     0,    49,
       0,    50,     0,    51,    52,     0,     0,     0,     0,     0,
      51,    52,    87,    88,    53,    89,    90,    91,    92,    93,
      94,    53,     0,     0,   107,    95,    87,    88,     0,    89,
      90,    91,    92,    93,    94,     0,     0,     0,   131,    95,
      87,    88,     0,    89,    90,    91,    92,    93,    94,     0,
       0,     0,   151,    95,    87,    88,     0,    89,    90,    91,
      92,    93,    94,     0,     0,     0,   158,    95,    87,    88,
       0,    89,    90,    91,    92,    93,    94,     0,     0,     0,
       0,    95
};

static const yytype_int16 yycheck[] =
{
       6,    35,    14,     3,    17,    39,    16,    61,    33,    15,
      36,    36,     0,    61,    39,    61,    41,    51,    52,    53,
      42,    43,    75,    57,    61,    50,    51,    37,    38,    63,
      64,    65,    66,    52,     4,    34,    61,    62,    37,    28,
      62,    61,     3,    62,    35,    36,    37,    81,    82,    62,
      56,     4,    52,    87,    88,    89,    90,    91,    92,    61,
      86,    95,   115,   116,    57,    58,     3,     3,    80,     3,
      63,    16,    78,    79,    28,    29,    30,    31,    32,   113,
      50,    51,    24,    53,    54,    55,    56,    57,    58,    18,
      18,    62,    62,    63,    61,    52,    25,    50,    51,    62,
      53,    54,    55,    56,    57,    58,    62,    62,    18,    -1,
      63,   124,    63,    43,   148,   149,    28,    29,    30,    31,
      32,    50,    51,   157,    53,    54,    55,    56,    57,    58,
      21,    35,    36,    37,    63,    39,    62,    -1,    -1,   145,
      50,    51,    -1,    53,    54,    55,    56,    57,    58,    -1,
     156,    -1,    -1,    63,    -1,    -1,   162,    -1,    -1,    50,
      51,    -1,    53,    54,    55,    56,    57,    58,     0,     1,
      -1,     3,    63,     5,    -1,     7,     8,     9,    10,    11,
      12,    13,    -1,    15,    -1,    35,    36,    37,    20,    39,
      22,    -1,    -1,    -1,    26,    44,    45,    46,    47,    48,
      49,    -1,    -1,    35,    36,    37,     1,    39,     3,    -1,
       5,    -1,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    -1,    17,    -1,    -1,    20,    -1,    22,    -1,    -1,
      -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      35,    36,    37,     1,    39,     3,    -1,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    -1,    15,    -1,    -1,
      -1,    -1,    20,    -1,    22,    -1,    -1,    -1,    26,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,    36,    37,
       1,    39,     3,    -1,     5,    -1,     7,     8,     9,    10,
      11,    12,    13,    -1,    15,    -1,    -1,    -1,    -1,    20,
      21,    22,    -1,    -1,    -1,    26,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    35,    36,    37,     1,    39,     3,
      -1,     5,    -1,     7,     8,     9,    10,    11,    12,    13,
      -1,    15,    -1,    -1,    -1,    -1,    20,    -1,    22,    -1,
      -1,    -1,    26,    27,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    35,    36,    37,     1,    39,     3,    -1,     5,    -1,
       7,     8,     9,    10,    11,    12,    13,    -1,    15,    -1,
      -1,    -1,    19,    20,    -1,    22,    -1,    -1,    -1,    26,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,    36,
      37,     1,    39,     3,    -1,     5,    -1,     7,     8,     9,
      10,    11,    12,    13,    -1,    15,    -1,    17,    -1,    -1,
      20,    -1,    22,    -1,    -1,    -1,    26,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    35,    36,    37,     1,    39,
       3,    -1,     5,    -1,     7,     8,     9,    10,    11,    12,
      13,    -1,    15,    -1,    -1,    -1,    -1,    20,    -1,    22,
      23,    -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    35,    36,    37,     1,    39,     3,    -1,     5,
      -1,     7,     8,     9,    10,    11,    12,    13,    -1,    15,
      -1,    -1,    -1,    -1,    20,    -1,    22,    23,    33,    34,
      26,    36,    37,    -1,    39,    -1,    41,    -1,    -1,    35,
      36,    37,    -1,    39,    -1,    50,    51,    33,    34,    35,
      36,    37,    -1,    39,    59,    41,    61,    -1,    53,    54,
      55,    56,    57,    58,    50,    51,    33,    34,    63,    36,
      37,    -1,    39,    33,    41,    61,    36,    -1,    -1,    39,
      -1,    41,    -1,    50,    51,    -1,    -1,    -1,    -1,    -1,
      50,    51,    50,    51,    61,    53,    54,    55,    56,    57,
      58,    61,    -1,    -1,    62,    63,    50,    51,    -1,    53,
      54,    55,    56,    57,    58,    -1,    -1,    -1,    62,    63,
      50,    51,    -1,    53,    54,    55,    56,    57,    58,    -1,
      -1,    -1,    62,    63,    50,    51,    -1,    53,    54,    55,
      56,    57,    58,    -1,    -1,    -1,    62,    63,    50,    51,
      -1,    53,    54,    55,    56,    57,    58,    -1,    -1,    -1,
      -1,    63
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    65,    66,     0,     1,     3,     5,     7,     8,     9,
      10,    11,    12,    13,    15,    20,    22,    26,    35,    36,
      37,    39,    67,    68,    69,    70,    71,    72,    73,    75,
      76,    77,    78,    82,    66,    61,    61,    61,    61,    61,
      61,    74,    74,    66,    82,    33,    34,    36,    37,    39,
      41,    50,    51,    61,    79,    81,    83,    28,     3,     3,
       3,     3,    28,    29,    30,    31,    32,     6,    81,    79,
      39,    82,    39,    82,    81,    59,    80,    83,    16,    18,
      21,    24,    61,    81,    81,    81,    52,    50,    51,    53,
      54,    55,    56,    57,    58,    63,    66,    81,    36,    37,
      39,    75,    83,    81,    81,    81,    81,    62,    62,    62,
      62,    62,    62,     4,    80,    42,    43,    62,    44,    45,
      46,    47,    48,    49,    84,    66,    66,    74,    81,    62,
      81,    62,    79,    81,    81,    81,    81,    81,    81,    81,
      27,    81,    80,    80,    83,    14,    17,    19,    21,     4,
      62,    62,    66,    81,    81,    17,    18,    25,    62,    66,
      81,    23,    18,    66,    23
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    64,    65,    66,    66,    66,    67,    67,    67,    67,
      67,    67,    67,    67,    67,    67,    67,    68,    69,    69,
      70,    71,    72,    73,    73,    74,    75,    75,    75,    75,
      75,    75,    75,    76,    76,    77,    77,    77,    77,    78,
      78,    79,    79,    79,    80,    80,    80,    80,    81,    81,
      81,    81,    81,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    81,    81,    82,    82,    82,    83,
      83,    84,    84,    84,    84,    84,    84
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     2,     1,     2,     2,     2,
       2,     1,     1,     1,     1,     1,     1,     3,     5,     7,
       4,     5,     4,    11,     9,     3,     3,     3,     3,     3,
       3,     3,     3,     4,     4,     4,     4,     4,     4,     1,
       6,     1,     1,     3,     3,     3,     3,     2,     1,     3,
       3,     3,     3,     3,     3,     2,     2,     2,     2,     3,
       3,     1,     1,     4,     3,     6,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 220 "ipe.y" /* yacc.c:1646  */
    {
		  	// Aqui solo se entra cuando acabamos el programa

			// Create a new AST
			(yyval.prog) = new lp::AST((yyvsp[0].stmts)); 

			// Assign the AST to the root
			root = (yyval.prog); 

			// End of parsing
			// return 1;
		  }
#line 1606 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 235 "ipe.y" /* yacc.c:1646  */
    {
			// std::cout<<"Se crea una lista nueva de sentencias\n";

			/*
				- La primera sentencia que coge (vacía), es el nodo raiz del Árbol AST
				- Se crea automáticamente al arrancar (regla epsilon)
			*/

			// create a empty list of statements
			if(!nodeRoot)
			{
				// std::cout<<"crea nodeRoot"<<std::endl;

				// apunto quien es el nodo raiz
				nodeRoot = new std::list<lp::Statement *>();

				// Esto me sirve para ejecutar las estructuras de control en el modo intérprete correctamente
				(yyval.stmts) = nodeRoot;
			}
			else
			{
				/*
					-Cada vez que crea una lista de sentencias nueva, 
					lo hace con la instrucción de abajo.
				*/

				(yyval.stmts) = new std::list<lp::Statement *>(); 
			}
		}
#line 1640 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 266 "ipe.y" /* yacc.c:1646  */
    {
			// copy up the list and add the stmt to it
			(yyval.stmts) = (yyvsp[-1].stmts);
			(yyval.stmts)->push_back((yyvsp[0].st));

			/*
				Solo se ejecuta el árbol (el stmtlist), si su padre es el nodo raiz
			*/
			if(1) // Solo si usamos el intérprete
			{
				if((yyvsp[-1].stmts) == nodeRoot)
				{
					//std::cout<<"padre es root"<<std::endl;
					(yyvsp[0].st)->evaluate();
				}
			}
		}
#line 1662 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 286 "ipe.y" /* yacc.c:1646  */
    { 
			// just copy up the stmtlist when an error occurs
			(yyval.stmts) = (yyvsp[-1].stmts);

			// The previous look-ahead token ought to be discarded with `yyclearin;'
			yyclearin; 
		}
#line 1674 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 297 "ipe.y" /* yacc.c:1646  */
    {
			// Create a new empty statement node
			(yyval.st) = new lp::EmptyStmt(); 
		}
#line 1683 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 303 "ipe.y" /* yacc.c:1646  */
    {
			// Default action
			// $$ = $1;
		}
#line 1692 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 309 "ipe.y" /* yacc.c:1646  */
    {
			// Default action
			// $$ = $1;
		}
#line 1701 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 315 "ipe.y" /* yacc.c:1646  */
    {
			// Default action
			// $$ = $1;
		}
#line 1710 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 321 "ipe.y" /* yacc.c:1646  */
    {
			// Default action
			// $$ = $1;
		}
#line 1719 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 328 "ipe.y" /* yacc.c:1646  */
    {
			// Default action
			// $$ = $1;
		}
#line 1728 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 335 "ipe.y" /* yacc.c:1646  */
    {
			// Default action
			// $$ = $1;
		}
#line 1737 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 341 "ipe.y" /* yacc.c:1646  */
    {
			// Default action
			// $$ = $1;
		}
#line 1746 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 347 "ipe.y" /* yacc.c:1646  */
    {
			// Default action
			// $$ = $1;
		}
#line 1755 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 353 "ipe.y" /* yacc.c:1646  */
    {
			// Default action
			// $$ = $1;
		}
#line 1764 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 360 "ipe.y" /* yacc.c:1646  */
    {
			// Default action
			// $$ = $1;
		}
#line 1773 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 367 "ipe.y" /* yacc.c:1646  */
    {
			// Create a new block of statements node
			(yyval.st) = new lp::BlockStmt((yyvsp[-1].stmts)); 
		}
#line 1782 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 377 "ipe.y" /* yacc.c:1646  */
    {
		// Create a new if statement node
		(yyval.st) = new lp::IfStmt((yyvsp[-3].logicExpNode), (yyvsp[-1].stmts));
	}
#line 1791 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 384 "ipe.y" /* yacc.c:1646  */
    {
		// Create a new if statement node
		(yyval.st) = new lp::IfStmt((yyvsp[-5].logicExpNode), (yyvsp[-3].stmts), (yyvsp[-1].stmts));
	}
#line 1800 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 391 "ipe.y" /* yacc.c:1646  */
    {
			(yyval.st) = new lp::SwitchStmt((yyvsp[-2].expNode), (yyvsp[-1].stmts));
		}
#line 1808 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 398 "ipe.y" /* yacc.c:1646  */
    {
			// Create a new while statement node
			(yyval.st) = new lp::WhileStmt((yyvsp[-3].logicExpNode), (yyvsp[-1].stmts));
		}
#line 1817 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 406 "ipe.y" /* yacc.c:1646  */
    {
			// Create a new repeat statement node
			(yyval.st) = new lp::RepeatStmt((yyvsp[0].logicExpNode), (yyvsp[-2].stmts));
		}
#line 1826 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 413 "ipe.y" /* yacc.c:1646  */
    {
			// Create a new for statement node
			(yyval.st) = new lp::ForStmt((yyvsp[-9].name), (yyvsp[-7].numericExpNode), (yyvsp[-5].numericExpNode), (yyvsp[-3].numericExpNode), (yyvsp[-1].stmts));
		}
#line 1835 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 419 "ipe.y" /* yacc.c:1646  */
    {
			// Create a new for statement node
			(yyval.st) = new lp::ForStmt((yyvsp[-7].name), (yyvsp[-5].numericExpNode), (yyvsp[-3].numericExpNode), (yyvsp[-1].stmts));
		}
#line 1844 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 427 "ipe.y" /* yacc.c:1646  */
    { 
			(yyval.logicExpNode) = (yyvsp[-1].logicExpNode);
		}
#line 1852 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 433 "ipe.y" /* yacc.c:1646  */
    { 
			// Create a new assignment node
			(yyval.st) = new lp::AssignmentStmt((yyvsp[-2].name), (yyvsp[0].expNode));
		}
#line 1861 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 439 "ipe.y" /* yacc.c:1646  */
    { 
			// Create a new assignment node
			(yyval.st) = new lp::PlusAssignmentStmt((yyvsp[-2].name), (yyvsp[0].numericExpNode));
		}
#line 1870 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 445 "ipe.y" /* yacc.c:1646  */
    { 
			// Create a new assignment node
			(yyval.st) = new lp::MinusAssignmentStmt((yyvsp[-2].name), (yyvsp[0].numericExpNode));
		}
#line 1879 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 451 "ipe.y" /* yacc.c:1646  */
    { 
			// Create a new assignment node
			(yyval.st) = new lp::MultAssignmentStmt((yyvsp[-2].name), (yyvsp[0].numericExpNode));
		}
#line 1888 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 457 "ipe.y" /* yacc.c:1646  */
    { 
			// Create a new assignment node
			(yyval.st) = new lp::DiviAssignmentStmt((yyvsp[-2].name), (yyvsp[0].numericExpNode));
		}
#line 1897 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 463 "ipe.y" /* yacc.c:1646  */
    {   
			// Get the name in the table of symbols as NumericConstant
			lp::NumericConstant *n = (lp::NumericConstant *) table.getSymbol((yyvsp[-2].name));

			execerror("Semantic error in assignment: it is not allowed to modify a constant ",
				n->getName());
		}
#line 1909 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 472 "ipe.y" /* yacc.c:1646  */
    { 
			// Create a new assignment node
			(yyval.st) = new lp::AssignmentStmt((yyvsp[-2].name), (lp::AssignmentStmt *) (yyvsp[0].st));
		}
#line 1918 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 479 "ipe.y" /* yacc.c:1646  */
    {
			// Create a new print node
			(yyval.st) = new lp::PrintStmt((yyvsp[-1].numericExpNode));
		}
#line 1927 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 485 "ipe.y" /* yacc.c:1646  */
    {
			// Create a new print node
			(yyval.st) = new lp::PrintStmt((yyvsp[-1].alphanumericExpNode));
		}
#line 1936 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 492 "ipe.y" /* yacc.c:1646  */
    {
			// Create a new read node
			 (yyval.st) = new lp::ReadStmt(NUMERICVARIABLE, (yyvsp[-1].name));

		}
#line 1946 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 499 "ipe.y" /* yacc.c:1646  */
    {   
			// Get the name in the table of symbols as NumericConstant
			lp::NumericConstant *n = (lp::NumericConstant *) table.getSymbol((yyvsp[-1].name));

			execerror("Semantic error in \"read statement\": it is not allowed to modify a constant ",
					   n->getName());
		}
#line 1958 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 508 "ipe.y" /* yacc.c:1646  */
    {
			// Create a new read node
			 (yyval.st) = new lp::ReadStmt(ALPHANUMERICVARIABLE, (yyvsp[-1].name));

		}
#line 1968 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 515 "ipe.y" /* yacc.c:1646  */
    {   
			// Get the name in the table of symbols as NumericConstant
			lp::NumericConstant *n = (lp::NumericConstant *) table.getSymbol((yyvsp[-1].name));

			execerror("Semantic error in \"read statement\": it is not allowed to modify a constant ",
					   n->getName());
		}
#line 1980 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 525 "ipe.y" /* yacc.c:1646  */
    {
			// Create a new Clean node
			(yyval.st) = new lp::CleanStmt();
		}
#line 1989 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 530 "ipe.y" /* yacc.c:1646  */
    {
			// Create a new Place node
			(yyval.st) = new lp::PlaceStmt((yyvsp[-3].numericExpNode), (yyvsp[-1].numericExpNode));
		}
#line 1998 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 537 "ipe.y" /* yacc.c:1646  */
    {
						// Create a new number node
						(yyval.alphanumericExpNode) = new lp::StringNode((yyvsp[0].name));
					}
#line 2007 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 543 "ipe.y" /* yacc.c:1646  */
    {
						// Create a new numeric variable node	
						(yyval.alphanumericExpNode) = new lp::AlphanumericVariableNode((yyvsp[0].name));
					}
#line 2016 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 549 "ipe.y" /* yacc.c:1646  */
    {
						// Create a new plus node
						(yyval.alphanumericExpNode) = new lp::ConcatenationNode((yyvsp[-2].alphanumericExpNode), (yyvsp[0].alphanumericExpNode));
					}
#line 2025 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 556 "ipe.y" /* yacc.c:1646  */
    {
				if ((yyvsp[-2].expNode)->isAlphanumeric() != (yyvsp[0].expNode)->isAlphanumeric()) // Deben ser del mismo tipo
					execerror("No se pueden comparar valores de diferentes tipos", "prueba");
				else
				{
					if((yyvsp[-1].integer) == LESS_THAN)
						(yyval.logicExpNode) = new lp::LessThanNode((yyvsp[-2].expNode),(yyvsp[0].expNode));
					
					if((yyvsp[-1].integer) == GREATER_THAN)
						(yyval.logicExpNode) = new lp::GreaterThanNode((yyvsp[-2].expNode),(yyvsp[0].expNode));

					if((yyvsp[-1].integer) == GREATER_OR_EQUAL)
						(yyval.logicExpNode) = new lp::GreaterOrEqualNode((yyvsp[-2].expNode),(yyvsp[0].expNode));

					if((yyvsp[-1].integer) == LESS_OR_EQUAL)
						(yyval.logicExpNode) = new lp::LessOrEqualNode((yyvsp[-2].expNode),(yyvsp[0].expNode));

					if((yyvsp[-1].integer) == EQUAL)
						(yyval.logicExpNode) = new lp::EqualNode((yyvsp[-2].expNode),(yyvsp[0].expNode));

					if((yyvsp[-1].integer) == NOT_EQUAL)
						(yyval.logicExpNode) = new lp::NotEqualNode((yyvsp[-2].expNode),(yyvsp[0].expNode));
				}
			}
#line 2054 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 582 "ipe.y" /* yacc.c:1646  */
    {
				// Create a new "logic and" node	
				(yyval.logicExpNode) = new lp::AndNode((yyvsp[-2].logicExpNode),(yyvsp[0].logicExpNode));
			}
#line 2063 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 588 "ipe.y" /* yacc.c:1646  */
    {
				// Create a new "logic or" node	
				(yyval.logicExpNode) = new lp::OrNode((yyvsp[-2].logicExpNode),(yyvsp[0].logicExpNode));
			}
#line 2072 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 594 "ipe.y" /* yacc.c:1646  */
    {
				// Create a new "logic negation" node	
				(yyval.logicExpNode) = new lp::NotNode((yyvsp[0].logicExpNode));
			}
#line 2081 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 602 "ipe.y" /* yacc.c:1646  */
    {
					// Create a new number node
					(yyval.numericExpNode) = new lp::NumberNode((yyvsp[0].number));
				}
#line 2090 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 608 "ipe.y" /* yacc.c:1646  */
    {
					// Create a new number node
					(yyval.numericExpNode) = (yyvsp[-1].numericExpNode);
				}
#line 2099 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 614 "ipe.y" /* yacc.c:1646  */
    { 
					// Create a new plus node
					(yyval.numericExpNode) = new lp::PlusNode((yyvsp[-2].numericExpNode), (yyvsp[0].numericExpNode));
				}
#line 2108 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 620 "ipe.y" /* yacc.c:1646  */
    {
					// Create a new minus node
					(yyval.numericExpNode) = new lp::MinusNode((yyvsp[-2].numericExpNode), (yyvsp[0].numericExpNode));
				}
#line 2117 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 626 "ipe.y" /* yacc.c:1646  */
    { 
					// Create a new multiplication node
					(yyval.numericExpNode) = new lp::MultiplicationNode((yyvsp[-2].numericExpNode), (yyvsp[0].numericExpNode));
				}
#line 2126 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 632 "ipe.y" /* yacc.c:1646  */
    {
					// Create a new division node	
					(yyval.numericExpNode) = new lp::DivisionNode((yyvsp[-2].numericExpNode), (yyvsp[0].numericExpNode));
				}
#line 2135 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 638 "ipe.y" /* yacc.c:1646  */
    {
					// Create a new division node	
					(yyval.numericExpNode) = new lp::IntDivisionNode((yyvsp[-2].numericExpNode), (yyvsp[0].numericExpNode));
				}
#line 2144 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 644 "ipe.y" /* yacc.c:1646  */
    { 
					// Create a new unary plus node	
					(yyval.numericExpNode) = new lp::UnaryPlusNode((yyvsp[0].numericExpNode));
				}
#line 2153 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 650 "ipe.y" /* yacc.c:1646  */
    { 
					// Create a new unary minus node
					(yyval.numericExpNode) = new lp::UnaryMinusNode((yyvsp[0].numericExpNode));
				}
#line 2162 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 656 "ipe.y" /* yacc.c:1646  */
    { 
					// Create a new unary minus node
					(yyval.numericExpNode) = new lp::DecrementNode((yyvsp[-1].numericExpNode));
				}
#line 2171 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 662 "ipe.y" /* yacc.c:1646  */
    { 
					// Create a new unary minus node
					(yyval.numericExpNode) = new lp::IncrementNode((yyvsp[-1].numericExpNode));
				}
#line 2180 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 668 "ipe.y" /* yacc.c:1646  */
    {
					// Create a new modulo node
					(yyval.numericExpNode) = new lp::ModuloNode((yyvsp[-2].numericExpNode), (yyvsp[0].numericExpNode));
				}
#line 2189 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 674 "ipe.y" /* yacc.c:1646  */
    { 
					// Create a new power node	
					(yyval.numericExpNode) = new lp::PowerNode((yyvsp[-2].numericExpNode), (yyvsp[0].numericExpNode));
				}
#line 2198 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 680 "ipe.y" /* yacc.c:1646  */
    {
					// Create a new numeric variable node	
					(yyval.numericExpNode) = new lp::NumericVariableNode((yyvsp[0].name));
				}
#line 2207 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 686 "ipe.y" /* yacc.c:1646  */
    {
					// Get the name in the table of symbols as NumericConstant
					lp::NumericConstant *n = (lp::NumericConstant *) table.getSymbol((yyvsp[0].name));

					// Check if the type of the name is NUMERICONSTANT
					if (n->getType() == NUMERICCONSTANT)
					{
						// Create a new numericConstant node	
						(yyval.numericExpNode) = new lp::NumericConstantNode((yyvsp[0].name));
					}
					else			 
						execerror("Undefined constant", n->getName());		
				}
#line 2225 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 701 "ipe.y" /* yacc.c:1646  */
    {
					// Create a new Builtin Function with 1 parameter node	
					(yyval.numericExpNode) = new lp::BuiltinFunctionNode((yyvsp[-3].name),(yyvsp[-1].numericExpNode));
				}
#line 2234 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 707 "ipe.y" /* yacc.c:1646  */
    {
					// Create a new Builtin Function with 0 parameters node	
					(yyval.numericExpNode) = new lp::BuiltinFunctionNode_0((yyvsp[-2].name));
				}
#line 2243 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 713 "ipe.y" /* yacc.c:1646  */
    {
					// Create a new Builtin Function with 2 parameters node	
					(yyval.numericExpNode) = new lp::BuiltinFunctionNode_2((yyvsp[-5].name),(yyvsp[-3].numericExpNode),(yyvsp[-1].numericExpNode));
				}
#line 2252 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 720 "ipe.y" /* yacc.c:1646  */
    {
				// std::cout<<"NUMERICVARIABLE -> identifier"<<std::endl;
			}
#line 2260 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 725 "ipe.y" /* yacc.c:1646  */
    {

			}
#line 2268 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 730 "ipe.y" /* yacc.c:1646  */
    {

			}
#line 2276 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 736 "ipe.y" /* yacc.c:1646  */
    {

		}
#line 2284 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 741 "ipe.y" /* yacc.c:1646  */
    {

		}
#line 2292 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 747 "ipe.y" /* yacc.c:1646  */
    {
				(yyval.integer) = GREATER_OR_EQUAL;
			}
#line 2300 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 752 "ipe.y" /* yacc.c:1646  */
    {
				(yyval.integer) = LESS_OR_EQUAL;
			}
#line 2308 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 757 "ipe.y" /* yacc.c:1646  */
    {
				(yyval.integer) = GREATER_THAN;
			}
#line 2316 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 762 "ipe.y" /* yacc.c:1646  */
    {
				(yyval.integer) = LESS_THAN;
			}
#line 2324 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 767 "ipe.y" /* yacc.c:1646  */
    {
				(yyval.integer) = EQUAL;
			}
#line 2332 "ipe.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 772 "ipe.y" /* yacc.c:1646  */
    {
				(yyval.integer) = NOT_EQUAL;
			}
#line 2340 "ipe.tab.c" /* yacc.c:1646  */
    break;


#line 2344 "ipe.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 777 "ipe.y" /* yacc.c:1906  */





