# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_pu_and_su_cpp_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED pu_and_su_cpp_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(pu_and_su_cpp_FOUND FALSE)
  elseif(NOT pu_and_su_cpp_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(pu_and_su_cpp_FOUND FALSE)
  endif()
  return()
endif()
set(_pu_and_su_cpp_CONFIG_INCLUDED TRUE)

# output package information
if(NOT pu_and_su_cpp_FIND_QUIETLY)
  message(STATUS "Found pu_and_su_cpp: 0.0.0 (${pu_and_su_cpp_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'pu_and_su_cpp' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${pu_and_su_cpp_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(pu_and_su_cpp_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${pu_and_su_cpp_DIR}/${_extra}")
endforeach()
