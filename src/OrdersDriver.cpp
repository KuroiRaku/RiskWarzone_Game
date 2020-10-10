#define _DEBUG
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define new new( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif

#include <iostream>
#include <vector>
#include <string>
#include "Orders.h"

int main() {
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	std::cout << "-------- OrderList driver program: Let's create some orders! -------\n" << std::endl;

	//creating new OrderList
	OrderList oList;

	//adding orders to the list
	oList.addToList(new Deploy());
	oList.addToList(new Advance());
	oList.addToList(new Bomb());
	oList.addToList(new Blockade());
	oList.addToList(new Negotiate());
	oList.addToList(new Airlift());

	//displaying list
	std::cout << std::endl << oList;

	//making a copy of the previous list (copy constructor)
	std::cout << "----- Copying previous list with Copy Constructor: Constructor chain -----" << std::endl;
	OrderList listCopy = oList;
	std::cout << std::endl;

	//moving the orders in the list & displaying list again
	oList.move(0, 2);
	std::cout << oList << std::endl;

	//displaying previously copied list
	std::cout << "Displaying previously copied list, which has not changed." << std::endl;
	std::cout << listCopy << std::endl;

	//removing item 1 from the list & displaying list again
	std::cout << "-> Removing item 1 from the list <-" << std::endl;
	oList.remove(1);
	std::cout << oList << std::endl;

	//Displaying an order without executing it
	std::cout << "Displaying an order before it has been executed:" << std::endl;
	Deploy obj;
	std::cout << obj << std::endl << std::endl;

	//Displaying an order when its been executed
	std::cout << "Displaying an order after it has been executed:" << std::endl;
	obj.execute();
	std::cout << obj << std::endl;

	//making a copy of the list with assignment operator and displaying it
	std::cout << "----- Copying previous list with assignment operator: Constructor chain -----" << std::endl;
	OrderList assignCopy;
	assignCopy = oList;
	std::cout << std::endl << "Copied list:" << std::endl << assignCopy << std::endl;

	std::cout << "----- Destructor call stack below -----" << std::endl;

	return 0;
}