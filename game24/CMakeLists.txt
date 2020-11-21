find_package(range-v3 CONFIG REQUIRED)

# Generic test that uses conan libs
add_executable(game24 exprs.cpp cal.cpp )

target_include_directories(game24 INTERFACE
          $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
         # $<INSTALL_INTERFACE:include>
                           )
target_link_libraries(
  game24 PRIVATE project_options project_warnings 
                  range-v3 )
