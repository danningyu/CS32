#include <iostream>
#include "newSequence.h"

Sequence::Sequence():m_size(0) {
	m_seq = new ItemType[DEFAULT_MAX_ITEMS];
	m_seqMaxSize = DEFAULT_MAX_ITEMS;
}
Sequence::Sequence(int numItems):m_size(0) {
	m_seqMaxSize = numItems;
	m_seq = new ItemType[numItems];
}

Sequence::Sequence(const Sequence& otherSeq):m_size(otherSeq.m_size), m_seqMaxSize(otherSeq.m_seqMaxSize) {
	m_seq = new ItemType[otherSeq.m_seqMaxSize];
	for (int i = 0; i < m_size; i++) {
		m_seq[i] = otherSeq.m_seq[i];
	}
}
Sequence::~Sequence() {
	delete[] m_seq;
	//why don't you need to delete the pointer here??
}
Sequence& Sequence::operator=(const Sequence& rhs) { //need to fix swap down below
	if (this != &rhs) {
		Sequence temp(rhs);
		swap(temp);
	}
	return *this;
}
bool Sequence::empty() const {
	if (m_size == 0) {
		return true;
	}
	return false;
}
// Return true if the sequence is empty, otherwise false.

int Sequence::size() const {
	return m_size;
}
// Return the number of items in the sequence.

int Sequence::insert(int pos, const ItemType& value) {
	if (pos >= 0 && pos <= m_size && m_size < m_seqMaxSize) {
		//within the current array and there's space to add another object
		for (int i = m_size - 1; i >= pos; i--) {
			m_seq[i + 1] = m_seq[i]; //shift everything up
		}
		m_seq[pos] = value;
		m_size++; //update m_size
		return pos;
	}
	return -1;
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
	//locate p, then call the insert function implemented above
	int p = DEFAULT_MAX_ITEMS + 1; //some impossible value
	for (int i = m_size - 1; i >= 0; i--) {
		if (value <= m_seq[i]) {
			p = i;
		}
	}
	if (p == DEFAULT_MAX_ITEMS + 1) { //no such item exists
		p = m_size;
	}
	int result = insert(p, value); //insert it and assign the output to result
	return result;
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
	if (pos >= 0 && pos < m_size) {
		for (int i = pos; i < m_size - 1; i++) {
			m_seq[i] = m_seq[i + 1]; //move each element down
		}
		m_size--;
		return true;
	}
	return false;
}
// If 0 <= pos < size(), remove the item at position pos from
// the sequence (so that all items that followed that item end up at
// positions one lower than they were at before), and return true.
// Otherwise, leave the sequence unchanged and return false.

int Sequence::remove(const ItemType& value) {
	int counter = 0;
	for (int i = 0; i < m_size; i++) {
		if (m_seq[i] == value) {
			counter++;
			erase(i);
			i--; //decrement to account for shrinking
		}
	}
	return counter;
}
// Erase all items from the sequence that == value.  Return the
// number of items removed (which will be 0 if no item == value).

bool Sequence::get(int pos, ItemType& value) const {
	if (pos >= 0 && pos < m_size) {
		value = m_seq[pos];
		return true;
	}
	return false;
}
// If 0 <= pos < size(), copy into value the item at position pos
// of the sequence and return true.  Otherwise, leave value unchanged
// and return false.

bool Sequence::set(int pos, const ItemType& value) {
	if (pos >= 0 && pos < m_size) {
		m_seq[pos] = value;
		return true;
	}
	return false;
}
// If 0 <= pos < size(), replace the item at position pos in the
// sequence with value and return true.  Otherwise, leave the sequence
// unchanged and return false.

int Sequence::find(const ItemType& value) const {
	int p = DEFAULT_MAX_ITEMS + 1; //some impossible value
	for (int i = m_size - 1; i >= 0; i--) {
		if (value == m_seq[i]) {
			p = i;
		}
	}
	if (p == DEFAULT_MAX_ITEMS + 1) { //no such item exists
		p = -1;
	}
	return p;
}
// Let p be the smallest integer such that value == the item at
// position p in the sequence; if no such item exists, let p be -1.
// Return p.

void Sequence::swap(Sequence& other) {
	int temp_size = m_size; //switch size
	m_size = other.m_size;
	other.m_size = temp_size;
	ItemType* tempPtr = m_seq; //switch pointers
	m_seq = other.m_seq;
	other.m_seq = tempPtr;
	int tempMaxSize = m_seqMaxSize; //switch max size
	m_seqMaxSize = other.m_seqMaxSize;
	other.m_seqMaxSize = tempMaxSize;
	tempPtr = nullptr; //deinitialize the temp pointer
}
// Exchange the contents of this sequence with the other one.

/*
void Sequence::dump() const {
	for (int i = 0; i < m_size; i++) {
		std::cerr << m_seq[i] << std::endl;
	}
}
*/