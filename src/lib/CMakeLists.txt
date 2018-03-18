find_package(tinyxml2 REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

include(GenerateExportHeader)

set(holidaymakerSrcs
  calender.cpp
  employee.cpp
  holiday.cpp
)

include_directories(
  ${TINYXML2_INCLUDE_DIRS}
)

add_library(holidaymaker  SHARED ${holidaymakerSrcs} )
add_library(holidaymaker-static STATIC ${holidaymakerSrcs} )

target_link_libraries(holidaymaker ${TINYXML2_LIBRARIES})
target_link_libraries(holidaymaker-static ${TINYXML2_LIBRARIES})    
  
generate_export_header(holidaymaker)

SET(CMAKE_INSTALL_LIBDIR lib CACHE PATH "Output directory for libraries")

set_property(TARGET holidaymaker PROPERTY VERSION ${Upstream_VERSION})
set_property(TARGET holidaymaker PROPERTY SOVERSION ${LIBV})
set_property(TARGET holidaymaker PROPERTY INTERFACE_httppp_MAJOR_VERSION ${LIBV})
set_property(TARGET holidaymaker APPEND PROPERTY COMPATIBLE_INTERFACE_STRING httppp_MAJOR_VERSION)

install(TARGETS holidaymaker EXPORT holidaymakerTargets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)

install(FILES employee.h
              calender.h
              holiday.h
              "${CMAKE_BINARY_DIR}/config.h"
              "${CMAKE_CURRENT_BINARY_DIR}/httppp_export.h"
        DESTINATION include/holidaymaker
        COMPONENT Devel
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/holidaymaker/holidaymakerConfigVersion.cmake"
  VERSION ${Upstream_VERSION}
  COMPATIBILITY AnyNewerVersion
)

export(EXPORT holidaymakerTargets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/holidaymaker/holidaymakerTargets.cmake"
  NAMESPACE Upstream::
)
configure_file(cmake/holidaymakerConfig.cmake
  "${CMAKE_CURRENT_BINARY_DIR}/holidaymaker/holidaymakerConfig.cmake"
  COPYONLY
)

set(ConfigPackageLocation lib/cmake/holidaymaker)
install(EXPORT holidaymakerTargets
  FILE
    holidaymakerTargets.cmake
  NAMESPACE
    Upstream::
  DESTINATION
    ${ConfigPackageLocation}
)

install(
  FILES
    cmake/httpppConfig.cmake
    "${CMAKE_CURRENT_BINARY_DIR}/holidaymaker/holidaymakerConfigVersion.cmake"
  DESTINATION
    ${ConfigPackageLocation}
  COMPONENT
    Devel
)

