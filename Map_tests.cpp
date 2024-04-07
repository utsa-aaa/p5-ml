#include "Map.hpp"
#include "unit_test_framework.hpp"

using namespace std;


TEST(test_stub) {
Map<int, string> map;
ASSERT_TRUE(map.empty());
ASSERT_EQUAL(map.size(), 0u);

map[1] = "hello";
ASSERT_EQUAL(map[1], "hello");

pair<double, string> tuple;
tuple.first = 2;
tuple.second =  "world";
map.insert(tuple);
ASSERT_EQUAL(map[2], "world");

map[3] = "!!";
map[4] = "four";

auto it_begin = map.find(1);
ASSERT_EQUAL(it_begin, map.begin());

auto it_end = map.find(5);
ASSERT_EQUAL(it_end, map.end());

auto it = map.find(3);

std::pair pair_it = {it, false};

std::pair pair_insert = {3, "hi"};

auto inserted = map.insert(pair_insert);
ASSERT_EQUAL(inserted, pair_it);

std::pair pair_inserted2 = {8, "words"};
auto inserted2 = map.insert(pair_inserted2);
ASSERT_EQUAL(inserted2.second, true);


Map<int, string> map2(map);

Map<int, string> map3;
map3 = map2;


ASSERT_EQUAL(map3.size(), 5);
ASSERT_EQUAL(map3[8], "words");

map3[2] = "new";
ASSERT_EQUAL(map3[2], "new");
ASSERT_EQUAL(map2[2], "world");

map2[2] = "testing";
ASSERT_EQUAL(map2[2], "testing");
ASSERT_EQUAL(map[2], "world");



    
}

TEST_MAIN()
