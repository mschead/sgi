#include <list>
#include "object/object.h"

using namespace std;

class Displayfile {
	
public:

	void addNewObject(Object object) {
		displayFile.push_back(object);
	}

	Object getObject() {
		return displayFile.front();
	}

private:
	list<Object> displayFile;

};