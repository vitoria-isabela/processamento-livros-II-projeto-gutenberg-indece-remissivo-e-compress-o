// classe nó auxiliar

#ifndef LIST_H
#define LIST_H

#include <cstddef>
#include <iostream>
#include <fstream>
#include "config.h"

using namespace std;

template <typename T>
class Node
{
private:
	T data;
	Node<T> *next;
	T *data_ptr;

	template <typename U>
	friend class LinkedList;

public:
	Node()
	{
		this->next = nullptr;
		this->data_ptr = &data;
	}

	T getData()
	{
		return this->data;
	}

	T *getDataPtr()
	{
		return this->data_ptr;
	}

	Node<T> *getNext()
	{
		return this->next;
	}

	~Node()
	{
		this->next = nullptr;
	}
};

template <typename T>
class LinkedList
{
private:
	Node<T> *head;

public:
    //construtor
	LinkedList();
	//destrutor
	~LinkedList();
	// verifica se lista está vazia
	bool empty();
	// esvazia a lista
	void clear();
	// adiciona no final da lista
	void add(T item);
	// adiciona no início
	void addFront(T item);
	// adiciona no índice
	void add(T item, int index);
	// tamanho
	int length();
	// Imprime Lista
	void printList(string word);
	// remove no final
	void remove();
	// remove no indice
	void remove(int index);
	// remove na frente
	void removeFront();
	// remove item
	void remove_item(T *item);
	// retorna dado no indece
	T get(int index);
	// Retorna get head
	Node<T> *getHead();
	// retorna dando do proximo
	T *getNext(int index);

	// vector<T> *ListToVector();
};

template <typename T>
LinkedList<T>::LinkedList()
{
	this->head = nullptr;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
	clear();
}

template <typename T>
bool LinkedList<T>::empty()
{
	return (head == NULL);
}

template <typename T>
void LinkedList<T>::add(T item)
{
	Node<T> *node = new Node<T>[1];
	node->data = item;
	if (head == nullptr)
	{
		head = node;
		return;
	}
	Node<T> *temp = head;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = node;
	
}

template <typename T>
Node<T> *LinkedList<T>::getHead()
{
	return this->head;
}

template <typename T>
void LinkedList<T>::addFront(T item)
{
	Node<T> *node = new Node<T>[1];
	node->data = item;
	if (head == NULL)
	{
		head = node;
		return;
	}
	node->next = head;
	head = node;
	
}

template <typename T>
void LinkedList<T>::add(T item, int index)
{
	if (index > length() || index < 0)
	{
		cout << "index out of bound !" << endl;
		return;
	}
	Node<T> *node = new Node<T>[1];
	node->data = item;
	int count = 0;
	Node<T> *temp = head;
	while (temp != NULL && count < index)
	{
		if (count == index - 1)
		{
			if (temp->next != NULL)
			{
				node->next = temp->next;
			}
			temp->next = node;
			break;
		}
		count++;
		temp = temp->next;
	}
}

template <typename T>
int LinkedList<T>::length()
{
	int len = 0;
	Node<T> *temp = head;
	while (temp != NULL)
	{
		len++;
		temp = temp->next;
	}
	return len;
}

template <typename T>
void LinkedList<T>::clear()
{
	while (!empty())
	{
	  removeFront();
	}
	
}

template <typename T>
void LinkedList<T>::printList( string word )
{
    fstream rindex;
    string dir = OUTPUT;
    string dir2 ="remissive_index.txt";
    dir = dir + dir2;
    rindex.open(dir, ios::out | ios::app );  
    
	
	if (head == NULL)
	{
		rindex << "linked list is empty" << endl;
		return;
	}
	rindex << "Palavra: " << word << endl;
	rindex << endl
		 << "----link list items------" << endl;
	Node<T> *temp = head;
	while (temp != NULL)
	{
		rindex << temp->data << " | ";
		temp = temp->next;
	}
	rindex << endl;
	rindex << "--------------------------" << endl;
}

template <typename T>
void LinkedList<T>::remove()
{
	if (head == NULL)
	{
		cout << "linked list is empty !" << endl;
		return;
	}
	if (head->next == NULL)
	{
		head = NULL;
		
		return;
	}

	Node<T> *temp = head;
	while (temp != NULL)
	{
		if (temp->next->next == NULL)
		{
			temp->next = NULL;
			
			break;
		}
		temp = temp->next;
	}
}

template <typename T>
void LinkedList<T>::remove(int index)
{
	if (head == NULL)
	{
		cout << "linked list is empty !" << endl;
		return;
	}
	if (index >= length() || index < 0)
	{
		cout << "index out of bound !" << endl;
		return;
	}
	if (index == 0)
	{
		removeFront();
		cout << "item removed at index " << index << endl;
		return;
	}
	int count = 0;
	Node<T> *temp = head;
	while (temp != NULL)
	{
		if (count == index - 1)
		{
			temp->next = temp->next->next;
			cout << "item removed at index " << index << endl;
			break;
		}
		count++;
		temp = temp->next;
	}
}

template <typename T>
void LinkedList<T>::removeFront()
{
	if (head == NULL)
	{
		cout << "linked list is empty !" << endl;
		return;
	}
	head = head->next;
	
}

template <typename T>
void LinkedList<T>::remove_item(T *item)
{

	Node<T> *node = new Node<T>[1];
	node->data_ptr = item;

	Node<T> *temp = head;
	Node<T> *before_temp = nullptr;

	if (head == nullptr)
	{
		cout << "Linked list is empty" << endl;
		return;
	}

	if (head->data_ptr == node->data_ptr)
	{
		removeFront();
		return;
	}

	while (temp != nullptr)
	{
		if (temp->data_ptr == node->data_ptr)
		{
			before_temp->next = temp->next;
			return;
		}
		before_temp = temp;
		temp = temp->next;
	}
}

template <typename T>
T LinkedList<T>::get(int index)
{
	if (head == NULL)
	{
		cout << "linked list is empty !" << endl;
		head = nullptr;
	}

	if (index >= length() || index < 0)
	{
		cout << "index out of bound !" << endl;
		head = nullptr;
	}

	if (index == 0)
	{
		return head->data;
	}

	int count = 0;
	T res;

	Node<T> *temp = head;

	while (temp != NULL)
	{
		if (count++ == index)
		{
			res = temp->data;
			break;
		}
		temp = temp->next;
	}

	return res;
}

template <typename T>
T *LinkedList<T>::getNext(int index)
{
	if (head == NULL)
	{
		cout << "linked list is empty !" << endl;
		return NULL;
	}
	if (index >= length() || index < 0)
	{
		cout << "index out of bound !" << endl;
		return NULL;
	}
	if (index == 0)
	{
		return &head->data;
	}
	int count = 0;
	T *res;
	Node<T> *temp = head;
	while (temp != NULL)
	{
		if (count++ == index)
		{
			res = &temp->next->data;
			break;
		}
		temp = temp->next->next;
	}

	return res;
}

#endif /* LIST_H */