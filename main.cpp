
#include "Trie.h"
#include <iostream>
#include <string>
#include <map>


class object
{
public:
	object() {}

	inline const int getValue() { return 1; }
};

int main()
{
	object o;

	std::string s1("nokia");
	std::string s2("nok");

	Trie<object> s;

	s.insert(s1, o);
	s.insert(s2, o);

	TrieNode<object> *t = s.find("nokia3230");

	if (t) {
		std::cout << const_cast<object*>(t->getObject())->getValue();
	}
	
	return 0;
}