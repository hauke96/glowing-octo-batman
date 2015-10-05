#include <Observable.h>
#include <iostream>

using namespace std;

/**
 * Attaches an observer to the list of all observers of this class.
 * @param observer The observer
 */
void Observable::attach(Observer* observer)
{
	observers.push_back(observer);
}

/**
 * Notifies all observers about a change.
 */
void Observable::notify()
{
	list<Observer*>::iterator iter = observers.begin();
	for(; iter != observers.end(); iter++)
	{
		(*iter)->notified();
	}
}
