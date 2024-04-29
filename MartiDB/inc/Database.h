#ifndef DATABASE_H
#define DATABASE_H

#include <string>

#define DEBUG_CHECK_TRUE(res, msg) \
    if (res == true) { \
        std::cout << msg << std::endl; \
    } else { \
        std::cout << "ERROR ERROR ERROR" << std::endl; \
    }

class Database {
public:
	Database(std::string name, std::string full_path);

	std::string     getDirectory(void);

	static Database createEmptyDatabase(std::string name);
	void            destroy(void);

	void            setKeyValue(std::string key, std::string value); //change to int in the future for <better> error handling
	std::string     getKeyValue(std::string key);

protected:
	std::string m_name;
	std::string m_fullpath;
};

#endif // !DATABASE_H
