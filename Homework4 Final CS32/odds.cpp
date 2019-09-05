void removeOdds(vector<int>& v) {
	auto iter = v.begin();
	while (iter != v.end()) {
		if ((*iter) % 2 == 1) {
			iter = v.erase(iter);
		}
		else {
			iter++;
		}
	}
}