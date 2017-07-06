#include <list>
#include <string.h>
#include "object.h"

using namespace std;

class Displayfile {
public:

    void addNewObject(Object* object);
    Object* getObject();
    list<Object*> getObjects();
    int getSize();
    void deleteAll();
    Object* getObjectByName(char* name);

private:
    list<Object*> displayFile;

};
