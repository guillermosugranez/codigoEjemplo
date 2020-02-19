/*! 
  \file interpreter.y
  \brief Grammar file
*/

%{
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

%}

/* In case of a syntactic error, more information is shown */
%error-verbose

/* Initial grammar symbol */
%start program

/*******************************************/
/* Data type YYSTYPE  */
/* NEW in example 4 */
%union {
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
}

/* Type of the non-terminal symbols */
// New in example 17: cond
%type <numericExpNode> numeric_exp 
%type <logicExpNode> logic_exp cond
%type <alphanumericExpNode> alphanumeric_exp
%type <expNode> exp 

%type <stmts> stmtlist

// New in example 17: if, while, block
%type <st> stmt asgn print esp read if while block repeat for switch
%type <name> identifier
%type <integer> relational

%type <prog> program

// Defined token 

/* Minimum precedence */

/*******************************************/
/* NEW in example 5 */
%token SEMICOLON
/*******************************************/

%token COMMA

// NEW in example 17
%token LETFCURLYBRACKET RIGHTCURLYBRACKET

// NEW in example 17: IF, ELSE, WHILE 
%token PRINT STRINGPRINT STRINGREAD READ CLEAN PLACE IF ELSE WHILE THEN ENDIF DO ENDWHILE REPEAT UNTIL FOR ENDFOR FROM STEP SWITCH ENDSWITCH

/* NEW in example 7 */
%right ASSIGNMENT PLUSASSIGNMENT MINUSASSIGNMENT DIVIASSIGNMENT MULTASSIGNMENT

/*******************************************/
/* MODIFIED in example 4 */
%token <number> NUMBER
%token <name> STRING
/*******************************************/

/* MODIFIED in examples 11, 13 */
%token <name> VARIABLE NUMERICVARIABLE ALPHANUMERICVARIABLE UNDEFINED CONSTANT NUMERICCONSTANT BUILTIN

/* Left associativity */

/*******************************************************/
/* NEW in example 15 */
%left OR

%left AND

%nonassoc GREATER_OR_EQUAL LESS_OR_EQUAL GREATER_THAN LESS_THAN EQUAL NOT_EQUAL

/*******************************************************/

/* MODIFIED in example 3 */
%left PLUS MINUS CONCATENATION

/* MODIFIED in example 5 */
%left MULTIPLICATION DIVISION INTDIVISION MODULO

%right INCREMENT DECREMENT

%left NOT

%nonassoc UNARY

%left LPAREN RPAREN

// Maximum precedence 
/* MODIFIED in example 5 */
%right POWER


%%


//! \name Grammar rules

/* MODIFIED  Grammar in examples 16 and 17 */

program : stmtlist
		  {
		  	// Aqui solo se entra cuando acabamos el programa

			// Create a new AST
			$$ = new lp::AST($1); 

			// Assign the AST to the root
			root = $$; 

			// End of parsing
			// return 1;
		  }
;

stmtlist:  /* empty: epsilon rule */
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
				$$ = nodeRoot;
			}
			else
			{
				/*
					-Cada vez que crea una lista de sentencias nueva, 
					lo hace con la instrucción de abajo.
				*/

				$$ = new std::list<lp::Statement *>(); 
			}
		}  

		| stmtlist stmt
		{
			// copy up the list and add the stmt to it
			$$ = $1;
			$$->push_back($2);

			/*
				Solo se ejecuta el árbol (el stmtlist), si su padre es el nodo raiz
			*/
			if(1) // Solo si usamos el intérprete
			{
				if($1 == nodeRoot)
				{
					//std::cout<<"padre es root"<<std::endl;
					$2->evaluate();
				}
			}
		}


		| stmtlist error 
		{ 
			// just copy up the stmtlist when an error occurs
			$$ = $1;

			// The previous look-ahead token ought to be discarded with `yyclearin;'
			yyclearin; 
		} 
;
 

stmt: SEMICOLON  /* Empty statement: ";" */
		{
			// Create a new empty statement node
			$$ = new lp::EmptyStmt(); 
		}

		| asgn  SEMICOLON
		{
			// Default action
			// $$ = $1;
		}

		| print SEMICOLON
		{
			// Default action
			// $$ = $1;
		}

		| read SEMICOLON
		{
			// Default action
			// $$ = $1;
		}

		| esp SEMICOLON
		{
			// Default action
			// $$ = $1;
		}

		/*  NEW in example 17 */
		| if 
		{
			// Default action
			// $$ = $1;
		}

		/*  NEW in example 17 */
		| while 
		{
			// Default action
			// $$ = $1;
		}
		
		| repeat 
		{
			// Default action
			// $$ = $1;
		}

		| for 
		{
			// Default action
			// $$ = $1;
		}

		| switch 
		{
			// Default action
			// $$ = $1;
		}

		/*  NEW in example 17 */
		| block 
		{
			// Default action
			// $$ = $1;
		}
;

block:	LETFCURLYBRACKET stmtlist RIGHTCURLYBRACKET  
		{
			// Create a new block of statements node
			$$ = new lp::BlockStmt($2); 
		}
;
 
/*  NEW in example 17 */

if:	/* Simple conditional statement */
	IF cond THEN stmtlist ENDIF 
	{
		// Create a new if statement node
		$$ = new lp::IfStmt($2, $4);
	}

	/* Compound conditional statement */
	| IF cond THEN stmtlist ELSE stmtlist ENDIF 
	{
		// Create a new if statement node
		$$ = new lp::IfStmt($2, $4, $6);
	}
;

switch:	SWITCH exp stmtlist ENDSWITCH
		{
			$$ = new lp::SwitchStmt($2, $3);
		}
;

	/*  NEW in example 17 */
while:  WHILE cond DO stmtlist ENDWHILE
		{
			// Create a new while statement node
			$$ = new lp::WhileStmt($2, $4);
		}
;


repeat:  REPEAT stmtlist UNTIL cond
		{
			// Create a new repeat statement node
			$$ = new lp::RepeatStmt($4, $2);
		}
;

for: 	FOR identifier FROM numeric_exp UNTIL numeric_exp STEP numeric_exp DO stmtlist ENDFOR
		{
			// Create a new for statement node
			$$ = new lp::ForStmt($2, $4, $6, $8, $10);
		}

		| FOR identifier FROM numeric_exp UNTIL numeric_exp DO stmtlist ENDFOR
		{
			// Create a new for statement node
			$$ = new lp::ForStmt($2, $4, $6, $8);
		}
;

	/*  NEW in example 17 */
cond: 	LPAREN logic_exp RPAREN
		{ 
			$$ = $2;
		}
;

asgn:   identifier ASSIGNMENT exp 
		{ 
			// Create a new assignment node
			$$ = new lp::AssignmentStmt($1, $3);
		}

		| identifier PLUSASSIGNMENT numeric_exp 
		{ 
			// Create a new assignment node
			$$ = new lp::PlusAssignmentStmt($1, $3);
		}
		
		| identifier MINUSASSIGNMENT numeric_exp 
		{ 
			// Create a new assignment node
			$$ = new lp::MinusAssignmentStmt($1, $3);
		}
		
		| identifier MULTASSIGNMENT numeric_exp 
		{ 
			// Create a new assignment node
			$$ = new lp::MultAssignmentStmt($1, $3);
		}
		
		| identifier DIVIASSIGNMENT numeric_exp 
		{ 
			// Create a new assignment node
			$$ = new lp::DiviAssignmentStmt($1, $3);
		}

		| CONSTANT ASSIGNMENT numeric_exp 
		{   
			// Get the name in the table of symbols as NumericConstant
			lp::NumericConstant *n = (lp::NumericConstant *) table.getSymbol($1);

			execerror("Semantic error in assignment: it is not allowed to modify a constant ",
				n->getName());
		}

		| identifier ASSIGNMENT asgn 
		{ 
			// Create a new assignment node
			$$ = new lp::AssignmentStmt($1, (lp::AssignmentStmt *) $3);
		}
;

print:  PRINT LPAREN numeric_exp RPAREN
		{
			// Create a new print node
			$$ = new lp::PrintStmt($3);
		}

		| STRINGPRINT LPAREN alphanumeric_exp RPAREN
		{
			// Create a new print node
			$$ = new lp::PrintStmt($3);
		}
;	

read:	READ LPAREN identifier RPAREN  
		{
			// Create a new read node
			 $$ = new lp::ReadStmt(NUMERICVARIABLE, $3);

		}

		| READ LPAREN CONSTANT RPAREN  
		{   
			// Get the name in the table of symbols as NumericConstant
			lp::NumericConstant *n = (lp::NumericConstant *) table.getSymbol($3);

			execerror("Semantic error in \"read statement\": it is not allowed to modify a constant ",
					   n->getName());
		}

		| STRINGREAD LPAREN identifier RPAREN  
		{
			// Create a new read node
			 $$ = new lp::ReadStmt(ALPHANUMERICVARIABLE, $3);

		}

		| STRINGREAD LPAREN CONSTANT RPAREN  
		{   
			// Get the name in the table of symbols as NumericConstant
			lp::NumericConstant *n = (lp::NumericConstant *) table.getSymbol($3);

			execerror("Semantic error in \"read statement\": it is not allowed to modify a constant ",
					   n->getName());
		}
;	

esp:	CLEAN
		{
			// Create a new Clean node
			$$ = new lp::CleanStmt();
		}
		| PLACE LPAREN numeric_exp COMMA numeric_exp RPAREN
		{
			// Create a new Place node
			$$ = new lp::PlaceStmt($3, $5);
		}
;

alphanumeric_exp:	STRING
					{
						// Create a new number node
						$$ = new lp::StringNode($1);
					}

					| ALPHANUMERICVARIABLE
					{
						// Create a new numeric variable node	
						$$ = new lp::AlphanumericVariableNode($1);
					}

					| alphanumeric_exp CONCATENATION alphanumeric_exp
					{
						// Create a new plus node
						$$ = new lp::ConcatenationNode($1, $3);
					}
;

logic_exp:	exp relational exp 	
			{
				if ($1->isAlphanumeric() != $3->isAlphanumeric()) // Deben ser del mismo tipo
					execerror("No se pueden comparar valores de diferentes tipos", "prueba");
				else
				{
					if($2 == LESS_THAN)
						$$ = new lp::LessThanNode($1,$3);
					
					if($2 == GREATER_THAN)
						$$ = new lp::GreaterThanNode($1,$3);

					if($2 == GREATER_OR_EQUAL)
						$$ = new lp::GreaterOrEqualNode($1,$3);

					if($2 == LESS_OR_EQUAL)
						$$ = new lp::LessOrEqualNode($1,$3);

					if($2 == EQUAL)
						$$ = new lp::EqualNode($1,$3);

					if($2 == NOT_EQUAL)
						$$ = new lp::NotEqualNode($1,$3);
				}
			}

			| logic_exp AND logic_exp 
			{
				// Create a new "logic and" node	
				$$ = new lp::AndNode($1,$3);
			}

			| logic_exp OR logic_exp 
			{
				// Create a new "logic or" node	
				$$ = new lp::OrNode($1,$3);
			}

			| NOT logic_exp 
			{
				// Create a new "logic negation" node	
				$$ = new lp::NotNode($2);
			}

;

numeric_exp:	NUMBER 
				{
					// Create a new number node
					$$ = new lp::NumberNode($1);
				}

				| LPAREN numeric_exp RPAREN
				{
					// Create a new number node
					$$ = $2;
				}

				| 	numeric_exp PLUS numeric_exp 
				{ 
					// Create a new plus node
					$$ = new lp::PlusNode($1, $3);
				}

				| 	numeric_exp MINUS numeric_exp
				{
					// Create a new minus node
					$$ = new lp::MinusNode($1, $3);
				}

				| 	numeric_exp MULTIPLICATION numeric_exp 
				{ 
					// Create a new multiplication node
					$$ = new lp::MultiplicationNode($1, $3);
				}

				| 	numeric_exp DIVISION numeric_exp
				{
					// Create a new division node	
					$$ = new lp::DivisionNode($1, $3);
				}

				| 	numeric_exp INTDIVISION numeric_exp
				{
					// Create a new division node	
					$$ = new lp::IntDivisionNode($1, $3);
				}

				| 	PLUS numeric_exp %prec UNARY
				{ 
					// Create a new unary plus node	
					$$ = new lp::UnaryPlusNode($2);
				}

				| 	MINUS numeric_exp %prec UNARY
				{ 
					// Create a new unary minus node
					$$ = new lp::UnaryMinusNode($2);
				}

				| 	numeric_exp DECREMENT %prec UNARY
				{ 
					// Create a new unary minus node
					$$ = new lp::DecrementNode($1);
				}

				| 	numeric_exp INCREMENT %prec UNARY
				{ 
					// Create a new unary minus node
					$$ = new lp::IncrementNode($1);
				}

				|	numeric_exp MODULO numeric_exp 
				{
					// Create a new modulo node
					$$ = new lp::ModuloNode($1, $3);
				}

				|	numeric_exp POWER numeric_exp 
				{ 
					// Create a new power node	
					$$ = new lp::PowerNode($1, $3);
				}

				| NUMERICVARIABLE
				{
					// Create a new numeric variable node	
					$$ = new lp::NumericVariableNode($1);
				}

				| CONSTANT
				{
					// Get the name in the table of symbols as NumericConstant
					lp::NumericConstant *n = (lp::NumericConstant *) table.getSymbol($1);

					// Check if the type of the name is NUMERICONSTANT
					if (n->getType() == NUMERICCONSTANT)
					{
						// Create a new numericConstant node	
						$$ = new lp::NumericConstantNode($1);
					}
					else			 
						execerror("Undefined constant", n->getName());		
				}

				| BUILTIN LPAREN numeric_exp RPAREN
				{
					// Create a new Builtin Function with 1 parameter node	
					$$ = new lp::BuiltinFunctionNode($1,$3);
				}

				| BUILTIN LPAREN RPAREN
				{
					// Create a new Builtin Function with 0 parameters node	
					$$ = new lp::BuiltinFunctionNode_0($1);
				}

				| BUILTIN LPAREN numeric_exp COMMA numeric_exp RPAREN
				{
					// Create a new Builtin Function with 2 parameters node	
					$$ = new lp::BuiltinFunctionNode_2($1,$3,$5);
				}
;

identifier: NUMERICVARIABLE
			{
				// std::cout<<"NUMERICVARIABLE -> identifier"<<std::endl;
			}

			| ALPHANUMERICVARIABLE
			{

			}

			| VARIABLE
			{

			}
;

exp:	numeric_exp
		{

		}

		| alphanumeric_exp
		{

		}
;

relational:	GREATER_OR_EQUAL
			{
				$$ = GREATER_OR_EQUAL;
			}
			
			| LESS_OR_EQUAL
			{
				$$ = LESS_OR_EQUAL;
			} 
			
			| GREATER_THAN
			{
				$$ = GREATER_THAN;
			}
			
			| LESS_THAN
			{
				$$ = LESS_THAN;
			}
			
			| EQUAL
			{
				$$ = EQUAL;
			}
			
			| NOT_EQUAL
			{
				$$ = NOT_EQUAL;
			}
;

%%




