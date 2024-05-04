#include <string>
#include <filesystem>
#include <catch2/catch_test_macros.hpp>

#include "MartiDB.h"

namespace fs = std::filesystem;

TEST_CASE("Database is successfully created.", "[database-managment]") {

    SECTION("Database is initialized with default settings.") {
        //Setup
        std::string db_name("test_database_123");
        Database db = MartiDB::createEmptyDatabase(db_name);

        //Check database folder is created
        REQUIRE(fs::is_directory(fs::status(db.getDirectory())));

        //Check database folder is empty after creation
        const auto& p = fs::directory_iterator(db.getDirectory());
        REQUIRE(begin(p) == end(p));

        //Cleanup
        db.destroy();
        REQUIRE(!fs::exists(fs::status(db.getDirectory())));
    }

}

TEST_CASE("Database is successfully loaded.", "[database-managment]") {

    SECTION("Database is initialized with default settings.") {
        //Setup
        std::string db_name("test_database_123");
        Database db = MartiDB::createEmptyDatabase(db_name);

        Database db_inst = MartiDB::loadDatabase(db_name);

        //Check database folder is created
        REQUIRE(fs::is_directory(fs::status(db_inst.getDirectory())));

        //Check database folder is empty after creation
        const auto& p = fs::directory_iterator(db_inst.getDirectory());
        REQUIRE(begin(p) == end(p));

        //Cleanup
        db.destroy();
        REQUIRE(!fs::exists(fs::status(db_inst.getDirectory())));
    }

}