
#include "other.h"
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class Singleton {
private:
  // member variables
  String name;
  char charVar254[254] = "VERY Long char[254] variable";
  char charVar25[25] = "Short[25] variable";

  static Singleton *instancePtr;
  // Default constructor
  Singleton() {}

public:
  // deleting copy constructor
  Singleton(const Singleton &obj) = delete;

  static Singleton *getInstance() {
    if (instancePtr == NULL) {
      instancePtr = new Singleton();
      return instancePtr;
    } else {
      return instancePtr;
    }
  }

  char *getCharVar254() {
    return charVar254; // Return pointer to charVar254 array
  }

  char *getCharVar25() {
    return charVar25; // Return pointer to charVar25 array
  }
  // sets values of member variables.
  void setStringName(String name) { this->name = name; }
  String getStringName() { return this->name; }

};
// end of class Singleton
// *******************************************************************************
