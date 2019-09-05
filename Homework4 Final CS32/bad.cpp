void removeBad(list<Movie*>& li){
	auto iter = li.begin();
	while (iter != li.end()) {
		if ((*iter)->rating() < 55) {
			Movie* temp = *iter;
			iter = li.erase(iter);
			delete temp;
		}
		else {
			iter++;
		}
	}
}