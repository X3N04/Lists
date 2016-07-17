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
	virtual void insert(const ItemType& newEntry) = 0;
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
	// Default Contructor
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
// Copys anItem to this Node's item
template<class ItemType>
Node<ItemType>::Node(const ItemType& anItem) : item(anItem), next(nullptr)
{
}
// Copys anItem to this Node's item
// Copys nextNodePtr to this Node's next
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
// Assistes List with access to next
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
public:
	// Default constructor
	LinkedList();
	// List Copy Constructor
	LinkedList(const LinkedList<ItemType>& aList);
	// Destructor
	virtual ~LinkedList();
	// Modify a specified Node's item
	void setEntry(int position, const ItemType& newEntry);
	// Get a specified Node's item
	ItemType getEntry(int position) const;
	// Get number of Nodes in List
	int getLength() const;
	// Sequential search for item
	bool isInList(const ItemType& anEntry);
	// Iterates first or next Node
	Node<ItemType>* traverse(bool first);
	// Inserts a Node in ascending order
	// Constructed with numbers in mind
	// Will need to be modified if using char
	void insert(const ItemType& newEntry);
	// Removes a Node and returns to Free List
	// Constructed with numbers in mind
	// Will need to modified if using char
	bool remove(const ItemType & newEntry);
	// Checks if itemCount is 0
	bool isEmpty() const;
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
// Up to the user to enter a legal poition
// Set curPtr to head of List
// Skip down the List to the specified position
// return a ptr to the specified Node
template<class ItemType>
Node<ItemType>* LinkedList<ItemType>::getNodeAt(int position) const
{
	assert((position >= 1) && (position <= itemCount));
	Node<ItemType>* curPtr = headPtr;
	for (int skip = 1; skip < position; skip++)
		curPtr = curPtr->getNext();
	return curPtr;
}
// Print all Node items in descending order by way of recursion
template<class ItemType>
void LinkedList<ItemType>::printRevHelper(Node<ItemType>* curPtr) const
{
	if (curPtr != NULL)
	{
		printRevHelper(curPtr->getNext());
		std::cout << curPtr->getItem() << std::endl;
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
// Up to the user to not copy two ptr that point to same memory
// If the thisList has Nodes, clear them
// Iterate to end of aList, inserting Nodes into thisList based on aList's Nodes
template<class ItemType>
LinkedList<ItemType>::LinkedList(const LinkedList<ItemType>& aList)
{
	if (headPtr != nullptr) clear();
	Node<ItemType> *curPtr = aList.headPtr;
	while (curPtr != NULL)
	{
		insert(curPtr->getItem());
		curPtr = curPtr->getNext();
	}
}
// Destructor just uses clear
template<class ItemType>
LinkedList<ItemType>::~LinkedList()
{
	clear();
}
// Up to the user to enter a legal poision
// Modifies specified Node's item
template<class ItemType>
void LinkedList<ItemType>::setEntry(int position, const ItemType & newEntry)
{
	assert((position >= 1) && (position <= itemCount));
	Node<ItemType>* nodePtr = getNodeAt(position);
	nodePtr->setItem(newEntry);
}
// Up to the user to enter a legal poision
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
// Gets a Node from Free List
// Halt traversal
// Initialize new Node's item to newEntry
// Inchworm down the Linked List looking for insertion point
// Ascending: curPtr->getItem() < newNode->getItem()
// /*Descending: curPtr->getItem() > newNode->getItem()*/
// If prevPtr is nullptr, Linked List is empty. Insert at head
// Else insert between two Nodes or at end f Linked List
template<class ItemType>
void LinkedList<ItemType>::insert(const ItemType& newEntry)
{
	Node<ItemType>* newNode = getListEl();
	//Node<ItemType>* curPtr, *prevPtr;
	TraverseOK = false;
	newNode->setItem(newEntry);
	// Insert new node at beginning of chai
	newNode->setNext(headPtr)
		headPtr = newNode;
	/* Insert in ascending order
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
	*/
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
// Check if Linked List has zero Nodes
template<class ItemType>
bool LinkedList<ItemType>::isEmpty() const
{
	return itemCount == 0;
}
// Iterate down Linked List deleting Nodes
// Zero out thisList
// Iterate down Free List deleting Nodes
// Zero out Free List
template<class ItemType>
void LinkedList<ItemType>::clear()
{
	Node<ItemType>* curPtr = headPtr, *prevPtr;
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
			std::cout << curPtr->getItem() << " ";
			curPtr = curPtr->getNext();
		}
	}
	else
		printRevHelper(curPtr);
}
// Mimic of String's substr function
// Creates a new List and copys thisList's items into newList's items
template<class ItemType>
LinkedList<ItemType>& LinkedList<ItemType>::subStr(int position, int len)
{
	LinkedList<ItemType> *newList = new LinkedList<ItemType>;
	if (position == this->getLength() ||
		((position >= 1) && (position <= itemCount)))
		return *newList;
	Node<ItemType> *curPtr = getNodeAt(position);
	for (int i = 0; i < len; ++i)
	{
		newList->insert(curPtr->getItem());
		curPtr = curPtr->getNext();
	}
	return *newList;
}
#if 0 // #if 1 to compile as a standalone program, not a library
int main()
{
	int choice = 0, key;
	Node<int> d, *e;
	LinkedList<int> list;
	while (choice != 8)
	{
		std::cout << "\n\n1. add an element\n"
			<< "2. see if an element exists\n"
			<< "3. remove an element by key\n"
			<< "4. print forward\n"
			<< "5. print reverse\n"
			<< "6. traverse (first)\n"
			<< "7. traverse (next)\n"
			<< "8. quit\n" << "\nEnter choice : "
			<< std::flush;
		std::cin >> choice;
		switch (choice)
		{
		case 1:
			std::cout << "Enter key : " << std::flush;
			std::cin >> key;
			d.setItem(key);
			e = new Node<int>;
			(*e) = d;
			list.insert(e->getItem());
			break;
		case 2:
			std::cout << "Enter key : " << std::flush;
			std::cin >> key;
			if (list.isInList(key))
				std::cout << "Key " << key << " is in the list\n";
			else
				std::cout << "Nah man, the key " << key << " isn't there\n";
			break;
		case 3:
			std::cout << "Enter key : " << std::flush;
			std::cin >> key;
			if (list.remove(key))
				std::cout << "Node has been removed" << std::endl;
			else
				std::cout << "Failed to remove node" << std::endl;
			break;
		case 4:
			list.printList(list.Forward);
			break;
		case 5:
			list.printList(list.Reverse);
			break;
		case 6:
			e = list.traverse(true);
			if (e == nullptr)
				std::cout << "There is no first key!\n";
			else
				std::cout << "Node has data " << e->getItem() << std::endl;
			break;
		case 7:
			e = list.traverse(false);
			if (e == nullptr)
				std::cout << "There is no next key!\n";
			else
				std::cout << "Node has data " << e->getItem() << std::endl;
			break;
		case 8:
			std::cout << "Goodbye!" << std::endl;
			break;
		default:
			std::cout << "Do you even numbers, bro???\n\n" << std::flush;
		}
	}
	return 0;
}
#endif

