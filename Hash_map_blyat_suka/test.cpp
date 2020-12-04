#include "pch.h"
#include <vector>
#include <unordered_map>

TEST(Allocator, A) {
	fefu::allocator<int> alloc;
	int* place = alloc.allocate();
	*place = 15;
	EXPECT_EQ(*place, 15);
}

TEST(Iterators, A) {
	fefu::hash_map<int, std::string> table(7);
	table.insert(std::make_pair(7, "make"));
	table.insert(std::make_pair(2, "me"));
	table.insert(std::make_pair(3, "happy"));
	auto iterator = table.begin();
	ASSERT_TRUE("me" == iterator->second);
	ASSERT_TRUE("make" == iterator.operator++()->second);
	ASSERT_TRUE("happy" == iterator.operator++(1)->second);
	ASSERT_TRUE(table.end() == iterator.operator++(1));

	for (auto i = table.begin(); i != table.end(); i++) {
		std::cout << (*i).second << std::endl;
	}
}

TEST(Iterators, B) {
	fefu::hash_map<int, std::string> table(7);
	table.insert(std::make_pair(7, "make"));
	table.insert(std::make_pair(2, "me"));
	table.insert(std::make_pair(3, "happy"));

	auto iterator = table.cbegin();
	ASSERT_TRUE("me" == iterator->second);
	ASSERT_TRUE("make" == iterator.operator++()->second);
	ASSERT_TRUE("happy" == iterator.operator++(1)->second);
	ASSERT_TRUE(table.cend() == iterator.operator++(1));

	for (auto i = table.begin(); i != table.end(); i++) {
		std::cout << i->first << " " << i->second << std::endl;
	}
}

TEST(Iterators, C) {
	fefu::hash_map<int, int> table({ {21, 1}, {0, 23}, {2, 3}, {-1, 11}, {-12, 11}, {21, 1} });
	fefu::hash_map_iterator<std::pair<const int, int>> itererator_one = table.begin();
	fefu::hash_map_const_iterator<std::pair<const int, int>> begin = itererator_one;
	fefu::hash_map_const_iterator<std::pair<const int, int>> end = table.end();

	ASSERT_FALSE(begin == end);
	for (auto i = table.cbegin(); i != table.cend(); i++) {
		std::cout << (*i).first << " " << (*i).second << std::endl;
	}
}

TEST(Iterators, D) {

}

TEST(Constructors, A) {
	fefu::hash_map<std::string, int> table(7);
	EXPECT_EQ(table.bucket_count(), 7);
	EXPECT_EQ(table.size(), 0);
	EXPECT_EQ(table.size(), 0);
	ASSERT_TRUE(table.empty());
}

TEST(Constructors, B) {
	fefu::hash_map<std::string, int> table;
	EXPECT_EQ(table.bucket_count(), 0);
	EXPECT_EQ(table.size(), 0);
	EXPECT_EQ(table.size(), 0);
	EXPECT_EQ(table.load_factor(), 0);
}

TEST(Constructors, C) {
	fefu::hash_map<std::string, int> table_one(10);
	table_one.insert(std::pair<std::string, int>("help", 4));
	table_one.insert(std::pair<const std::string, int>("death", 1));
	table_one.insert(std::pair<const std::string, int>("make", 8));
	table_one.insert(std::pair<const std::string, int>("peace", 6));
	table_one.insert(std::pair<const std::string, int>("death", 5));

	fefu::hash_map<std::string, int> table(table_one);
	ASSERT_TRUE(table.contains("death"));
	ASSERT_FALSE(table.contains("rest"));
	ASSERT_FALSE(table.contains("in"));
	ASSERT_TRUE(table.contains("peace"));
	ASSERT_TRUE(table.contains("help"));
}

TEST(Constructors, D) {
	std::vector<std::pair<std::string, int>> elements(9);
	elements[0] = { "death", 1 };
	elements[1] = { "rest", 2 };
	elements[2] = { "in", 3 };
	elements[3] = { "peace", 4 };
	elements[4] = { "help", 5 };
	fefu::hash_map<std::string, int> table(elements.begin(), elements.end());
	std::cout << table.contains("death");
}

TEST(Constructors, E) {
	fefu::hash_map<std::string, int> table_one(10);
	std::vector<std::pair<std::string, int>> elements(5);
	elements[0] = { "death", 1 };
	elements[1] = { "rest", 2 };
	elements[2] = { "in", 3 };
	elements[3] = { "peace", 4 };
	elements[4] = { "help", 5 };
	table_one.insert(elements.begin(), elements.end());
	fefu::hash_map<std::string, int> table = std::move(table_one);
	ASSERT_TRUE(table_one.empty());
	ASSERT_TRUE(table.size() == 5);
}

TEST(Constructors, F) {
	fefu::hash_map<std::string, int> table({ {"death", 1}, {"rest", 23}, {"help", 3}, {"my", 11}, {"give", 11} });
	EXPECT_EQ(table.at("death"), 1);
	ASSERT_FALSE(table.cbegin() == table.cend());
}

TEST(Constructors, G) {
	std::vector<std::pair<std::string, int>> elements(9);
	elements[0] = { "death", 1 };
	elements[1] = { "rest", 2 };
	elements[2] = { "in", 3 };
	elements[3] = { "peace", 4 };
	elements[4] = { "help", 5 };
	fefu::hash_map<std::string, int> table(elements.begin(), elements.end(), 7);
	std::cout << table.contains("death");
}

TEST(Assignment, A) {
	fefu::hash_map<std::string, int> table({ {"death", 1}, {"rest", 23}, {"help", 3}, {"my", 11}, {"give", 11} });
	fefu::hash_map<std::string, int> new_table;
	new_table = table;

	ASSERT_TRUE(table.begin() == new_table.begin());
	ASSERT_TRUE(table.end() == new_table.end());
	ASSERT_TRUE(table.contains("death") == new_table.contains("death"));
	ASSERT_TRUE(table.contains("rest") == new_table.contains("rest"));
	ASSERT_TRUE(table.contains("help") == new_table.contains("help"));
	ASSERT_TRUE(table.contains("my") == new_table.contains("my"));
	ASSERT_TRUE(table.contains("give") == new_table.contains("give"));
}

TEST(Assignment, B) {
	fefu::hash_map<std::string, int> another_table({ {"death", 1}, {"rest", 23}, {"help", 3}, {"my", 11}, {"give", 11} });
	fefu::hash_map<std::string, int> table;
	table = { {"death", 1}, {"rest", 23}, {"help", 3}, {"my", 11}, {"give", 11} };
	ASSERT_TRUE(table == another_table);
}

TEST(Assignment, C) {
	fefu::hash_map<std::string, int> table({ {"death", 1}, {"rest", 23}, {"help", 3}, {"my", 11}, {"give", 11} });
	fefu::hash_map<std::string, int> new_table;
	new_table = std::move(table);
	ASSERT_TRUE(table.bucket_count() == 0);
	ASSERT_TRUE(new_table.contains("death"));
	ASSERT_TRUE(new_table.contains("rest"));
	ASSERT_TRUE(new_table.contains("help"));
	ASSERT_TRUE(new_table.contains("my"));
	ASSERT_TRUE(new_table.contains("give"));
	ASSERT_TRUE(new_table.size() == 5);
}

TEST(End_Begin, A) {
	fefu::hash_map<int, char> table;
	EXPECT_EQ(table.begin(), table.end());
	ASSERT_TRUE(table.cbegin() == table.cend());
}

TEST(End_Begin, B) {
	fefu::hash_map<std::string, int> table(2);
	std::pair<std::string, int> element{ "yes", 1 };
	table.insert(element);
	ASSERT_TRUE(table.begin()->first == "yes");
	ASSERT_TRUE(table.begin()->second == 1);
}

TEST(End_Begin, C) {
	fefu::hash_map<std::string, int> table({ {"death", 1}, {"rest", 23}, {"help", 3}, {"my", 11}, {"give", 11} });
	ASSERT_FALSE(table.cbegin() == table.cend());
}

TEST(Insert, A) {
	fefu::hash_map<std::string, int> table(10);
	std::vector<std::pair<std::string, int>> elements(5);
	elements[0] = { "death", 1 };
	elements[1] = { "rest", 2 };
	elements[2] = { "in", 3 };
	elements[3] = { "peace", 4 };
	elements[4] = { "help", 5 };

	table.insert(elements.begin(), elements.end());
	ASSERT_TRUE(table.contains("death"));
	ASSERT_TRUE(table.contains("rest"));
	ASSERT_TRUE(table.contains("in"));
	ASSERT_TRUE(table.contains("peace"));
	ASSERT_TRUE(table.contains("help"));
}

TEST(InsertOrAssign, A) {
	fefu::hash_map<std::string, int> table(10);
	std::vector<std::pair<std::string, int>> elements(5);
	elements[0] = { "death", 1 };
	elements[1] = { "rest", 2 };
	elements[2] = { "in", 3 };
	elements[3] = { "peace", 4 };
	elements[4] = { "help", 5 };

	//в этом случае будет key_type&& k, _Obj&& obj так как rvalue
	table.insert_or_assign("death", 1);
	table.insert_or_assign("rest", 2);
	ASSERT_TRUE(table.contains("death"));
	ASSERT_TRUE(table.contains("rest"));
	ASSERT_TRUE(table.at("rest") == 2);
	table.insert_or_assign("rest", 12);
	ASSERT_TRUE(table.at("rest") == 12);
}

TEST(InsertOrAssign, B) {
	fefu::hash_map<std::string, int> table(10);
	std::vector<std::pair<std::string, int>> elements(5);
	elements[0] = { "death", 1 };
	elements[1] = { "rest", 2 };
	elements[2] = { "in", 3 };
	elements[3] = { "peace", 4 };
	elements[4] = { "help", 5 };
	std::string word = "please";
	int number = 89;
	//в этом случае будет const key_type& k, _Obj&& obj, так как lvalue
	table.insert_or_assign(word, number);
	ASSERT_TRUE(table.contains("please"));
	ASSERT_TRUE(table.at(word) == 89);
	int new_number = 11;
	table.insert_or_assign(word, new_number);
	ASSERT_TRUE(table.at(word) == 11);
}

TEST(InsertOrAssign, C) {
	fefu::hash_map<std::string, int> table(10);
	std::vector<std::pair<std::string, int>> elements(5);

	std::string word = "death";
	//в этом случае будет const key_type& k, _Obj&& obj, так как k - lvalue, obj - rvalue
	table.insert_or_assign(word, 1);
	ASSERT_TRUE(table.contains("death"));
	ASSERT_TRUE(table.at(word) == 1);
	table.insert_or_assign(word, 12);
	ASSERT_TRUE(table.at(word) == 12);
}

TEST(Emplace, A) {
	fefu::hash_map<std::string, std::string> table(10);

	table.emplace(std::make_pair(std::string("please"), std::string("please")));
	table.emplace(std::make_pair("me", "mine"));
	table.emplace("dog", "bark");

	ASSERT_TRUE(table.size() == 3);
	ASSERT_TRUE(table.bucket_count() == 10);
	ASSERT_TRUE(table.at("please") == "please");
	ASSERT_TRUE(table.at("me") == "mine");
	ASSERT_TRUE(table.at("dog") == "bark");
}

TEST(TryEmplace, A) {
	fefu::hash_map<std::string, std::string> table(10);

	table.try_emplace("five", "six");
	table.try_emplace("nine", 9, '9');
	ASSERT_TRUE(table.at("nine") == "999999999");
}

TEST(TryEmplace, B) {
	fefu::hash_map<std::string, std::string> table(10);

	std::string word = "five";
	table.try_emplace(word, "six");
	table.try_emplace("Six", 10, '6');
	ASSERT_TRUE(table.at("Six") == "6666666666");
}

TEST(TryEmplace, C) {
	fefu::hash_map<int, std::tuple<int, std::string, std::string>> table(10);
	std::tuple<int, std::string, std::string> element = { 20, "Alexander", "Master" };

	auto person_one = table.try_emplace(1, element);
	auto person_two = table.try_emplace(2, 34, "Henrik", "Hansen");
	ASSERT_TRUE(table[1] == element);
	ASSERT_TRUE(person_one.second == true);
	std::tuple<int, std::string, std::string> element_two = { 34, "Henrik", "Hansen" };
	ASSERT_TRUE(table[2] == element_two);
	ASSERT_TRUE(person_two.second == true);
}

//TEST(Erase, A) {
//	fefu::hash_map<std::string, int> table(10);
//	std::vector<std::pair<std::string, int>> elements(5);
//	elements[0] = { "death", 1 };
//	elements[1] = { "rest", 2 };
//	elements[2] = { "in", 3 };
//	elements[3] = { "peace", 4 };
//	elements[4] = { "help", 5 };
//
//	table.insert(elements.begin(), elements.end());
//	table.erase("death");
//	ASSERT_FALSE(table.contains("death"));
//}
TEST(At, A) {
	fefu::hash_map<std::string, int> table(10);
	std::pair<std::string, int> element_one("death", 1);
	std::pair<std::string, int> element_two("rest", 2);
	table.insert(element_one);
	table.insert(element_two);

	EXPECT_EQ(table.at("death"), 1);
	EXPECT_EQ(table.at("rest"), 2);
	EXPECT_THROW(table.at("help_me"), std::out_of_range);

}

TEST(At, B) {
	//std::pair<const std::string, const int> element_one("death", 1);
	fefu::hash_map<std::string, int> table(7);
	std::vector<std::pair<std::string, int>> elements(5);
	elements[0] = { "death", 1 };
	elements[1] = { "rest", 2 };
	elements[2] = { "in", 3 };
	elements[3] = { "peace", 4 };
	elements[4] = { "help", 5 };
	//fefu::hash_map<std::string, int> table(elements.begin(), elements.end());

	table.insert(elements.begin(), elements.end());
	EXPECT_EQ(table.at("death"), 1);
	EXPECT_THROW(table.at("help_me"), std::out_of_range);

}

TEST(At, C) {
	fefu::hash_map<std::string, int> table({ {"death", 1}, {"rest", 23}, {"help", 3}, {"my", 11}, {"give", 11} });
	table.insert(std::pair<const std::string, const int>("clear", 4));
	ASSERT_TRUE(table.at("clear") == 4);

	fefu::hash_map<int, int> table_two;
	table_two.insert(std::pair<const int, const int>(2, 4));
	ASSERT_TRUE(table_two.at(2) == 4);
}

TEST(At, D) {

}

TEST(Size, A) {
	fefu::hash_map<std::string, int> table(10);
	std::vector<std::pair<std::string, int>> elements(2);
	elements[0] = { "death", 1 };
	elements[1] = { "rest", 2 };
	table.insert(elements.begin(), elements.end());
	ASSERT_TRUE(table.max_size() == std::numeric_limits<size_t>::max());
}

TEST(Operators, A) {
	fefu::hash_map<int, int> table(10);
	table[6] = -120;
	table[2] = 12;
	ASSERT_TRUE(table[6] == -120);
	ASSERT_TRUE(table[2] == 12);
}

TEST(Operators, B) {
	fefu::hash_map<std::string, int> table(10);
	const std::string word = "please";
	const int number = 6;
	table[word] = number;
	ASSERT_TRUE(table["please"] == 6);
	ASSERT_TRUE(table.at("please") == 6);
}

TEST(Operators, C) {
	fefu::hash_map<std::string, int> table({ {"ab1", 1}, {"ab2", 2}, {"ab3", 3}, {"ab4", 4} });
	fefu::hash_map<std::string, int> table_one(table);
}

TEST(Operators, D) {
	fefu::hash_map<std::string, int> one_table({ {"death", 1}, {"rest", 23}, {"help", 3}, {"my", 11}, {"give", 11} });
	fefu::hash_map<std::string, int> two_table({ {"death", 1}, {"rest", 23}, {"help", 3}, {"my", 11}, {"give", 11} });
	fefu::hash_map<std::string, int> three_table({ {"hey", 1}, {"rest", 23}, {"help", 3}, {"clear", 11}, {"give", 11} });

	ASSERT_TRUE(one_table == two_table);
	ASSERT_FALSE(one_table == three_table);
	ASSERT_FALSE(two_table == three_table);
}

TEST(Operators, E) {
	fefu::hash_map<std::string, int> one_table({ {"death", 1}, {"rest", 23}, {"help", 3}, {"my", 11}, {"give", 11} });
	fefu::hash_map<std::string, int> two_table({ {"death", 1}, {"rest", 23}, {"help", 3}, {"my", 11} });

	ASSERT_FALSE(one_table == two_table);

	std::vector<std::pair<std::string, int>> elements(4);
	elements[0] = { "death", 1 };
	elements[1] = { "rest", 2 };
	elements[2] = { "help", 3 };
	elements[3] = { "my", 4 };
	fefu::hash_map<std::string, int> three_table(elements.begin(), elements.end());

	ASSERT_FALSE(two_table == three_table);
}

TEST(Bucket, A) {
	fefu::hash_map<std::string, int> table({ {"give", 11}, {"love", 41}, {"me", 3}, {"death", 41} });
	ASSERT_TRUE(table.bucket("give"));
	ASSERT_TRUE(table.bucket("love"));

	table.insert(std::pair<std::string, int>("help", 4));
	table.insert(std::pair<std::string, int>("death", 1));
	table.insert(std::pair<std::string, int>("make", 8));
	table.insert(std::pair<std::string, int>("peace", 6));
	table.insert(std::pair<std::string, int>("pie", 9));

	ASSERT_TRUE(table.bucket("help"));
	ASSERT_TRUE(table.bucket("death"));
	ASSERT_TRUE(table.bucket("me"));
	ASSERT_TRUE(table.bucket("make"));
	ASSERT_TRUE(table.bucket("pie"));
}

TEST(Load, A) {
	fefu::hash_map<int, int> table(10);
	for (size_t i = 0; i < 3; i++) {
		std::pair<int, int> p = std::make_pair(i, i);
		table.insert(p);
	}
	table.max_load_factor(0.5);
	ASSERT_TRUE(table.max_load_factor() == 0.5);
	ASSERT_TRUE(table.load_factor() == 0.3f);
}

TEST(Load, B) {
	std::vector<std::pair<std::string, int>> elements(4);
	elements[0] = { "death", 1 };
	elements[1] = { "rest", 2 };
	elements[2] = { "in", 3 };
	elements[3] = { "peace", 4 };
	fefu::hash_map<std::string, int> table(elements.begin(), elements.end());

	ASSERT_TRUE(table.bucket("rest"));
	ASSERT_TRUE(table.bucket("death"));
	ASSERT_TRUE(table.bucket("in"));
	ASSERT_TRUE(table.bucket("peace"));

	ASSERT_TRUE(table.max_load_factor() == 0.75);
	ASSERT_TRUE(table.load_factor() == 0.5f);
	table.insert(std::pair<std::string, int>("help", 53));
	table.insert(std::pair<std::string, int>("mine", 21));
	table.insert(std::pair<std::string, int>("make", -8));
	ASSERT_TRUE(table.load_factor() == 0.4375f);
}

TEST(Reserve, A) {
	fefu::hash_map<std::string, std::string> table;
	table.reserve(10);

	ASSERT_TRUE(table.size() == 0);
	table.insert(std::pair<std::string, std::string>("help", "me"));
	table.insert(std::pair<std::string, std::string>("mine", "bark"));
	table.insert(std::pair<std::string, std::string>("make", "dog"));
	ASSERT_TRUE(table.size() == 3);
}
