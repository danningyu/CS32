#include "ScoreList.h"

ScoreList::ScoreList() {
	
}

bool ScoreList::add(unsigned long score) {
	if (score <= 100) {
		if (m_scores.insert(score) == -1) {
			return false;
		}
		return true;
	}
	return false;
}

bool ScoreList::remove(unsigned long score) {
	if (m_scores.empty() == true) {
		return false;
	}
	int pos = m_scores.find(score);
	if (pos == -1) { //failed to find the item
		return false;
	}
	bool result = m_scores.erase(pos);
	if (result == true) {
		return true;
	}
	return false;
}
int ScoreList::size() const {
	return m_scores.size();
}

unsigned long ScoreList::minimum() const {
	unsigned long result = NO_SCORE; //an impossible value
	if (m_scores.empty() == true) {
		return NO_SCORE;
	}
	m_scores.get(0, result); //0th element should be smallest if code implemented correctly
	return result;
}

unsigned long ScoreList::maximum() const {
	if (m_scores.empty() == true) {
		return NO_SCORE;
	}
	unsigned long result = -1; //an impossible value
	m_scores.get(m_scores.size() - 1, result);
	return result;
}