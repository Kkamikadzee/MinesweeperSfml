# Generated by Boost 1.78.0

# address-model=64

if(CMAKE_SIZEOF_VOID_P EQUAL 4)
  _BOOST_SKIPPED("libboost_python38-mgw8-mt-d-x64-1_78.a" "64 bit, need 32")
  return()
endif()

# python=3.8

if(Boost_PYTHON_VERSION)
  string(REGEX REPLACE "([0-9]+[.][0-9]+)([.].*)?" "\\1" __boost_pyver ${Boost_PYTHON_VERSION})
  if(NOT __boost_pyver VERSION_EQUAL "3.8")
    _BOOST_SKIPPED("libboost_python38-mgw8-mt-d-x64-1_78.a" "3.8, Boost_PYTHON_VERSION=${Boost_PYTHON_VERSION}")
    return()
  endif()
endif()

if(Boost_PYTHON_VERSION_MAJOR)
  if(NOT "3.8" MATCHES "^${Boost_PYTHON_VERSION_MAJOR}[.]")
    _BOOST_SKIPPED("libboost_python38-mgw8-mt-d-x64-1_78.a" "3.8, Boost_PYTHON_VERSION_MAJOR=${Boost_PYTHON_VERSION_MAJOR}")
    return()
  endif()
endif()

# layout=versioned

# toolset=mgw8

if(Boost_COMPILER)
  if(NOT Boost_COMPILER STREQUAL "mgw8" AND NOT Boost_COMPILER STREQUAL "-mgw8")
    _BOOST_SKIPPED("libboost_python38-mgw8-mt-d-x64-1_78.a" "mgw8, Boost_COMPILER=${Boost_COMPILER}")
    return()
  endif()
else()
  if(BOOST_DETECTED_TOOLSET AND NOT BOOST_DETECTED_TOOLSET STREQUAL "mgw8")
    _BOOST_SKIPPED("libboost_python38-mgw8-mt-d-x64-1_78.a" "mgw8, detected ${BOOST_DETECTED_TOOLSET}, set Boost_COMPILER to override")
    return()
  endif()
endif()

# link=static

if(DEFINED Boost_USE_STATIC_LIBS)
  if(NOT Boost_USE_STATIC_LIBS)
    _BOOST_SKIPPED("libboost_python38-mgw8-mt-d-x64-1_78.a" "static, Boost_USE_STATIC_LIBS=${Boost_USE_STATIC_LIBS}")
    return()
  endif()
else()
  if(NOT WIN32 AND NOT _BOOST_SINGLE_VARIANT)
    _BOOST_SKIPPED("libboost_python38-mgw8-mt-d-x64-1_78.a" "static, default is shared, set Boost_USE_STATIC_LIBS=ON to override")
    return()
  endif()
endif()

# runtime-link=shared

if(Boost_USE_STATIC_RUNTIME)
  _BOOST_SKIPPED("libboost_python38-mgw8-mt-d-x64-1_78.a" "shared runtime, Boost_USE_STATIC_RUNTIME=${Boost_USE_STATIC_RUNTIME}")
  return()
endif()

# runtime-debugging=on

if(NOT "${Boost_USE_DEBUG_RUNTIME}" STREQUAL "" AND NOT Boost_USE_DEBUG_RUNTIME)
  _BOOST_SKIPPED("libboost_python38-mgw8-mt-d-x64-1_78.a" "debug runtime, Boost_USE_DEBUG_RUNTIME=${Boost_USE_DEBUG_RUNTIME}")
  return()
endif()

# threading=multi

if(DEFINED Boost_USE_MULTITHREADED AND NOT Boost_USE_MULTITHREADED)
  _BOOST_SKIPPED("libboost_python38-mgw8-mt-d-x64-1_78.a" "multithreaded, Boost_USE_MULTITHREADED=${Boost_USE_MULTITHREADED}")
  return()
endif()

# variant=debug

if(NOT "${Boost_USE_DEBUG_LIBS}" STREQUAL "" AND NOT Boost_USE_DEBUG_LIBS)
  _BOOST_SKIPPED("libboost_python38-mgw8-mt-d-x64-1_78.a" "debug, Boost_USE_DEBUG_LIBS=${Boost_USE_DEBUG_LIBS}")
  return()
endif()

if(Boost_VERBOSE OR Boost_DEBUG)
  message(STATUS "  [x] libboost_python38-mgw8-mt-d-x64-1_78.a")
endif()

if(NOT Boost_PYTHON_VERSION)
  if(Boost_DEBUG)
    message(STATUS "  Setting Boost_PYTHON_VERSION to 3.8")
  endif()
  set(Boost_PYTHON_VERSION "3.8")
endif()

# Create imported target Boost::python

if(NOT TARGET Boost::python)
  add_library(Boost::python STATIC IMPORTED)

  set_target_properties(Boost::python PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${_BOOST_INCLUDEDIR}"
    INTERFACE_COMPILE_DEFINITIONS "BOOST_PYTHON_NO_LIB"
  )
endif()

# Target file name: libboost_python38-mgw8-mt-d-x64-1_78.a

get_target_property(__boost_imploc Boost::python IMPORTED_LOCATION_DEBUG)
if(__boost_imploc)
  message(SEND_ERROR "Target Boost::python already has an imported location '${__boost_imploc}', which is being overwritten with '${_BOOST_LIBDIR}/libboost_python38-mgw8-mt-d-x64-1_78.a'")
endif()
unset(__boost_imploc)

set_property(TARGET Boost::python APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)

set_target_properties(Boost::python PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG CXX
  IMPORTED_LOCATION_DEBUG "${_BOOST_LIBDIR}/libboost_python38-mgw8-mt-d-x64-1_78.a"
  )

list(APPEND _BOOST_PYTHON_DEPS headers)
