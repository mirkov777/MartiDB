#include <catch2/catch_test_macros.hpp>

#include "MartiDB.h"

TEST_CASE("Store and retrive key-value pairs", "") {
	SECTION("Correct value is returned for a specific key.") {
		//Setup
		std::string db_name("test_database_123");
		Database db = MartiDB::createEmptyDatabase(db_name);
		std::string key = "special_key";
		std::string expected_value = "12345 is a cool number!";

		//Set key-value pair
		db.setKeyValue(key, expected_value);
		//Check correct value is retrieved
		REQUIRE(db.getKeyValue(key) == expected_value);

		//Cleanup
		db.destroy();
	}
}