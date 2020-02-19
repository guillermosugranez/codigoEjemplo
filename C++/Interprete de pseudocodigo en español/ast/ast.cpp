/*!	
	\file    ast.cpp
	\brief   Code of funcitons of AST clas
	\author  
	\date    2017-12-5
	\version 1.0
*/

#include <iostream>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <list>


// pow
#include <math.h>

#include "ast.hpp"

#include "../table/table.hpp"

// execerror
#include "../error/error.hpp"

// Macros for the screen
#include "../includes/macros.hpp"
#include "../includes/util.hpp"

#include "../table/variable.hpp"
#include "../table/numericConstant.hpp"

#include "../table/builtinParameter0.hpp"
#include "../table/builtinParameter1.hpp"
#include "../table/builtinParameter2.hpp"

//
#include "../parser/ipe.tab.h"

extern int modoFichero; // Sirve para diferenciar el modo interprete y el modo fichero



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

extern lp::Table table; //!< Reference to the Table of Symbols


extern lp::AST *root; //!< Reference to the object at the base of the AST

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

bool lp::ExpNode::isAlphanumeric() const
{
	return alphanumeric;
}

void lp::ExpNode::setAlphanumeric(const bool flag)
{
	alphanumeric = flag;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
 
void lp::NumberNode::print()
{
	std::cout << "NumberNode: " << this->_number << std::endl;
}

double lp::NumberNode::evaluate() 
{ 
		return this->_number; 
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
 
void lp::StringNode::print()
{
	std::cout << "StringNode: " << this->_string << std::endl;
}

std::string lp::StringNode::evaluate() 
{
	return this->_string; 
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::NumericVariableNode::print() 
{
	std::cout << "NumericVariableNode: " << this->_id << std::endl;
}

double lp::NumericVariableNode::evaluate() 
{
	// std::cout<<"Variable evaluate\n";

	// Get the identifier in the table of symbols as Variable
	lp::Variable *n = (lp::Variable *) table.getSymbol(this->_id);

	// Check if the type of the identifier is undefined
	if (n->getType() == UNDEFINED)
		execerror("Undefined variable", n->getName());

	// Return the value of the identifier
	return n->getNumber();
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::AlphanumericVariableNode::print() 
{
	std::cout << "AlphanumericVariableNode: " << this->_id << std::endl;
}

std::string lp::AlphanumericVariableNode::evaluate() 
{
	// std::cout<<"Variable evaluate\n";

	// Get the identifier in the table of symbols as Variable
	lp::Variable *n = (lp::Variable *) table.getSymbol(this->_id);

	// Check if the type of the identifier is undefined
	if (n->getType() == UNDEFINED)
		execerror("Undefined variable", n->getName());

	// Return the value of the identifier
	return n->getString();
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::NumericConstantNode::print() 
{
	std::cout << "NumericVariableNode: " << this->_id << std::endl;
}

double lp::NumericConstantNode::evaluate() 
{ 
	// Get the identifier in the table of symbols as NumericConstant
	lp::NumericConstant *n = (lp::NumericConstant *) table.getSymbol(this->_id);

	// Check if the type of the identifier is undefined
	if (n->getType() == UNDEFINED)
		execerror("Undefined variable", n->getName());

	// Return the value of the identifier
	return n->getValue();
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


void lp::UnaryMinusNode::print() 
{
	std::cout << "UnaryMinusNode: "  << std::endl;
	std::cout << "-";
	this->_exp->print();
}

double lp::UnaryMinusNode::evaluate()
{

	return - this->_exp->evaluate();
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::DecrementNode::print() 
{
	std::cout << "DecrementNode: "  << std::endl;
	std::cout << "--";
	this->_exp->print();
}

double lp::DecrementNode::evaluate()
{
	double aux = this->_exp->evaluate();
	aux--; 
	return aux;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::IncrementNode::print() 
{
	std::cout << "IncrementNode: "  << std::endl;
	std::cout << "++";
	this->_exp->print();
}

double lp::IncrementNode::evaluate()
{
	double aux = this->_exp->evaluate();
	aux++; 
	return aux;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


void lp::UnaryPlusNode::print() 
{
	std::cout << "UnaryPlusNode: "  << std::endl;
	this->_exp->print();
}

double lp::UnaryPlusNode::evaluate()
{
	return - this->_exp->evaluate();
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::PlusNode::print() 
{
	std::cout << "PlusNode: "  << std::endl;
	this->_numeric_left->print();
	std::cout << " + ";
	this->_numeric_right->print();
}

double lp::PlusNode::evaluate()
{
	return this->_numeric_left->evaluate() + this->_numeric_right->evaluate();
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::MinusNode::print() 
{
	std::cout << "MinusNode: "  << std::endl;
	this->_numeric_left->print();
	std::cout << " - ";
	this->_numeric_right->print();
}

double lp::MinusNode::evaluate() 
{
	return this->_numeric_left->evaluate() - this->_numeric_right->evaluate();
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


void lp::MultiplicationNode::print() 
{
	std::cout << "MultiplicationNode: "  << std::endl;
	this->_numeric_left->print();
	std::cout << " * ";
	this->_numeric_right->print();
}

double lp::MultiplicationNode::evaluate() 
{
	return this->_numeric_left->evaluate() * this->_numeric_right->evaluate();
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::DivisionNode::print()
{
	std::cout << "DivisionNode: " << std::endl;
	this->_numeric_left->print();
	std::cout << " / ";
	this->_numeric_right->print();
}

double lp::DivisionNode::evaluate() 
{
		double leftNumber, rightNumber;

		leftNumber = this->_numeric_left->evaluate();
		rightNumber = this->_numeric_right->evaluate();

		if(rightNumber == 0.0)
			{
		execerror("Runtime error", "Division by zero");
		}


		return leftNumber / rightNumber;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::IntDivisionNode::print()
{
	std::cout << "IntDivisionNode: " << std::endl;
	this->_numeric_left->print();
	std::cout << " _div ";
	this->_numeric_right->print();
}

double lp::IntDivisionNode::evaluate() 
{
		int a, b;

		a = this->_numeric_left->evaluate();
		b = this->_numeric_right->evaluate();

		if(a == 0.0)
		{
			execerror("Runtime error", "Division by zero");
		}
		
		int c = (int)a / b;

	return c;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::ModuloNode::print()
{
	std::cout << "ModuloNode: " << std::endl;
	this->_numeric_left->print();
	std::cout << " _mod ";
	this->_numeric_right->print();
}

double lp::ModuloNode::evaluate() 
{
		double leftNumber, rightNumber;

		leftNumber = this->_numeric_left->evaluate();
		rightNumber = this->_numeric_right->evaluate();

		if(rightNumber == 0.0)
			{
		execerror("Runtime error", "Division by zero");
		}

		return (int) leftNumber % (int) rightNumber;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::PowerNode::print() 
{
	std::cout << "PowerNode: "  << std::endl;
	this->_numeric_left->print();
	std::cout << " ** ";
	this->_numeric_right->print();
}

double lp::PowerNode::evaluate() 
{
	return pow(this->_numeric_left->evaluate(), this->_numeric_right->evaluate());
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::ConcatenationNode::print() 
{
	std::cout << "ConcatenationNode: "  << std::endl;
	this->_alphanumeric_left->print();
	std::cout << " + ";
	this->_alphanumeric_right->print();
}

std::string lp::ConcatenationNode::evaluate()
{
	return this->_alphanumeric_left->evaluate() + this->_alphanumeric_right->evaluate();
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::BuiltinFunctionNode::print() 
{
	std::cout << "BuiltinFunctionNode: "  << std::endl;
	std::cout << this->_id;
	std::cout << " ( " ;  
	this->_exp->print();
	std::cout << " ) " ;
}

double lp::BuiltinFunctionNode::evaluate() 
{
	// Get the identifier in the table of symbols as BuiltinParameter1
	lp::BuiltinParameter1 *f = (lp::BuiltinParameter1 *) table.getSymbol( this->_id);


	// Apply the function to the parameter and copy the result
	return f->getFunction()(this->_exp->evaluate());
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::BuiltinFunctionNode_0::print() 
{
	std::cout << "BuiltinFunctionNode_0: "  << std::endl;
	std::cout << this->_id;
	std::cout << " ( ) " ;
}

double lp::BuiltinFunctionNode_0::evaluate() 
{
	// Get the identifier in the table of symbols as BuiltinParameter0
	lp::BuiltinParameter0 *f = (lp::BuiltinParameter0 *) table.getSymbol(this->_id);

	// Apply the function and copy the result
		return f->getFunction()();
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::BuiltinFunctionNode_2::print() 
{
	std::cout << "BuiltinFunctionNode_2: "  << std::endl;
	std::cout << this->_id;
	std::cout << " ( " ;  
	this->_exp1->print();
	std::cout << " , " ;
	this->_exp2->print();
	std::cout << " ) " ;
}

double lp::BuiltinFunctionNode_2::evaluate() 
{
	// Get the identifier in the table of symbols as BuiltinParameter2
	lp::BuiltinParameter2 *f = (lp::BuiltinParameter2 *) table.getSymbol(this->_id);

	// Apply the function to the parameters and copy the result
		return f->getFunction()(this->_exp1->evaluate(),this->_exp2->evaluate());
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::LessThanNode::print()
{
	std::cout << "LessThanNode: " << std::endl;

	if(this->isAlphanumeric())
		this->_alphanumeric_left->print();
	else
		this->_numeric_left->print();
	
	std::cout << " < ";

	if(this->isAlphanumeric())
		this->_alphanumeric_right->print();
	else
		this->_numeric_right->print();
}

bool lp::LessThanNode::evaluate() 
{
	if(_numeric_right == NULL && _numeric_left == NULL)
	{
		return ( (this->_alphanumeric_left->evaluate()) < (this->_alphanumeric_right->evaluate()) ) ? 1 : 0;
	}
	else
		return ( (this->_numeric_left->evaluate()) < (this->_numeric_right->evaluate()) ) ? 1 : 0;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::GreaterThanNode::print()
{
	std::cout << "GreaterThanNode: " << std::endl;

	if(this->isAlphanumeric())
		this->_alphanumeric_left->print();
	else
		this->_numeric_left->print();
	
	std::cout << " < ";

	if(this->isAlphanumeric())
		this->_alphanumeric_right->print();
	else
		this->_numeric_right->print();
}

bool lp::GreaterThanNode::evaluate() 
{
	if(_numeric_right == NULL && _numeric_left == NULL)
		return ( (this->_alphanumeric_left->evaluate()) > (this->_alphanumeric_right->evaluate()) ) ? 1 : 0;
	else
		return ( (this->_numeric_left->evaluate()) > (this->_numeric_right->evaluate()) ) ? 1 : 0;
}




///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::GreaterOrEqualNode::print()
{
	std::cout << "GreaterOrEqualNode: " << std::endl;

	if(this->isAlphanumeric())
		this->_alphanumeric_left->print();
	else
		this->_numeric_left->print();
	
	std::cout << " < ";

	if(this->isAlphanumeric())
		this->_alphanumeric_right->print();
	else
		this->_numeric_right->print();
}

bool lp::GreaterOrEqualNode::evaluate() 
{
	if(_numeric_right == NULL && _numeric_left == NULL)
		return ( (this->_alphanumeric_left->evaluate()) >= (this->_alphanumeric_right->evaluate()) ) ? 1 : 0;
	else
		return ( (this->_numeric_left->evaluate()) >= (this->_numeric_right->evaluate()) ) ? 1 : 0;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::LessOrEqualNode::print()
{
	std::cout << "LessOrEqualNode: " << std::endl;

	if(this->isAlphanumeric())
		this->_alphanumeric_left->print();
	else
		this->_numeric_left->print();
	
	std::cout << " < ";

	if(this->isAlphanumeric())
		this->_alphanumeric_right->print();
	else
		this->_numeric_right->print();
}

bool lp::LessOrEqualNode::evaluate() 
{
	if(_numeric_right == NULL && _numeric_left == NULL)
		return ( (this->_alphanumeric_left->evaluate()) <= (this->_alphanumeric_right->evaluate()) ) ? 1 : 0;
	else
		return ( (this->_numeric_left->evaluate()) <= (this->_numeric_right->evaluate()) ) ? 1 : 0;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::EqualNode::print()
{
	std::cout << "EqualNode: " << std::endl;

	if(this->isAlphanumeric())
		this->_alphanumeric_left->print();
	else
		this->_numeric_left->print();
	
	std::cout << " < ";

	if(this->isAlphanumeric())
		this->_alphanumeric_right->print();
	else
		this->_numeric_right->print();
}

bool lp::EqualNode::evaluate() 
{
	if(_numeric_right == NULL && _numeric_left == NULL)
		return ( (this->_alphanumeric_left->evaluate()) == (this->_alphanumeric_right->evaluate()) ) ? 1 : 0;
	else
		return ( (this->_numeric_left->evaluate()) == (this->_numeric_right->evaluate()) ) ? 1 : 0;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::NotEqualNode::print()
{
	std::cout << "NotEqualNode: " << std::endl;

	if(this->isAlphanumeric())
		this->_alphanumeric_left->print();
	else
		this->_numeric_left->print();
	
	std::cout << " < ";

	if(this->isAlphanumeric())
		this->_alphanumeric_right->print();
	else
		this->_numeric_right->print();
}

bool lp::NotEqualNode::evaluate() 
{
	if(_numeric_right == NULL && _numeric_left == NULL)
		return ( (this->_alphanumeric_left->evaluate()) != (this->_alphanumeric_right->evaluate()) ) ? 1 : 0;
	else
		return ( (this->_numeric_left->evaluate()) != (this->_numeric_right->evaluate()) ) ? 1 : 0;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::AndNode::print()
{
  std::cout << "AndNode: " << std::endl;
  this->_numeric_left->print();
  std::cout << " _y ";
  this->_numeric_right->print();
}

bool lp::AndNode::evaluate() 
{
    bool leftNumber, rightNumber;

    leftNumber = this->_numeric_left->evaluate();
    rightNumber = this->_numeric_right->evaluate();

  return (leftNumber && rightNumber)? 1 : 0;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::OrNode::print()
{
  std::cout << "OrNode: " << std::endl;
  this->_numeric_left->print();
  std::cout << " _o ";
  this->_numeric_right->print();
}

bool lp::OrNode::evaluate() 
{
    bool leftNumber, rightNumber;

    leftNumber = this->_numeric_left->evaluate();
    rightNumber = this->_numeric_right->evaluate();

  return (leftNumber || rightNumber)? 1 : 0;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::NotNode::print()
{
	std::cout << "NotNode: " << std::endl;
	std::cout << " _no ";
	this->_numeric_right->print();
}

bool lp::NotNode::evaluate() 
{
	return ! this->_numeric_right->evaluate();
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::AssignmentStmt::print() 
{
	if(_numeric_exp)
	{
		std::cout << "assignment_node: "  << std::endl;
		std::cout << this->_id << " = ";
		this->_numeric_exp->print();
		std::cout << std::endl;
	}
	else
	{
		this->_alphanumeric_exp->print();
		std::cout << std::endl;
	}
}

void lp::AssignmentStmt::evaluate() 
{
	double value;
	std::string str;

	if(_numeric_exp)
	{
		// evaluate the expression
		value = this->_numeric_exp->evaluate();

		// Get the identifier in the table of symbols as Variable
		lp::Variable *n = (lp::Variable *) table.getSymbol(this->_id);

		// Assignment the read value to the identifier in the table of symbols
		n->setValue(value);

		// Change the type of the identifier if it was undefined
		if (n->getType() == UNDEFINED)
				 n->setType(NUMERICVARIABLE);

		// Copy the value of the expression to allow multiple assignment: a = b = c = 2;
		// return value;
	}
	else if (_alphanumeric_exp)
	{
		// evaluate the expression
		std::string str = this->_alphanumeric_exp->evaluate();

		// Get the identifier in the table of symbols as Variable
		lp::Variable *s = (lp::Variable *) table.getSymbol(this->_id);

		// Assignment the read value to the identifier in the table of symbols
		s->setValue(str);

		// Change the type of the identifier if it was undefined
		if (s->getType() == UNDEFINED)
				 s->setType(ALPHANUMERICVARIABLE);

		// Copy the value of the expression to allow multiple assignment: a = b = c = 2;
		// return value;
	}

	else // asignacion múltiple
	{
		// evaluate the assigment child
		this->_asgn->evaluate();


		if (this->_asgn->_numeric_exp != NULL)
		{
			// evaluate the expression of the assigment child
		 	value = this->_asgn->_numeric_exp->evaluate();
		 	str = "";
		}
		else if (this->_asgn->_alphanumeric_exp != NULL)
		{
			// evaluate the expression of the assigment child
		 	str = this->_asgn->_alphanumeric_exp->evaluate();
		 	value = 0;
		}
		else
		// take the value of the identifier of the expression of the assigment child
		{
			lp::Variable *aux = (lp::Variable *) table.getSymbol(this->_asgn->_id);

			if(aux->getType() == NUMERICVARIABLE)
			{
				value = aux->getNumber();
				str = "";
			}
			else if(aux->getType() == ALPHANUMERICVARIABLE)
			{
				str = aux->getString();
				value = 0;
			}
		}

	  	// Get the identifier in the table of symbols as NumericVariable
		lp::Variable *n = (lp::Variable *) table.getSymbol(this->_id);

		if(value)
		{
			// Assignment the read value to the identifier in the table of symbols
			n->setValue(value);

			// Change the type of the identifier if it was undefined
			if (n->getType() == UNDEFINED)
					 n->setType(NUMERICVARIABLE);
		}
		else
		{
			// Assignment the read value to the identifier in the table of symbols
			n->setValue(str);

			// Change the type of the identifier if it was undefined
			if (n->getType() == UNDEFINED)
					 n->setType(ALPHANUMERICVARIABLE);
		}

	}
	
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::PlusAssignmentStmt::print() 
{
	std::cout << "PlusAssignment_node: "  << std::endl;
	std::cout << this->_id << " :+= ";
	this->_numeric_exp->print();
	std::cout << std::endl;
}

void lp::PlusAssignmentStmt::evaluate() 
{
	double value;

	// evaluate the expression
	value = this->_numeric_exp->evaluate();

	// Get the identifier in the table of symbols as Variable
	lp::Variable *n = (lp::Variable *) table.getSymbol(this->_id);

	value += n->getNumber();

	// PlusAssignment the read value to the identifier in the table of symbols
	n->setValue(value);

	// Change the type of the identifier if it was undefined
	if (n->getType() == UNDEFINED)
			 n->setType(NUMERICVARIABLE);
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::MinusAssignmentStmt::print() 
{
	std::cout << "MinusAssignment_node: "  << std::endl;
	std::cout << this->_id << " :-= ";
	this->_numeric_exp->print();
	std::cout << std::endl;
}

void lp::MinusAssignmentStmt::evaluate() 
{
	double value;

	// evaluate the expression
	value = this->_numeric_exp->evaluate();

	// Get the identifier in the table of symbols as Variable
	lp::Variable *n = (lp::Variable *) table.getSymbol(this->_id);

	value = n->getNumber() - value;

	// MinusAssignment the read value to the identifier in the table of symbols
	n->setValue(value);

	// Change the type of the identifier if it was undefined
	if (n->getType() == UNDEFINED)
			 n->setType(NUMERICVARIABLE);
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::MultAssignmentStmt::print() 
{
	std::cout << "MultAssignment_node: "  << std::endl;
	std::cout << this->_id << " :*= ";
	this->_numeric_exp->print();
	std::cout << std::endl;
}

void lp::MultAssignmentStmt::evaluate() 
{
	double value;

	// evaluate the expression
	value = this->_numeric_exp->evaluate();

	// Get the identifier in the table of symbols as Variable
	lp::Variable *n = (lp::Variable *) table.getSymbol(this->_id);

	value *= n->getNumber();

	// MultAssignment the read value to the identifier in the table of symbols
	n->setValue(value);

	// Change the type of the identifier if it was undefined
	if (n->getType() == UNDEFINED)
			 n->setType(NUMERICVARIABLE);
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::DiviAssignmentStmt::print() 
{
	std::cout << "DiviAssignment_node: "  << std::endl;
	std::cout << this->_id << " :/= ";
	this->_numeric_exp->print();
	std::cout << std::endl;
}

void lp::DiviAssignmentStmt::evaluate() 
{
	double value;

	// evaluate the expression
	value = this->_numeric_exp->evaluate();

	// Get the identifier in the table of symbols as Variable
	lp::Variable *n = (lp::Variable *) table.getSymbol(this->_id);

	value = n->getNumber() / value;

	// DiviAssignment the read value to the identifier in the table of symbols
	n->setValue(value);

	// Change the type of the identifier if it was undefined
	if (n->getType() == UNDEFINED)
			 n->setType(NUMERICVARIABLE);
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::PrintStmt::print() 
{
	if(_numeric_exp)
	{
		std::cout << "PrintStmt: "  << std::endl;
		std::cout << " print ";
		this->_numeric_exp->print();
		std::cout << std::endl;
	}
	else
	{
		this->_alphanumeric_exp->print();
	}
}


void lp::PrintStmt::evaluate() 
{
	if(_numeric_exp)
	{
		double aux = this->_numeric_exp->evaluate();		
		
		if(aux > 0)
			std::cout << BPURPLE;
		else
			std::cout << BRED;

		std::cout<<aux;
		std::cout << RESET; 

		/*
		if(!modoFichero)
			std::cout<<std::endl;
		*/
	}
	else
	{
		std::cout << BIYELLOW;

		std::string str = this->_alphanumeric_exp->evaluate();

		int tamCadena = str.length();
		char cadena[tamCadena+1];
		strcpy(cadena,str.c_str());

		for(unsigned int i = 0; i < strlen(cadena); i++)
		{
			if(cadena[i] != '\\')
				std::cout<<cadena[i];
			else if(i < strlen(cadena))
			{
				if(cadena[i]=='\\' && cadena[i+1]=='n')
				{
					std::cout<<"\n";
					i++;
				}
				if(cadena[i]=='\\' && cadena[i+1]=='t')
				{
					std::cout<<"\t";
					i++;
				}
			}
		}

		std::cout << RESET;
	}
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::ReadStmt::print() 
{
	std::cout << "ReadStmt: "  << std::endl;
	std::cout << " read (" << this->_id << ")";
	std::cout << std::endl;
}


void lp::ReadStmt::evaluate() 
{
	double value = 0;
	std::string str = "";

	// Get the identifier in the table of symbols as Variable
	lp::Variable *n = (lp::Variable *) table.getSymbol(this->_id);


	if(_type == NUMERICVARIABLE)
	{
		/*
		std::cout << BIYELLOW; 
		std::cout << "Insert a numeric value --> " ;
		std::cout << RESET;
		*/

		// Assignment the read value to the identifier in the table of symbols
		std::cin >> value;
		n->setValue(value);
	}
	else if(_type == ALPHANUMERICVARIABLE)
	{
		/*
		std::cout << BIYELLOW; 
		std::cout << "Insert a alphanumeric value --> " ;
		std::cout << RESET;
		*/

		// Assignment the read string to the identifier in the table of symbols
		std::cin >> str;

		n->setValue(str);
	}

	n->setType(_type);

	//std::cout<<std::endl;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// NEW in IPE

void lp::CleanStmt::print() 
{
	std::cout << "CleanStmt: "  << std::endl;
	std::cout << std::endl;
}


void lp::CleanStmt::evaluate() 
{
	std::cout << CLEAR_SCREEN;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// NEW in IPE

void lp::PlaceStmt::print() 
{
	std::cout << "PlaceStmt: "  << std::endl;
	// Condition
	this->_x->print();

	// Body of the while loop
	this->_y->print();

	std::cout << std::endl;
}


void lp::PlaceStmt::evaluate() 
{
	int x = (int)this->_x->evaluate();
	int y = (int)this->_y->evaluate();

	PLACE(x, y);
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// NEW in example 17

void lp::IfStmt::print() 
{
	std::cout << "IfStmt: "  << std::endl;
	
	// Condition
	this->_cond->print();

	std::list<Statement *>::iterator stmtIter;

	for (stmtIter = this->_stmts1->begin(); stmtIter != this->_stmts1->end(); stmtIter++) 
	{
		 (*stmtIter)->print();
	}

	// The alternative is printed if exists
	if (this->_stmts2 != NULL)
	{
		for (stmtIter = this->_stmts2->begin(); stmtIter != this->_stmts2->end(); stmtIter++) 
		{
			(*stmtIter)->print();
		}
	}

	std::cout << std::endl;
}


void lp::IfStmt::evaluate() 
{
	std::list<Statement *>::iterator stmtIter;

	if (this->_cond->evaluate() != 0)
	{
		// If the condition is not zero, the consequent is run
		for (stmtIter = this->_stmts1->begin(); stmtIter != this->_stmts1->end(); stmtIter++) 
		{
			(*stmtIter)->evaluate();
		}
	}
	else if (this->_stmts2 != NULL)
	{
		// Otherwise, the alternative is run if exists
		for (stmtIter = this->_stmts2->begin(); stmtIter != this->_stmts2->end(); stmtIter++) 
		{
			(*stmtIter)->evaluate();
		}
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// NEW in example 17

void lp::WhileStmt::print() 
{
	std::cout << "WhileStmt: "  << std::endl;
	// Condition
	this->_cond->print();

	std::list<Statement *>::iterator stmtIter;

	for (stmtIter = this->_stmts->begin(); stmtIter != this->_stmts->end(); stmtIter++) 
	{
		 (*stmtIter)->print();
	}

	std::cout << std::endl;
}


void lp::WhileStmt::evaluate() 
{
	std::list<Statement *>::iterator stmtIter;

	// While the condition is not zero, the body is run 
	while (this->_cond->evaluate() != 0)
	{ 
		// If the condition is not zero, the consequent is run
		
		for (stmtIter = this->_stmts->begin(); stmtIter != this->_stmts->end(); stmtIter++) 
		{
			(*stmtIter)->evaluate();
		}
	}

}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// New IPE

void lp::RepeatStmt::print() 
{
	std::cout << "RepeatStmt: "  << std::endl;
	// Condition
	this->_cond->print();

	// Body of the repeat loop
	std::list<Statement *>::iterator stmtIter;

	for (stmtIter = this->_stmts->begin(); stmtIter != this->_stmts->end(); stmtIter++) 
	{
		 (*stmtIter)->print();
	}

	std::cout << std::endl;
}


void lp::RepeatStmt::evaluate() 
{
	std::list<Statement *>::iterator stmtIter;

	// Repeat the condition is not zero, the body is run 
	do
	{
		for (stmtIter = this->_stmts->begin(); stmtIter != this->_stmts->end(); stmtIter++) 
		{
			(*stmtIter)->evaluate();
		}
		
	} while (this->_cond->evaluate() == 0); 

}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// New IPE

void lp::ForStmt::print() 
{
	std::cout << "ForStmt: "  << std::endl;

	// identificador
	std::cout << this->_id << " id ";

	// desde
	this->_exp1->print();

	// hasta
	this->_exp2->print();

	// paso
	this->_exp3->print();

	// Body of the for loop

	std::list<Statement *>::iterator stmtIter;

	for (stmtIter = this->_stmts->begin(); stmtIter != this->_stmts->end(); stmtIter++) 
	{
		 (*stmtIter)->print();
	}

	std::cout << std::endl;

	std::cout << std::endl;
}


void lp::ForStmt::evaluate() 
{
	// evaluate the expression
	double desde = this->_exp1->evaluate();

	// Get the identifier in the table of symbols as Variable
	lp::Variable *n = (lp::Variable *) table.getSymbol(this->_id);

	n->setType(NUMERICVARIABLE);
		
	// Assignment the read value to the identifier in the table of symbols
	n->setValue(desde);

	double hasta = this->_exp2->evaluate();
	double paso = 1; // Valor por defecto

	if(_exp3)
		paso = this->_exp3->evaluate();

	/*
	std::cout<< "Desde " <<desde <<std::endl;
	std::cout<< "Hasta " << hasta <<std::endl;
	std::cout<< "Paso " << paso <<std::endl;
	*/

	if(paso > 0 && desde > hasta)
		execerror("Bucle infinito", "Desde mayor que hasta con paso positivo");

	if(paso < 0 && hasta > desde)
		execerror("Bucle infinito", "Hasta mayor que desde con paso negativo");

	if(paso == 0)
		execerror("Bucle infinito", "Paso nulo");

	for(double i = desde; i <= hasta; i = i + paso)
	{
		n->setValue(i);

		std::list<Statement *>::iterator stmtIter;
		
		for (stmtIter = this->_stmts->begin(); stmtIter != this->_stmts->end(); stmtIter++) 
		{
			(*stmtIter)->evaluate();
		}
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// NEW in example 17

void lp::SwitchStmt::print() 
{
	std::list<Statement *>::iterator stmtIter;

	std::cout << "SwitchStmt: "  << std::endl;

	for (stmtIter = this->_stmts->begin(); stmtIter != this->_stmts->end(); stmtIter++) 
	{
		 (*stmtIter)->print();
	}
}


void lp::SwitchStmt::evaluate() 
{
	std::list<Statement *>::iterator stmtIter;

	for (stmtIter = this->_stmts->begin(); stmtIter != this->_stmts->end(); stmtIter++) 
	{
		(*stmtIter)->evaluate();
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// NEW in example 17

void lp::BlockStmt::print() 
{
	std::list<Statement *>::iterator stmtIter;

	std::cout << "BlockStmt: "  << std::endl;

	for (stmtIter = this->_stmts->begin(); stmtIter != this->_stmts->end(); stmtIter++) 
	{
		 (*stmtIter)->print();
	}
}


void lp::BlockStmt::evaluate() 
{
	std::list<Statement *>::iterator stmtIter;

	for (stmtIter = this->_stmts->begin(); stmtIter != this->_stmts->end(); stmtIter++) 
	{
		(*stmtIter)->evaluate();
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::EmptyStmt::print() 
{
	std::cout << "EmptyStmt "  << std::endl;
}

void lp::EmptyStmt::evaluate() 
{
	// Empty
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::AST::print() 
{
	std::list<Statement *>::iterator stmtIter;

	for (stmtIter = stmts->begin(); stmtIter != stmts->end(); stmtIter++) 
	{
		 (*stmtIter)->print();
	}
}



void lp::AST::evaluate() 
{
	std::list<Statement *>::iterator stmtIter;

	for (stmtIter = stmts->begin(); stmtIter != stmts->end(); stmtIter++) 
	{
		(*stmtIter)->evaluate();
	}
}







