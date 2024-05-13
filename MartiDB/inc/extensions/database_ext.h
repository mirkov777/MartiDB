#ifndef DATABASE_EXT_H
#define DATABASE_EXT_H

#include "database.h"

namespace martidbext {

using namespace martidb;

// EmbeddedDatabase (currently the binary has the database libraries built into it and that manages its own database so its not a separate thing)
class EmbeddedDatabase : public IDatabase {
public:
	EmbeddedDatabase(std::string dbname, std::string full_path);
	~EmbeddedDatabase();

	std::string                             getDirectory(void);

	//Managment
	static const std::unique_ptr<IDatabase> createEmptyDatabase(std::string name);
	static const std::unique_ptr<IDatabase> load(std::string name);
	void                                    destroy(void);

	//Key-Value
	void                                    setKeyValue(std::string key, std::string value); //Maybe change to int in the future for <better> error handling
	std::string                             getKeyValue(std::string key);

	class Impl;
private:
	std::unique_ptr<Impl> m_Impl;
};

}
#endif //DATABASE_EXT_H