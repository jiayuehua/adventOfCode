find_package(range-v3 CONFIG REQUIRED)
find_package(boost CONFIG REQUIRED)

# Generic test that uses conan libs
add_executable(game24 exprs.cpp cal.cpp )

find_path(BOOST_SPIRIT_INCLUDE_DIRS "boost/spirit.hpp")
target_include_directories(game24 private
          $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
${BOOST_SPIRIT_INCLUDE_DIRS}
         # $<INSTALL_INTERFACE:include>
                           )
target_link_libraries(
  game24 PRIVATE project_options project_warnings 
                   range-v3 range-v3-meta range-v3::meta range-v3-concepts )
