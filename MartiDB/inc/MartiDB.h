#ifndef MARTIDB_H
#define MARTIDB_H

#include "database.h"

namespace martidb {

	class MartiDB {
	public:
		MartiDB();

		static const std::unique_ptr<IDatabase> createEmptyDatabase(std::string& name);

		static const std::unique_ptr<IDatabase> loadDatabase(std::string& name);
	};

}

#endif // MARTIDB_H.
