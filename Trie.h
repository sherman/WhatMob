
#ifndef _TRIE_H
#define	_TRIE_H

#include <map>
#include <string>
#include <iostream>

	template <class T>
	class TrieNode
	{
		public:
			TrieNode(const T& object) : terminal_(false), object_(object) {}
			TrieNode() : terminal_(false), object_() {}

			inline bool isTerminal() { return terminal_; }
			void setTerminal(bool orly) { terminal_ = orly; }

			bool hasChild(char value) const
			{
				return (childNodes_.find(value) != childNodes_.end());
			}

			TrieNode* addChild(char value, const T& object)
			{
				childNodes_[value] = TrieNode(object);
				return getChild(value);
			}

			TrieNode* getChild(char value)
            {
				return &childNodes_[value];
            }

			const T* getObject() { return &object_; }
		private:
			bool terminal_;
			std::map<char, TrieNode> childNodes_;
			T object_;
	};

	template <class T>
	class Trie
	{
		public:
			Trie() : root_(new TrieNode<T>()) {}

			TrieNode<T> *insert(const std::string&, const T&);
			TrieNode<T> *find(const std::string&) const;
		private:
			TrieNode<T>* root_;
	};

	template <class T> TrieNode<T>* Trie<T>::insert(
		const std::string& str,
		const T& object
	)
	{
		TrieNode<T>* current = root_;

        std::string::const_iterator iter = str.begin();

        while (iter != str.end()) {
                current = current->addChild(*iter, object);
                ++iter;
        }

        current->setTerminal(true);

		return current;
	};

	template <class T> TrieNode<T>* Trie<T>::find(const std::string& str) const
	{
		TrieNode<T>* current = root_;

		std::string::const_iterator iter = str.begin();

		while (iter != str.end()) {
			if (!current->hasChild(*iter))
				break;

			current = current->getChild(*iter);

			++iter;
		}

		if (current->isTerminal())
			return current;
		else
			return 0;
	}

#endif	/* _TRIE_H */

