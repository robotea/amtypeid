/**
 * @file: AMCETypeID.h
 * Constant expression implementation of type id.
 *
 * @author Zdeněk Skulínek  &lt;<a href="mailto:zdenek.skulinek@seznam.cz">me@zdenekskulinek.cz</a>&gt;
 */

#ifndef AMCETypeID_H
#define AMCETypeID_H

#include "amfnv1a/AMCEFNV1a.h"

using namespace std;

#if defined(__clang__)
    #define _D_PRETTY_FUNCTION __PRETTY_FUNCTION__
	#define _D_PRETTY_FUNCTION_PREFIX   "static AMCore::AMCETypeID::_T_string AMCore::AMCETypeID<"
	#define _D_PRETTY_FUNCTION_SEPARATOR1 ">::stringInit() [with T = "
    #define _D_PRETTY_FUNCTION_PREFIX_I "static int AMCore::AMCETypeID<"
	#define _D_PRETTY_FUNCTION_SEPARATOR3 ">::typeLen() [T = "
    #define _D_PRETTY_FUNCTION_SUFFIX "]"
	#define _D_PRETTY_FUNCTION_LENGTH ((sizeof(_D_PRETTY_FUNCTION) - sizeof(_D_PRETTY_FUNCTION_PREFIX_I) - sizeof(_D_PRETTY_FUNCTION_SUFFIX) - sizeof(_D_PRETTY_FUNCTION_SEPARATOR3) + 3) / 2 + 1)
    //#error test it!!!
#elif defined(__GNUC__) && !defined(__clang__)
    #define _D_PRETTY_FUNCTION __PRETTY_FUNCTION__
	#define _D_PRETTY_FUNCTION_PREFIX   "static constexpr AMCore::AMCETypeID<T>::_T_string AMCore::AMCETypeID<T>::stringInit() [with T = "
    #define _D_PRETTY_FUNCTION_PREFIX_I "static constexpr int AMCore::AMCETypeID<T>::typeLen() [with T = "
    #define _D_PRETTY_FUNCTION_SUFFIX "]"
	#define _D_PRETTY_FUNCTION_LENGTH sizeof(_D_PRETTY_FUNCTION) - sizeof(_D_PRETTY_FUNCTION_PREFIX_I) - sizeof(_D_PRETTY_FUNCTION_SUFFIX) + 2
#elif defined(_MSC_VER)
    #define _D_PRETTY_FUNCTION __FUNCSIG__
	#define _D_PRETTY_FUNCTION_PREFIX   "struct AMCore::AMCETypeID<T>::_T_string __cdecl AMCore::AMCETypeID<T>::stringInit<"
	#define _D_PRETTY_FUNCTION_PREFIX_I "struct int __cdecl AMCore::AMCETypeID<T>::typeLen<"
    #define _D_PRETTY_FUNCTION_SUFFIX ">(void)"
    #error test it!!!
#else
    #error "Andromeda Library do not support this compiler."
#endif

#include <iostream>

namespace AMCore {


#ifdef COLLECTING_DATA

	template<bool>
	struct _T_AMTypeId_list_leaf {
		static _T_AMTypeId_list_leaf* _M_first;
		_T_AMTypeId_list_leaf* _M_next;
		const char* _M_name;
		uint64_t _M_hash;
        uint64_t _M_id;
	public:
		constexpr _T_AMTypeId_list_leaf(const char* name, uint64_t hash):_M_name(name),_M_hash(hash),_M_next(_M_first),_M_id(_M_first ? _M_first->_M_id + 1 : 0) {
			_M_first = this;
		}
	};
	template<bool b>
	_T_AMTypeId_list_leaf<b>* _T_AMTypeId_list_leaf<b>::_M_first = nullptr;

#endif

	/**
	 *  @ingroup Typing
	 *  @brief Constant expression id for types
	 *  Simply, retrieve from given type it's name as a string, and integral
	 *  id.
	 */
	template<typename T>
	class AMCETypeID
	{
	public:
        static constexpr int typeLen()
        {
            return _D_PRETTY_FUNCTION_LENGTH;
        }
        static constexpr int _M_lengthCE = AMCETypeID<T>::typeLen();
        class _T_string
        {
        public:
            constexpr _T_string(): _M_array() {};
            char _M_array[AMCETypeID<T>::_M_lengthCE];
        };
		static constexpr _T_string cc(_T_string dst, int index,const char* src)
		{
			dst._M_array[index] = src[0];
			if (_M_lengthCE-1 <= index) {
				return dst;
			}
			return cc(dst, index+1, src+1);
		}
		static constexpr _T_string stringInit()
		{
			 _T_string rv;
			const char* ctype = _D_PRETTY_FUNCTION ;
			int offset = - 1 + sizeof(_D_PRETTY_FUNCTION_PREFIX);
			const int length = _M_lengthCE -1;
			for(int i=0; i < length ; i++,offset++) {
			    rv._M_array[i] = ctype[offset];
			}
			rv._M_array[_M_lengthCE-1] = 0;
			return rv;
		}
        static const _T_string _M_name;
        static constexpr const _T_string _M_nameCE = AMCETypeID<T>::stringInit();
        static constexpr const uint64_t _M_hashCE = AMCEFNV1aAlgorithm::fnv1a64(_M_nameCE._M_array);
        static constexpr const uint32_t _M_hashCE32 = AMCEFNV1aAlgorithm::fnv1a32(_M_nameCE._M_array);

		#ifdef COLLECTING_DATA
		public:
			static _T_AMTypeId_list_leaf<true> _leaf;
		#endif
	public:
		/**
		 *  @brief Name of class
		 *  @returns Zero ended string
		 */
		static constexpr const char* name()
		{
			return _M_name._M_array;
            #ifdef COLLECTING_DATA
			const uint64_t static_member_starter = _leaf._M_hash;
            #endif
		}
		/**
		 *  @brief Name length
		 *  Zero at end is included
		 *  @returns length
		 */
		static constexpr int nameLength()
        {
		    return _M_lengthCE;
            #ifdef COLLECTING_DATA
			const uint64_t static_member_starter = _leaf._M_hash;
            #endif
        }
		/**
		 *  @brief Hash code
		 *  64-bit size.
		 *  @returns hash
		 */
        static constexpr uint64_t hash_code()
        {
            return _M_hashCE;
            #ifdef COLLECTING_DATA
			const uint64_t static_member_starter = _leaf._M_hash;
            #endif
        }
		/**
		 *  @brief Hash code
		 *  32-bit size.
		 *  @returns hash
		 */
        static constexpr uint32_t hash_code32()
        {
            return _M_hashCE32;
            #ifdef COLLECTING_DATA
			const uint64_t static_member_starter = _leaf._M_hash;
            #endif
        }
		/**
		 *  @brief id
		 *  Practically, id is some index in range in 0 to N.
		 *  Main purpose is optimize switch statement, there compiler is able
		 *  to make jump table, instead of comparing with many values.
		 *  To ensure this functionality, program must be compiled with macro
		 *  COLLECTING_DATA defined. Without it, this function returns 64-bit hash,
		 *  so, can be used in cases of switch statement.
		 *
		 *  id is not *constexpr* if COLLECTING_DATA if defined. If you need *constexpr*,
		 *  you may use \ref hash_code function.
		 *  @return id 64-bit
		 */
		static constexpr uint64_t id()
        {
            #ifdef COLLECTING_DATA
            return _leaf._M_id;
            const uint64_t static_member_starter = _leaf._M_hash;
            #else
            return _M_hashCE;
            #endif
        }
		/**
		 *  @brief lowest 32 bit of id()
		 *  @returns 32-bit sized id
		 */
		static constexpr uint32_t id32()
        {
            return (uint32_t)id() & 0xFFFFFFFF;
            #ifdef COLLECTING_DATA
			const uint64_t static_member_starter = _leaf._M_hash;
            #endif
        }
	};
	template<typename T>
    const typename AMCETypeID<T>::_T_string AMCETypeID<T>::_M_name =  AMCETypeID<T>::_M_nameCE;
	#ifdef COLLECTING_DATA
		template<typename T>
		_T_AMTypeId_list_leaf<true> AMCETypeID<T>::_leaf = _T_AMTypeId_list_leaf<true>(AMCETypeID<T>::name(), AMCETypeID<T>::hash_code());
	#endif


}//namespace

#endif //AMCETypeID_H
