#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <chrono>
#include <vector>
#include <functional>
#include <cctype>
using namespace std;
using namespace std::chrono;

#if defined(_MSC_VER)  &&  !defined(_DEBUG)
#include <iostream>
#include <windows.h>
#include <conio.h>

struct KeepWindowOpenUntilDismissed
{
	~KeepWindowOpenUntilDismissed()
	{
		DWORD pids[1];
		if (GetConsoleProcessList(pids, 1) == 1)
		{
			std::cout << "Press any key to continue . . . ";
			_getch();
		}
	}
} keepWindowOpenUntilDismissed;
#endif

const int CHARS_PER_NODE = 9; //set at 8 for now, lower should be more resolution (but slower)
const int HASH_TABLE_SIZE = 15661; //~15k for now? need to test
const int ADD_COPY_CUTOFF = 5; //decreasing it makes copies more prevalent
//5 seems to be optimal

struct Node {
	string m_data;
	Node* m_next = nullptr;
	vector<int> m_offsets;
	Node(string data) :m_data(data) {}
	Node() {}
};

void createDiff(istream& fold, istream& fnew, ostream& fdiff);
bool applyDiff(istream& fold, istream& fdiff, ostream& fnew);

bool getCommand(istream& inf, char& cmd, int& length, int& offset);
bool getInt(istream& inf, int& n);
string istreamToStr(istream &in);

void createDiff(istream& fold, istream& fnew, ostream& fdiff) {
	//high_resolution_clock::time_point t1Func = high_resolution_clock::now();
	hash<string> hashFunc;
	if (!fold || !fnew) {
		//file can't be opened
		cerr << "Error opening files" << endl;
		return;
	}
	int collisionCounter = 0; //hash metrics, can take out later
	int repeatsCounter = 0;//hash metrics, can take out later
	Node* hashTable[HASH_TABLE_SIZE]; //will be filled with empty Nodes
	for (int i = 0; i < HASH_TABLE_SIZE; i++) {
		hashTable[i] = nullptr; //initialize all to nullptr
	}
	string strDiff = "";
	string strOld = istreamToStr(fold);
	string strNew = istreamToStr(fnew);
	bool inserted = false;
	//special case if the str size is less than CHARS_PER_NODE
	if (strOld.size() < CHARS_PER_NODE) {
		hashTable[hashFunc(strOld) % HASH_TABLE_SIZE] = new Node(strOld); //no offset
		hashTable[hashFunc(strOld) % HASH_TABLE_SIZE]->m_offsets.push_back(0); //add the offset of 0
	}
	//otherwise, hash it normally
	else {
		for (size_t i = 0; i < strOld.size() - CHARS_PER_NODE; i++) {
			string newChunk = strOld.substr(i, CHARS_PER_NODE);
			int key = hashFunc(strOld.substr(i, CHARS_PER_NODE)) % HASH_TABLE_SIZE;
			if (hashTable[key] == nullptr) { //no element there, so add one
				hashTable[key] = new Node(newChunk);
				hashTable[key]->m_offsets.push_back(i); //push back the offset i
			}
			else { //collision detected
				collisionCounter++;
				Node* temp = hashTable[key];
				while (temp->m_next != nullptr) { //add to the end of the list
					if (temp->m_data == newChunk) { //repeat value found 
						inserted = true;
						repeatsCounter++;
						temp->m_offsets.push_back(i); //just add the offset
						break;
					}
					temp = temp->m_next;
				}
				if (inserted == false) {
					Node* ptr = new Node(strOld.substr(i, CHARS_PER_NODE));
					ptr->m_offsets.push_back(i); //add the offset value
					temp->m_next = ptr;//add the new node to the list
				}
			}
			inserted = false; //reset inserted
		} //done hashing
	}
	
	// now start taking sequences from the new string
	size_t i = 0;
	for (; i < strNew.size() - CHARS_PER_NODE; i++) {
		char key = strNew.at(i);
		string newChunk = strNew.substr(i, CHARS_PER_NODE); //string to be examined from new file		
		int offset = -1;
		if (hashTable[hashFunc(newChunk) % HASH_TABLE_SIZE] == nullptr) { //match not found in table			
			strDiff = strDiff + "A1:" + key; //then just add the current character, check starting from next			
			continue; //skip the rest of the stuff in the loop
		}
		else { //match POTENTIALLY found due to matching hash, but NOT guaranteed
			Node* temp = hashTable[hashFunc(newChunk) % HASH_TABLE_SIZE];
			vector<int> matchingData;
			int copyCounter = 0;
			int copyCounterBest = 0; //for the best copyCounter
			int offsetBest = -1; //for the best offset
			while (temp != nullptr) { //this while loop should be redundant but keep it in for now
				if (temp->m_data == newChunk) {
					for (size_t j = 0; j < temp->m_offsets.size(); j++) {
						matchingData.push_back(temp->m_offsets.at(j)); //add the offsets to the matchingData
					}
				}
				temp = temp->m_next; //increment to next one
				//this line should be redundant
			}
			//CASE 1: now have a vector filled with all the first matches
			if (matchingData.empty() == false) { //alternatively, found == true
				for (size_t j = 0; j < matchingData.size(); j++) { //find the pathway with longest match
					size_t k = 0; //set and reset k
					int copyCounterTemp = CHARS_PER_NODE; //starts at 8, set/reset
					while (i + CHARS_PER_NODE + k < strNew.size() && matchingData.at(j) + CHARS_PER_NODE + k < strOld.size() &&  //check size bounds
						strNew.at(k + CHARS_PER_NODE + i) == strOld.at(matchingData.at(j) + k + CHARS_PER_NODE)) {
						k++;
						copyCounterTemp++;
					}
					if (copyCounterTemp > copyCounterBest) {
						copyCounterBest = copyCounterTemp;
						offsetBest = matchingData.at(j);

					}
				}
				i = i + copyCounterBest; //skip everything that's been found in the main for loop
				copyCounter = copyCounterBest; //save the best values
				offset = offsetBest;//save the best values
				strDiff = strDiff + "C" + to_string(copyCounter) + "," + to_string(offset); //convert to C(len),(offset) cmd
				i--; //roll back by 1 b/c loop will do i++
				continue; //skip everything in the for-loop because you're done processing i strings																						   //break; //at least one match was found so break out of while loop
			}
			//CASE 2: no exact matches found...found == false OR matchingData.empty() == true
			//but somehow a hash matches a non-nullptr element in hash table			
			else if (matchingData.empty() == true) {
				//let's find the best # of matches instead
				string bestPartialMatch = "";
				int countMatches = 0;
				int bestNumMatches = 0;
				for (int j = 0; j < HASH_TABLE_SIZE; j++) {
					if (hashTable[j] != nullptr) {
						int k = 0;
						//what if the value is not the first in the linked list?						
						while (k < CHARS_PER_NODE && hashTable[j]->m_data.at(k) == newChunk.at(k)) {
							countMatches++; //one match found
							k++; //check next character
						}
					}
					if (countMatches > bestNumMatches) { //one with more matches found						
						bestNumMatches = countMatches;
						offset = hashTable[j]->m_offsets.at(0); //record the offset at which this occurs, 
																//any one of them is fine, want lower number for shorter									
					}
					countMatches = 0; //reset countMatches
				} //end FOR loop
				//bestNumMatches is updated, offset is the right one, closestMatch points to that node
				if (bestNumMatches > ADD_COPY_CUTOFF) {
					//5-8 matching chars, so a copy command is shorter: C(len),(offset)
					strDiff = strDiff + "C" + to_string(bestNumMatches) + "," + to_string(offset); //copy the chars that are the same
				}
				else if (bestNumMatches <= ADD_COPY_CUTOFF) {//matching hash found but no matching string, so take the best one
					//1-4 matching chars, so an add command is better: A(len):(whatToAdd)
					strDiff = strDiff + "A" + to_string(bestNumMatches) + ":" + strOld.substr(offset, bestNumMatches);
				}
				i = i + bestNumMatches - 1; //advance by number of matches found, and adjust by 1 again for i++
			} //end ELSE-IF
			if (offset == -1) { //hash matches but no actual matching element found			
				strDiff = strDiff + "A1:" + key; //then just add the current character, check starting from next				
				continue;
			}
		}
	} //end main FOR loop	
	if (i < strNew.size()) { //there's elements left to process
		strDiff = strDiff + "A" + to_string(strNew.substr(i).size()) + ":" + strNew.substr(i);
	}

	//now consolidate the strDiff file
	string newDiff = "";
	string addStore = "";
	string stringInt = "";
	bool shouldConsolidate = false;
	int addCounter = 0;
	for (size_t i = 0; i < strDiff.size(); i++) {
		while (i < strDiff.size() && strDiff.at(i) == 'A') { //add command found; format: A(len):(whatToAdd)
			shouldConsolidate = true;
			i++; //i is now on starting length number	
			while (isdigit(strDiff.at(i))) { //keep adding digits till you hit the colon
				stringInt += strDiff.at(i);
				i++;
			} //terminates when strDiff.at(i) is :
			addCounter += stoi(stringInt);
			i++; //now read in the chars
			for (int j = 0; j < stoi(stringInt); j++) {
				addStore += strDiff.at(i + j); //i, plus how much offset
			}
			i += stoi(stringInt); //increment i to past whatToAdd
			stringInt = "";
		}
		if (shouldConsolidate == true) {
			newDiff = newDiff + "A" + to_string(addCounter) + ":" + addStore;
			i--; //because i is currently what should start, but the for loop will increment it too
		}
		else if (shouldConsolidate == false) {
			newDiff = newDiff + strDiff.at(i);
		}
		addCounter = 0; //reset variables
		addStore = "";
		shouldConsolidate = false;
	}

	//convert the string into an ostream file

	if (!fdiff) {
		cerr << "Bad file" << endl;
		return;
	}
	for (size_t i = 0; i < newDiff.size(); i++) {
		fdiff << newDiff.at(i);
	}
}

string istreamToStr(istream &in) {
	string result;
	char buffer[4096];
	while (in.read(buffer, sizeof(buffer)))
		result.append(buffer, sizeof(buffer));
	result.append(buffer, in.gcount());
	return result;
}

bool getInt(istream& inf, int& n) {
	char ch;
	if (!inf.get(ch) || !isascii(ch) || !isdigit(ch))
		return false;
	inf.unget();
	inf >> n;
	return true;
}

bool getCommand(istream& inf, char& cmd, int& length, int& offset) {
	if (!inf.get(cmd))
	{
		cmd = 'x';  // signals end of file
		return true;
	}
	char ch;
	switch (cmd)
	{
	case 'A':
		return getInt(inf, length) && inf.get(ch) && ch == ':';
	case 'C':
		return getInt(inf, length) && inf.get(ch) && ch == ',' && getInt(inf, offset);
	case '\r':
	case '\n':
		return true;
	}
	cerr << cmd << endl;
	return false;
}

bool applyDiff(istream& fold, istream& fdiff, ostream& fnew) {
	string strOld = "";
	if (!fold || !fdiff) {
		//file can't be opened
		return false;
	}
	if (!fnew) {
		return false;
	}
	strOld = istreamToStr(fold); //note: this kills fold (makes it empty)
	char cmd = 'T'; //some random value
	int length = 0;
	int offset = 0;
	while (cmd != 'x') {
		if (getCommand(fdiff, cmd, length, offset) == false) {
			return false; //bad sequence of chars found
		}
		if (offset < 0 || length < 0 || length>strOld.size() || offset >= strOld.size() || length>strOld.size() - offset) {
			//cerr << "Bad sequence found 4" << endl;
			return false;
		}

		if (cmd == 'C') {
			fnew << strOld.substr(offset, length);
		}
		else if (cmd == 'A') {
			while (length > 0) {
				fnew << char(fdiff.get()); //typecast as char
				length--;
			}
		}
		else if (cmd == '\n' || cmd == '\r') {
			continue;
		}
	}
	return true;
}

int main() {
	ofstream outfdiff1("diff1.txt");
	ifstream infsmallmart1("warandpeace1.txt");
	ifstream infsmallmart1B("warandpeace1.txt");
	ifstream infsmallmart2("warandpeace2.txt");
	ifstream infdiff2("diff2.txt");
	ofstream outfoutput("output.txt");
	//outfile2 should be the same as infile2

	//cerr << "Calling createDiff" << endl;
	createDiff(infsmallmart1, infsmallmart2, outfdiff1);

	//cerr << "Testing applyDiff" << endl;
	//applyDiff(infsmallmart1B, infdiff2, outfoutput);

	cerr << "Done testing functions" << endl;
	return 0;
}