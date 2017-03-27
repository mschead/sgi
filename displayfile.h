#include <list>
#include "object.h"

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

    void deleteAll() {
		displayFile.clear();
	}

	Object* getObjectByName(char* name) {
		for (Object* object : displayFile) {
			// printf("%s\n", object->getName());
			if (strcmp(object->getName(), name) == 0) {
				return object;
			}
		}
	}

private:
	list<Object*> displayFile;

};
