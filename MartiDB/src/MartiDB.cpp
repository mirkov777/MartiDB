#include "MartiDB.h"
#include <iostream>

MartiDB::MartiDB() {};

Database MartiDB::createEmptyDatabase(std::string& name) {
	return Database::createEmptyDatabase(name);
};




//using namespace std;
//
//int main()
//{
//	//std::cout << "Hello CMake." << std::endl;
//	return 0;
//}
