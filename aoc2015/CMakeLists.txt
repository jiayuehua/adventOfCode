find_package(range-v3 CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(TBB CONFIG REQUIRED)
function(aoc arg)
# Generic test that uses conan libs
add_executable(${arg} "${arg}.cpp")
find_package(Threads MODULE REQUIRED)
#find_package(folly CONFIG REQUIRED)
#target_link_libraries(my_app PRIVATE Threads::Threads)
#    find_path(CONSTEXPR_INCLUDE_DIRS "cx_algorithm.h")
#    target_include_directories(${arg} PRIVATE ${CONSTEXPR_INCLUDE_DIRS})


#find_path(BOOST_ITERATOR_INCLUDE_DIRS "boost/function_output_iterator.hpp")
target_include_directories(${arg} PRIVATE
          ${CMAKE_CURRENT_SOURCE_DIR} 
          # ${BOOST_ITERATOR_INCLUDE_DIRS} 
           )
target_link_libraries(
  ${arg} PRIVATE project_options project_warnings 
                  range-v3 range-v3-meta range-v3::meta range-v3-concepts fmt::fmt-header-only TBB::tbb
                  Threads::Threads #Folly::folly Folly::folly_deps #Folly::follybenchmark Folly::folly_test_util
                   )

                   endfunction()
#aoc(aoc150401)


#aoc(aoc150101)
#aoc(aoc150102)
#aoc(aoc150201)
#aoc(aoc150202)
#aoc(aoc150301)
#aoc(aoc150302)
#aoc(aoc150501)
#aoc(aoc150502)
#aoc(aoc150601)
#aoc(aoc150602)
#aoc(aoc150801)
#aoc(aoc150802)
#aoc(aoc151101)
#aoc(aoc151301)
#aoc(aoc151302)
#aoc(aoc151401)
#aoc(aoc151501)
#aoc(aoc151502)
#aoc(aoc151701)
#aoc(aoc151801)
#aoc(aoc151802)
#aoc(aoc152001)
#aoc(aoc152002)
#aoc(aoc151901)
#aoc(aoc151902)
##aoc(aoc151201)
##aoc(aoc151202)
#aoc(aoc152301)
#aoc(aoc152302)
#aoc(aoc152401)
#aoc(aoc152402)
#
