#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <memory>

namespace martidb {

	class IDatabase {
	public:
		IDatabase() = default;
		virtual ~IDatabase() = default;
		virtual std::string                       getDirectory(void) = 0;

		//Managment
		static const std::unique_ptr<IDatabase>   createEmptyDatabase(std::string name);
		static const std::unique_ptr<IDatabase>   load(std::string name);
		virtual void                              destroy(void) = 0;

		//Key-Value
		virtual void                              setKeyValue(std::string key, std::string value) = 0; //Maybe change to int in the future for <better> error handling
		virtual std::string                       getKeyValue(std::string key) = 0;

	private:
		 
	};

}

#endif // !DATABASE_H
