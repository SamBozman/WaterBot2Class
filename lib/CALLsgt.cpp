
// initializing instancePtr with NULL
Singleton *Singleton ::instancePtr = NULL;
// Place this above setup() for global scope

// Place choice bits withing functions that need to access the Singleton variable(s)
Singleton *sgt = Singleton ::getInstance();
  char *ptr;

  ptr = sgt->getCharVar254();
  debug("Length of array254 is ");
  debugln(strlen(ptr));

  ptr = sgt->getCharVar25();
  debug("Length of array25 is ");
  debugln(strlen(ptr));

  
  sgt->setStringName("Manish");
  String theName = sgt->getStringName();
  debug("sgt set the name to ");
  debugln(theName);

  Singleton *gfg = Singleton ::getInstance();

  // setting values of member variables.
  gfg->setStringName("Vartika");
  theName = gfg->getStringName();
  debug("gfg set the name to ");
  debugln(theName);