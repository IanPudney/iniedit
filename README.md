INIEdit
=========

INIEdit is an INI parser and editor for C++. It is cross-platform and extremely lightweight, consisting only of a single header file. To date, no other INI library offers both editing capabilities and such lightweight, human-readable code.


Documentation
----

Creating and using an INI object is extremely simple. Take a look at the following fully-functional example.
```
INI ini("example.ini");
//read some stuff
cout<<ini["mySection"]["myProperty"];
//write some stuff
ini["alpha"]["beta"]="gamma";
ini.save();
```
This code opens an ini file, reads one property, sets another, and saves.
 - `INI ini("example.ini");` Opens the file example.ini, and loads it into memory. The file is created if it doesn't exist.
 - `cout<<ini["mySection"]["myProperty"];` reads from the property `myProperty` in the section `mySection`. Prints it to the screen.
 - `ini["alpha"]["beta"]="gamma";` Finds the property `beta` in section `alpha` and sets it to the value `gamma`.
 - `ini.save();` Writes changes to disk. This is usually unneccessary, as it is automatically called when an `INI` object is destructed.

##### Reading and writing
```
string& INI::property(const string& sectionName, const string& propertyName)```
Returns a reference to the property named   `propertyName`, located in section `sectionName`. If the property does not exist, it is created (with an empty value). Because this method returns a reference, it can be used for both reading and writing; `x = ini.property(/*...*/)` will assign x to the property's value, whereas `ini.property(/*...*/) = x` will do the opposite.
```
INI::Section& INI::operator[](const string& section)```
This method serves the same purpose as `INI::property()`, but using operator overloads for increased readability. It returns a reference to the section `sectionName` (or creates it if it does not exist. That `Section` is actually a `map<string, string>`, and so individual properties can be accessed with an additional `operator[]`. For example, values can be read with `x = ini["a"]["b"]` and written with `ini["a"]["b"] = x`.
```
string getProperty(const string& sectionName, const string& propertyName)```
_Deprecated: use `property()` or `operator[]` instead_. This method returns the property `propertyName` in section `sectionName`, or creates it if it does not exist. This function has a similar signature to many other parsing libraries, but lacks the simplicity that the rest of this library's methods have.
```
void setProperty(const string& sectionName, const string& propertyName, const string& value);```
_Deprecated: use `property()` or `operator[]` instead_. This method sets the property `propertyName` insection `sectionName` to value `value.` This function has a similar signature to many other parsing libraries, but lacks the simplicity that the rest of this library's methods have. 
##### Opening and closing
```
INI(const string& filename)```
This constructor instantiates an INI object, and immediately opens the file at `filename`. It creates it if it does not exist.
```
INI()```
This default constructor does not open a file. You must call `open()` before attempting to read or write data with this object.
```
INI::open(const string& filename)```
Opens an INI file, or creates it if it doesn't exist. Loads all sections and properties of the file into memory, then closes the file handle. The handle will be reopened on save.
```
INI::save()```
Opens a write handle to the file, writes out the data stored in the object, and closes the write handle. This does not change the state of the INI object; properties remain loaded in memory, and `.save()` can be called again after further changes to re-write the file.

It is usually unneccessary to call this method manually, as `.save()` is called automatically by the destructor. 

```
INI::abort()```
Clears all properties and sets the object to a 'closed' state, but does not write out any properties. This can be useful if a user has decided to exit without saving, or if you are using this library only as a reader and do not wish to have the overhead of re-writing the ini file every time the object is destroyed.

```
~INI()```
Destructor for an `INI` object. If a file is open, this desctructor saves any changes before exiting. If you do not want this behavior, call `abort()` first.
