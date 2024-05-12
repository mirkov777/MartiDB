//Own includes
#include "martidb.h"
//System includes
#include <iostream>
#include <filesystem>
#include <chrono>
#include <unordered_map>
//Other includes
#include <catch2/catch_test_macros.hpp>

namespace fs = std::filesystem;

using namespace martidb;

TEST_CASE("Performance test against 100,000 records", "") {

    SECTION("setKeyValue and getKeyValue performance agains 100k records.") {
        //Setup
        std::string db_name("test_database_123");
        std::unique_ptr<martidb::IDatabase> db = MartiDB::createEmptyDatabase(db_name);

        std::uint32_t max_records = 100000, i = 0;

        std::unordered_map<std::string, std::string> kv_map;

        //Pre-generating key-value pairs in memory
        for (; i < max_records; i++) {
            kv_map.emplace(std::to_string(i), std::to_string(i));
        }

        std::chrono::steady_clock::time_point start_time, end_time;

        //Store 100k key-value pairs raw (no overlapping)
        std::cout << "::setKeyValue" << std::endl;
        start_time = std::chrono::steady_clock::now();
        for (auto iter = kv_map.begin(); iter != kv_map.end(); iter++) {
            db->setKeyValue(iter->first, iter->second);
        }
        end_time = std::chrono::steady_clock::now();
        std::cout << kv_map.size() << " requests completed in " << (std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count() / 100000) << " seconds." << std::endl;


        //Retrive 100k key-value pairs raw (no overlapping)
        std::cout << "::getKeyValue" << std::endl;
        std::string result = "";
        start_time = std::chrono::steady_clock::now();
        for (auto iter = kv_map.begin(); iter != kv_map.end(); iter++) {
            result = db->getKeyValue(iter->first);
        }
        end_time = std::chrono::steady_clock::now();
        std::cout << kv_map.size() << " requests completed in " << (std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count() / 100000) << " seconds." << std::endl;


        //Cleanup
        db->destroy();
        REQUIRE(!fs::exists(fs::status(db->getDirectory())));
    }

}