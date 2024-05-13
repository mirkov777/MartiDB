//Own includes
#include "martidb.h"
//System includes
#include <filesystem>
//Other includes
#include <catch2/catch_test_macros.hpp>

namespace fs = std::filesystem;

using namespace martidb;

TEST_CASE("Database is successfully created.", "[database-managment]") {

    SECTION("Database is initialized with default settings.") {
        //Setup
        std::string db_name("test_database_123");
        std::unique_ptr<martidb::IDatabase> db = MartiDB::createEmptyDatabase(db_name);

        //Check database folder is created
        REQUIRE(fs::is_directory(fs::status(db->getDirectory())));

        //Check database folder is empty after creation
        const auto& p = fs::directory_iterator(db->getDirectory());
        REQUIRE(begin(p) == end(p));

        //Cleanup
        db->destroy();
        REQUIRE(!fs::exists(fs::status(db->getDirectory())));
    }

}

TEST_CASE("Database is successfully loaded.", "[database-managment]") {

    SECTION("Database is initialized with default settings.") {
        //Setup
        std::string db_name("test_database_123");
        std::unique_ptr<martidb::IDatabase> db = MartiDB::createEmptyDatabase(db_name);

        std::unique_ptr<martidb::IDatabase> db_inst = MartiDB::loadDatabase(db_name);

        //Check database folder is created
        REQUIRE(fs::is_directory(fs::status(db_inst->getDirectory())));

        //Check database folder is empty after creation
        const auto& p = fs::directory_iterator(db_inst->getDirectory());
        REQUIRE(begin(p) == end(p));

        //Cleanup
        db->destroy();
        REQUIRE(!fs::exists(fs::status(db_inst->getDirectory())));
    }

}