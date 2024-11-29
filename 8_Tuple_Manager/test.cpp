#include "pch.h"
#include "TupleManager.h"

// Testing TupleManager functionality
TEST(TupleManagerTest, ConstructorAndAccessors) {
    TupleManager<std::string, std::string, char> tm{ "0101", "--..-", 'A' };
    EXPECT_EQ(tm.getBinaryKey(), "0101");
    EXPECT_EQ(tm.getString(), "--..-");
    EXPECT_EQ(tm.getASCIIValue(), 'A');
}

TEST(TupleManagerTest, Mutators) {
    TupleManager<std::string, std::string, char> tm{ "0101", "--..-", 'A' };
    tm.setBinaryKey("1001");
    tm.setString("-.-.");
    tm.setASCIIValue('B');
    EXPECT_EQ(tm.getBinaryKey(), "1001");
    EXPECT_EQ(tm.getString(), "-.-.");
    EXPECT_EQ(tm.getASCIIValue(), 'B');
}

TEST(TupleManagerTest, EqualityOperator) {
    TupleManager<std::string, std::string, char> tm1{ "0101", "--..-", 'A' };
    TupleManager<std::string, std::string, char> tm2{ "0101", "--..-", 'A' };
    TupleManager<std::string, std::string, char> tm3{ "1001", "-.-.", 'B' };
    EXPECT_TRUE(tm1 == tm2);
    EXPECT_FALSE(tm1 == tm3);
}

TEST(TupleManagerTest, Swap) {
    TupleManager<std::string, std::string, char> tm1{ "0101", "--..-", 'A' };
    TupleManager<std::string, std::string, char> tm2{ "1001", "-.-.", 'B' };
    tm1.swap(tm2);
    EXPECT_EQ(tm1.getBinaryKey(), "1001");
    EXPECT_EQ(tm1.getString(), "-.-.");
    EXPECT_EQ(tm1.getASCIIValue(), 'B');
    EXPECT_EQ(tm2.getBinaryKey(), "0101");
    EXPECT_EQ(tm2.getString(), "--..-");
    EXPECT_EQ(tm2.getASCIIValue(), 'A');
}

// Testing HashTable functionality
TEST(HashTableTest, InsertAndAccess) {
    HashTable<std::string, std::string, char> ht;
    ht.insert({ "0101", "--..-", 'A' });
    ht.insert({ "1001", "-.-.", 'B' });
    EXPECT_EQ(ht["0101"], 'A');
    EXPECT_EQ(ht("--..-"), 'A');
    EXPECT_EQ(ht["1001"], 'B');
    EXPECT_EQ(ht("-.-."), 'B');
}

TEST(HashTableTest, AccessNonExistentKey) {
    HashTable<std::string, std::string, char> ht;
    ht.insert({ "0101", "--..-", 'A' });
    EXPECT_THROW(ht["9999"], std::out_of_range);
    EXPECT_THROW(ht("...."), std::out_of_range);
}

TEST(HashTableTest, EraseByKey) {
    HashTable<std::string, std::string, char> ht;
    ht.insert({ "0101", "--..-", 'A' });
    ht.insert({ "1001", "-.-.", 'B' });
    ht.eraseByKey("0101");
    EXPECT_THROW(ht["0101"], std::out_of_range);
    EXPECT_EQ(ht["1001"], 'B');  // Check that other elements remain
}

TEST(HashTableTest, EraseByString) {
    HashTable<std::string, std::string, char> ht;
    ht.insert({ "0101", "--..-", 'A' });
    ht.insert({ "1001", "-.-.", 'B' });
    ht.eraseByString("--..-");
    EXPECT_THROW(ht("0101"), std::out_of_range);
    EXPECT_EQ(ht("-.-."), 'B');  // Check that other elements remain
}

TEST(HashTableTest, FindByKey) {
    HashTable<std::string, std::string, char> ht;
    ht.insert({ "0101", "--..-", 'A' });
    ht.insert({ "1001", "-.-.", 'B' });
    auto it = ht.findByKey("0101");
    EXPECT_NE(it, ht.end());
    EXPECT_EQ(it->getASCIIValue(), 'A');
}

TEST(HashTableTest, FindByString) {
    HashTable<std::string, std::string, char> ht;
    ht.insert({ "0101", "--..-", 'A' });
    ht.insert({ "1001", "-.-.", 'B' });
    auto it = ht.findByString("-.-.");
    EXPECT_NE(it, ht.end());
    EXPECT_EQ(it->getASCIIValue(), 'B');
}

TEST(HashTableTest, FindNonExistentKey) {
    HashTable<std::string, std::string, char> ht;
    ht.insert({ "0101", "--..-", 'A' });
    auto it = ht.findByKey("9999");
    EXPECT_EQ(it, ht.end());
}

TEST(HashTableTest, FindNonExistentString) {
    HashTable<std::string, std::string, char> ht;
    ht.insert({ "0101", "--..-", 'A' });
    auto it = ht.findByString("....");
    EXPECT_EQ(it, ht.end());
}
