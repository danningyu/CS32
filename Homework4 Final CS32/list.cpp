void listAll(const Domain* d, string path){
	//problem 4(a)
	//base case is EMPTY vector, NOT d is a nullptr
	if (d->subdomains().empty() == true) {
		cout << path << endl;
		return;
	}
	string original = path;
	for (size_t i = 0; i < d->subdomains().size(); i++) {
			if (d->label() == "") {
				path = d->subdomains().at(i)->label()  + path;
			}
			else {
				path = d->subdomains().at(i)->label() + "." + path;
			}
			listAll(d->subdomains().at(i), path);	
		path = original;	//reset path	
	}
}