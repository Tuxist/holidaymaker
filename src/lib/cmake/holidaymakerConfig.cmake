include("${CMAKE_CURRENT_LIST_DIR}/holidaymakerTargets.cmake")

get_filename_component(holidaymaker_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
if(EXISTS "${holidaymaker_CMAKE_DIR}/CMakeCache.txt")
  # In build tree
  include("${holidaymaker_CMAKE_DIR}/holidaymakerBuildTreeSettings.cmake")
else()
  set(holidaymaker_INCLUDE_DIRS "${httppp_CMAKE_DIR}/@CONF_REL_INCLUDE_DIR@")
endif()

set(holidaymaker_LIBRARIES holidaymaker)
set(holidaymaker_INCLUDE_DIR "holidaymaker")
