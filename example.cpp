#include <iostream>
#include "INI.h"
using namespace std;

int main() {
	//create or open an ini file
	INI ini("example.ini");

	//write some stuff
	ini.property("mySection", "myProperty") = "myValue";
	ini["alpha"]["beta"]="gamma";

	//read some stuff
	cout<<ini["mySection"]["myProperty"]<<endl; //prints "myValue"
	cout<<ini.property("alpha", "beta")<<endl; //prints "gamma"

	//destructor saves changes
}
