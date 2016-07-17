#include<iostream>
#include "LinkedList.h"
bool isPalindrome(LinkedList<char> &s)
{
	if (s.isEmpty() || s.getLength() == 1)
		return true;
	else if (s.getEntry(1) == s.getEntry(s.getLength()))
		return isPalindrome(s.subStr(2, s.getLength() - 1));
	else
		return false;
}
int main()
{
	LinkedList<char> word1, word2;
	char s1[] = { "tattattat" };
	for (unsigned int i = 0; i < strlen(s1); ++i) word1.insert(s1[i]);
	std::cout << isPalindrome(word1) << std::endl;
	char s2[] = { "ermehgerd" };
	for (unsigned int i = 0; i < strlen(s2); ++i) word2.insert(s2[i]);
	std::cout << isPalindrome(word2) << std::endl;
	int stop;
	std::cin >> stop;
	return 0;
}
