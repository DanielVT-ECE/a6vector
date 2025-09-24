#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "vector.hpp"

TEST_CASE("Push, size and element access with const reference", "[push][access][const]") {
    dsa::Vector<int> v;
    for (int i{0}; i < 5; ++i)
        v.push_back(i);

    const dsa::Vector<int>& cv = v;

    REQUIRE(v.size() == 5);
    REQUIRE(!v.empty());

    for (int i = 0; i < 5; ++i) {
        REQUIRE(v[i] == i);
        REQUIRE(cv[i] == i); // const access
    }

    REQUIRE(v.front() == 0);
    REQUIRE(v.back() == 4);
}

TEST_CASE("At() throws on out-of-bounds indices", "[at][bounds][error]"){
    dsa::Vector<int> v;
    for (int i{0}; i < 5; ++i)
        v.push_back(i);

    const dsa::Vector<int>& cv = v;

    REQUIRE_THROWS_AS(v.at(-1), std::out_of_range);
    REQUIRE_THROWS_AS(v.at(5), std::out_of_range);
    REQUIRE_THROWS_AS(cv.at(5), std::out_of_range);
}

TEST_CASE("Insert and erase maintain element ordering", "[insert][erase]"){
    dsa::Vector<int> v;
    for (int i{0}; i < 5; ++i)
        v.push_back(i);

    // insert at front
    v.insert(0, 100);
    REQUIRE(v.size() == 6);
    REQUIRE(v.front() == 100);
    REQUIRE(v[1] == 0);

    // insert in middle
    v.insert(3, 200);
    REQUIRE(v[3] == 200);
    REQUIRE(v.size() == 7);

    // erase the middle element
    v.erase(3);
    REQUIRE(v.size() == 6);
    REQUIRE(v[3] == 2); // original element shifted back into position

    // erase first element
    v.erase(0);
    REQUIRE(v.front() == 0);
    REQUIRE(v.size() == 5);

    // final sequence should be 0..4
    for (int i = 0; i < 5; ++i) REQUIRE(v[i] == i);
}

TEST_CASE("Reserve, pop_back, shrink and shrink_to_fit behavior", "[reserve][pop][shrink]"){
    dsa::Vector<int> v;
    for (int i{0}; i < 8; ++i) v.push_back(i);

    int before_size = v.size();
    int before_cap = v.capacity();
    REQUIRE(before_size == 8);
    REQUIRE(before_cap >= before_size);

    // pop one element
    v.pop_back();
    REQUIRE(v.size() == 7);

    // reserve a larger capacity
    v.reserve(20);
    REQUIRE(v.capacity() >= 20);
    REQUIRE(v.size() == 7); // size unchanged by reserve

    // shrink_to_fit should make capacity >= size but not less than 1
    v.shrink_to_fit();
    REQUIRE(v.capacity() >= v.size());

    // remove many elements to trigger shrink()
    for (int k = 0; k < 6; ++k) v.pop_back(); // now size should be 1
    REQUIRE(v.size() == 1);
    v.shrink();
    REQUIRE(v.capacity() >= 1);
}

TEST_CASE("Reserve on empty vector and basic empty behavior", "[empty][edge]"){
    dsa::Vector<int> v;
    REQUIRE(v.empty());

    v.reserve(3);
    REQUIRE(v.capacity() >= 3);
    REQUIRE(v.size() == 0);
}

