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
#aoc(aoc170101)
#aoc(aoc170102)
#aoc(aoc170201)
#aoc(aoc170202)
#aoc(aoc170301)
#aoc(aoc170302)
#aoc(aoc170901)
#aoc(aoc170902)
#aoc(aoc170401)
#aoc(aoc170402)
#aoc(aoc170501)
#aoc(aoc170502)
#aoc(aoc171101)
#aoc(aoc171102)
#aoc(aoc171102)
#aoc(aoc171701)
#aoc(aoc171702)
#aoc(aoc171801)
#aoc(aoc172001)
#aoc(aoc172101)
#aoc(aoc172101_other)
#aoc(aoc172201)
#aoc(aoc172202)
#aoc(aoc172301)
#aoc(aoc170702)
#aoc(aoc172101_other)
#aoc(aoc171901)
