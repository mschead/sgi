#include <list>
#include "object/object.h"

using namespace std;

class Displayfile {
	
public:

	void addNewObject(Object* object) {
		displayFile.push_back(object);
	}

	Object* getObject() {
		return displayFile.front();
	}

	list<Object*> getObjects() {
		return displayFile;
	}

	int getSize() {
		return displayFile.size();
	}

private:
	list<Object*> displayFile;

};