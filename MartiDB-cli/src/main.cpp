//Own includes
#include "martidb.h"
//System includes
#include <iostream>
#include <memory>
//Other includes
#include <cxxopts.hpp>

#define FIRST_ARG 1

using namespace martidb;

void printUsage() {
	std::cout << "Usage: " << std::endl; //#TODO
}

//Make this more robust and make it a fully functioning cli (loop)
int main(int argc, char* argv[]) {

	std::unique_ptr<cxxopts::Options> allocated(new cxxopts::Options("MartiDB-cli", "Command line interface for MartiDb"));
	auto& options = *allocated;

	options.add_options()
		("c, create", "Create a database.")
		("d, destroy", "Destroy an existing database.")
		("n, name", "Name for the database (required)", cxxopts::value<std::string>())
		("s, set", "Instert a key into the database.")
		("g, get", "Retrieve a key from the database.")
		("k, key", "Key to be inserted/retrieved.", cxxopts::value<std::string>())
		("v, value", "Value to be set for a key.", cxxopts::value<std::string>())
	;

	auto result = options.parse(argc, argv);

	if (result.count("c") == FIRST_ARG) {
		if (result.count("n") == 0) {
			std::cout << "Missing name argument. (hint: -n)" << std::endl;
			return 1;
		}

		std::string dbname(result["n"].as<std::string>());
		std::unique_ptr<martidb::IDatabase> db(MartiDB::createEmptyDatabase(dbname));

		return 0;
	}

	if (result.count("s") == FIRST_ARG) {
		if (result.count("n") == 0) {
			std::cout << "Missing name argument. (hint: -n)" << std::endl;
			return 1;
		}
		if (result.count("k") == 0) {
			std::cout << "Missing key name. (hint: -k)" << std::endl;
			return 1;
		}
		if (result.count("v") == 0) {
			std::cout << "Missing value. (hint: -v)" << std::endl;
			return 1;
		}

		std::string dbname(result["n"].as<std::string>());
		std::string read_key(result["k"].as<std::string>());
		std::string read_value(result["v"].as<std::string>());

		std::unique_ptr<martidb::IDatabase> db(MartiDB::loadDatabase(dbname));
		db->setKeyValue(read_key, read_value);

		return 0;
	}

	if (result.count("g") == FIRST_ARG) {
		if (result.count("n") == 0) {
			std::cout << "Missing name argument. (hint: -n)" << std::endl;
			return 1;
		}

		if (result.count("k") == 0) {
			std::cout << "Missing key name. (hint: -k)" << std::endl;
			return 1;
		}

		std::string dbname(result["n"].as<std::string>());
		std::string read_key(result["k"].as<std::string>());

		std::unique_ptr<martidb::IDatabase> db(MartiDB::loadDatabase(dbname));
		std::cout << db->getKeyValue(read_key) << std::endl;

		return 0;
	}

	if (result.count("d") == FIRST_ARG) {
		if (result.count("n") == 0) {
			std::cout << "Missing name argument. (hint: -n)" << std::endl;
			return 1;
		}

		std::string dbname(result["n"].as<std::string>());
		std::unique_ptr<martidb::IDatabase> db(MartiDB::loadDatabase(dbname));

		db->destroy();

		return 0;
	}

	std::cout << "No valid arguments passed!" << std::endl;
	printUsage();

	return 1;
}