/*
* LinkedList.h
* Daniel Salazar
* 07/17/2016
* A container of items organized in ascending order
* ItemType can be char, int, float, or double
* Node<ItemType> is the List Element
* LinkedList<ItemType> is the collection of Nodes
*/
#include <cassert>		// assert
#include <iostream>		// cin, cout, endl, flush
// Abstract base classes
template<class ItemType>
class ListInterface
{
public:
	virtual void setEntry(int position, const ItemType& newEntry) = 0;
	virtual ItemType getEntry(int position) const = 0;
	virtual void insert(int position, const ItemType& newEntry) = 0;
	virtual bool remove(const ItemType & newEntry) = 0;
	virtual bool isEmpty() const = 0;
	virtual int getLength() const = 0;
	virtual void clear() = 0;
};
// A container class that holds a variable
template<class ItemType>
class Node
{
private:
	ItemType item;
	Node<ItemType>* next;
public:
	// Default Constructor
	Node();
	// item Copy Constructor
	Node(const ItemType& anItem);
	// item/next Copy Constructor
	Node(const ItemType& anItem, Node<ItemType>* nextNodePtr);
	// Sets Node's item
	void setItem(const ItemType& anItem);
	// Sets Node's nextPtr
	void setNext(Node<ItemType>* nextNodePtr);
	// Get Node's Item
	ItemType getItem() const;
	// Get Node's nextPtr
	Node<ItemType>* getNext() const;
};
// Initializes a new Node
template<class ItemType>
Node<ItemType>::Node() : next(nullptr)
{
}
// Copies anItem to this Node's item
template<class ItemType>
Node<ItemType>::Node(const ItemType& anItem) : item(anItem), next(nullptr)
{
}
// Copies anItem to this Node's item
// Copies nextNodePtr to this Node's next
template<class ItemType>
Node<ItemType>::Node(const ItemType& anItem, Node<ItemType>* nextNodePtr) :
	item(anItem), next(nextNodePtr)
{
}
// Replaces this Node's item with anItem
template<class ItemType>
void Node<ItemType>::setItem(const ItemType& anItem)
{
	item = anItem;
}
// Replaces this Node's next with nextNodePtr
template<class ItemType>
void Node<ItemType>::setNext(Node<ItemType>* nextNodePtr)
{
	next = nextNodePtr;
}
// Assists List with access to item
template<class ItemType>
ItemType Node<ItemType>::getItem() const
{
	return item;
}
// Assists List with access to next
template<class ItemType>
Node<ItemType>* Node<ItemType>::getNext() const
{
	return next;
}
// Linked List of Nodes
template<class ItemType>
class LinkedList : public ListInterface<ItemType>
{
private:
	// Points to nullptr/First Node
	Node<ItemType>* headPtr;
	// Count of Nodes
	int itemCount;
	// Prevents heap fragmentation
	static Node<ItemType>* free;
	// Iterator
	Node<ItemType>* trav_p;
	// Iterator flag
	bool TraverseOK;
	// Creates a new Node or pulls one from the free list
	Node<ItemType>* getListEl(void);
	// Get/Set Entry helper function: returns ptr to Node
	Node<ItemType>* getNodeAt(int position) const;
	// Print in descending order
	void printRevHelper(Node<ItemType>* curPtr) const;
	// Links a removed Node to Free List for reuse
	void freeListEl(Node<ItemType>* curPtr);
	// Recursively make a substring
	void substrHelper(Node<ItemType>* anEntry, LinkedList<ItemType>& aList, int len);
	// Returns a ptr to thisList's headPtr
	Node<ItemType>* getHeadPtr(void);
	// Modify ptr to a specific list
	void setHeadPtr(Node<ItemType>* newList);
	// Allows reverse to perform recursively
	Node<ItemType>* reverseHelper(Node<ItemType>* anEntry);
	// Appends rhs to lhs
	void appendHelper(Node<ItemType> *lhs, Node<ItemType> *rhs);
public:
	// Default constructor
	LinkedList();
	// List Copy Constructor
	LinkedList(const LinkedList<ItemType>& aList);
	// Assignment operator copies aList into thisList
	LinkedList<ItemType>& operator=(const LinkedList<ItemType>& aList);
	// Destructor
	virtual ~LinkedList();
	// Modify a specified Node's item
	void setEntry(int position, const ItemType& newEntry);
	// Increase or decrease itemCount manually
	void setLength(int n);
	// Get a specified Node's item
	ItemType getEntry(int position) const;
	// Get number of Nodes in List
	int getLength() const;
	// Sequential search for item
	bool isInList(const ItemType& anEntry);
	// Iterates first or next Node
	Node<ItemType>* traverse(bool first);
	// Inserts a Node into the specified position of thisList
	void insert(int position, const ItemType& newEntry);
	// Inserts a Node in ascending order
	void insertSorted(const ItemType& newEntry);
	// Inserts Node at the beginning of List
	void push(const ItemType& newEntry);
	// Removes a Node and returns to Free List
	bool remove(const ItemType & newEntry);
	// Removes first Node and returns to Free List
	bool pop();
	// Checks if itemCount is 0
	bool isEmpty() const;
	// Increase/decrease the number of Nodes in thisList
	void resize(int len, const ItemType& value);
	// Removes all Nodes in the List
	void clear(void);
	// Displays all Node's item to stdout
	void printList(int direction) const;
	// printList's direction variables
	static int Forward;
	static int Reverse;
	// Returns a newly constructed string object with its
	// value initialized to a copy of a substring of this object.
	LinkedList<ItemType> &subStr(int position, int len);
	// Appends aList to the end of thisList
	LinkedList<ItemType> &append(LinkedList<ItemType>& aList);
	// Reverses in place
	LinkedList<ItemType> &reverse(void);
	// Empties a list's contents
	void deleteList(void);
};
// Initialize Free List
template<class ItemType>
Node<ItemType>* LinkedList<ItemType>::free = nullptr;
// If Free List has a Node set curPtr to that Node
// and unlink it from the Free List
// Else create a new Node
// Zero out Node's variables and return
template<class ItemType>
Node<ItemType>* LinkedList<ItemType>::getListEl(void)
{
	Node<ItemType>* curPtr;
	if (free != nullptr)
	{
		curPtr = free;
		free = free->getNext();
	}
	else
		curPtr = new Node<ItemType>;
	curPtr->setItem(NULL);
	curPtr->setNext(nullptr);
	return curPtr;
}
// Up to the user to enter a legal position
// Set curPtr to head of List
// Skip down the List to the specified position
// return a ptr to the specified Node
template<class ItemType>
Node<ItemType>* LinkedList<ItemType>::getNodeAt(int position) const
{
	assert((position >= 1) && (position <= itemCount));
	if (position == 1) return headPtr;
	Node<ItemType>* curPtr = headPtr;
	for (int skip = 1; skip < position; skip++, curPtr = curPtr->getNext());
	return curPtr;
}
// Print all Node items in descending order by way of recursion
template<class ItemType>
void LinkedList<ItemType>::printRevHelper(Node<ItemType>* curPtr) const
{
	if (curPtr != NULL)
	{
		printRevHelper(curPtr->getNext());
		std::cout << curPtr->getItem() << " ";
	}
}
// Link a removed Node to the Free List
template<class ItemType>
void LinkedList<ItemType>::freeListEl(Node<ItemType>* curPtr)
{
	curPtr->setItem(NULL);
	curPtr->setNext(free);
	free = curPtr;
}
// Allows subStr to perform recursively.
// Folds to end of anEntry's List
template<class ItemType>
void LinkedList<ItemType>::substrHelper(Node<ItemType>* anEntry, LinkedList<ItemType>& aList, int len)
{
	if (len != 0)
	{
		substrHelper(anEntry->getNext(), aList, (len - 1));
		aList.push(anEntry->getItem());
	}
}
// Used with printList function
template<class ItemType>
int LinkedList<ItemType>::Forward = 1;
template<class ItemType>
int LinkedList<ItemType>::Reverse = -1;
// Initiate the Linked List's headPtr and itemCount
template<class ItemType>
LinkedList<ItemType>::LinkedList() : headPtr(nullptr), itemCount(0)
{
}
// Prevent from self assignment
// If the thisList has Nodes, clear them
// Iterate to end of aList, inserting Nodes into thisList based on aList's Nodes
template<class ItemType>
LinkedList<ItemType>::LinkedList(const LinkedList<ItemType>& aList)
{
	assert(this != &aList);
	TraverseOK = false;
	deleteList();
	Node<ItemType> *lhs = nullptr;
	Node<ItemType> *rhs = aList.headPtr;
	while (rhs != nullptr)
	{
		if (lhs == nullptr)
		{
			push(rhs->getItem());
			lhs = headPtr;
		}
		else
		{
			Node<ItemType> *newNode = getListEl();
			newNode->setItem(rhs->getItem());
			newNode->setNext(nullptr);
			lhs->setNext(newNode);
			lhs = lhs->getNext();
			++itemCount;
		}
		rhs = rhs->getNext();
	}
}
// Clears thisList
// Copies all aList items into thisList
template<class ItemType>
inline LinkedList<ItemType>& LinkedList<ItemType>::operator=(const LinkedList<ItemType>& aList)
{
	assert(this != &aList);
	TraverseOK = false;
	deleteList();
	Node<ItemType> *lhs = nullptr;
	Node<ItemType> *rhs = aList.headPtr;
	while (rhs != nullptr)
	{
		if (lhs == nullptr)
		{
			push(rhs->getItem());
			lhs = headPtr;
		}
		else
		{
			Node<ItemType> *newNode = getListEl();
			newNode->setItem(rhs->getItem());
			newNode->setNext(nullptr);
			lhs->setNext(newNode);
			lhs = lhs->getNext();
			++itemCount;
		}
		rhs = rhs->getNext();
	}
	return *this;
}
// Destructor just uses clear
template<class ItemType>
LinkedList<ItemType>::~LinkedList()
{
	clear();
}
// Used to point thisList elsewhere
template<class ItemType>
void LinkedList<ItemType>::setHeadPtr(Node<ItemType>* newList)
{
	headPtr = newList;
}
template<class ItemType>
Node<ItemType>* LinkedList<ItemType>::reverseHelper(Node<ItemType>* anEntry)
{
	if (anEntry != nullptr)
	{
		Node<ItemType>* ptr = reverseHelper(anEntry->getNext());
		if (ptr == nullptr)
		{
			headPtr = anEntry;
			return anEntry;
		}
		else
		{
			anEntry->setNext(nullptr);
			ptr->setNext(anEntry);
			return anEntry;
		}
	}
	return nullptr;
}
template<class ItemType>
void LinkedList<ItemType>::appendHelper(Node<ItemType>* lhs, Node<ItemType>* rhs)
{
	TraverseOK = false;
	if (lhs == nullptr)
		lhs = rhs;
	else
	{
		Node<ItemType> *curPtr = rhs;
		while (curPtr->getNext() != nullptr)
			curPtr = curPtr->getNext();
		curPtr->setNext(rhs);
	}
	rhs = nullptr;
}
// Up to the user to enter a legal position
// Modifies specified Node's item
template<class ItemType>
void LinkedList<ItemType>::setEntry(int position, const ItemType & newEntry)
{
	assert((position >= 1) && (position <= itemCount));
	Node<ItemType>* nodePtr = getNodeAt(position);
	nodePtr->setItem(newEntry);
}
// Increase/Decrease itemCount
template<class ItemType>
void LinkedList<ItemType>::setLength(int n)
{
	assert(n >= 0);
	itemCount = n;
}
// Up to the user to enter a legal position
// Returns the specified Node's item
template<class ItemType>
ItemType LinkedList<ItemType>::getEntry(int position) const
{
	assert((position >= 1) && (position <= itemCount));
	Node<ItemType>* nodePtr = getNodeAt(position);
	return nodePtr->getItem();
}
// Returns count of Nodes
template<class ItemType>
int LinkedList<ItemType>::getLength() const
{
	return itemCount;
}
template<class ItemType>
Node<ItemType>* LinkedList<ItemType>::getHeadPtr(void)
{
	return headPtr;
}
// Sequentially search for anEntry in thisList
// True if found else false
template<class ItemType>
bool LinkedList<ItemType>::isInList(const ItemType & anEntry)
{
	Node<ItemType>* curPtr = headPtr;
	while (curPtr != nullptr && curPtr->getItem() < anEntry)
		curPtr = curPtr->getNext();
	return curPtr != nullptr && curPtr->getItem() == anEntry;
}
// If first is true, point travPtr to head (could be nullptr)
// If traverse flag is false, do not iterate (return nullptr)
// Else point travPtr to next Node
// If travPtr != nullPtr return travPtr
// Else return nullptr
template<class ItemType>
Node<ItemType>* LinkedList<ItemType>::traverse(bool first)
{
	if (first)
	{
		trav_p = headPtr;
		TraverseOK = true;
	}
	else if (TraverseOK == false)
	{
		return nullptr;
	}
	else if (trav_p != nullptr)
	{
		trav_p = trav_p->getNext();
	}
	if (trav_p != nullptr)
	{
		return trav_p;
	}
	return nullptr;
}
// Inchworm down the List
// Initialized and inserts new Node
template<class ItemType>
inline void LinkedList<ItemType>::insert(int position, const ItemType & newEntry)
{
	assert((position >= 1) && (position <= itemCount + 1));
	if (position == 1) push(newEntry);
	else
	{
		Node<ItemType> *curPtr = getNodeAt(position - 1);
		Node<ItemType> *newNode = getListEl();
		newNode->setItem(newEntry);
		newNode->setNext(nullptr);
		TraverseOK = false;
		if (curPtr->getNext() == nullptr)
			curPtr->setNext(newNode);
		else
		{
			newNode->setNext(curPtr->getNext()->getNext());
			curPtr->setNext(newNode);
		}
		++itemCount;
	}
}
// Gets a Node from Free List
// Halt traversal
// Initialize new Node's item to newEntry
// Inchworm down the Linked List looking for insertion point
// Ascending: curPtr->getItem() < newNode->getItem()
// /*Descending: curPtr->getItem() > newNode->getItem()*/
// If prevPtr is nullptr, Linked List is empty. Insert at head
// Else insert between two Nodes or at end f Linked List
template<class ItemType>
void LinkedList<ItemType>::insertSorted(const ItemType& newEntry)
{
	if (headPtr == nullptr) push(newEntry);
	else
	{
		Node<ItemType> *newNode = getListEl();
		Node<ItemType> *curPtr, *prevPtr;
		TraverseOK = false;
		newNode->setItem(newEntry);
		for (curPtr = headPtr, prevPtr = nullptr;
			curPtr != nullptr && curPtr->getItem() < newNode->getItem();
			prevPtr = curPtr, curPtr = curPtr->getNext());
		if (prevPtr == nullptr)
		{
			newNode->setNext(headPtr);
			headPtr = newNode;
		}
		else
		{
			newNode->setNext(curPtr);
			prevPtr->setNext(newNode);
		}
		++itemCount;
	}
}
// Inserts a Node at the head of thisList
template<class ItemType>
inline void LinkedList<ItemType>::push(const ItemType & newEntry)
{
	Node<ItemType>* newNode = getListEl();
	TraverseOK = false;
	newNode->setItem(newEntry);
	newNode->setNext(headPtr);
	headPtr = newNode;
	++itemCount;
}
// Inchworm down Linked List
// If curPtr == nullptr, item not found
// If prevPtr == nullptr, Unlink first Node
// Else unlink Node in the middle or end of Linked List
// Reduce item Count
// Return Node to Free List
// Halt Traversal
template<class ItemType>
bool LinkedList<ItemType>::remove(const ItemType& newEntry)
{
	Node<ItemType>* curPtr = headPtr, *prevPtr = nullptr;
	while (curPtr != nullptr && curPtr->getItem() != newEntry)
	{
		prevPtr = curPtr;
		curPtr = curPtr->getNext();
	}
	if (curPtr == nullptr)
		return false;
	else if (prevPtr == nullptr)
		headPtr = headPtr->getNext();
	else
		prevPtr->setNext(curPtr->getNext());
	--itemCount;
	freeListEl(curPtr);
	TraverseOK = false;
	return true;
}
// Removes the first Node in thisList
template<class ItemType>
inline bool LinkedList<ItemType>::pop()
{
	if (headPtr == nullptr) return false;
	Node<ItemType>* curPtr = headPtr;
	headPtr = headPtr->getNext();
	--itemCount;
	freeListEl(curPtr);
	TraverseOK = false;
	return true;
}
// Check if Linked List has zero Nodes
template<class ItemType>
bool LinkedList<ItemType>::isEmpty() const
{
	return itemCount == 0;
}
// If the list is empty and new length is greater than thisList's length
//  or if the resize value is equal to thisList's length then exit
// If thisList is any size and the user wants to resize it to zero
//  delete thisList
// Else increase or decrease the size of thisList
// If increasing, push/insert Nodes into thisList
// If decreasing,
template<class ItemType>
void LinkedList<ItemType>::resize(int len, const ItemType& value)
{
	assert(len >= 0);
	if (len == itemCount) return *this;
	else if ((itemCount >= 1) && (len == 0))
		while (!isEmpty()) pop();
	else
	{
		bool remove = ((len < itemCount) ? (true) : (false));
		Node<ItemType> *curPtr, *nextPtr;
		TraverseOK = false;
		if (itemCount == 0)
			push(value);
		if (itemCount == 0 || itemCount == 1)
			curPtr = getNodeAt(1);
		else
			curPtr = getNodeAt(((remove) ? (len) : (itemCount)));
		while (itemCount != len)
		{
			if (remove)
			{
				nextPtr = curPtr->getNext();
				curPtr->setNext((nextPtr != nullptr) ? (nextPtr->getNext()) : (nullptr));
				freeListEl(nextPtr);
			}
			else
			{
				Node<ItemType> *newEntry = getListEl();
				curPtr->setNext(newEntry);
				curPtr = curPtr->getNext();
			}
			itemCount += ((remove) ? (-1) : (1));
		}
	}
	return *this;
}
// Iterate down Linked List deleting Nodes
// Zero out thisList
// Iterate down Free List deleting Nodes
// Zero out Free List
template<class ItemType>
void LinkedList<ItemType>::clear()
{
	Node<ItemType>* curPtr = headPtr, *prevPtr;
	TraverseOK = false;
	while (curPtr != nullptr)
	{
		prevPtr = curPtr;
		curPtr = curPtr->getNext();
		delete prevPtr;
	}
	curPtr = free;
	while (curPtr != nullptr)
	{
		prevPtr = curPtr;
		curPtr = curPtr->getNext();
		delete prevPtr;
	}
	free = nullptr;
}
// If direction == 1, then iterate down thisList printing items
// Else recurse up thisList then print items
template<class ItemType>
void  LinkedList<ItemType>::printList(int direction) const
{
	Node<ItemType>* curPtr = headPtr;
	if (direction == Forward)
	{
		while (curPtr != NULL)
		{
			std::cout << curPtr->getItem();
			curPtr = curPtr->getNext();
		}
	}
	else
		printRevHelper(curPtr);
}
// Creates a new List and copies thisList's items into newList's items
template<class ItemType>
LinkedList<ItemType>& LinkedList<ItemType>::subStr(int position, int len)
{
	assert((position >= 1) && (position <= itemCount));
	TraverseOK = false;
	LinkedList<ItemType> *newList = new LinkedList<ItemType>;
	if (position == itemCount)
		return *newList;
	Node<ItemType> *curPtr = getNodeAt(position);
	substrHelper(curPtr, *newList, len);
	return *newList;
}
// Appends thisList to aList
//sets aList headPtr to null
template<class ItemType>
LinkedList<ItemType> &LinkedList<ItemType>::append(LinkedList<ItemType>& aList)
{
	if (aList.headPtr == nullptr) return *this;
	TraverseOK = false;
	// find node to start insert
	Node<ItemType> *curPtr;
	if (headPtr == nullptr)
		curPtr = headPtr;
	else
		curPtr = getNodeAt(itemCount);
	// deep copy from aList
	Node<ItemType> *cpy = aList.headPtr;
	while (cpy != nullptr)
	{
		Node<ItemType> *newNode = getListEl();
		newNode->setItem(cpy->getItem());
		newNode->setNext(nullptr);
		if (headPtr == nullptr)
		{
			headPtr = newNode;
			curPtr = headPtr;
		}
		else
		{
			curPtr->setNext(newNode);
			curPtr = curPtr->getNext();
		}
		cpy = cpy->getNext();
		++itemCount;
	}
	aList.headPtr = nullptr;
	aList.itemCount = 0;
	return *this;
}
// Recursively reverses thisList
template<class ItemType>
LinkedList<ItemType> &LinkedList<ItemType>::reverse(void)
{
	TraverseOK = false;
	reverseHelper(headPtr);
	return *this;
}
template<class ItemType>
void LinkedList<ItemType>::deleteList(void)
{
	Node<ItemType> *curPtr = headPtr;
	while (curPtr != nullptr)
	{
		pop();
		curPtr = headPtr;
	}
}
#if 0 // #if 1 to compile as a standalone program, not a library
int main()
{
	int choice = 0, key, position;
	Node<int> d, *e;
	LinkedList<int> list;
	LinkedList<int> temp;
	temp.push(3);
	temp.push(2);
	temp.push(1);
	LinkedList<int> two;
	while (choice != 16)
	{
		std::cout << "\n\n1. push element\n"
			<< "2. insert element at designated location\n"
			<< "3. insert element in order\n"
			<< "4. see if an element exists\n"
			<< "5. remove an element by value\n"
			<< "6. pop element\n"
			<< "7. resize list\n"
			<< "8. print forward\n"
			<< "9. print reverse\n"
			<< "10. traverse (first)\n"
			<< "11. traverse (next)\n"
			<< "12. create a substring\n"
			<< "13. append [1,2,3]\n"
			<< "14. reverse list\n"
			<< "15. assign to list\n"
			<< "16. quit\n" << "\nEnter choice : "
			<< std::flush;
		std::cin >> choice;
		switch (choice)
		{
		case 1:
			std::cout << "Enter key : " << std::flush;
			std::cin >> key;
			list.push(key);
			break;
		case 2:
			std::cout << "Enter key : " << std::flush;
			std::cin >> key;
			std::cout << "\nEnter position : " << std::flush;
			std::cin >> position;
			if ((position < 1) || (position > (list.getLength() + 1)))
				std::cout << "You can't insert a Node there\n";
			else
				list.insert(position, key);
			break;
		case 3:
			std::cout << "Enter key : " << std::flush;
			std::cin >> key;
			list.insertSorted(key);
			break;
		case 4:
			std::cout << "Enter key : " << std::flush;
			std::cin >> key;
			if (list.isInList(key))
				std::cout << "Key " << key << " is in the list\n";
			else
				std::cout << "Nah man, the key " << key << " isn't there\n";
			break;
		case 5:
			std::cout << "Enter key : " << std::flush;
			std::cin >> key;
			if (list.remove(key))
				std::cout << "Node has been removed" << std::endl;
			else
				std::cout << "Failed to remove node" << std::endl;
			break;
		case 6:
			list.pop();
			break;
		case 7:
			std::cout << "Enter new length : " << std::flush;
			std::cin >> key;
			list.resize(key, 0);
			break;
		case 8:
			list.printList(list.Forward);
			std::cout << " : " << list.getLength() << std::endl;
			break;
		case 9:
			list.printList(list.Reverse);
			std::cout << " : " << list.getLength() << std::endl;
			break;
		case 10:
			e = list.traverse(true);
			if (e == nullptr)
				std::cout << "There is no first key!\n";
			else
				std::cout << "Node has data " << e->getItem() << std::endl;
			break;
		case 11:
			e = list.traverse(false);
			if (e == nullptr)
				std::cout << "There is no next key!\n";
			else
				std::cout << "Node has data " << e->getItem() << std::endl;
			break;
		case 12:
			std::cout << "Enter position : " << std::flush;
			std::cin >> position;
			std::cout << "Enter number of characters : " << std::flush;
			std::cin >> key;
			if (key > list.getLength() ||
				position < 1 ||
				position > list.getLength())
				std::cout << "That goes out of range!\n" << std::endl;
			else
				(list.subStr(position, key)).printList(1);
			break;
		case 13:
			list.append(temp);
			break;
		case 14:
			list.reverse();
			break;
		case 15:
			if (!two.isEmpty())
			{
				two.printList(1);
				std::cout << std::endl;
			}
			else
				std::cout << "Two is empty!\n" << std::flush;
			two = list;
			if (!two.isEmpty())
				two.printList(1);
			else
				std::cout << "Two is empty!\n" << std::flush;
			break;
		case 16:
			std::cout << "Goodbye!" << std::endl;
			break;
		default:
			std::cout << "Do you even numbers, bro???\n\n" << std::flush;
		}
	}
	return 0;
}
#endif

