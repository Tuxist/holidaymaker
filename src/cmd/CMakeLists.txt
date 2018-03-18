include_directories(
    ${CMAKE_SOURCE_DIR}/src/lib
)

add_executable (holidaymakercmd holidaymaker.cpp)

target_link_libraries(holidaymakercmd holidaymaker-static)
