find_package(range-v3 CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
function(aoc arg)
# Generic test that uses conan libs
add_executable(${arg} "${arg}.cpp")

#    find_path(CONSTEXPR_INCLUDE_DIRS "cx_algorithm.h")
#    target_include_directories(${arg} PRIVATE ${CONSTEXPR_INCLUDE_DIRS})


#find_path(BOOST_ITERATOR_INCLUDE_DIRS "boost/function_output_iterator.hpp")
target_include_directories(${arg} PRIVATE
          ${CMAKE_CURRENT_SOURCE_DIR} 
          # ${BOOST_ITERATOR_INCLUDE_DIRS} 
           )
target_link_libraries(
  ${arg} PRIVATE project_options project_warnings 
                  range-v3 range-v3-meta range-v3::meta range-v3-concepts fmt::fmt-header-only
                   )
                   endfunction()
aoc(day0101)
aoc(day0102)
aoc(day0201)
aoc(day0202)
aoc(day0301)
aoc(day0302)
aoc(day0401)
aoc(day0501)
aoc(day0502)
aoc(aoc200601)
aoc(aoc200602)
aoc(aoc200801)
aoc(aoc200802)
aoc(aoc200901)
aoc(aoc200902)
aoc(y15day0101)
aoc(y15day0102)
aoc(aoc150201)
aoc(aoc150202)
aoc(aoc150301)
aoc(aoc150302)
#aoc(aoc150401)
aoc(aoc150501)
aoc(aoc150601)
aoc(aoc150602)
aoc(aoc150801)
aoc(aoc150802)
aoc(aoc151101)
aoc(aoc151401)


