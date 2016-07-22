/*
* BigInt.h
* Daniel Salazar
* 07/22/2016
* ADT that uses LinkedList.h to store
* a list of numbers representing digits
* in an arbitrarily long unsigned int.
* The number is stored and processed in
* reverse in order to reduce complexity
* of the + and * functions. Every digit
* will be a number from 0 - 9. 
*/
#include "LinkedList.h"
class BigInt
{
private:
	LinkedList<unsigned long long> number;
public:
	// Default Constructor
	BigInt();
	// User Defined Constructor
	// Takes in a number and assigns it
	// to a new BigInt
	BigInt(unsigned long long num);
	// Copy Constructor
	BigInt(BigInt &num);
	// Copy assign
	BigInt &operator=(BigInt & num);
	// User defined assign
	// Copies num into thisBigInt
	BigInt &operator=(unsigned long long num);
	// Adds two BigInts, returns a newBigInt 
	BigInt &operator+(BigInt &rhs);
	// Assigns the sum of thisBigInt and
	// rhs to thisBigInt
	BigInt &operator+=(BigInt &rhs);
	// Multiplies two BigInts, returns a
	// newBigInt
	BigInt &operator*(BigInt &rhs);
	// Assigns the product of thisBigInt and
	// rhs to thisBigInt
	BigInt &operator*=(BigInt &rhs);
	// returns thisBigInt's itemCount
	int getSize();
	// Prints a BigInt in readable direction 
	// instead of reverse
	friend std::ostream &operator<<(std::ostream& os, const BigInt& num);
};
// Constructs a BigInt with default value 0
BigInt::BigInt()
{
	number.push(0);
}
// Uses the operator= function for simplicity
// if num is 0, push 0
BigInt::BigInt(unsigned long long num)
{
	if (num != 0)
		*this = num;
	else
		number.push(0);
	number.reverse();
}
// Uses the LinkedList.h operator= function
// Reverse the number for ease of BigInt.h
// function usage
BigInt::BigInt(BigInt &num)
{
	number = num.number;
	number.reverse();
}
// Destroy thisBigInt and push each digit of num
// into thisBigInt (reverse order)
BigInt &BigInt::operator=(unsigned long long num)
{
	number.clear();
	unsigned long long r = num;
	int d = 0;
	while (r != 0)
	{
		d = r % 10;
		r /= 10;
		number.push(d);
	}
	return *this;
}
// Uses the LinkedList.h operator= function
// Reverse the number for ease of BigInt.h
// function usage
BigInt &BigInt::operator=(BigInt & num)
{
	number = num.number;
	return *this;
}
// num is already in reverse, so print it in reverse
// will make it readable
std::ostream & operator<<(std::ostream & os, const BigInt & num)
{
	num.number.printList(-1);
	return os;
}
// returns thisBigInt's itemCount
int BigInt::getSize()
{
	return number.getLength();
}
// if thisBigInt is empty return rhs
// if rhs is empty return thisBigInt
// otherwise move down both BigInts
// taking the sum of both digits and 
// pushing it into newNumber and return
/*
 * Example: 246 + 135
 * a = 642
 * b = 531
 * c = 1
 * c = 81
 * c = 381
 * return 183
 */ 
BigInt &BigInt::operator+(BigInt &rhs)
{
	BigInt *newNumber;
	if (number.isEmpty())
		return rhs;
	else if (rhs.number.isEmpty())
		return *this;
	else
	{
		newNumber = new BigInt();
		newNumber->number.pop();
		Node<unsigned long long> *ls = number.traverse(true);
		Node<unsigned long long> *rs = rhs.number.traverse(true);
		unsigned long long left, right, sum, digit, carry = 0;
		// walk down both lists
		while (ls || rs || carry)
		{
			if (ls == nullptr)
				left = 0;
			else
				left = ls->getItem();
			if (rs == nullptr)
				right = 0;
			else
				right = rs->getItem();
			sum = left + right + carry;
			digit = sum % 10;
			carry = sum / 10;
			newNumber->number.push(digit);
			if (ls != nullptr) ls = ls->getNext();
			if (rs != nullptr) rs = rs->getNext();
		}
	}
	newNumber->number.reverse();
	return *newNumber;
}
// Adds two BigInts and assigns it to
// thisBigInt
BigInt & BigInt::operator+=(BigInt & rhs)
{
	*this = *this + rhs;
	return *this;
}
// Performs multiplication using this method:
/*
 * multiply(a[1..p], b[1..q], base)
 * product = [1..p+q]
 * for b_i = 1 to q
 *    carry = 0
 *    for a_i = 1 to p
 *       product[a_i + b_i - 1] += carry + a[a_i] * b[b_i]
 *       carry = product[a_i + b_i - 1] / base
 *       product[a_i + b_i - 1] = product[a_i + b_i - 1] mod base
 *    product[b_i + p] += carry
 * end for
 */
// Then it reverses the number and removes any excess
// zeros that were added during allocation portion
// finally reversing it for further use and returning 
// newNumber
BigInt &BigInt::operator*(BigInt &rhs)
{
	BigInt *product = new BigInt();
	product->number.resize(this->number.getLength() + rhs.number.getLength(), 0);
	Node<unsigned long long> *productPtr = product->number.traverse(true), *a_i, *b_i;
	unsigned long long carry;
	int i, j;
	for (i = 1, b_i = rhs.number.traverse(true);
		b_i != nullptr;
		++i, b_i = rhs.number.traverse(false))
	{
		carry = 0;
		for (j = 1, a_i = number.traverse(true);
			a_i != nullptr;
			++j, a_i = number.traverse(false))
		{
			productPtr = product->number.getNodeAt(i + j - 1);
			productPtr->setItem(productPtr->getItem() +\
				carry + a_i->getItem() * b_i->getItem());
			carry = productPtr->getItem() / 10;
			productPtr->setItem(productPtr->getItem() % 10);
			productPtr = productPtr->getNext();
		}
		productPtr = product->number.getNodeAt(i + number.getLength());
		productPtr->setItem(productPtr->getItem() + carry);
	}
	product->number.reverse();
	productPtr = product->number.traverse(true);
	while (productPtr->getItem() == 0)
	{
		product->number.pop();
		productPtr = product->number.traverse(true);
	}
	product->number.reverse();
	return *product;
}
// Assigns the product of thisBigInt and rhs
// to thisBigInt
BigInt & BigInt::operator*=(BigInt & rhs)
{
	*this = *this * rhs;
	return *this;
}
#if 0 // #if 1 to compile as a standalone program, not a library
void fact(int n)
{
	if (n > 100)
	{
		std::cout << "n is to large...";
		return;
	}
	BigInt fact(1);
	BigInt arr[100];
	unsigned long long len = 0, pw = 0;
	for (int i = 1; i <= n; ++i)
	{
		BigInt temp(i);
		fact *= temp;
		arr[i - 1] = fact;
		len = fact.getSize();
	}
	for (int j = 0; j < n; ++j)
	{
		pw = len - arr[j].getSize();
		for (int pW = 0; pW < pw; ++pW)
		{
			std::cout << " ";
		}
		std::cout << arr[j] << std::endl;
	}
}
void fib(int n)
{
	if (n > 100)
	{
		std::cout << "n is to large...";
		return;
	}
	BigInt arr[100];
	BigInt b1(1);
	arr[0] = b1;
	BigInt b2(1);
	arr[1] = b2;
	BigInt t;
	unsigned long long len = 0, pw = 0;
	for (int i = 2; i < 100; i++)
	{
		t = b1 + b2;
		b2 = b1;
		b1 = t;
		arr[i] = t;
		len = t.getSize();
	}
	for (int j = 0; j < n; ++j)
	{
		pw = len - arr[j].getSize();
		for (int pW = 0; pW < pw; ++pW)
		{
			std::cout << " ";
		}
		std::cout << arr[j] << std::endl;
	}
	return;
}
int main()
{
	int choice = 0, key = 0;
	while (choice != 3)
	{
		std::cout << "\n\n1. Factorial\n"
			<< "2. Fibonacci\n"
			<< "3. quit\n"
			<< std::flush;
		std::cin >> choice;
		switch (choice)
		{
		case 1:
			std::cout << "Enter length : " << std::flush;
			std::cin >> key;
			fib(key);
			break;
		case 2:
			std::cout << "Enter length : " << std::flush;
			std::cin >> key;
			fact(key);
			break;
		case 3:
			std::cout << "Goodbye!" << std::endl;
			break;
		default:
			std::cout << "Do you even numbers, bro???\n\n" << std::flush;
			break;
		}
	}
	return 0;
}
#endif

