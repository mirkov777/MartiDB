#include <iostream>
#include <filesystem>
#include <fstream>

#include "Database.h"

namespace fs = std::filesystem;

Database::Database(std::string dbname, std::string full_path) : m_name(dbname), m_fullpath(full_path) { std::cout << m_fullpath << std::endl; };

Database Database::createEmptyDatabase(std::string dbname) {
	std::string base_dir("./MartiDB");
	if (!fs::exists(base_dir)) {
		fs::create_directory(base_dir);
	}

	std::string database_folder(base_dir + "/" + dbname);
	if (!fs::exists(database_folder)) {  
		fs::create_directory(database_folder);
	}

	return Database(dbname, database_folder);
};

Database Database::load(std::string dbname) {
	std::string base_dir("./MartiDB");
	std::string database_folder(base_dir + "/" + dbname);

	return Database(dbname, database_folder);
}

void Database::destroy() {
	if (fs::exists(m_fullpath)) {
		fs::remove_all(m_fullpath);
		//std::uintmax_t n(fs::remove_all(m_fullpath));
		//std::cout << n + "files removed upon database destruction" << std::endl;
	}
}

std::string Database::getDirectory() {
	return m_fullpath;
};

void Database::setKeyValue(std::string key, std::string value) {
	std::ofstream ofs;
	std::string kv_file(m_fullpath + "/" + key + "_string.kv");

	ofs.open(kv_file, std::ofstream::out | std::ofstream::trunc);
	ofs << value;
	ofs.close();
}

std::string Database::getKeyValue(std::string key) {
	std::string kv_file(m_fullpath + "/" + key + "_string.kv");
	//std::string read_value;
	std::ifstream ifs;

	ifs.open(kv_file, std::ifstream::in);
	std::string read_value(
		(std::istreambuf_iterator<char>(ifs)),
		std::istreambuf_iterator<char>()
	);

	ifs.close();

	return read_value;
}