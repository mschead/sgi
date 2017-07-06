#include "displayfile.h"

void Displayfile::addNewObject(Object* object) {
    displayFile.push_back(object);
}

Object* Displayfile::getObject() {
    return displayFile.front();
}

list<Object*> Displayfile::getObjects() {
    return displayFile;
}

int Displayfile::getSize() {
    return displayFile.size();
}

void Displayfile::deleteAll() {
    displayFile.clear();
}

Object* Displayfile::getObjectByName(char* name) {
    for (Object* object : displayFile) {
        if (strcmp(object->getName(), name) == 0) {
            return object;
        }
    }
}

