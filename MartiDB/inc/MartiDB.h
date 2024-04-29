#ifndef MARTIDB_H
#define MARTIDB_H

#include <Database.h>

class MartiDB {
public:
	MartiDB();

	static Database createEmptyDatabase(std::string& name);
};

#endif // MARTIDB_H.
