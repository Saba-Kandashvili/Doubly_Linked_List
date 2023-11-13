#pragma once
#include <iostream>
#include <stdexcept>
#include <string>
using std::cout;
using std::cerr;
using std::endl;
using std::nothrow;
using std::string;

template <typename T>
struct Node
{
	Node* next;
	Node* prev;
	T data;
};

template <typename T>
class LinkedList
{
private:
	Node<T>* head;
	Node<T>* tail;

public:
	int size;

	LinkedList() : head(nullptr), tail(nullptr), size(0) {}


	~LinkedList() // destructor
	{
		Node<T>* current = head;
		while (current != nullptr) // untill it reaches the end where 'next' is a nullptr
		{
			Node<T>* nextNode = current->next; // next node
			delete current; // free the current
			current = nextNode; // move onto the next node
		}
	}


	LinkedList(const LinkedList& list) // copy constructor
	{
		head = nullptr;
		tail = nullptr;
		Node<T>* temp = list.head;
		while (temp != nullptr) // iterate untill the end where 'next' is nullptr
		{
			add_at_beginning(temp->data); // copy over every node
			temp = temp->next; // move onto the next node
		}
	}

	template <typename T>
	void add_at_beginning(const T& _data) // add an element at the start of the linked list
	{
		Node<T>* newNode = new(nothrow) Node<T>;
		if (newNode == nullptr) // in the case of a heap overflow
		{
			cerr << "Heap Overflow." << endl;
			throw std::runtime_error("Heap Overflow");
		}

		newNode->data = _data;
		newNode->prev = nullptr;
		newNode->next = head;

		if (head != nullptr) // if the head was already storing a node adress
			head->prev = newNode; // old head node becomes the second elemnt and 'prev' points to the new head node

		head = newNode; // head saves the new starting node's adress

		if (tail == nullptr) // if the list was empty both head and tail point to new node
			tail = newNode;

		size++;
	}

	template <typename T>
	void add_at_end(const T& _data) // add an element at the end of the linked list
	{
		Node<T>* newNode = new(nothrow) Node<T>;
		if (newNode == nullptr) // in the case of a heap overflow
		{
			cerr << "Heap Overflow." << endl;
			throw std::runtime_error("Heap Overflow");
		}

		newNode->data = _data;
		newNode->next = nullptr; // it's the last element

		if (head == nullptr) // if the list was empty both head and tail point to new node
		{
			newNode->prev = nullptr;
			head = newNode;
			tail = newNode;
		}
		else // if the list already had elements
		{
			newNode->prev = tail;  // prev* of the newNode is the previous last element of the list
			tail->next = newNode; // newNode becomes the last element
			tail = newNode; // tail points to the newNode
		}

		size++;
	}

	template <typename T>
	void add_after_index(const T& _data, const int& index) // add an element after the provided index-th element
	{
		if (size == -1)
		{
			cerr << "The List Was Empty. Adding The New Element at The Start." << endl;
			add_at_beginning(_data);
			return;
		}

		if (index < 0 || index >= size) // if index isn't appropriate
		{
			cerr << "Index Out of Bounds." << endl;
			throw std::runtime_error("Index Out of Bounds");
		}

		if (index == 0) { add_at_beginning(_data); return; } // insert at the begining (technically 0th element means a new element)
		if (index == size - 1) { add_at_end(_data); return; } // insert after the last element

		Node<T>* newNode = new(nothrow) Node<T>;
		if (newNode == nullptr) // in the case of a heap overflow
		{
			cerr << "Heap Overflow." << endl;
			throw std::runtime_error("Heap Overflow");
		}

		Node<T>* temp;
		if (index < size / 2) // starting at head because it's closer
		{
			temp = head;
			for (int i = 0; i < index; i++)
			{
				temp = temp->next; // find the element at index
			}
		}
		else // staring at tail because it's close
		{
			temp = tail;
			for (int i = size - 1; i > index; i--)
			{
				temp = temp->prev; // find the element at index
			}
		}

		newNode->data = _data;
		newNode->prev = temp;
		newNode->next = temp->next; // put the newNode inbetween the index-th and index+1-th nodes and correctly re-assing all the pointers
		temp->next->prev = newNode;
		temp->next = newNode;

		size++;
	}

	template <typename T>
	T pop_at_beginning() // return the data and delete the first element
	{
		if (size == 0)
		{
			cerr << "Can Not Remove Element From an Empty List." << endl;
			throw std::runtime_error("Can Not Remove Element From an Empty List");
		}

		Node<T>* temp = head;
		T data = temp->data; // get the data to return
		head = head->next; // head moves forward

		if (head != nullptr)
			head->prev = nullptr;
		else // if the list only had a single element
			tail = nullptr; // head = tail = nullptr

		delete temp; // free the memory and pacify the pointers
		temp = nullptr;
		size--; // decrease the size of the list
		return data; // return the data of the deleted element
	}

	template <typename T>
	T pop_at_end() // return the data and delete the last element
	{
		if (size == 0)
		{
			cerr << "Can Not Remove Element From an Empty List." << endl;
			throw std::runtime_error("Can Not Remove Element From an Empty List");
		}

		Node<T>* temp = tail;
		T data = tail->data; // get the data to return
		tail = tail->prev; // tail moves back

		if (tail != nullptr)
			tail->next = nullptr;
		else // if the list only had a single element
			head = nullptr; // head = tail = nullptr

		delete temp; // free the memory and pacify the pointers
		temp = nullptr;
		size--; // decrease the size of the list
		return data; // return the data of the deleted element
	}

	template <typename T>
	T pop_at_index(const int& index) // return the data and delete the provided index-th element
	{
		if (size == 0)
		{
			cerr << "Can Not Remove Element From an Empty List." << endl;
			throw std::runtime_error("Can Not Remove Element From an Empty List");
		}

		if (index < 0 || index >= size)
		{
			cerr << "Index Out of Bounds." << endl;
			throw std::runtime_error("Index Out of Bounds");
		}

		if (index == 0) return pop_at_beginning(); // remove the first element
		if (index == size - 1) return pop_at_end(); // remove the last element

		Node<T>* temp;
		if (index < size / 2) // starting at head because it's closer
		{
			temp = head;
			for (int i = 0; i < index; i++)
				temp = temp->next; // find the element at index
		}
		else // starting at tail becaise it's closer
		{
			temp = tail;
			for (int i = size - 1; i > index; i--)
				temp = temp->prev; // find the element at index
		}

		T data = temp->data; // get the data to return
		temp->prev->next = temp->next;
		temp->next->prev = temp->prev; // remove the index-th element and re-assign the pointers

		delete temp; // free the memory and pacify the pointers
		temp = nullptr;
		size--; // decrease the size of the list
		return data; // return the data of the deleted element
	}

	template <typename T>
	void display() const // neatly display data of the nodes
	{
		Node<T>* temp = head;
		if (temp == nullptr)
		{
			cout << "List Is Empty" << endl;
			return;
		}

		for (size_t i = 0; i < size; i++)
		{
			cout << temp->data << " ";
			temp = temp->next;
		} cout << endl;
	}

	template <typename T>
	friend std::ostream& operator<<(std::ostream& out, const LinkedList<T>& that) // detailed information for debugging
	{
		Node<T>* temp = that.head;
		int index = 0;
		out << "|Size: " << that.size << "|\t";
		while (temp != nullptr) // use while becausei it's foolproof in case of size being messed up
		{
			out << temp->data << '[' << index << ']' << '\t'; // show the data + it's 'index'
			temp = temp->next;
			index++;
		} out << endl;
		return out;
	}
};