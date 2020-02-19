/*! 
  \file ipe.l
  \brief Lexical or scanner file
*/
%{
#include <iostream>

/*********************/
/* NEW in example 4 */
/* atof */
#include <stdlib.h>
/*********************/

/* Macros for the screen */
#include "../includes/macros.hpp"
#include "../includes/util.hpp"

/*********************/
/* 
  NEW in example 16 
  AST class
  IMPORTANT: must be written before interpreter.tab.h
*/
#include "../ast/ast.hpp"
/*********************/

/*  interpreter.tab.h contains the numeric values of the tokens produced by the parser */
#include "ipe.tab.h"

/********************/
/* NEW in example 3 */
#include "../error/error.hpp"
/********************/


/*********************************************/
/* NEW in example 7 */
/* Table of symbols */
#include "../table/table.hpp"

#include "../table/variable.hpp"

extern lp::Table table; //!< External Table of Symbols
/*********************************************/

extern int lineNumber; //!< External line counter

/* Indica el número de comentario */
int numero_cadenas = 0;

/* Indica el número de líneas de cada comentario */
int lineas_cadenas;

/* Indica el número de comentario */
int comentario = 0;

/* Indica el número de líneas de cada comentario */
int lineas_comentario;

#include <ctype.h>

%}


/*! \name REGULAR DEFINITIONS  */

DIGIT  [0-9] 

LETTER [a-zA-Z]

NUMBER	{DIGIT}+(\.{DIGIT}+)?(E[+\-]?{DIGIT}+)?

IDENTIFIER	{LETTER}(_?({LETTER}|{DIGIT})+)*

WRONG_INDENTIFIER	_?{LETTER}+(_|__+.*)*

/* NEW in example 3 */
/* STATE  */
%x ERROR

/* Se define un nuevo estado: ESTADO_CADENA */
%x ESTADO_CADENA

/* Se define un nuevo estado: ESTADO_COMENTARIO */
%x ESTADO_COMENTARIO

/*! \name REGULAR EXPRESSIONS  */
%%



"'"	{
	
	/* Se activa el reconocimiento de la cadena */
	BEGIN ESTADO_CADENA; // Empieza el estado Cadena (solo se aplican las reglas correspondientes)
	numero_cadenas++; 
	lineas_cadenas=1;

}


<ESTADO_CADENA>"'"	{ /* Fin de la cadena: se vuelve al estado por defecto */
	
	BEGIN 0; // Vuelta al estado incial

	//fprintf(yyout, "\n nº cadena = %d, lineas_cadenas = %d\n",numero_cadenas, lineas_cadenas);
	yytext[yyleng-1]='\0'; // Quito las comillas
	//fprintf(yyout, "\t Cadena reconocida = %s\n",yytext);

	yylval.name =  strdup(yytext);

	return STRING;
}

<ESTADO_CADENA>"\\\'"	{

	yymore();
}

<ESTADO_CADENA>.	{
	yymore();
}

<ESTADO_CADENA>\n	{

	lineas_cadenas++; yymore();
}




"#"	{
			    
	/* Se activa el reconocimiento de un comentario */
	BEGIN ESTADO_COMENTARIO; 
	comentario++; 
	lineas_comentario=1;
}

<ESTADO_COMENTARIO>"#"	{ /* Fin del comentario: se vuelve al estado por defecto */
	
	BEGIN 0; // Estado por defecto
	//fprintf(yyout, "\n nº comentario = %d, lineas_comentario = %d\n",comentario, lineas_comentario);
}      

<ESTADO_COMENTARIO>.	{

	;
}

<ESTADO_COMENTARIO>\n	{

	lineas_comentario++;
}

"@"(.*|\n)	{

	comentario++;
	lineas_comentario=1;
	//fprintf(yyout, "\n nº comentario = %d, lineas_comentario = %d\n",comentario, lineas_comentario);
}



[ \t] 	{ ; }    /* skip white space and tabular */

\n      { 
			/* Line counter */
			lineNumber++; 
	
			/* MODIFIED in example 3 */
			/* COMMENTED in example 5 */
			/* return NEWLINE; */
		}

";"		{
			/* NEW in example 5 */
			return SEMICOLON;
		}


","		{
			/* NEW in example 14 */
			return COMMA;
		}

{NUMBER}  {

	/* MODIFIED in example 4 */
	/* Conversion of type and sending of the numerical value to the parser */
	yylval.number = atof(yytext); 

	return NUMBER;
}

{IDENTIFIER} {
	
	for(int i=0; i<yyleng; i++) // No distingue entre minúsculas y mayúsculas.
		yytext[i]=tolower(yytext[i]); // Lo convierto todo a minúsculas.

	/* NEW in example 7 */
	std::string name(yytext); // Sirve para buscar en la tabla de simbolos

	/* 
	  strdup() function returns a pointer to a new string which  is a duplicate of the string yytext
	  Sirve para copiar (con memoria dinámica) yytext
	  yylval es lo que le pasamos a ipe.y
	*/
	yylval.name = strdup(yytext); 

	/* If the name is not in the table of symbols then it is inserted */	
	if (table.lookupSymbol(name) == false)
	{
		/*
			The name is inserted into the symbol table as undefined Variable
		*/
		lp::Variable *n = new lp::Variable(name,VARIABLE,UNDEFINED);

		/* A pointer to the new NumericVariable is inserted into the table of symbols */
		table.installSymbol(n);

		return VARIABLE;
	}

	/* MODIFIED in example 11 */
	/* 
		If the name is in the table of symbols then its token is returned 
			The name can be a variable or a numeric constant
	*/
	else 
	{
		lp::Symbol	*s = table.getSymbol(name);

		

		/*
		std::cout << "lex: "<< s->getName() 
				  << "token " << s->getToken()
				  << std::endl; 
		*/

		/*  If the name is in the table then its token is returned  */
		if(s->getToken() == VARIABLE)
		{
			lp::Variable *var = (lp::Variable *) s; // El símbolo ahora es una variable
			
			if(var->getType() == UNDEFINED) // Lo requiere el for
				return NUMERICVARIABLE;
			else
				return var->getType();
		}
		else
			return s->getToken();
	}
}

{WRONG_INDENTIFIER}	{

	for(int i=0; i<yyleng; i++) // No distingue entre minúsculas y mayúsculas.
		yytext[i]=tolower(yytext[i]); // Lo convierto todo a minúsculas.

	std::string palabraReservada(yytext);

	if (table.lookupSymbol(palabraReservada)) // Si encuentra
	{
		lp::Symbol	*s = table.getSymbol(palabraReservada);
		return s->getToken();
	}
	else
	{
		warning("Syntax error. Invalid name", yytext);
		yymore();
	}
}


"{"		{ return LETFCURLYBRACKET; } 	/* NEW in example 17 */

"}"		{ return RIGHTCURLYBRACKET; }	/* NEW in example 17 */

"-"		{ return MINUS;  } 			/* NEW in example 3 */
"+"		{ return PLUS;   } 			/* NEW in example 3 */

"*"	    { return MULTIPLICATION; } 	/* NEW in example 3 */
"/"     { return DIVISION; } 		/* NEW in example 3 */

"("     { return LPAREN; } 			/* NEW in example 3 */
")"	    { return RPAREN; } 			/* NEW in example 3 */

"**"	{ return POWER; }			/* NEW in example 5 */

":=" 	{ return ASSIGNMENT; }		/* NEW in example 7 */
":+=" 	{ return PLUSASSIGNMENT; }		/* NEW in example 7 */
":-=" 	{ return MINUSASSIGNMENT; }		/* NEW in example 7 */
":/=" 	{ return DIVIASSIGNMENT; }		/* NEW in example 7 */
":*=" 	{ return MULTASSIGNMENT; }		/* NEW in example 7 */

"="		{ return EQUAL; }			/* NEW in example 15 */

"<>"	{ return NOT_EQUAL; }		/* NEW in example 15 */

">="	{ return GREATER_OR_EQUAL; }/* NEW in example 15 */

"<="	{ return LESS_OR_EQUAL; }	/* NEW in example 15 */

">"		{ return GREATER_THAN; }	/* NEW in example 15 */

"<"		{ return LESS_THAN; }		/* NEW in example 15 */

"++"	{ return INCREMENT; }	/* NEW in IPE */

"--"	{ return DECREMENT; }	/* NEW in IPE */

"||"	{ return CONCATENATION; }	/* NEW in IPE */



^ç { /* The interpreter finishes when the symbol # is written at the beginning of the line */
	// std::cout << CLEAR_SCREEN; 
//	  PLACE(24,10);
	  std::cout <<  BIYELLOW;
	  std::cout <<  ">>>>>>> End of program <<<<<<<";
	  std::cout << std::endl;
	  std::cout << RESET;
//	  PLACE(25,1);

	  return 0;
	}

<<EOF>> { /* The interpreter finishes when finds the end of file character */
		  

		  return 0;
	}


.								{ 	
									/* Any other character */
									/* MODIFIIED in example 3 */
									/* Change to error state */
									BEGIN(ERROR); 

									/* 
										- The current value of yytext will be concatenated with the next character

										- Creo que esta funcion permite continuar con el análisis
										- No se vacia YYTEXT, se concatena con el siguiente entrada
									*/
									yymore();  
								}

<ERROR>[^0-9+\-*/()\^% \t\n\;a-zA-Z=<>!&]	{ /* MODIFIED in examples 5, 7, 15 */
								  /* NEW in example 3 */
								  /* 
									The current value of yytext 
									will be concatenated with the next character
								  */
									yymore(); 
								}

<ERROR>(.|\n)                { 
								/* NEW in example 3 */
								/* Rewind one position */
								yyless(yyleng-1); 

								/* Display the error message */
								warning("Lexical error", yytext);

								/* Restore the initial state */
								BEGIN(INITIAL);
							}
%%

