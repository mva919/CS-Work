/*
Name: Marcos Villanueva, 5006480097, CS 202 - 1002, ASSIGNMENT_6
Description: This file is the implementation of the list class. The list
class is similar to the vector class where it keeps track of the count,
size, and we can add elements. When the item count is larger then the 
size of the list, a new bigger list is allocated and the elements are
copied over. 
Input: File name of the map to read and use
Output: Steps of the map to reach the treasure
*/
#ifndef LIST_H
#define LIST_H true

#include <iostream>
using namespace std;

/* List class used to store some generic type. Stores all items in the
order. That they are added an allows for them to be accessed like an
array. Functionally similar to a C++ vector. */
template <class T>
class List{
	T* contents; //Pointer to the array
	int size; //Size of the array 
	int count; //How many items are in the array
	//How much to resize the array by when expanding
	const int RESIZE_AMOUNT = 4; 

public:
	int getCount() const { return count; }
	void addElement(T new_element);

	//Constructors
	List() { size = count = 0; contents = nullptr; }
	List(int start_size) { size = start_size; count = 0; 
	contents = new T[start_size]; }
	List(const List& other);
	~List();

	//Operator overloads
	//Indexing overload lets this be used with array syntax
	T& operator [] (int index) const { return contents[index]; } 
	void operator = (List<T> other);
};

//TODO: Finish List functions

/**/
template <class T>
void List<T>::addElement(T new_element){
	//Add an element to the dynamic array
	//If the array is out of space or does not exist (is null)
//Make a new array, copy over any old elements, and update the pointer
	//Be sure to avoid memory leaks
	
	//if the array is empty creating an array
	if(!contents){
		contents = new T[RESIZE_AMOUNT];
		size+=RESIZE_AMOUNT;
		contents[count++] = new_element;
		return;
	}

	//checking size before adding
	if(count == size){
		//making a new bigger array
		T *temp = new T[size + RESIZE_AMOUNT];
		//deep copying elements
		for(int i=0; i<size; i++)
			temp[i] = contents[i];
		//updating the size
		size+=RESIZE_AMOUNT;
		//deleting old array
		delete [] contents;
		//assigning new array
		contents = temp;
		//making temp null
		temp = NULL;
	}
	//Then add the new_element to the end
	contents[count++] = new_element;
}

/**/
template <class T>
List<T>::~List(){
	//Deallocate the contents of the array if they exist
	//and then mark the contents as null
	if(contents){
		delete [] contents;
		contents = NULL;
	}
}

/**/
template <class T>
List<T>::List(const List& other){
	//Copy the contents of the other list to this one
	//Also set the count and size members
	//Don't forget to allocate a new array

	//Remember that we want a deep copy, so copying pointers
	//directly will not work and is why we must explicitly write 
	//an = overload and a copy contructor

	//setting the count and size
	count = other.count;
	size = other.size;
	contents = new T[size];
	//copying the contents array
	for(int i=0; i<count; i++)
		contents[i] = other.contents[i];
}

template <class T>
void List<T>::operator = (List<T> other){
	//Make a deep copy of the other list and set it to this one
	//Essentially the same code as the copy constructor
	//Consider deleting any old array to avoid memory leaks
	//setting the count and size
	~List<T>();
	
	count = other.count;
	size = other.size;
	contents = new T[size];
	//copying the contents array
	for(int i=0; i<count; i++)
		contents[i] = other.contents[i];
}

#endif
