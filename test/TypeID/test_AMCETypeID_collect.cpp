/**
 * Constant expression implementation of type id.
 *
 * @author Zdeněk Skulínek  &lt;<a href="mailto:zdenek.skulinek@seznam.cz">me@zdenekskulinek.cz</a>&gt;
 */

#define COLLECTING_DATA

#include "../../AMCETypeID.h"
#include "gtest/gtest.h"
#include "gmock/gmock-matchers.h"
#include <algorithm>


using namespace std;
using namespace AMCore;

TEST(AMCETypeID, basicTest) {

	uint64_t sw = AMCETypeID<uint64_t>::hash_code();

    switch(sw)
    {
		case AMCETypeID<uint32_t>::hash_code(): FAIL() << "Switch: bad branch selected";break;
		case AMCETypeID<int64_t>::hash_code(): FAIL() << "Switch: bad branch selected";break;
		case AMCETypeID<uint64_t>::hash_code(): ;break;
		case AMCETypeID<char*>::hash_code(): FAIL() << "Switch: bad branch selected";break;
    }

	uint32_t sw32 = AMCETypeID<uint64_t>::hash_code32();

    switch(sw32)
    {
		case AMCETypeID<uint32_t>::hash_code32(): FAIL() << "Switch: bad branch selected";break;
		case AMCETypeID<int64_t>::hash_code32(): FAIL() << "Switch: bad branch selected";break;
		case AMCETypeID<uint64_t>::hash_code32(): ;break;
		case AMCETypeID<char*>::hash_code32(): FAIL() << "Switch: bad branch selected";break;
    }
	#if defined(__clang__)
		EXPECT_STREQ(AMCETypeID<uint64_t>::name(), "unsigned long");
		EXPECT_STREQ(AMCETypeID<int64_t>::name(), "long");
		EXPECT_STREQ(AMCETypeID<uint32_t>::name(), "unsigned int");
		EXPECT_STREQ(AMCETypeID<int32_t>::name(), "int");
		EXPECT_STREQ(AMCETypeID<char*>::name(), "char *");
        EXPECT_STREQ(AMCETypeID<char>::name(), "char");
	#elif defined(__GNUC__) && !defined(__clang__)
		EXPECT_STREQ(AMCETypeID<uint64_t>::name(), "long unsigned int");
		EXPECT_STREQ(AMCETypeID<int64_t>::name(), "long int");
		EXPECT_STREQ(AMCETypeID<uint32_t>::name(), "unsigned int");
		EXPECT_STREQ(AMCETypeID<int32_t>::name(), "int");
		EXPECT_STREQ(AMCETypeID<char*>::name(), "char*");
        EXPECT_STREQ(AMCETypeID<char>::name(), "char");

	#elif defined(_MSC_VER)
	    #error test it!!!
	#else
	    #error "Andromeda Library do not support this compiler."
    #endif

    #if defined(__GNU_LIBRARY__)
        EXPECT_STREQ(AMCETypeID<std::string>::name(), "std::__cxx11::basic_string<char> ");
    #else
        EXPECT_STREQ(AMCETypeID<std::string>::name(), "std::basic_string<char>");
    #endif
}

namespace AMCore {

    template<> inline constexpr uint64_t AMCETypeID<uint64_t>::id() { return 100;}
    template<> inline constexpr uint64_t AMCETypeID<int64_t>::id() { return 101;}
    template<> inline constexpr uint64_t AMCETypeID<const char*>::id() { return 102;}
    template<> inline constexpr uint64_t AMCETypeID<uint32_t>::id() { return 104;}
}

TEST(AMCETypeID, basicId) {

	uint64_t sw = AMCETypeID<uint64_t>::id();
    if (sw == AMCETypeID<uint32_t>::id()) {
        FAIL() << "bad branch selected";
    } else if (sw == AMCETypeID<int64_t>::id()) {
        FAIL() << "bad branch selected";
    } else if (sw == AMCETypeID<uint64_t>::id()) {
        std::cout << "OK";
    } else if (sw == AMCETypeID<char*>::id()) {
        FAIL() << "bad branch selected";
    }

    EXPECT_EQ(AMCETypeID<uint64_t>::id(), 100);
    EXPECT_EQ(AMCETypeID<int64_t>::id(), 101);
    EXPECT_EQ(AMCETypeID<uint32_t>::id(), 104);
    EXPECT_EQ(AMCETypeID<int32_t>::id(), 4);
    EXPECT_EQ(AMCETypeID<const char*>::id(), 102);
    #if defined(__GNU_LIBRARY__)
        EXPECT_EQ(AMCETypeID<std::string>::id(), 6);
    #else
        EXPECT_EQ(AMCETypeID<std::string>::id(), 6);
    #endif

    EXPECT_EQ(AMCETypeID<uint64_t>::id32(), 100);
    EXPECT_EQ(AMCETypeID<int64_t>::id32(), 101);
    EXPECT_EQ(AMCETypeID<uint32_t>::id32(), 104);
    EXPECT_EQ(AMCETypeID<int32_t>::id32(), 4);

}

TEST(AMCETypeID, collecting) {

	uint64_t sw = AMCETypeID<uint64_t>::id();
	uint64_t sw2 = AMCETypeID<int64_t>::id();
	uint64_t sw3 = AMCETypeID<const char *>::id();
	uint64_t sw4 = AMCETypeID<char>::id();

    _T_AMTypeId_list_leaf<true>* leaf = _T_AMTypeId_list_leaf<true>::_M_first;
	int i=1;
	while(leaf) {
		i++;
		leaf = leaf->_M_next;
	}
	EXPECT_EQ(i, 7+1);
	i=0;
	leaf = _T_AMTypeId_list_leaf<true>::_M_first;
	std::array<uint64_t,7> hashes;
	while(leaf) {
		hashes[i] = leaf->_M_hash;
		i++;
		leaf = leaf->_M_next;
	}

    EXPECT_THAT(hashes, testing::Contains(AMCETypeID<char*>::hash_code()));
    EXPECT_THAT(hashes, testing::Contains(AMCETypeID<int32_t>::hash_code()));
    EXPECT_THAT(hashes, testing::Contains(AMCETypeID<uint64_t>::hash_code()));
    EXPECT_THAT(hashes, testing::Contains(AMCETypeID<uint32_t>::hash_code()));
    EXPECT_THAT(hashes, testing::Contains(AMCETypeID<int64_t>::hash_code()));
    EXPECT_THAT(hashes, testing::Contains(AMCETypeID<char>::hash_code()));
    EXPECT_THAT(hashes, testing::Contains(AMCETypeID<std::string>::hash_code()));
}

int main(int argc, char **argv) {

     ::testing::InitGoogleTest(&argc, argv);
     return RUN_ALL_TESTS();
}
