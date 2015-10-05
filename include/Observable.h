#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include <Observer.h>
#include <list>

using namespace std;

class Observable
{
	public:
		void attach(Observer* observer);
		void notify();
	private:
		list<Observer*> observers;
};

#endif // OBSERVABLE_H
