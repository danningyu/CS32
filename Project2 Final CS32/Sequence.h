//Danning Yu
//CS32 Project 2

#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <string>

using ItemType = std::string;

class Sequence {
public:
	Sequence();
	~Sequence(); //destructor
	Sequence(const Sequence& other); //copy constructor
	Sequence& operator=(const Sequence& rhs); //implement assignment operator
	bool empty() const;  // Return true if the sequence is empty, otherwise false.
	int size() const;    // Return the number of items in the sequence.
	int insert(int pos, const ItemType& value);
	int insert(const ItemType& value);
	bool erase(int pos);
	int remove(const ItemType& value);
	bool get(int pos, ItemType& value) const;
	bool set(int pos, const ItemType& value);
	int find(const ItemType& value) const;
	void swap(Sequence& other);
	// void dump();

private:
	struct Node {
		ItemType m_value;
		Node* m_next;
		Node* m_prev;
	};
	int m_size; //current size of array
	Node* dum; //dummy/sentinel node
};

int subsequence(const Sequence& seq1, const Sequence& seq2);
void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result);

#endif
