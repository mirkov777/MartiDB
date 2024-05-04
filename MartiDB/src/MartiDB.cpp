#include "MartiDB.h"
#include <iostream>

MartiDB::MartiDB() {};

Database MartiDB::createEmptyDatabase(std::string& name) {
	return Database::createEmptyDatabase(name);
};

Database MartiDB::loadDatabase(std::string& name) {
	return Database::load(name);
}


//using namespace std;
//
//int main()
//{
//	//std::cout << "Hello CMake." << std::endl;
//	return 0;
//}
