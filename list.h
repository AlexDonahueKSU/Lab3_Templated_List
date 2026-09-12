// node class tempate used to contruct lists 
// Alex Donahue
// 9/12/26 
#include <iostream>
#include <stdexcept>
using namespace std;
#ifndef LIST_H_ 
#define LIST_H_ 

// the pointer part of every list is the same 
// lists differ by data part 
template <typename T> 
class node
{ 
	public: 
	node(): next_(nullptr) {} 
	
	// functions can be inlined 
	T getData()const
	{
		return data_;
	} 
	
	void setData(const T& data)
	{
		data_=data;
	} 

	// or can be defined outside 
	node* getNext() const; 
	void setNext(node *const); 

	private: 
	T data_; 
	node *next_; 
}; 

// Member functions for node 
template <typename T>
node<T>* node<T>::getNext() const
{ 
	return next_; 
} 

template <typename T>
void node<T>::setNext(node<T> *const next)
{ 
	next_ = next; 
} 


template <typename T>
class Collection
{
public:
    Collection() : head_(nullptr), tail_(nullptr) {}

    ~Collection()
    {
        while (head_ != nullptr)
        {
            node<T>* oldHead = head_;
            head_ = head_->getNext();
            delete oldHead;
        }
    }

    void addItem(const T& item)
    {
        node<T>* newNode = new node<T>;
        newNode->setData(item);

        if (head_ == nullptr)
        {
            head_ = newNode;
            tail_ = newNode;
        }
        else
        {
            tail_->setNext(newNode);
            tail_ = newNode;
        }
    }

    void removeItem(const T& item)
    {
        node<T>* current = head_;
        node<T>* previous = nullptr;

        while (current != nullptr)
        {
            if (current->getData() == item)
            {
                if (previous == nullptr)
                    head_ = current->getNext();
                else
                    previous->setNext(current->getNext());

                if (current == tail_)
                    tail_ = previous;

                delete current;
                return;
            }

            previous = current;
            current = current->getNext();
        }
    }

    void printCollection() const
    {
        for (node<T>* current = head_;
             current != nullptr;
             current = current->getNext())
        {
            cout << current->getData() << " ";
        }

        cout << endl;
    }

    T& lastItem()
    {
        if (tail_ == nullptr)
            throw std::out_of_range("Collection is empty");

        return tail_->getData();
    }

private:
    node<T>* head_;
    node<T>* tail_;
};

#endif // LIST_H_ 
