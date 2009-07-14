
//#include "BinaryTree.h";
#include "Trie.h";
#include "SuffixTree.h";
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

	/*BinaryTree<std::string> tree;

	std::string s1("nokia");
	std::string s2("microsotf");
	std::string s3("asus");
	std::string s4("Nokia");

	tree.insert(s1);
	tree.insert(s2);
	tree.insert(s3);
	tree.insert(s4);

	std::string s5("Nokia");

	std::string *s = tree.search(s5);

	if (s)
		std::cout << *s;
	//if (s)


	
	/*tree.insert('2');
	tree.insert('3');
	tree.insert('5');*/

	//tree.traverseInOrder();

	//tree.traversePreOrder();
	/*SuffixTree tree("nok_Nok_NOk_asus_Nokia3_nokia");

	std::cout << tree.findSubstring("as");*/
	
	return 1;
}