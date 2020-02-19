/*!	
	\file   init.hpp
	\brief   Prototype of the function for the initialization of table of symbols
	\author  
	\date    2017-12-5
	\version 1.0
*/

#ifndef _INIT_HPP_
#define _INIT_HPP_

// sin, cos, atan, fabs, ...
#include <math.h>

#include "table.hpp"

///////////////////////////////////////
// NEW in example 16
// IMPORTANT: This file must be before y.tab.h
#include "../ast/ast.hpp"
///////////////////////////////////////

//  interpreter.tab.h contains the number values of the tokens produced by the parser
#include "../parser/ipe.tab.h"

///////////////////////////////////////
// NEW in example 13
#include "mathFunction.hpp"
#include "builtinParameter1.hpp"
///////////////////////////////////////

///////////////////////////////////////
// NEW in example 14
#include "builtinParameter0.hpp"
#include "builtinParameter2.hpp"
///////////////////////////////////////





/*!
  \ brief Predefined numeric constants
*/
static struct {
          std::string name ;
	      double value;
	      } constants[] = {
	                    "pi",    3.14159265358979323846,
	                    "e",     2.71828182845904523536,
	                    "gamma", 0.57721566490153286060,
	                    "deg",  57.29577951308232087680,
	                    "phi",   1.61803398874989484820,
	                    "",      0
	                   };


// NEW in example 12 
/*!
  \ brief Predefined keywords
*/
static struct {
          std::string name ;
	      int token;
	      } keywords[] = {
	                    "escribir",	PRINT,
	                    "leer",	READ,
						"si",	IF,   		// NEW in example 17
						"si_no",	ELSE, 		// NEW in example 17
						"mientras",	WHILE,	// NEW in example 17
						"_mod",	MODULO,
						"_y",	AND,
						"_no",	NOT,
						"_o",	OR,
						"_div",	INTDIVISION,
						"entonces", THEN,
						"fin_si",	ENDIF,
						"hacer",	DO,
						"fin_mientras",	ENDWHILE,
						"repetir",	REPEAT,
						"hasta",	UNTIL,
						"para",	FOR,
						"fin_para",	ENDFOR,
						"desde",	FROM,
						"paso",	STEP,
						"_borrar",	CLEAN,
						"_lugar",	PLACE,
						"escribir_cadena",	STRINGPRINT,
						"leer_cadena",	STRINGREAD,
						"segun",	SWITCH,
						"fin_segun",	ENDSWITCH,
	                    "",      0
	                   };


// NEW in example 13

static struct {    /* Predefined functions names */ 
                std::string name ;
				lp::TypePointerDoubleFunction_1 function;
              } functions [] = {
	                   "sin",     sin,
		               "cos",     cos,
		               "atan",    atan,
		               "log",     Log,
		               "log10",   Log10,
		               "exp",     Exp,
		               "sqrt",    Sqrt,
		               "integer", integer,
		               "abs",     fabs,   
		                "",       0
		              };

// NEW in example 14
static struct {   
                std::string name ;
				lp::TypePointerDoubleFunction_0 function;
              } functions_0 [] = {
						"azar", azar,
		                "",       0
		              };


// NEW in example 14

static struct {    /* Nombres predefinidos de funciones con 2 argumentos */ 
                std::string name ;
				lp::TypePointerDoubleFunction_2 function;
              } functions_2 [] = {
	                   "atan2",   Atan2,
		                "",       0
		              };



/*!		
	\brief   Initialize the table of symbols
	\return  void 
*/

void init(lp::Table &t);

// End of _INIT_HPP_
#endif
