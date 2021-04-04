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
#aoc(aoc160501)
#aoc(aoc160502)

#aoc(aoc161401)
#aoc(aoc161402)

#aoc(aoc161501)
#aoc(aoc161502)
#
#aoc(aoc160101)
#aoc(aoc160102)
#aoc(aoc160201)
#aoc(aoc160202)
#aoc(aoc160301)
#aoc(aoc160302)
#aoc(aoc160401)
#aoc(aoc160402)
#aoc(aoc160601)
#aoc(aoc160602)
#aoc(aoc160701)
#aoc(aoc160702)
#aoc(aoc160801)
#aoc(aoc160901)
#aoc(aoc160902)
#aoc(aoc161201)
#aoc(aoc161202)
#aoc(aoc161301)
#aoc(aoc161302)
##aoc(aoc161701)
##aoc(aoc161702)
##aoc(aoc161801)
#aoc(aoc161802)
#aoc(aoc161901)
#aoc(aoc161902)
#aoc(aoc162101)
#aoc(aoc162102)
#aoc(aoc162301)
#aoc(aoc162302)
#aoc(aoc162401)
#aoc(aoc162402)
#aoc(aoc162501)
