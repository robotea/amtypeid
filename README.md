# AMTypeID - unique integral id for an every type

Useful for example for implementing variant types. You may have *union* of multiple types and tag with stored type.

## Usage

Typical usage is very simple...

    #include "amtypeid/AMCETypeID.h"

    uint64_t sw = AMCETypeID<uint64_t>::id();

    switch(sw) {
        case AMCETypeID<uint32_t>::id(): FAIL() << "Switch: bad branch selected";break;
        case AMCETypeID<int64_t>::id(): FAIL() << "Switch: bad branch selected";break;
        case AMCETypeID<uint64_t>::id(): ;break;
        case AMCETypeID<char*>::id(): FAIL() << "Switch: bad branch selected";break;
        case AMCETypeID<std::string>::id(): FAIL() << "Switch: bad branch selected";break;
    }

If you dislike long range of hash, you may put its own id by:

    namespace AMCore {
        template<> inline constexpr uint64_t AMCETypeID<uint64_t>::id() { return 100;}
        template<> inline constexpr uint64_t AMCETypeID<int64_t>::id() { return 101;}
        template<> inline constexpr uint64_t AMCETypeID<const char*>::id() { return 102;}
        template<> inline constexpr uint64_t AMCETypeID<uint32_t>::id() { return 104;}
    }

## Documetation

There are doxygen generated documentation [here on libandromeda.org](http://libandromeda.org/amtypeid/latest/).

## Building AMTypeID

### Getting sources

```bash
git submodule update
```

### Compiling

```bash

mkdir cmake-build-debug

cd cmake-build-debug

cmake ..

make
```

### Single test (not necessary)

```bash
./TEST_AMTypeID

./TEST_AMTypeID_collect
```

## License

This library is under GNU GPL v3 license. If you need business license, don't hesitate to contact [me](mailto:zdenek.skulinek\@robotea.com\?subject\=License%20for%20AMTypeID).

## Contribute

Please contact [me](mailto:zdenek.skulinek\@robotea.com\?subject\=License%20for%20AMTypeID).

## Ask for help

Please contact [me](mailto:zdenek.skulinek\@robotea.com\?subject\=Consultation).

## Dependencies

- [Google test](https://github.com/google/googletest.git)
- [FNV1a hash algorithm](https://github.com/robotea/amfnv1a.git)
