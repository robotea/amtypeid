/**
 * Constant expression implementation of type id.
 *
 * @author Zdeněk Skulínek  &lt;<a href="mailto:zdenek.skulinek@seznam.cz">me@zdenekskulinek.cz</a>&gt;
 */

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

    switch(sw)
    {
		case AMCETypeID<uint32_t>::id(): FAIL() << "Switch: bad branch selected";break;
		case AMCETypeID<int64_t>::id(): FAIL() << "Switch: bad branch selected";break;
		case AMCETypeID<uint64_t>::id(): ;break;
		case AMCETypeID<char*>::id(): FAIL() << "Switch: bad branch selected";break;
    }

    EXPECT_EQ(AMCETypeID<uint64_t>::id(), 100);
    EXPECT_EQ(AMCETypeID<int64_t>::id(), 101);
    EXPECT_EQ(AMCETypeID<uint32_t>::id(), 104);
    EXPECT_EQ(AMCETypeID<int32_t>::id(), 0x2B9FFF192BD4C83EULL);
    EXPECT_EQ(AMCETypeID<const char*>::id(), 102);
    #if defined(__GNU_LIBRARY__)
        EXPECT_EQ(AMCETypeID<std::string>::id(), 0x225ED5CC4E0BFC21ULL);
    #else
        EXPECT_EQ(AMCETypeID<std::string>::id(), 0xDD402F4DE8D36956ULL);
    #endif

    EXPECT_EQ(AMCETypeID<uint64_t>::id32(), 100);
    EXPECT_EQ(AMCETypeID<int64_t>::id32(), 101);
    EXPECT_EQ(AMCETypeID<uint32_t>::id32(), 104);
    EXPECT_EQ(AMCETypeID<int32_t>::id32(), 0x2BD4C83EULL);

}

int main(int argc, char **argv) {

     ::testing::InitGoogleTest(&argc, argv);
     return RUN_ALL_TESTS();
}
