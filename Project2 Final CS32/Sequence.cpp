#include <iostream>
#include "Sequence.h"

Sequence::Sequence():m_size(0){ //default constructor
	dum = new Node; //new node allocated, make sure to DELETE!!
	dum->m_next = dum; //circular list
	dum->m_prev = dum;
}

Sequence::Sequence(const Sequence& otherSeq){
	m_size = 0; //reset size
	dum = new Node; //new node allocated, make sure to DELETE!!	
	dum->m_next = dum; //circular list
	dum->m_prev = dum;
	// head = dum; //head pointer points to the dummy Node	
	Node* temp = otherSeq.dum->m_next; //temp pointer to first item of otherSeq
	for (int i = 0; i < otherSeq.m_size; i++) {
		insert(m_size, temp->m_value);
		temp = temp->m_next;
	}
}
Sequence::~Sequence() {
	while (erase(0)) {}
	delete dum; //delete the dummy node
}
Sequence& Sequence::operator=(const Sequence& rhs) {
	if (this != &rhs) { //not referring to the same sequence
		while (erase(0)) {} //erase the original nodes
		Sequence temp = rhs; //in case rhs is the same as this
		swap(temp);
	}
	return *this;
}
bool Sequence::empty() const { //DONE
	if (m_size == 0) {
		return true;
	}
	return false;
}
// Return true if the sequence is empty, otherwise false.

int Sequence::size() const { //DONE
	return m_size;
}
// Return the number of items in the sequence.

int Sequence::insert(int pos, const ItemType& value) {
	if (pos<0 || pos > m_size) {
		return -1;
	}
	Node* item = new Node; //new returns a pointer...
	item->m_value = value;
	if (m_size == 0) {
		item->m_next = dum;
		item->m_prev = dum;
		dum->m_next = item;
		dum->m_prev = item;
	}
	else {
		Node* temp = dum->m_next; //start pointer pointing at first node (0th element)
		for (int i = 0; i < pos; i++) { //loop until temp points to Node at pos
			temp = temp->m_next;
		}
		item->m_next = temp;
		item->m_prev = temp->m_prev;
		(temp->m_prev)->m_next = item;
		temp->m_prev = item;
	}
	m_size++;
	return pos;
}
// Insert value into the sequence so that it becomes the item at
// position pos.  The original item at position pos and those that
// follow it end up at positions one higher than they were at before.
// Return pos if 0 <= pos <= size() and the value could be
// inserted.  (It might not be, if the sequence has a fixed capacity,
// e.g., because it's implemented using a fixed-size array.)  Otherwise,
// leave the sequence unchanged and return -1.  Notice that
// if pos is equal to size(), the value is inserted at the end.

int Sequence::insert(const ItemType& value) {
	Node* temp = dum->m_next; //point to 0th element
	int p = -1;
	for (int i = 0; i < m_size; i++) {		
		if (value <= temp->m_value) {
			p = i;
			break;
		}
		temp = temp->m_next; //go to the next node
	}
	if (p == -1) {
		p = m_size;
	}
	insert(p, value);
	return p;
}
// Let p be the smallest integer such that value <= the item at
// position p in the sequence; if no such item exists (i.e.,
// value > all items in the sequence), let p be size().  Insert
// value into the sequence so that it becomes the item at position
// p.  The original item at position p and those that follow it end
// up at positions one higher than before.  Return p if the value
// was actually inserted.  Return -1 if the value was not inserted
// (perhaps because the sequence has a fixed capacity and is full).

bool Sequence::erase(int pos) {
	if (pos < 0 || pos >= m_size) {
		return false;
	}
	Node* temp = dum->m_next; //start at 0th node
	for (int i = 0; i < pos; i++) { //loop until temp points to element you want to remove
		temp = temp->m_next;
	}
	(temp->m_prev)->m_next = temp->m_next; //redirect pointers
	(temp->m_next)->m_prev = temp->m_prev;
	delete temp;
	m_size--; //update size
	return true;
}
// If 0 <= pos < size(), remove the item at position pos from
// the sequence (so that all items that followed that item end up at
// positions one lower than they were at before), and return true.
// Otherwise, leave the sequence unchanged and return false.

int Sequence::remove(const ItemType& value) {
	int counter = 0;
	Node* temp = dum->m_next; //start at first node
	for (int i = 0; i < m_size; i++) {
		if (temp->m_value == value) { //if node temp is pointing to matches the value
			temp = temp->m_next; //move temp to the next value so that it isn't pointing to nothing
			erase(i);
			i--; //lower index to account for reduction of # of items
			counter++;
		}
		else {
			temp = temp->m_next; //move on to the next pointer
		}
	}
	return counter;
}
// Erase all items from the sequence that == value.  Return the
// number of items removed (which will be 0 if no item == value).

bool Sequence::get(int pos, ItemType& value) const {
	if (pos < 0 || pos >= m_size) {
		return false;
	}
	Node* temp = dum->m_next; //start from 0th node
	for (int i = 0; i < pos; i++) {
		temp = temp->m_next;
	}
	value = temp->m_value;
	return true;
}
// If 0 <= pos < size(), copy into value the item at position pos
// of the sequence and return true.  Otherwise, leave value unchanged
// and return false.

bool Sequence::set(int pos, const ItemType& value) {
	if (pos < 0 || pos >= m_size) { //invalid position
		return false;
	}
	Node* temp = dum->m_next; //pointer to first node
	for (int i = 0; i < pos; i++) { //make temp point to node at pos
		temp = temp->m_next;
	}
	temp->m_value = value;
	return true;
}
// If 0 <= pos < size(), replace the item at position pos in the
// sequence with value and return true.  Otherwise, leave the sequence
// unchanged and return false.

int Sequence::find(const ItemType& value) const {
	Node* temp = dum->m_next;
	for (int i = 0; i < m_size; i++) {
		if (temp->m_value == value) {
			return i;
		}
		temp = temp->m_next;
	}
	return -1;
}
// Let p be the smallest integer such that value == the item at
// position p in the sequence; if no such item exists, let p be -1.
// Return p.

void Sequence::swap(Sequence& other) {
	int tempSize = m_size; //swap sizes
	m_size = other.m_size;
	other.m_size = tempSize;	
	Node* tempNext = dum->m_next;
	Node* tempPrev = dum->m_prev;
	(dum->m_prev)->m_next = other.dum; //redirect m_next pointer of last item in sequence
	((other.dum)->m_prev)->m_next = dum;
	(dum->m_next)->m_prev = other.dum; //redict m_prev pointer of first item in sequence
	((other.dum)->m_next)->m_prev = dum;
	dum->m_next = other.dum->m_next; //redict dum's pointers
	dum->m_prev = other.dum->m_prev;
	other.dum->m_next = tempNext; //redirect other.dum's pointers
	other.dum->m_prev = tempPrev;
}
// Exchange the contents of this sequence with the other one.

int subsequence(const Sequence& seq1, const Sequence& seq2) {
	if (seq2.empty() == true || seq2.size() > seq1.size()) {
		return -1;
	}
	bool found = false;
	ItemType temp1; //temp itemtype for seq1
	ItemType temp2; //temp itemtype for seq2
	seq2.get(0, temp2); //set temp to first value in seq2
	int startPos = -1; //impossible value
	for (int i = 0; i < seq1.size(); i++) {
		seq1.get(i, temp1);
		if (temp2 == temp1) { //first item in sequence matches!!
			for (int j = i; j < i + seq2.size(); j++) { //then check if the rest of the items match
				seq1.get(j, temp1);
				seq2.get(j - i, temp2);
				if (temp1 != temp2) { //if the two items aren't equal
					break;
				}
				//but if all the items in seq2 match elements starting from i in seq1
				else if(j == i+seq2.size()-1){ //if j managed to reach the end of seq2
					startPos = i;
					found = true;
				}
			}
		}
		seq2.get(0, temp2); //reset temp2 to 0th value again for the next iteration
		if (found == true) { //element has been found, no need to loop any more
			break;
		}
	}
	if (found == true) { //if it found one
		return startPos;
	}
	return -1; //temp
}
//want to find starting position in seq1 where the subsequence seq2 appears

void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result) {
	Sequence tempSeq; //if result is the same as seq1 or seq2
	ItemType temp1, temp2; //temp item holders for items from seq1 and seq2
	if (seq1.empty() == true && seq2.empty() == true) {
		result = tempSeq;
		return; //seq1 and seq2 empty, so don't do anything (result is empty too now)
	}
	if (seq1.empty() == true) {
		tempSeq = seq2;
		result = tempSeq;
		return;
	}
	if (seq2.empty() == true) {
		tempSeq = seq1;
		result = tempSeq;
		return;
	}
	int equalSizeAt = -1; //some temp value
	if (seq2.size() > seq1.size()) {
		equalSizeAt = seq1.size();
	}
	else if (seq2.size() <= seq1.size()) {
		equalSizeAt = seq2.size();
	}
	for (int i = equalSizeAt-1; i >=0; i--) { //produce the interwoven list
		seq2.get(i, temp2); //work backwards to insert items
		seq1.get(i, temp1);
		tempSeq.insert(0, temp2);
		tempSeq.insert(0, temp1);
	}
	if (seq2.size() > seq1.size()) { //take care of leftover seq2 elements
		for (int i = equalSizeAt; i < seq2.size(); i++) {
			seq2.get(i, temp2);			
			tempSeq.insert(tempSeq.size(), temp2);
		}
	}
	else if (seq2.size() < seq1.size()) { //take care of leftover seq1 elements
		for (int i = equalSizeAt; i < seq1.size(); i++) {
			seq1.get(i, temp1);
			tempSeq.insert(tempSeq.size(), temp1);
		}
	}
	result = tempSeq;
}
