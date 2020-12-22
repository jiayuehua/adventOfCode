find_package(range-v3 CONFIG REQUIRED)

# Generic test that uses conan libs
function(aoc arg)
add_executable(${arg} exprs.cpp "${arg}.cpp" )

find_path(BOOST_SPIRIT_INCLUDE_DIRS "boost/spirit.hpp")
target_include_directories(${arg} PRIVATE
          ${CMAKE_CURRENT_SOURCE_DIR} 
           ${BOOST_SPIRIT_INCLUDE_DIRS} )
target_link_libraries(
  ${arg} PRIVATE project_options project_warnings 
                   range-v3 range-v3-meta range-v3::meta range-v3-concepts )
                   endfunction()
                   aoc(game24)
                   aoc(aoc201801)
                   aoc(aoc201802)
                   aoc(aoc201901)
                   aoc(aoc201902)
                   aoc(aoc161601)
