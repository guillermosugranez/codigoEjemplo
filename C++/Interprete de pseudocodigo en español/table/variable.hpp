/*!	
	\file    variable.hpp
	\brief   Declaration of Variable class
	\author  
	\date    2017-12-1
	\version 1.0
*/

#ifndef _VARIABLE_HPP_
#define _VARIABLE_HPP_

#include <iostream>
#include <stdlib.h>
#include <string>
#include <list>


// pow
#include <math.h>

#include "../ast/ast.hpp"

#include "../table/table.hpp"

// execerror
#include "../error/error.hpp"

// Macros for the screen
#include "../includes/macros.hpp"
#include "../includes/util.hpp"

#include "variable.hpp"
#include "../table/numericConstant.hpp"

#include "../table/builtinParameter0.hpp"
#include "../table/builtinParameter1.hpp"
#include "../table/builtinParameter2.hpp"

//
#include "../parser/ipe.tab.h"


/*!	
	\namespace lp
	\brief Name space for the subject Language Processors
*/
namespace lp{

/*!	
  \class   Value
  \brief   Definition of atributes and methods of Value class
*/
class Value
{
private:
	// atributos
	double _number;
	std::string _string;
	bool _bool;

public:

	// métodos
	double getNumber() const;
	std::string getString() const;
	bool getBool() const;

	void setNumber(const double &n);
	void setString(const std::string &s);
	void setBool(const bool &b);
};

/*!	
  \class     Variable
  \attention Abstrac class
  \brief     Definition of atributes and methods of Variable class
  \note      Variable Class publicly inherits from Symbol class
*/
class Variable:public lp::Symbol
{
/*!		
\name Protected atribute of Variable class
*/
	private:
		int		_type;	//!< \brief Type of the  Variable: UNDEFINED, NUMERICVAR, STRINGVAR
		Value	_value;	//!< \brief Value of the  Variable: string, double, bool

/*!		
\name Public methods of Variable class
*/
	public:

/*!	
	\name Constructors
*/
		
/*!		
	\brief Constructor with arguments with default values
	\note  Inline function that uses Symbol's constructor as members initializer
	\param name: name of the Variable
	\param token: token of the Variable
	\param type: type of the Variable
	\pre   None
	\post  A new Variable is created with the values of the parameters
	\sa   setName, setToken, setType
*/
	inline Variable(std::string name="", int token = 0, int type = 0): Symbol(name,token)
	{
		this->setType(type);
	}
		
/*!		
	\brief Copy constructor
	\note  Inline function
	\param s: object of Variable class
	\pre   None
	\post  A new Variable is created with the values of an existent Variable
	\sa    setName, setValue
*/
	inline Variable(const Variable & s)
	{
		// Inherited methods
		this->setName(s.getName());
		this->setToken(s.getToken());

		//  Own method
		this->setType(s.getType());
	}


/*!	
	\name Observer
*/

/*!
	\brief   Public method that returns the type of the Variable
	\note    Inline function
	\pre     None
	\post    None
	\return  int Type of the Variable
	\sa		 getName, getToken
*/
	inline int getType() const
	{
		return this->_type;
	}	


/*!	
	\name Modifier
*/


/*!	
	\brief   This functions modifies the token of the Variable
	\note    Función inline
	\param   type: new type of the Variable
	\pre     None
	\post    The type of the Variable is equal to the parameter 
	\return  void
	\sa 	 setName, setToken
*/
	inline void setType(int type) 
	{
	    this->_type = type;
	}

	/*!	
		\brief   This functions modifies the value of the Variable
		\param   type: new value
		\pre     None
		\post    The type of the Variable is equal to the parameter 
		\return  void
	*/
	void setValue(const double &value) 
	{
		this->_value.setNumber(value);
		this->_value.setString("");
		this->_value.setBool(0);

		setType(NUMERICVARIABLE);
	}

	void setValue(const std::string &value) 
	{
		this->_value.setNumber(0);
		this->_value.setString(value);
		this->_value.setBool(0);

		setType(ALPHANUMERICVARIABLE);
	}

	void setValue(const bool &value) 
	{
		this->_value.setNumber(0);
		this->_value.setString(0);
		this->_value.setBool(value);

		setType(NUMERICVARIABLE);
	}

	/*!
		\brief   Public method that returns the value of the Variable
		\pre     None
		\post    None
		\return  Value of the Variable
	*/
	inline double getNumber() const
	{
		return this->_value.getNumber();
	}

	/*!
		\brief   Public method that returns the value of the Variable
		\pre     None
		\post    None
		\return  Value of the Variable
	*/
	inline std::string getString() const
	{
		return this->_value.getString();
	}

	/*!
		\brief   Public method that returns the value of the Variable
		\pre     None
		\post    None
		\return  Value of the Variable
	*/
	inline bool getBool() const
	{
		return this->_value.getBool();
	}


/*!	
	\name Operator
*/
	
/*!		
	\brief  Assignment Operator
	\note   Virtual method: can be redefined in the heir class
	\param  v: objecto of Variable class
	\post   The atributes of this object are equal to the atributes of the parameter
	\return Reference to this object
*/
	virtual Variable &operator=(const Variable &v);
		

		
/*!	
	\name I/O Functions
*/
		

/*!		
	\brief Write a Variable
	\note  Virtual method: can be redefined in the heir class
	\pre   None
	\post  None
    \sa    read
*/
	virtual void write() const;


/*!		
	\brief   Read a Variable
	\note   Virtual method: can be redefined in the heir class
	\pre     None
	\post    The atributes of the Variable are modified with the read values
    \sa      writeS
*/
	virtual void read();

	
// End of Variable class
};

// End of name space lp
}

// End of _VARIABLE_HPP_
#endif
