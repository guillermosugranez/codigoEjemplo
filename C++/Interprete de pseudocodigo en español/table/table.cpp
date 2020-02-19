/*!	

	\file   table.cpp
	\brief   Code of some functions of Table class
	\author  
	\date    2017-12-13
	\version 1.0
*/

#include <map>

#include <cassert>

#include "tableInterface.hpp"

#include "table.hpp"

#include <iostream>

using namespace std;



bool lp::Table::lookupSymbol(const string & name) const 
{		
	if (this->_table.find(name) !=  this->_table.end())
		return true;
	else
		return false;
}


void lp::Table::showTable()
{
	map<string, Symbol *>::iterator iter;

	
	for(iter = this->_table.begin(); iter != this->_table.end(); iter++)
	{
		cout << "Clave: " << iter->first << "\t Valor: "<< iter->second << endl;
	}
	
}


lp::Symbol * lp::Table::getSymbol(const string & name)
{
 #ifndef NDEBUG
   // Precondition
   assert (this->lookupSymbol(name) == true);
 #endif //NDEBUG

	return	this->_table[name];
}



void lp::Table::installSymbol(Symbol * s)
{
 #ifndef NDEBUG
  // Precondition
   assert (this->lookupSymbol(s->getName()) == false);
 #endif //NDEBUG

   // The pointer to symbol is inserted in the map
	this->_table[s->getName()] = s;

 #ifndef NDEBUG
  // Postcondition
   assert (this->lookupSymbol(s->getName()) == true);
 #endif //NDEBUG

}


