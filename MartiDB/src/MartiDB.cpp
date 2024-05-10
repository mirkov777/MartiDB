//Own includes
#include "martidb.h"
#include "extensions/database_ext.h"

using namespace martidb;
using namespace martidbext;

	MartiDB::MartiDB() {};

	const std::unique_ptr<IDatabase> MartiDB::createEmptyDatabase(std::string& name) {
		return EmbeddedDatabase::createEmptyDatabase(name);
	};

	const std::unique_ptr<IDatabase> MartiDB::loadDatabase(std::string& name) {
		return EmbeddedDatabase::load(name);
	}
