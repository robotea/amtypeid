/**
 * @mainpage Andromeda typeid library
 * @brief AMTypeID - unique integral id for an every type
 *
 * Useful for example for implementing variant types. You may have *union* of multiple types and tag with stored type.
 *
 * Usage
 * =====
 *
 * Typical usage is very simple...
 *
 * \code
 *
 * #include "amtypeid/AMCETypeID.h"
 *
 * uint64_t sw = AMCETypeID<uint64_t>::id();
 *
 *  switch(sw) {
 *		case AMCETypeID<uint32_t>::id(): FAIL() << "Switch: bad branch selected";break;
 *		case AMCETypeID<int64_t>::id(): FAIL() << "Switch: bad branch selected";break;
 *		case AMCETypeID<uint64_t>::id(): ;break;
 *		case AMCETypeID<char*>::id(): FAIL() << "Switch: bad branch selected";break;
 *		case AMCETypeID<std::string>::id(): FAIL() << "Switch: bad branch selected";break;
 *  }
 *
 * \endcode
 *
 * If you dislike long range of hash, you may put its own id by:
 *
 * \code
 *
 * namespace AMCore {
 *      template<> inline constexpr uint64_t AMCETypeID<uint64_t>::id() { return 100;}
 *      template<> inline constexpr uint64_t AMCETypeID<int64_t>::id() { return 101;}
 *      template<> inline constexpr uint64_t AMCETypeID<const char*>::id() { return 102;}
 *      template<> inline constexpr uint64_t AMCETypeID<uint32_t>::id() { return 104;}
 *   }
 * \endcode
 *
 * Sources
 * =======
 *
 * Download at [GitHUB](https://github.com/robotea/amtypeid)
 *
 * Building AMTypeID
 * ==================
 *
 * Getting sources
 * ---------------
 *
 * \code
 * git submodule update
 * \endcode
 *
 * Compiling
 * ---------
 *
 * \code
 * mkdir cmake-build-debug
 *
 * cd cmake-build-debug
 *
 * cmake ..
 *
 * make
 * \endcode
 *
 * Output Library
 * --------------
 *
 * \code
 * /lib/libAMTypeID.so
 * \endcode
 *
 * Single test (not necessary)
 * ---------------------------
 *
 * \code
 * ./TEST_AMTypeID
 *
 * ./TEST_AMTypeID_collect
 * \endcode
 *
 * License
 * =======
 *
 * This library is under GNU GPL v3 license. If you need business license, don't hesitate to contact [me](mailto:zdenek.skulinek@robotea.com?subject=License for AMException).
 *
 * Contribute
 * ==========
 *
 * Please contact [me](mailto:zdenek.skulinek@robotea.com?subject=License for AMException).
 *
 * Dependencies
 * ============
 *
 * - [Google test](https://github.com/google/googletest.git)
 * - [FNV1a hash algorithm](https://github.com/robotea/amfnv1a.git)
 */
