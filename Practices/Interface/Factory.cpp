//
//  Factory.cpp
//  
//  Modified by 罗铮 on 05/13/14.
//  
//  http://sourcemaking.com/design_patterns/factory_method
//  http://sourcemaking.com/design_patterns/factory_method/cpp/1

/*
	Intent

	Define an interface for creating an object, 
	but let subclasses decide which class to instantiate. 
	Factory Method lets a class defer instantiation to subclasses.
	
	Defining a "virtual" constructor.
	
	The new operator considered harmful.
*/

/*
	Before

	The architect has done an admirable job of decoupling the client from 
	Stooge concrete derived classes, and, exercising polymorphism. But there 
	remains coupling where instances are actually created. If we design an 
	"extra level of indirection" (a "factory method") and have clients use 
	it (instead of "new"), then the last bit of coupling goes away. The 
	"factory method" (aka "virtual constructor") can be defined in the 
	Stooge base class, or, in a separate "factory" class. Note that main() 
	is no longer dependent on Stooge derived classes.
*/

/*
	After

	A factory method is a static method of a class that returns an object of 
	that class' type. But unlike a constructor, the actual object it returns 
	might be an instance of a subclass. Another advantage of a factory 
	method is that it can return existing instances multiple times.
*/

#include <iostream>
#include <vector>

using namespace std;

class Stooge
{
public:
	// Factory Method
    static Stooge *make_stooge(int choice);
	virtual void slap_stick() = 0;
	virtual ~Stooge() {};
};

class Larry: public Stooge
{
public:
	void slap_stick()
	{
	    cout << "Larry: poke eyes\n";
	}
	virtual ~Larry() {};
};
class Moe: public Stooge
{
public:
	void slap_stick()
	{
	    cout << "Moe: slap head\n";
	}
	virtual ~Moe() {};
};
class Curly: public Stooge
{
 public:
	void slap_stick()
	{
	    cout << "Curly: suffer abuse\n";
	}
	virtual ~Curly() {};
};

Stooge *Stooge::make_stooge(int choice)
{
	if (choice == 1)
		return new Larry;
	else if (choice == 2)
		return new Moe;
	else
		return new Curly;
}


int main()
{
	vector<Stooge*> roles;
	int choice;

	while (true)
	{
		cout << "Larry(1) Moe(2) Curly(3) Go(0): ";
		cin >> choice;
		if (choice == 0)
			break;
		/*
		else if (choice == 1)
			roles.push_back(new Larry);
		else if (choice == 2)
			roles.push_back(new Moe);
		else
			roles.push_back(new Curly);
		*/
		roles.push_back(Stooge::make_stooge(choice));
	}
	for (int i = 0; i < roles.size(); i++)
		roles[i]->slap_stick();
	for (int i = 0; i < roles.size(); i++)
		delete roles[i];

	return 0;
}
