#include "stdafx.h"

#include <iostream>
#include <cstdio>
using namespace std;

/* This is the node of our linked list */
template <class T>
class ListItem
{
private:
	T* item;
	ListItem<T>* prev;
	ListItem<T>* next;
public:
	ListItem<T>(T* item);
	ListItem<T>* getPrev();
	void setPrev(ListItem<T>* prev);
	ListItem<T>* getNext();
	void setNext(ListItem<T>* next);
	T* getItem();
	void setItem(T* prev);
};

/* This is our doubly linked list */
template <class T>
class LinkedList
{
private:
	ListItem<T>* first; // point to first item
	ListItem<T>* last; // point to last item
public:
	LinkedList<T>();
	// functions to find data in the list
	// please note that T must properly implement/override operator = (equal)
	// in order for these functions  to work
	ListItem<T>* Find(T*);
	ListItem<T>* Find(T);
	void Insert(T*);
	void Insert(T);
	// Delete() can only work if its input is an actual node of this list, or null.
	// So we should only pass result of Find() into this function.
	void Delete(ListItem<T>*);
	T Maximum();
	T Minimum();
	// print the entire list, for testing purpose
	void Print(ListItem<T>*);
};

/* Main function to test our LinkedList */
int main()
{
	LinkedList<int> list;

	cout << "Insert(1)" << endl;
	list.Insert(1);
	list.Print(nullptr);

	cout << "Find(1)" << endl;
	ListItem<int>* r1 = list.Find(1);
	list.Print(r1);
	cout << "Delete the item found above" << endl;
	list.Delete(r1);
	list.Print(nullptr);

	cout << "Insert(2)" << endl;
	list.Insert(2);
	list.Print(nullptr);
	cout << "Insert(4)" << endl;
	list.Insert(4);
	list.Print(nullptr);
	cout << "Insert(3)" << endl;
	list.Insert(3);
	list.Print(nullptr);
	cout << "Maximum: " << list.Maximum() << endl;
	cout << "Minimum: " << list.Minimum() << endl;

	cout << "Find(1), not found" << endl;
	r1 = list.Find(1);
	list.Print(r1);
	cout << "Find(5), not found" << endl;
	ListItem<int>* r2 = list.Find(5);
	list.Print(r2);
	cout << "Find(4)" << endl;
	ListItem<int>* r3 = list.Find(4);
	list.Print(r3);

	cout << "Delete(1)" << endl;
	list.Delete(r1);
	list.Print(nullptr);
	cout << "Delete(4)" << endl;
	list.Delete(r3);
	list.Print(nullptr);
	cout << "Maximum: " << list.Maximum() << endl;
	cout << "Minimum: " << list.Minimum() << endl;

	cout << "Find(4), not found" << endl;
	r3 = list.Find(4);
	list.Print(r3);

	getchar();
    return 0;
}

/*********************************/
/* ListItem function declaration */
/*********************************/
template <class T>
ListItem<T>::ListItem<T>(T* item)
{
	this->item = item;
	this->next = nullptr;
	this->prev = nullptr;
}

template <class T>
ListItem<T>* ListItem<T>::getPrev()
{
	return this->prev;
}

template <class T>
void ListItem<T>::setPrev(ListItem<T>* prev)
{
	this->prev = prev;
}

template <class T>
ListItem<T>* ListItem<T>::getNext()
{
	return this->next;
}

template <class T>
void ListItem<T>::setNext(ListItem<T>* next)
{
	this->next = next;
}

template <class T>
T* ListItem<T>::getItem()
{
	return this->item;
}

template <class T>
void ListItem<T>::setItem(T* item)
{
	this->item = item;
}

/***********************************/
/* LinkedList function declaration */
/***********************************/
template <class T>
LinkedList<T>::LinkedList<T>()
{
	// remember to initialize our pointer
	this->first = nullptr;
	this->last = nullptr;
}

template <class T>
ListItem<T>* LinkedList<T>::Find(T* data)
{
	// start with the first item in the list
	// please note that it can be null
	ListItem<T>* temp = this->first;
	// loop through the list using next pointer
	while (temp != nullptr && *(temp->getItem()) != *data)
	{
		temp = temp->getNext();
	}
	// if temp is null here, the data is not in the list
	return temp;
}

template <class T>
ListItem<T>* LinkedList<T>::Find(T data)
{
	return this->Find(&data);
}

template <class T>
void LinkedList<T>::Insert(T* data)
{
	if (this->first == nullptr)
	{
		// the list is empty
		this->first = new ListItem<T>(data);
		this->last = this->first;
	}
	else
	{
		// create new item
		ListItem<T>* newItem = new ListItem<T>(data);
		// point next pointer of current last item to the new item
		this->last->setNext(newItem);
		// point prev pointer of the new item to current last item
		newItem->setPrev(this->last);
		// move last pointer to the new item
		this->last = newItem;
	}
}

template <class T>
void LinkedList<T>::Insert(T data)
{
	T* dataPtr = new T(data);
	this->Insert(dataPtr);
}

template <class T>
void LinkedList<T>::Delete(ListItem<T>* node)
{
	// the node returned from Find() can be null
	if (node != nullptr)
	{
		ListItem<T>* prev = node->getPrev();
		ListItem<T>* next = node->getNext();

		if (prev == nullptr && next == nullptr)
		{
			// the node is the only one in the list
			this->first = this->last = nullptr;
		}
		else if (prev == nullptr)
		{
			// the node is the first one
			// point first pointer to next node
			this->first = this->first->getNext();
			// clear prev pointer of the next node (which is now the first one)
			this->first->setPrev(nullptr);
		}
		else if (next == nullptr)
		{
			// the node is the last one
			// point last pointer to previous node
			this->last = this->last->getPrev();
			// clear next pointer of the previous node (which is now the last one)
			this->last->setNext(nullptr);
		}
		else
		{
			// the node is in the middle of the list
			// point the next node and the previous node toward each other
			next->setPrev(prev);
			prev->setNext(next);
		}
	}
}

template <class T>
T LinkedList<T>::Minimum()
{
	T min;
	ListItem<T>* temp = this->first;
	if (temp != nullptr)
	{
		min = *(temp->getItem());
		temp = temp->getNext();
	}
	// loop through the list using next pointer
	while (temp != nullptr)
	{
		if (min > *(temp->getItem()))
		{
			min = *(temp->getItem());
		}
		// move to next node
		temp = temp->getNext();
	}
	return min;
}

template <class T>
T LinkedList<T>::Maximum()
{
	T max;
	ListItem<T>* temp = this->first;
	if (temp != nullptr)
	{
		max = *(temp->getItem());
		temp = temp->getNext();
	}
	// loop through the list using next pointer
	while (temp != nullptr)
	{
		if (max < *(temp->getItem()))
		{
			max = *(temp->getItem());
		}
		// move to next node
		temp = temp->getNext();
	}
	return max;
}

template <class T>
void LinkedList<T>::Print(ListItem<T>* anchor)
{
	cout << "< ";
	// start with the first item in the list
	// please note that it can be null
	ListItem<T>* temp = this->first;
	// loop through the list using next pointer
	while (temp != nullptr)
	{
		if (temp == anchor)
		{
			// hightlight the anchor
			cout << "(" << *(temp->getItem()) << ") ";
		}
		else
		{
			cout << *(temp->getItem()) << " ";
		}
		// move to next node
		temp = temp->getNext();
	}
	cout << ">" << endl;
}
