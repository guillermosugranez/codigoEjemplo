/*!	
	\file    ast.hpp
	\brief   Declaration of AST class
	\author  
	\date    2017-12-12
	\version 1.0
*/

#ifndef _AST_HPP_
#define _AST_HPP_

#include <iostream>
#include <stdlib.h>
#include <string>
#include <list>

#include "../includes/util.hpp"

namespace lp
{
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   ExpNode
  \brief   Definition of atributes and methods of ExpNode class
  \warning Abstract class
*/
class ExpNode 
{
	private:
		bool alphanumeric; //!< \brief Indicate if it is a numeric expression

	public:
	/*!	
		\brief   Print the expression
		\warning Pure virtual function: must be redefined in the heir classes
		\return  void
		\sa		 evaluate
	*/
    virtual void print() = 0;

    bool isAlphanumeric() const;

    void setAlphanumeric(const bool flag);
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   NumericExpNode
  \brief   Definition of atributes and methods of NumericExpNode class
  \warning Abstract class
*/
class NumericExpNode : public ExpNode
{
  public:
	/*!	
		\brief   Print the expression
		\warning Pure virtual function: must be redefined in the heir classes
		\return  void
		\sa		 evaluate
	*/
    virtual void print() {}

	/*!	
		\brief   Evaluate the expression
		\warning Pure virtual function: must be redefined in the heir classes
		\return  double
		\sa		 print
	*/
    virtual double evaluate() = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   LogicExpNode
  \brief   Definition of atributes and methods of LogicExpNode class
  \warning Abstract class
*/
class LogicExpNode : public ExpNode
{
  public:
	/*!	
		\brief   Print the expression
		\warning Pure virtual function: must be redefined in the heir classes
		\return  void
		\sa		 evaluate
	*/
	virtual void print() {}

	/*!	
		\brief   Evaluate the expression
		\warning Pure virtual function: must be redefined in the heir classes
		\return  double
		\sa		 print
	*/
    virtual bool evaluate() = 0;
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   AlphanumericExpNode
  \brief   Definition of atributes and methods of AlphanumericExpNode class
  \warning Abstract class
*/
class AlphanumericExpNode : public ExpNode
{
  public:

	/*!	
		\brief   Print the expression
		\warning Pure virtual function: must be redefined in the heir classes
		\return  void
		\sa		 evaluate
	*/
	virtual void print() {}

	/*!	
		\brief   Evaluate the expression
		\warning Pure virtual function: must be redefined in the heir classes
		\return  double
		\sa		 print
	*/
    virtual std::string evaluate() = 0;
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class NumberNode
  \brief Definition of atributes and methods of NumberNode class
  \note  NumberNode Class publicly inherits from NumericExpNode class
*/
class NumberNode : public NumericExpNode 
{
 private: 	
   double _number; //!< \brief number of the NumberNode
 
 public:

	/*!		
		\brief Constructor of NumberNode
		\param value: double
		\post  A new NumberNode is created with the value of the parameter
		\note  Inline function
	*/
	NumberNode(double value)
	{
		setAlphanumeric(0);
	    this->_number = value;
	}

/*!
	\brief   Print the expression
	\return  void
	\sa		 evaluate
*/
  void print();

/*!	
	\brief   Evaluate the expression
	\return  double
	\sa		 print
*/
  double evaluate();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class StringNode
  \brief Definition of atributes and methods of StringNode class
  \note  StringNode Class publicly inherits from AlphanumericExpNode class
*/
class StringNode : public AlphanumericExpNode 
{
 private: 	
   std::string _string; //!< \brief string of the StringNode
 
 public:

	/*!		
		\brief Constructor of StringNode
		\param value: std::string
		\post  A new StringNode is created with the value of the parameter
		\note  Inline function
	*/
	StringNode(char * s)
	{
		setAlphanumeric(1); // Indica que la expresion es alphanumeric

		std::string str(s);
		this->_string = str;
	}

	/*!
		\brief   Print the expression
		\return  void
		\sa		 evaluate
	*/
	void print();

	/*!	
		\brief   Evaluate the expression
		\return  std::string
		\sa		 print
	*/
	std::string evaluate();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class NumericVariableNode
  \brief Definition of atributes and methods of NumericVariableNode class
  \note  NumericVariableNode Class publicly inherits from NumericExpNode class
*/
class NumericVariableNode : public NumericExpNode 
{
private:
	std::string _id; //!< Name of the NumericVariableNode

public:

/*!		
	\brief Constructor of NumericVariableNode
	\param value: string
	\post  A new NumericVariableNode is created with the name of the parameter
	\note  Inline function
*/
  NumericVariableNode(std::string value)
	{
		setAlphanumeric(0);
		this->_id = value; 
	}

/*!
	\brief   Print the Variable
	\return  void
	\sa		 evaluate
*/
  void print();

/*!	
	\brief   Evaluate the Variable
	\return  double
	\sa		 print
*/
  double evaluate();

};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class AlphanumericVariableNode
  \brief Definition of atributes and methods of AlphanumericVariableNode class
  \note  AlphanumericVariableNode Class publicly inherits from AlphanumericExpNode class
*/
class AlphanumericVariableNode : public AlphanumericExpNode 
{
private:
	std::string _id; //!< Name of the AlphanumericVariableNode

public:

	/*!		
		\brief Constructor of AlphanumericVariableNode
		\param value: std::string
		\post  A new AlphanumericVariableNode is created with the name of the parameter
		\note  Inline function
	*/
	AlphanumericVariableNode(char * str)
	{
		setAlphanumeric(1);

		std::string value(str);
		this->_id = value; 
	}

	/*!
		\brief   Print the Variable
		\return  void
		\sa		 evaluate
	*/
	void print();

	/*!	
		\brief   Evaluate the Variable
		\return  string
		\sa		 print
	*/
	std::string evaluate();

};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class NumericConstantNode
  \brief Definition of atributes and methods of NumericConstantNode class
  \note  NumericConstantNode Class publicly inherits from NumericExpNode class
*/
class NumericConstantNode : public NumericExpNode 
{

 private:
  std::string _id; //!< Name of the NumericConstantNode

public:

/*!		
	\brief Constructor of NumericVariableNode
	\param value: double
	\post  A new NumericVariableNode is created with the name of the parameter
*/
  NumericConstantNode(std::string value)
	{
		setAlphanumeric(0);
		this->_id = value; 
	}


/*!
	\brief   Print the NumericConstantNode
	\return  void
	\sa		 evaluate
*/
  void print();

/*!	
	\brief   Evaluate the NumericConstantNode
	\return  double
	\sa		 print
*/
  double evaluate();

};



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   UnaryOperatorNode
  \brief   Definition of atributes and methods of UnaryOperatorNode class
  \note    UnaryOperatorNode Class publicly inherits from NumericExpNode class
  \warning Abstract class, because it does not redefine the print and evaluate methods of NumericExpNode
*/
class UnaryOperatorNode : public NumericExpNode 
{
 protected:
  NumericExpNode *_exp;  //!< Child expression

 public:

/*!		
	\brief Constructor of UnaryOperatorNode links the node to it child,
           and stores the character representation of the operator.
	\param expression: pointer to NumericExpNode
	\post  A new NumericOperatorNode is created with the parameters
	\note  Inline function
*/
  UnaryOperatorNode(NumericExpNode *expression)
	{
		setAlphanumeric(0);
		this->_exp = expression;
	}
};



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   UnaryMinusNode
  \brief   Definition of atributes and methods of UnaryMinusNode class
  \note    UnaryMinusNode Class publicly inherits from UnaryOperatorNode class
*/
class UnaryMinusNode : public UnaryOperatorNode 
{

 public:

	/*!		
		\brief Constructor of UnaryMinusNode uses UnaryOperatorNode's constructor as member initializer.
		\param expression: pointer to NumericExpNode
		\post  A new UnaryMinusNode is created with the parameter
		\note  Inline function: the NumericExpNode's constructor is used ad member initializer
	*/
	UnaryMinusNode(NumericExpNode *expression): UnaryOperatorNode(expression) 
	{
		// empty
	} 

/*!
	\brief   Print the expression
	\return  void
	\sa		 evaluate
*/
  void print();

/*!	
	\brief   Evaluate the expression
	\return  double
	\sa		 print
*/
  double evaluate();
};

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/*!	
  \class   UnaryPlusNode
  \brief   Definition of atributes and methods of UnaryPlusNode class
  \note    UnaryPlusNode Class publicly inherits from UnaryOperatorNode class
*/
class UnaryPlusNode : public UnaryOperatorNode 
{

 public:

/*!		
	\brief Constructor of UnaryPlusNode uses UnaryOperatorNode's constructor as member initializer
	\param expression: pointer to NumericExpNode
	\post  A new UnaryPlusNode is created with the parameter
*/
  UnaryPlusNode(NumericExpNode *expression): UnaryOperatorNode(expression) 
	{
		// empty
	} 

/*!
	\brief   Print the expression
	\return  void
	\sa		 evaluate
*/
  void print();

/*!	
	\brief   Evaluate the expression
	\return  double
	\sa		 print
*/
  double evaluate();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   DecrementNode
  \brief   Definition of atributes and methods of DecrementNode class
  \note    DecrementNode Class publicly inherits from UnaryOperatorNode class
*/
class DecrementNode : public UnaryOperatorNode 
{

 public:

	/*!		
		\brief Constructor of DecrementNode uses UnaryOperatorNode's constructor as member initializer.
		\param expression: pointer to NumericExpNode
		\post  A new DecrementNode is created with the parameter
		\note  Inline function: the NumericExpNode's constructor is used ad member initializer
	*/
	DecrementNode(NumericExpNode *expression): UnaryOperatorNode(expression) 
	{
		// empty
	} 

	/*!
		\brief   Print the expression
		\return  void
		\sa		 evaluate
	*/
	void print();

	/*!	
		\brief   Evaluate the expression
		\return  double
		\sa		 print
	*/
	double evaluate();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   IncrementNode
  \brief   Definition of atributes and methods of IncrementNode class
  \note    IncrementNode Class publicly inherits from UnaryOperatorNode class
*/
class IncrementNode : public UnaryOperatorNode 
{

 public:

	/*!		
		\brief Constructor of IncrementNode uses UnaryOperatorNode's constructor as member initializer.
		\param expression: pointer to NumericExpNode
		\post  A new IncrementNode is created with the parameter
		\note  Inline function: the NumericExpNode's constructor is used ad member initializer
	*/
	IncrementNode(NumericExpNode *expression): UnaryOperatorNode(expression) 
	{
		// empty
	} 

	/*!
		\brief   Print the expression
		\return  void
		\sa		 evaluate
	*/
	void print();

	/*!	
		\brief   Evaluate the expression
		\return  double
		\sa		 print
	*/
	double evaluate();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
/*NEW in IPE*/

/*!	
  \class   NumericOperatorNode
  \brief   Definition of atributes and methods of NumericOperatorNode class
  \note    NumericOperatorNode Class publicly inherits from NumericExpNode class
  \warning Abstract class, because it does not redefine the print and evaluate methods of NumericExpNode
*/
class NumericOperatorNode : public NumericExpNode 
{
protected:
    NumericExpNode *_numeric_left;    //!< Left expression
    NumericExpNode *_numeric_right;   //!< Right expression

public:
/*!		
	\brief Constructor of NumericOperatorNode links the node to its children,
           and stores the character representation of the operator.
	\param L: pointer to NumericExpNode
	\param R: pointer to NumericExpNode
	\post  A new NumericOperatorNode is created with the parameters
*/
    NumericOperatorNode(NumericExpNode *L, NumericExpNode *R)
	{
		setAlphanumeric(0);
	    this->_numeric_left  = L;
    	this->_numeric_right = R;
	}

};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
/*NEW in IPE*/

/*!	
	\class   AlphanumericOperatorNode
	\brief   Definition of atributes and methods of AlphanumericOperatorNode class
	\note    AlphanumericOperatorNode Class publicly inherits from AlphanumericExpNode class
	\warning Abstract class, because it does not redefine the print and evaluate methods of AlphanumericExpNode
*/
class AlphanumericOperatorNode : public AlphanumericExpNode 
{
protected:
AlphanumericExpNode *_alphanumeric_left;    //!< Left expression
AlphanumericExpNode *_alphanumeric_right;   //!< Right expression

public:
	
	/*!		
		\brief Constructor of AlphanumericOperatorNode links the node to its children, and stores the character representation of the operator.
		\param L: pointer to AlphanumericExpNode
		\param R: pointer to AlphanumericExpNode
		\post  A new AlphanumericOperatorNode is created with the parameters
	*/
		AlphanumericOperatorNode(AlphanumericExpNode *L, AlphanumericExpNode *R)
	{
		setAlphanumeric(1);

		this->_alphanumeric_left  = L;
		this->_alphanumeric_right = R;
	}

};



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
/*NEW in IPE*/

/*!	
  \class   LogicOperatorNode
  \brief   Definition of atributes and methods of LogicOperatorNode class
  \note    LogicOperatorNode Class publicly inherits from LogicExpNode class
  \warning Abstract class, because it does not redefine the print and evaluate methods of LogicExpNode
*/
class LogicOperatorNode : public LogicExpNode 
{
protected:
    LogicExpNode *_numeric_left;    //!< Left expression
    LogicExpNode *_numeric_right;   //!< Right expression

public:
/*!		
	\brief Constructor of LogicOperatorNode links the node to its children,
           and stores the character representation of the operator.
	\param L: pointer to LogicExpNode
	\param R: pointer to LogicExpNode
	\post  A new LogicOperatorNode is created with the parameters
*/
    LogicOperatorNode(LogicExpNode *L, LogicExpNode *R)
	{
	    this->_numeric_left  = L;
    	this->_numeric_right = R;
	}

	/*!		
		\brief Constructor of unary LogicOperatorNode links the node to its children, and stores the character representation of the operator. (use for NotNode)
		\param R: pointer to LogicExpNode
		\post  A new LogicOperatorNode is created with the parameter
	*/
    LogicOperatorNode(LogicExpNode *R)
	{
	    this->_numeric_left  = 0;
    	this->_numeric_right = R;
	}

};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
/*NEW in IPE*/

/*!	
  \class   RelationalOperatorNode
  \brief   Definition of atributes and methods of RelationalOperatorNode class
  \note    RelationalOperatorNode Class publicly inherits from LogicExpNode class
  \warning Abstract class, because it does not redefine the print and evaluate methods of LogicExpNode
*/
class RelationalOperatorNode : public LogicExpNode 
{
protected:
	NumericExpNode *_numeric_left;    //!< Left expression
	NumericExpNode *_numeric_right;   //!< Right expression

	AlphanumericExpNode *_alphanumeric_left;    //!< Left expression
	AlphanumericExpNode *_alphanumeric_right;   //!< Right expression

public:

	/*!		
		\brief Constructor of RelationalOperatorNode links the node to its children,
			   and stores the character representation of the operator.
		\param L: pointer to ExpNode
		\param R: pointer to ExpNode
		\post  A new RelationalOperatorNode is created with the parameters
	*/
	RelationalOperatorNode(ExpNode *L, ExpNode *R)
	{
		if(L->isAlphanumeric())
			this->_alphanumeric_left = (AlphanumericExpNode *)L;
		else
			this->_numeric_left = (NumericExpNode *)L;

		if(R->isAlphanumeric())
			this->_alphanumeric_right = (AlphanumericExpNode *)R;
		else
			this->_numeric_right = (NumericExpNode *)R;
	}

	/*!		
		\brief Constructor of RelationalOperatorNode links the node to its children,
			   and stores the character representation of the operator.
		\param L: pointer to ExpNode
		\param R: pointer to ExpNode
		\post  A new RelationalOperatorNode is created with the parameters
	*/
	RelationalOperatorNode(NumericExpNode *L, NumericExpNode *R)
	{
		this->_numeric_left  = L;
		this->_numeric_right = R;

		_alphanumeric_left = NULL;
		_alphanumeric_right = NULL;
	}

	RelationalOperatorNode(AlphanumericExpNode *L, AlphanumericExpNode *R)
	{
		this->_alphanumeric_left  = L;
		this->_alphanumeric_right = R;

		_numeric_left = NULL;
		_numeric_right = NULL;
	}
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   PlusNode
  \brief   Definition of atributes and methods of PlusNode class
  \note    PlusNode Class publicly inherits from NumericOperatorNode class 
		   and adds its own print and evaluate functions
*/
class PlusNode : public NumericOperatorNode 
{
  public:
/*!		
	\brief Constructor of PlusNode uses NumericOperatorNode's constructor as members initializer
	\param L: pointer to NumericExpNode
	\param R: pointer to NumericExpNode
	\post  A new PlusNode is created with the parameter
*/
  PlusNode(NumericExpNode *L, NumericExpNode *R) : NumericOperatorNode(L,R) 
  {
		// Empty
  }

/*!
	\brief   Print the PlusNode
	\return  void
	\sa		 evaluate
*/
  void print();

/*!	
	\brief   Evaluate the PlusNode
	\return  double
	\sa		 print
*/
  double evaluate();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   MinusNode
  \brief   Definition of atributes and methods of MinusNode class
  \note    MinusNode Class publicly inherits from NumericOperatorNode class 
		   and adds its own print and evaluate functions
*/
class MinusNode : public NumericOperatorNode 
{
  public:

/*!		
	\brief Constructor of MinusNode uses NumericOperatorNode's constructor as members initializer
	\param L: pointer to NumericExpNode
	\param R: pointer to NumericExpNode
	\post  A new MinusNode is created with the parameter
*/
  MinusNode(NumericExpNode *L, NumericExpNode *R): NumericOperatorNode(L,R) 
  {
		// Empty
  }
/*!
	\brief   Print the MinusNode
	\return  void
	\sa		 evaluate
*/
  void print();

/*!	
	\brief   Evaluate the MinusNode
	\return  double
	\sa		 print
*/
  double evaluate();
};



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   MultiplicationNode
  \brief   Definition of atributes and methods of MultiplicationNode class
  \note    MultiplicationNode Class publicly inherits from NumericOperatorNode class 
		   and adds its own print and evaluate functions
*/
class MultiplicationNode : public NumericOperatorNode 
{
  public:

/*!		
	\brief Constructor of MultiplicationNode uses NumericOperatorNode's constructor as members initializer
	\param L: pointer to NumericExpNode
	\param R: pointer to NumericExpNode
	\post  A new MultiplicationNode is created with the parameter
*/
  MultiplicationNode(NumericExpNode *L, NumericExpNode *R): NumericOperatorNode(L,R) 
  {
		// Empty
  }
/*!
	\brief   Print the MultiplicationNode
	\return  void
	\sa		 evaluate
*/
  void print();

/*!	
	\brief   Evaluate the MultiplicationNode
	\return  double
	\sa		 print
*/
  double evaluate();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   DivisionNode
  \brief   Definition of atributes and methods of DivisionNode class
  \note    DivisionNode Class publicly inherits from NumericOperatorNode class 
		   and adds its own print and evaluate functions
*/
class DivisionNode : public NumericOperatorNode 
{
  public:
/*!		
	\brief Constructor of DivisionNode uses NumericOperatorNode's constructor as members initializer
	\param L: pointer to NumericExpNode
	\param R: pointer to NumericExpNode
	\post  A new DivisionNode is created with the parameter
*/
  DivisionNode(NumericExpNode *L, NumericExpNode *R): NumericOperatorNode(L,R) 
  {
		// Empty
  }
/*!
	\brief   Print the DivisionNode
	\return  void
	\sa		 evaluate
*/
  void print();

/*!	
	\brief   Evaluate the DivisionNode
	\return  double
	\sa		 print
*/
  double evaluate();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   IntDivisionNode
  \brief   Definition of atributes and methods of IntDivisionNode class
  \note    IntDivisionNode Class publicly inherits from NumericOperatorNode class 
		   and adds its own print and evaluate functions
*/
class IntDivisionNode : public NumericOperatorNode 
{
  public:
/*!		
	\brief Constructor of IntDivisionNode uses NumericOperatorNode's constructor as members initializer
	\param L: pointer to NumericExpNode
	\param R: pointer to NumericExpNode
	\post  A new IntDivisionNode is created with the parameter
*/
  IntDivisionNode(NumericExpNode *L, NumericExpNode *R): NumericOperatorNode(L,R) 
  {
		// Empty
  }
/*!
	\brief   Print the IntDivisionNode
	\return  void
	\sa		 evaluate
*/
  void print();

/*!	
	\brief   Evaluate the IntDivisionNode
	\return  double
	\sa		 print
*/
  double evaluate();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   ModuloNode
  \brief   Definition of atributes and methods of ModuloNode class
  \note    ModuloNode Class publicly inherits from NumericOperatorNode class 
		   and adds its own print and evaluate functions
*/
class ModuloNode : public NumericOperatorNode 
{
  public:
/*!		
	\brief Constructor of ModuloNode uses NumericOperatorNode's constructor as members initializer
	\param L: pointer to NumericExpNode
	\param R: pointer to NumericExpNode
	\post  A new ModuloNode is created with the parameter
*/
  ModuloNode(NumericExpNode *L, NumericExpNode *R): NumericOperatorNode(L,R) 
  {
		// Empty
  }
/*!
	\brief   Print the ModuloNode
	\return  void
	\sa		 evaluate
*/
  void print();

/*!	
	\brief   Evaluate the ModuloNode
	\return  double
	\sa		 print
*/
  double evaluate();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   PowerNode
  \brief   Definition of atributes and methods of PowerNode class
  \note    PowerNode Class publicly inherits from NumericOperatorNode class 
		   and adds its own print and evaluate functions
*/
class PowerNode : public NumericOperatorNode 
{
  public:
/*!		
	\brief Constructor of PowerNode uses NumericOperatorNode's constructor as members initializer
	\param L: pointer to NumericExpNode
	\param R: pointer to NumericExpNode
	\post  A new PowerNode is created with the parameter
*/
  PowerNode(NumericExpNode *L, NumericExpNode *R): NumericOperatorNode(L,R) 
  {
		// Empty
  }

/*!
	\brief   Print the PowerNode
	\return  void
	\sa		 evaluate
*/
  void print();

/*!	
	\brief   Evaluate the PowerNode
	\return  double
	\sa		 print
*/
  double evaluate();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
	\class   ConcatenationNode
	\brief   Definition of atributes and methods of ConcatenationNode class
	\note    ConcatenationNode Class publicly inherits from AlphanumericOperatorNode class 
			 and adds its own print and evaluate functions
*/
class ConcatenationNode : public AlphanumericOperatorNode 
{
public:
	/*!		
		\brief Constructor of ConcatenationNode uses AlphanumericOperatorNode's constructor as members initializer
		\param L: pointer to AlphanumericExpNode
		\param R: pointer to AlphanumericExpNode
		\post  A new ConcatenationNode is created with the parameter
	*/
	ConcatenationNode(AlphanumericExpNode *L, AlphanumericExpNode *R) : AlphanumericOperatorNode(L,R) 
	{
		setAlphanumeric(1);
	}

	/*!
		\brief   Print the ConcatenationNode
		\return  void
		\sa		 evaluate
	*/
	void print();

	/*!	
		\brief   Evaluate the ConcatenationNode
		\return  string
		\sa		 print
	*/
	std::string evaluate();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   BuiltinFunctionNode
  \brief   Definition of atributes and methods of BuiltinFunctionNode class
  \note    BuiltinFunctionNode Class publicly inherits from NumericExpNode class 
		   and adds its own print and evaluate functions
*/
class BuiltinFunctionNode : public NumericExpNode 
{
  private:
	std::string _id; //!< Name of the BuiltinFunction
	NumericExpNode *_exp;  //!< Argument of the BuiltinFunction

  public:
/*!		
	\brief Constructor of BuiltinFunctionNode
	\param id: string, name of the BuiltinFunction
	\param expression: pointer to NumericExpNode, argument of the BuiltinFunction
	\post  A new BuiltinFunctionNode_2 is created with the parameters
*/
  BuiltinFunctionNode(std::string id, NumericExpNode *expression)
	{
		setAlphanumeric(0);
		this->_id = id;
		this->_exp = expression;
	}

/*!
	\brief   Print the BuiltinFunctionNode
	\return  void
	\sa		 evaluate
*/
  void print();

/*!	
	\brief   Evaluate the BuiltinFunctionNode
	\return  double
	\sa		 print
*/
  double evaluate();
};



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   BuiltinFunctionNode_0
  \brief   Definition of atributes and methods of BuiltinFunctionNode_0 class
  \note    BuiltinFunctionNode_0 Class publicly inherits from NumericExpNode class 
		   and adds its own print and evaluate functions
*/
class BuiltinFunctionNode_0 : public NumericExpNode 
{
  private: 
	std::string _id; //!< Name of the BuiltinFunction_0
	
  public:
/*!		
	\brief Constructor of BuiltinFunctionNode_0
	\param id: string, name of the BuiltinFunction
	\post  A new BuiltinFunctionNode_2 is created with the parameter
*/
  BuiltinFunctionNode_0(std::string id)
	{
		setAlphanumeric(0);
		this->_id = id;
	}

/*!
	\brief   Print the BuiltinFunctionNode_0
	\return  void
	\sa		 evaluate
*/
  void print();

/*!	
	\brief   Evaluate the BuiltinFunctionNode_0
	\return  double
	\sa		 print
*/
  double evaluate();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   BuiltinFunctionNode_2
  \brief   Definition of atributes and methods of BuiltinFunctionNode_2 class
  \note    BuiltinFunctionNode_2 Class publicly inherits from OperatoNumericExpNoderNode class 
		   and adds its own print and evaluate functions
*/
class BuiltinFunctionNode_2 : public NumericExpNode 
{
 private:
	std::string _id; //!< Name of the BuiltinFunction_2
	NumericExpNode *_exp1; //!< First argument of the BuiltinFunction_2
	NumericExpNode *_exp2; //!< Second argument of the BuiltinFunction_2

  public:
/*!		
	\brief Constructor of BuiltinFunctionNode_2
	\param id: string, name of the BuiltinFunction_2
	\param expression1: pointer to NumericExpNode, first argument of the BuiltinFunctionNode
	\param expression2: pointer to NumericExpNode, second argument of the BuiltinFunctionNode
	\post  A new BuiltinFunctionNode_2 is created with the parameters
*/
  BuiltinFunctionNode_2(std::string id,NumericExpNode *expression1,NumericExpNode *expression2)
	{
		setAlphanumeric(0);
		this->_id = id;
		this->_exp1 = expression1;
		this->_exp2 = expression2;
	}

/*!
	\brief   Print the BuiltinFunctionNode_2
	\return  void
	\sa		 evaluate
*/
  void print();

/*!	
	\brief   Evaluate the BuiltinFunctionNode_2
	\return  double
	\sa		 print
*/
  double evaluate();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   LessThanNode
  \brief   Definition of atributes and methods of LessThanNode class
  \note    LessThanNode Class publicly inherits from OperatorNode class 
		   and adds its own print and evaluate functions
*/
class LessThanNode : public RelationalOperatorNode 
{
  public:

  	/*!		
		\brief Constructor of LessThanNode uses RelationalOperatorNode's constructor as members initializer
		\param L: pointer to ExpNode
		\param R: pointer to ExpNode
		\post  A new LessThanNode is created with the parameter
	*/
	LessThanNode(ExpNode *L, ExpNode *R): RelationalOperatorNode(L,R)
	{
		// std::cout<<"LessThanNode constructor Exp\n";
	}

/*!
	\brief   Print the LessThanNode
	\return  void
	\sa		 evaluate
*/
  void print();

/*!	
	\brief   Evaluate the LessThanNode
	\return  double
	\sa		 print
*/
  bool evaluate();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   GreaterThanNode
  \brief   Definition of atributes and methods of GreaterThanNode class
  \note    GreaterThanNode Class publicly inherits from RelationalOperatorNode class 
		   and adds its own print and evaluate functions
*/
class GreaterThanNode : public RelationalOperatorNode 
{
public:

	/*!		
		\brief Constructor of GreaterThanNode uses RelationalOperatorNode's constructor as members initializer
		\param L: pointer to ExpNode
		\param R: pointer to ExpNode
		\post  A new GreaterThanNode is created with the parameter
	*/
	GreaterThanNode(ExpNode *L, ExpNode *R): RelationalOperatorNode(L,R)
	{
		// std::cout<<"GreaterThanNode constructor Exp\n";
	}

/*!
	\brief   Print the GreaterThanNode
	\return  void
	\sa		 evaluate
*/
  void print();

/*!	
	\brief   Evaluate the GreaterThanNode
	\return  double
	\sa		 print
*/
  bool evaluate();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   GreaterOrEqualNode
  \brief   Definition of atributes and methods of GreaterOrEqualNode class
  \note    GreaterOrEqualNode Class publicly inherits from RelationalOperatorNode class 
		   and adds its own print and evaluate functions
*/
class GreaterOrEqualNode : public RelationalOperatorNode 
{
public:

	/*!		
		\brief Constructor of GreaterOrEqualNode uses RelationalOperatorNode's constructor as members initializer
		\param L: pointer to ExpNode
		\param R: pointer to ExpNode
		\post  A new GreaterOrEqualNode is created with the parameter
	*/
	GreaterOrEqualNode(ExpNode *L, ExpNode *R): RelationalOperatorNode(L,R)
	{
		// std::cout<<"GreaterOrEqualNode constructor Exp\n";
	}


/*!
	\brief   Print the GreaterOrEqualNode
	\return  void
	\sa		 evaluate
*/
  void print();

/*!	
	\brief   Evaluate the GreaterOrEqualNode
	\return  double
	\sa		 print
*/
  bool evaluate();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   LessOrEqualNode
  \brief   Definition of atributes and methods of LessOrEqualNode class
  \note    LessThanNode Class publicly inherits from RelationalOperatorNode class 
		   and adds its own print and evaluate functions
*/
class LessOrEqualNode : public RelationalOperatorNode 
{
public:

	/*!		
		\brief Constructor of LessOrEqualNode uses RelationalOperatorNode's constructor as members initializer
		\param L: pointer to ExpNode
		\param R: pointer to ExpNode
		\post  A new LessOrEqualNode is created with the parameter
	*/
	LessOrEqualNode(ExpNode *L, ExpNode *R): RelationalOperatorNode(L,R)
	{
		// std::cout<<"LessOrEqualNode constructor Exp\n";
	}

	/*!
		\brief   Print the LessOrEqualNode
		\return  void
		\sa		 evaluate
	*/
	void print();

	/*!	
		\brief   Evaluate the LessOrEqualNode
		\return  double
		\sa		 print
	*/
	bool evaluate();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   EqualNode
  \brief   Definition of atributes and methods of EqualNode class
  \note    EqualNode Class publicly inherits from RelationalOperatorNode class 
		   and adds its own print and evaluate functions
*/
class EqualNode : public RelationalOperatorNode 
{
public:

	/*!		
		\brief Constructor of EqualNode uses RelationalOperatorNode's constructor as members initializer
		\param L: pointer to ExpNode
		\param R: pointer to ExpNode
		\post  A new EqualNode is created with the parameter
	*/
	EqualNode(ExpNode *L, ExpNode *R): RelationalOperatorNode(L,R)
	{
		// std::cout<<"EqualNode constructor Exp\n";
	}

/*!
	\brief   Print the EqualNode
	\return  void
	\sa		 evaluate
*/
  void print();

/*!	
	\brief   Evaluate the EqualNode
	\return  double
	\sa		 print
*/
  bool evaluate();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   NotEqualNode
  \brief   Definition of atributes and methods of NotEqualNode class
  \note    NotEqualNode Class publicly inherits from RelationalOperatorNode class 
		   and adds its own print and evaluate functions
*/
class NotEqualNode : public RelationalOperatorNode 
{
  public:

	/*!		
		\brief Constructor of NotEqualNode uses RelationalOperatorNode's constructor as members initializer
		\param L: pointer to ExpNode
		\param R: pointer to ExpNode
		\post  A new NotEqualNode is created with the parameter
	*/
	NotEqualNode(ExpNode *L, ExpNode *R): RelationalOperatorNode(L,R)
	{
		// std::cout<<"NotEqualNode constructor Exp\n";
	}

/*!
	\brief   Print the NotEqualNode
	\return  void
	\sa		 evaluate
*/
  void print();

/*!	
	\brief   Evaluate the NotEqualNode
	\return  double
	\sa		 print
*/
  bool evaluate();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*! 
  \class   AndNode
  \brief   Definition of atributes and methods of AndNode class
  \note    AndNode Class publicly inherits from LogicOperatorNode class 
       and adds its own print and evaluate functions
*/
class AndNode : public LogicOperatorNode 
{
  public:

/*!   
  \brief Constructor of AndNode uses LogicOperatorNode's constructor as members initializer
  \param L: pointer to LogicExpNode
  \param R: pointer to LogicExpNode
  \post  A new AndNode is created with the parameter
*/
  AndNode(LogicExpNode *L, LogicExpNode *R): LogicOperatorNode(L,R) 
  {
    // Empty
  }

/*!
  \brief   Print the AndNode
  \return  void
  \sa    evaluate
*/
  void print();

/*! 
  \brief   Evaluate the AndNode
  \return  double
  \sa    print
*/
  bool evaluate();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*! 
  \class   OrNode
  \brief   Definition of atributes and methods of OrNode class
  \note    OrNode Class publicly inherits from LogicOperatorNode class 
       and adds its own print and evaluate functions
*/
class OrNode : public LogicOperatorNode 
{
  public:

/*!   
  \brief Constructor of AndNode uses LogicOperatorNode's constructor as members initializer
  \param L: pointer to LogicExpNode
  \param R: pointer to LogicExpNode
  \post  A new AndNode is created with the parameter
*/
  OrNode(LogicExpNode *L, LogicExpNode *R): LogicOperatorNode(L,R) 
  {
    // Empty
  }

/*!
  \brief   Print the OrNode
  \return  void
  \sa    evaluate
*/
  void print();

/*! 
  \brief   Evaluate the OrNode
  \return  double
  \sa    print
*/
  bool evaluate();
};


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/*! 
  \class   NotNode
  \brief   Definition of atributes and methods of UnaryPlusNode class
  \note    NotNode Class publicly inherits from LogicOperatorNode class
*/
class NotNode : public LogicOperatorNode 
{

 public:

/*!   
  \brief Constructor of NotNode uses LogicOperatorNode's constructor as member initializer
  \param expression: pointer to LogicExpNode
  \post  A new UnaryPlusNode is created with the parameter
*/
  NotNode(LogicExpNode *expression): LogicOperatorNode(expression) 
  {
    // empty
  } 

/*!
  \brief   Print the NotNode
  \return  void
  \sa    evaluate
*/
  void print();

/*! 
  \brief   Evaluate the NotNode
  \return  double
  \sa    print
*/
  bool evaluate();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   Statement
  \brief   Definition of atributes and methods of Statement class
  \warning Abstract class
*/

class Statement {
 public:

/*!	
	\brief   Print the Statement
	\note    Virtual function: can be redefined in the heir classes
	\return  double
	\sa		 print
*/

  virtual void print() {}

/*!	
	\brief   Evaluate the Statement
	\warning Pure virtual function: must be redefined in the heir classes
	\return  double
	\sa		 print
*/
  virtual void evaluate() = 0;
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   AssignmentStmt
  \brief   Definition of atributes and methods of AssignmentStmt class
  \note    AssignmentStmt Class publicly inherits from Statement class 
		   and adds its own print and evaluate functions
*/
class AssignmentStmt : public Statement 
{
 private:
  std::string _id;    //!< Name of the variable of the assignment statement
  
  ExpNode * _exp;
  NumericExpNode *_numeric_exp; //!< Expresssion the assignment statement
  AlphanumericExpNode *_alphanumeric_exp; //!< Expresssion the assignment statement

  AssignmentStmt *_asgn;  //!< Allow multiple assigment -> a = b = 2 

 public:

	/*!		
		\brief Constructor of AssignmentStmt 
		\param id: string, variable of the AssignmentStmt
		\param expression: pointer to NumericExpNode
		\post  A new AssignmentStmt is created with the parameters
	*/
 	AssignmentStmt(std::string id, ExpNode *expression): _id(id), _exp(expression)
	{
		this->_asgn = NULL;

		if(expression->isAlphanumeric())
		{
			_alphanumeric_exp = (AlphanumericExpNode *) expression;
			_numeric_exp = NULL;
		}
		else
		{
			_numeric_exp = (NumericExpNode *) expression;
			_alphanumeric_exp = NULL;
		}
	}

	/*!		
		\brief Constructor of AssignmentStmt 
		\param id: string, variable of the AssignmentStmt
		\param asgn: pointer to AssignmentStmt
		\post  A new AssignmentStmt is created with the parameters
		\note  Allow multiple assigment -> a = b = 2 
	*/
	AssignmentStmt(std::string id, AssignmentStmt *asgn): _id(id), _asgn(asgn)
	{
		_numeric_exp = 0;
		_alphanumeric_exp = 0;
	}

	/*!
		\brief   Print the AssignmentStmt
		\return  void
		\sa		 evaluate
	*/
	void print();

	/*!	
		\brief   Evaluate the AssignmentStmt
		\return  void
		\sa		 print
	*/
	void evaluate();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   PlusAssignmentStmt
  \brief   Definition of atributes and methods of PlusAssignmentStmt class
  \note    PlusAssignmentStmt Class publicly inherits from Statement class 
		   and adds its own print and evaluate functions
*/
class PlusAssignmentStmt : public Statement 
{
private:
	std::string _id;    //!< Name of the variable of the assignment statement
	NumericExpNode *_numeric_exp; //!< Expresssion the assignment statement

public:

	/*!		
		\brief Constructor of PlusAssignmentStmt 
		\param id: string, variable of the PlusAssignmentStmt
		\param expression: pointer to NumericExpNode
		\post  A new PlusAssignmentStmt is created with the parameters
	*/
 	PlusAssignmentStmt(std::string id, NumericExpNode *expression): _id(id), _numeric_exp(expression)
	{
		// empty
	}

	/*!
		\brief   Print the PlusAssignmentStmt
		\return  void
		\sa		 evaluate
	*/
	void print();

	/*!	
		\brief   Evaluate the PlusAssignmentStmt
		\return  void
		\sa		 print
	*/
	void evaluate();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   MinusAssignmentStmt
  \brief   Definition of atributes and methods of MinusAssignmentStmt class
  \note    MinusAssignmentStmt Class publicly inherits from Statement class 
		   and adds its own print and evaluate functions
*/
class MinusAssignmentStmt : public Statement 
{
private:
	std::string _id;    //!< Name of the variable of the assignment statement
	NumericExpNode *_numeric_exp; //!< Expresssion the assignment statement

public:

	/*!		
		\brief Constructor of MinusAssignmentStmt 
		\param id: string, variable of the MinusAssignmentStmt
		\param expression: pointer to NumericExpNode
		\post  A new MinusAssignmentStmt is created with the parameters
	*/
 	MinusAssignmentStmt(std::string id, NumericExpNode *expression): _id(id), _numeric_exp(expression)
	{
		// Empty
	}

	/*!
		\brief   Print the MinusAssignmentStmt
		\return  void
		\sa		 evaluate
	*/
	void print();

	/*!	
		\brief   Evaluate the MinusAssignmentStmt
		\return  void
		\sa		 print
	*/
	void evaluate();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   MultAssignmentStmt
  \brief   Definition of atributes and methods of MultAssignmentStmt class
  \note    MultAssignmentStmt Class publicly inherits from Statement class 
		   and adds its own print and evaluate functions
*/
class MultAssignmentStmt : public Statement 
{
private:
	std::string _id;    //!< Name of the variable of the assignment statement
	NumericExpNode *_numeric_exp; //!< Expresssion the assignment statement

public:

	/*!		
		\brief Constructor of MultAssignmentStmt 
		\param id: string, variable of the MultAssignmentStmt
		\param expression: pointer to NumericExpNode
		\post  A new MultAssignmentStmt is created with the parameters
	*/
 	MultAssignmentStmt(std::string id, NumericExpNode *expression): _id(id), _numeric_exp(expression)
	{
		// Empty
	}

	/*!
		\brief   Print the MultAssignmentStmt
		\return  void
		\sa		 evaluate
	*/
	void print();

	/*!	
		\brief   Evaluate the MultAssignmentStmt
		\return  void
		\sa		 print
	*/
	void evaluate();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   DiviAssignmentStmt
  \brief   Definition of atributes and methods of DiviAssignmentStmt class
  \note    DiviAssignmentStmt Class publicly inherits from Statement class 
		   and adds its own print and evaluate functions
*/
class DiviAssignmentStmt : public Statement 
{
private:
	std::string _id;    //!< Name of the variable of the assignment statement
	NumericExpNode *_numeric_exp; //!< Expresssion the assignment statement

public:

	/*!		
		\brief Constructor of DiviAssignmentStmt 
		\param id: string, variable of the DiviAssignmentStmt
		\param expression: pointer to NumericExpNode
		\post  A new DiviAssignmentStmt is created with the parameters
	*/
 	DiviAssignmentStmt(std::string id, NumericExpNode *expression): _id(id), _numeric_exp(expression)
	{
		// Empty
	}

	/*!
		\brief   Print the DiviAssignmentStmt
		\return  void
		\sa		 evaluate
	*/
	void print();

	/*!	
		\brief   Evaluate the DiviAssignmentStmt
		\return  void
		\sa		 print
	*/
	void evaluate();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   PrintStmt
  \brief   Definition of atributes and methods of PrintStmt class
  \note    PrintStmt Class publicly inherits from Statement class and adds its own print and evaluate functions
  \warning  In this class, print and evaluate functions have the same meaning.
*/
class PrintStmt: public Statement 
{
 private:
  NumericExpNode *_numeric_exp; //!< numericExpresssion the print statement
  AlphanumericExpNode *_alphanumeric_exp; //!< alphanumericExpresssion the print statement

 public:
	/*!		
		\brief Constructor of PrintStmt 
		\param expression: pointer to NumericExpNode
		\post  A new PrintStmt is created with the parameter
	*/
	PrintStmt(NumericExpNode *expression)
	{
		this->_numeric_exp = expression;
		_alphanumeric_exp = 0;
	}

	/*!		
		\brief Constructor of PrintStmt 
		\param expression: pointer to AlphanumericExpNode
		\post  A new PrintStmt is created with the parameter
	*/
	PrintStmt(AlphanumericExpNode *expression)
	{
		this->_alphanumeric_exp = expression;
		_numeric_exp = 0;
	}

	/*!
		\brief   Print the PrintStmt
		\return  void
		\sa		 evaluate
	*/
	void print();

	/*!	
		\brief   Evaluate the PrintStmt
		\return  double
		\sa		 print
	*/
	void evaluate();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   CleanStmt
  \brief   Definition of atributes and methods of CleanStmt class
  \note    CleanStmt Class publicly inherits from Statement class 
		   and adds its own print and evaluate functions
  \warning  In this class, print and evaluate functions have the same meaning.
*/
class CleanStmt: public Statement 
{
 private:

 public:
/*!		
	\brief Constructor of CleanStmt 
	\param expression: pointer to NumericExpNode
	\post  A new CleanStmt is created with the parameter
*/
  CleanStmt()
	{
		// void
	}

/*!
	\brief   Clean the CleanStmt
	\return  void
	\sa		 evaluate
*/
  void print();

/*!	
	\brief   Evaluate the CleanStmt
	\return  double
	\sa		 print
*/
  void evaluate();
};



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// NEW in IPE

/*!	
  \class   PlaceStmt
  \brief   Definition of atributes and methods of PlaceStmt class
  \note    PlaceStmt Class publicly inherits from Statement class 
		   and adds its own print and evaluate functions
*/
class PlaceStmt : public Statement 
{
 private:
  NumericExpNode *_x; //!< x
  NumericExpNode *_y; //!< y

  public:
/*!		
	\brief Constructor of  PlaceStmt
	\param condition: NumericExpNode of the condition
	\param statement: Statement of the body of the loop 
	\post  A new PlaceStmt is created with the parameters
*/
  PlaceStmt(NumericExpNode *x, NumericExpNode *y)
	{
		this->_x = x;
		this->_y = y;
	}


/*!
	\brief   Print the PlaceStmt
	\return  void
	\sa		 evaluate
*/
  void print();

/*!	
	\brief   Evaluate the PlaceStmt
	\return  void
	\sa		 print
*/
  void evaluate();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   ReadStmt
  \brief   Definition of atributes and methods of ReadStmt class
  \note    ReadStmt Class publicly inherits from Statement class 
		   and adds its own print and evaluate functions
*/
class ReadStmt : public Statement 
{
  private:
	std::string _id; //!< Name of the ReadStmt
	int _type;
	

  public:

	/*!		
		\brief Constructor of ReadStmt
		\param id: string, name of the variable of the ReadStmt
		\post  A new ReadStmt is created with the parameter
	*/
	  ReadStmt(int type, std::string id)
		{
			this->_id = id;
			this->_type = type;
		}

/*!
	\brief   Print the ReadStmt
	\return  void
	\sa		 evaluate
*/
  void print();

/*!	
	\brief   Evaluate the ReadStmt
	\return  void
	\sa		 print
*/
  void evaluate();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   EmptyStmt
  \brief   Definition of atributes and methods of EmptyStmt class
  \note    EmptyStmt Class publicly inherits from Statement class 
		   and adds its own print and evaluate functions
*/
class EmptyStmt : public Statement 
{
  // No attributes

  public:
/*!		
	\brief Constructor of  WhileStmt
	\post  A new EmptyStmt is created 
*/
  EmptyStmt()
	{
		// Empty
	}


/*!
	\brief   Print the EmptyStmt
	\return  void
	\sa		 evaluate
*/
  void print();

/*!	
	\brief   Evaluate the EmptyStmt
	\return  void
	\sa		 print
*/
  void evaluate();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// NEW in example 17

/*! 
  \class   IfStmt
  \brief   Definition of atributes and methods of IfStmt class
  \note    IfStmt Class publicly inherits from Statement class 
       and adds its own print and evaluate functions
*/
class IfStmt : public Statement 
{
 private:
  LogicExpNode *_cond; //!< Condicion of the if statement
  std::list<Statement *> *_stmts1;  //!< List of statements
  std::list<Statement *> *_stmts2;  //!< List of statements

  public:
/*!   
  \brief Constructor of Single IfStmt (without alternative)
  \param condition: LogicExpNode of the condition
  \param statement1: Statement of the consequent
  \post  A new IfStmt is created with the parameters
*/
  IfStmt(LogicExpNode *condition, std::list<Statement *> *stmtList1)
  {
    this->_cond = condition;
    this->_stmts1 = stmtList1;
    this->_stmts2 = NULL;
  }


/*!   
  \brief Constructor of Compound IfStmt (with alternative)
  \param condition: LogicExpNode of the condition
  \param statement1: Statement of the consequent
  \param statement2: Statement of the alternative
  \post  A new IfStmt is created with the parameters
*/
  IfStmt(LogicExpNode *condition, std::list<Statement *> *stmtList1, std::list<Statement *> *stmtList2)
  {
    this->_cond = condition;
    this->_stmts1 = stmtList1;
    this->_stmts2 = stmtList2;
  }


/*!
  \brief   Print the IfStmt
  \return  void
  \sa    evaluate
*/
  void print();

/*! 
  \brief   Evaluate the IfStmt
  \return  void
  \sa    print
*/
  void evaluate();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// NEW in example 17

/*! 
	\class   WhileStmt
	\brief   Definition of atributes and methods of WhileStmt class
	\note    WhileStmt Class publicly inherits from Statement class 
				and adds its own print and evaluate functions
*/
class WhileStmt : public Statement 
{
private:
	LogicExpNode *_cond; //!< Condicion of the while statement
	std::list<Statement *> *_stmts; //!< Statement of the body of the while loop

public:
	/*!   
		\brief Constructor of  WhileStmt
		\param condition: LogicExpNode of the condition
		\param statement: Statement of the body of the loop 
		\post  A new WhileStmt is created with the parameters
	*/
	WhileStmt(LogicExpNode *condition, std::list<Statement *> *stmtList)
	{
		this->_cond = condition;
		this->_stmts = stmtList;
	}


	/*!
		\brief   Print the WhileStmt
		\return  void
		\sa    evaluate
	*/
	void print();

	/*! 
		\brief   Evaluate the WhileStmt
		\return  void
		\sa    print
	*/
	void evaluate();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// NEW in IPE

/*! 
  \class   RepeatStmt
  \brief   Definition of atributes and methods of RepeatStmt class
  \note    RepeatStmt Class publicly inherits from Statement class 
       and adds its own print and evaluate functions
*/
class RepeatStmt : public Statement 
{
 private:
  LogicExpNode *_cond; //!< Condicion of the while statement
  std::list<Statement *> *_stmts; //!< Statement of the body of the while loop

  public:
/*!   
  \brief Constructor of  RepeatStmt
  \param condition: LogicExpNode of the condition
  \param statement: Statement of the body of the loop 
  \post  A new RepeatStmt is created with the parameters
*/
  RepeatStmt(LogicExpNode *condition, std::list<Statement *> *stmtList)
  {
    this->_cond = condition;
    this->_stmts = stmtList;
  }


/*!
  \brief   Print the RepeatStmt
  \return  void
  \sa    evaluate
*/
  void print();

/*! 
  \brief   Evaluate the RepeatStmt
  \return  void
  \sa    print
*/
  void evaluate();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// NEW in IPE

/*!	
  \class   ForStmt
  \brief   Definition of atributes and methods of ForStmt class
  \note    ForStmt Class publicly inherits from Statement class 
		   and adds its own print and evaluate functions
*/
class ForStmt : public Statement 
{
private:
	
	std::string _id;    //!< Name of the variable of the assignment statement

	NumericExpNode *_exp1; //!< Desde
	NumericExpNode *_exp2; //!< Hasta
	NumericExpNode *_exp3; //!< Paso

	std::list<Statement *> *_stmts; //!< Statement of the body of the while loop

public:
	/*!		
		\brief Constructor of  ForStmt
		\param condition: NumericExpNode of the condition
		\param statement: Statement of the body of the loop 
		\post  A new ForStmt is created with the parameters
	*/
  	ForStmt(std::string id, NumericExpNode * desde, NumericExpNode * hasta, NumericExpNode * paso, std::list<Statement *> *stmtList)
	{
		this->_id = id;

		this->_exp1 = desde;
		this->_exp2 = hasta;
		this->_exp3 = paso;

		this->_stmts = stmtList;
	}

	ForStmt(std::string id, NumericExpNode * desde, NumericExpNode * hasta, std::list<Statement *> *stmtList)
	{
		this->_id = id;

		this->_exp1 = desde;
		this->_exp2 = hasta;
		this->_exp3 = NULL;

		this->_stmts = stmtList;
	}


/*!
	\brief   Print the ForStmt
	\return  void
	\sa		 evaluate
*/
  void print();

/*!	
	\brief   Evaluate the ForStmt
	\return  void
	\sa		 print
*/
  void evaluate();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// NEW in example 17

/*! 
	\class   SwitchStmt
	\brief   Definition of atributes and methods of SwitchStmt class
	\note    SwitchStmt Class publicly inherits from Statement class and adds its own print and evaluate functions
*/
class SwitchStmt : public Statement 
{
private:
	ExpNode *_exp; //!< Expression of the switch statement

	NumericExpNode *_numeric_exp; //!< Expression of the switch statement
	AlphanumericExpNode *_alphanumeric_exp; //!< Alphanumeric Expression of the switch statement

	std::list<Statement *> *_stmts; //!< Statement of the body of the switch statement

public:
	
	/*!   
		\brief Constructor of  SwitchStmt
		\param expression: ExpNode of the expression
		\param statement: Statement of the body of the loop 
		\post  A new SwitchStmt is created with the parameters
	*/
	SwitchStmt(ExpNode *expression, std::list<Statement *> *stmtList)
	{
		this->_exp = expression;
		
		if(_exp->isAlphanumeric())
			_numeric_exp = (NumericExpNode *) _exp;
		else
			_alphanumeric_exp = (AlphanumericExpNode *) _alphanumeric_exp;

		this->_stmts = stmtList;
	}


	/*!
		\brief   Print the SwitchStmt
		\return  void
		\sa    evaluate
	*/
	void print();

	/*! 
		\brief   Evaluate the SwitchStmt
		\return  void
		\sa    print
	*/
	void evaluate();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// NEW in example 17

/*!	
  \class   BlockStmt
  \brief   Definition of atributes and methods of BlockStmt class
  \note    BlockStmt Class publicly inherits from Statement class 
		   and adds its own print and evaluate functions
*/
class BlockStmt : public Statement 
{
 private:
   std::list<Statement *> *_stmts;  //!< List of statements

  public:
/*!		
	\brief Constructor of  WhileStmt
	\param stmtList: list of Statement
	\post  A new BlockStmt is created with the parameters
*/
  BlockStmt(std::list<Statement *> *stmtList): _stmts(stmtList)
	{
		// Empty
	}


/*!
	\brief   Print the BlockStmt
	\return  void
	\sa		 evaluate
*/
  void print();

/*!	
	\brief   Evaluate the BlockStmt
	\return  void
	\sa		 print
*/
  void evaluate();
};



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   AST
  \brief   Definition of atributes and methods of AST class
*/
class AST {
 private:
  std::list<Statement *> *stmts;  //!< List of statements

 public:

/*!		
	\brief Constructor of PrintStmt 
	\param stmtList: pointer to a list of pointers to Statement
	\post  A new PrintStmt is created with the parameter
*/
  AST(std::list<Statement *> *stmtList): stmts(stmtList)
	{
		// Empty
	}

/*!
	\brief   print the AST
	\return  void
	\sa		 evaluate
*/
  void print();

/*!	
	\brief   evaluate the AST
	\return  double
	\sa		 print
*/
  void evaluate();
};

// End of name space lp
}



// End of _AST_HPP_
#endif




