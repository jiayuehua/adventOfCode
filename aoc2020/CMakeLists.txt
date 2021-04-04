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


#aoc(aoc200101)
#aoc(aoc200102)
#aoc(aoc200201)
#aoc(aoc200202)
#aoc(aoc200301)
#aoc(aoc200302)
#aoc(aoc200401)
#aoc(aoc200501)
#aoc(aoc200502)
#aoc(aoc200601)
#aoc(aoc200602)
#aoc(aoc200801)
#aoc(aoc200802)
#aoc(aoc200901)
#aoc(aoc200902)
#aoc(aoc201001)
#aoc(aoc201002)
#aoc(aoc201101)
#aoc(aoc201102)
#aoc(aoc201201)
#aoc(aoc201202)
#aoc(aoc201301)
#aoc(aoc201302)
#aoc(aoc201401)
#aoc(aoc201402)
#aoc(aoc201501)
#aoc(aoc201502)
#aoc(aoc201602)
#aoc(aoc201502)
#aoc(aoc202201)
#
#aoc(aoc202202)
#aoc(aoc202401)
#aoc(aoc202402)
#aoc(aoc202501)
#aoc(aoc201701)
#aoc(aoc201702)
