/*! 
\file interpreter.cpp
\brief Main program
*/

/*!
\mainpage Flex and Bison: example 17
\author   
\date     2018 - 4 - 26
\version  1.0
\note Novelties
+ AST: intermidiate code
+ New statements: if, while, block
*/



// New in example 2
#include <stdio.h>
#include <string>
#include <cstring>
//

/////////////////////////////
/* 
NEW in example 16 
AST class
IMPORTANT: must be written before interpreter.tab.h
*/
#include "ast/ast.hpp"
////////////////////////////////////////

#include "./parser/ipe.tab.h"

int lineNumber = 1; //!< Line counter
int modoFichero = 0;

// New in example 2
extern FILE * yyin; //!< Standard input device for yylex() 
std::string progname; //!<  Program name
//


//////////////////////////////////////////////
// NEW in example 6 

// Use for recovery of runtime errors 
#include <setjmp.h>
#include <signal.h>

// Error recovery functions 
#include "error/error.hpp"


lp::AST *root; //!< Root of the abstract syntax tree AST
///////////////////////////////////////////// 

//////////////////////////////////////////////
// NEW in example 10 

#include "table/init.hpp"


/*
jhmp_buf
This is an array type capable of storing the information of a calling environment to be restored later.
This information is filled by calling macro setjmp and can be restored by calling function longjmp.
*/
extern jmp_buf begin; //!<  It enables recovery of runtime errors 

//////////////////////////////////////////////
// NEW in example 7 

#include "table/table.hpp"
#include "./includes/macros.hpp"

lp::Table table; //!< Table of Symbols

// cout.precision
#include <iostream>

//////////////////////////////////////////////////

//! \name Main program

/*! 
\brief  Main function
\param  argc: number of command line parameters
\param  argv: values of command line parameters
\return int
\note   C++ requires that main returns an int value
\sa     yyparse, yylex
*/
int main(int argc, char *argv[])
{
	// Option -t needed
	// yydebug = 1;

	/* 
	If the input file exists 
	then 
	it is set as input device for yylex();
	otherwise
	the input device is the keyboard (stdin)
	*/
	if (argc == 2)
	{
		//Comprobar extension
		std::string extension(argv[1]);

		if(extension[extension.size() - 1] == 'e' && extension[extension.size() - 2] == '.')
		{
			yyin = fopen(argv[1], "r"); // abro el fichero

			if (yyin == 0)
			{
				fprintf(stderr, "\n\tEl archivo \" %s \""" no ha sido encontrado.\n\n", argv[1]);
				exit(1);
			}
		}
		else
		{
			fprintf(stderr, "La extension del archivo no es válida\n");
			exit(1);
		}

	}

	// Copy the name of the interpreter 
	progname = argv[0];

	/* Number of decimal places */ 
	std::cout.precision(7);

	/* 
	Table of symbols initialization 
	Must be written before the recovery sentence: setjmp
	*/
	init(table);

	/* Sets a viable state to continue after a runtime error */
	setjmp(begin);

	/* The name of the function to handle floating-point errors is set */
	signal(SIGFPE,fpecatch);

	// Parser function
	yyparse();

	PLACE(24,10);
	std::cout <<  BICYAN;
	std::cout <<  ">>>>>>> End of file <<<<<<<";
	std::cout << std::endl;
	std::cout << RESET;
	PLACE(25,1);

	/* End of program */
	return 0;
}



