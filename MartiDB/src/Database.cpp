//Own includes
#include "database.h"
#include "extensions/database_ext.h"

//System includes
#include <iostream>
#include <filesystem>
#include <fstream>
#include <unordered_map>

//Defines
#define FILE_DELIM "_"

namespace fs = std::filesystem;

using namespace martidb;
using namespace martidbext;

	//Embedded Database Impl
	class EmbeddedDatabase::Impl : public IDatabase {
	public:
		Impl(std::string dbname, std::string full_path);
		~Impl();

		std::string                             getDirectory(void);

		//Managment
		static const std::unique_ptr<IDatabase> createEmptyDatabase(std::string name);
		static const std::unique_ptr<IDatabase> load(std::string name);
		void                                    destroy(void);

		//Key-Value
		void                                    setKeyValue(std::string key, std::string value); //Maybe change to int in the future for <better> error handling
		std::string                             getKeyValue(std::string key);

	private:
		std::string m_name;
		std::string m_fullpath;
		std::unordered_map<std::string, std::string> m_keyValueStore;
	};

	EmbeddedDatabase::Impl::Impl(std::string dbname, std::string full_path) : m_name(dbname), m_fullpath(full_path) {
		//Load .kv files into memory
		for (const auto& p : fs::directory_iterator(getDirectory())) {
			if (p.exists() && p.is_regular_file()) {
				fs::path filename = p.path().filename();
				if (filename.extension() == ".kv") {
					std::string key = filename.string().substr(0, filename.string().find(FILE_DELIM));

					std::ifstream ifs;
					ifs.open(p.path(), std::ifstream::in);
					std::string value(
						(std::istreambuf_iterator<char>(ifs)),
						std::istreambuf_iterator<char>()
					);
					ifs.close();

					//std::cout << "Inserting pair into hashmap {" + key + ": " + value + "}" << std::endl;
					m_keyValueStore.insert({ key, value });

				}
			}

		}

	};

	EmbeddedDatabase::Impl::~Impl() {
		//Optionaly flush latest known state to disc here
	};

	//Managment functions
	const std::unique_ptr<IDatabase> EmbeddedDatabase::Impl::createEmptyDatabase(std::string dbname) {
		std::string base_dir("./MartiDB");
		if (!fs::exists(base_dir)) {
			fs::create_directory(base_dir);
		}

		std::string database_folder(base_dir + "/" + dbname);
		if (!fs::exists(database_folder)) {
			fs::create_directory(database_folder);
		}

		return std::make_unique<EmbeddedDatabase::Impl>(dbname, database_folder);
	};

	const std::unique_ptr<IDatabase> EmbeddedDatabase::Impl::load(std::string dbname) {
		std::string base_dir("./MartiDB");
		std::string database_folder(base_dir + "/" + dbname);

		return std::make_unique<EmbeddedDatabase::Impl>(dbname, database_folder);
	}

	void EmbeddedDatabase::Impl::destroy() {
		if (fs::exists(m_fullpath)) {
			fs::remove_all(m_fullpath);
		}
		m_keyValueStore.clear();
	}

	//Instance functions
	std::string EmbeddedDatabase::Impl::getDirectory() {
		return m_fullpath;
	};

	void EmbeddedDatabase::Impl::setKeyValue(std::string key, std::string value) {
		std::ofstream ofs;
		std::string kv_file(m_fullpath + "/" + key + "_string.kv");

		ofs.open(kv_file, std::ofstream::out | std::ofstream::trunc);
		ofs << value;
		ofs.close();

		m_keyValueStore.insert({ key, value });
	}

	std::string EmbeddedDatabase::Impl::getKeyValue(std::string key) {
		const auto& v = m_keyValueStore.find(key);

		if (v == m_keyValueStore.end()) {
			return "Key not found!"; //#TODO better error handling
		}

		return v->second;
	}


	//Embedded Database

	EmbeddedDatabase::EmbeddedDatabase(std::string dbname, std::string full_path) : m_Impl(std::make_unique<EmbeddedDatabase::Impl>(dbname, full_path)) {};

	EmbeddedDatabase::~EmbeddedDatabase() {};

	const std::unique_ptr<IDatabase> EmbeddedDatabase::createEmptyDatabase(std::string dbname) {
		return EmbeddedDatabase::Impl::createEmptyDatabase(dbname);
	};

	const std::unique_ptr<IDatabase> EmbeddedDatabase::load(std::string dbname) {
		return EmbeddedDatabase::Impl::load(dbname);
	}

	void EmbeddedDatabase::destroy() {
		m_Impl->destroy();
	}

	//Instance functions
	std::string EmbeddedDatabase::getDirectory() {
		return m_Impl->getDirectory();
	};

	void EmbeddedDatabase::setKeyValue(std::string key, std::string value) {
		m_Impl->setKeyValue(key, value);
	}

	std::string EmbeddedDatabase::getKeyValue(std::string key) {
		return m_Impl->getKeyValue(key);
	}
