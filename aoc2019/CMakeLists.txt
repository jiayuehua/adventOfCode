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

    find_path(PLF_COLONY_INCLUDE_DIRS "plf_colony.h")

    find_package(date CONFIG REQUIRED)

    find_path(THINK_CELL_RANGE_INCLUDE_DIRS "think-cell/range/accumulator.h")
    target_include_directories(${arg} PRIVATE ${THINK_CELL_RANGE_INCLUDE_DIRS})

#find_path(BOOST_ITERATOR_INCLUDE_DIRS "boost/function_output_iterator.hpp")
target_include_directories(${arg} PRIVATE
          ${CMAKE_CURRENT_SOURCE_DIR} 
          # ${BOOST_ITERATOR_INCLUDE_DIRS} 
           )
target_link_libraries(
  ${arg} PRIVATE project_options project_warnings 
                  range-v3 range-v3-meta range-v3::meta range-v3-concepts fmt::fmt-header-only TBB::tbb
                  Threads::Threads #Folly::folly Folly::folly_deps #Folly::follybenchmark Folly::folly_test_util
date::date date::date-tz
     ${PLF_COLONY_INCLUDE_DIRS})

                   endfunction()
#aoc(aoc190101)
#aoc(aoc190102)
#aoc(aoc190201)
#aoc(aoc190202)
#aoc(aoc190301)
#aoc(aoc190302)
#aoc(aoc190401)
#aoc(aoc190402)
#aoc(aoc190501)
#aoc(aoc190502)
#aoc(aoc190801)
#aoc(aoc190802)
#aoc(aoc190901)
#aoc(aoc190701)
#aoc(aoc190601)
#oc(aoc190602)
#aoc(aoc190702)
#aoc(aoc191001)
#aoc(aoc191002)

aoc(rangev3)
aoc(thinkcell)
