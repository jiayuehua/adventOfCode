find_package(range-v3 CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package( Threads  REQUIRED )
# Generic test that uses conan libs
function(aoc arg)
add_executable(${arg} exprs.cpp "${arg}.cpp"  "machine.h")
#find_path(BOOST_DYNAMIC_BITSET_INCLUDE_DIRS "boost/dynamic_bitset.hpp")
find_path(BOOST_SPIRIT_INCLUDE_DIRS "boost/spirit.hpp")

find_path(BOOST_CIRCULAR_BUFFER_INCLUDE_DIRS "boost/circular_buffer.hpp")
    find_path(BOOST_INTRUSIVE_INCLUDE_DIRS "boost/intrusive/any_hook.hpp")
target_include_directories(${arg} PRIVATE
          ${CMAKE_CURRENT_SOURCE_DIR} 
          ${BOOST_SPIRIT_INCLUDE_DIRS}
          ${BOOST_INTRUSIVE_INCLUDE_DIRS}
${BOOST_CIRCULAR_BUFFER_INCLUDE_DIRS}
#${Boost_INCLUDE_DIRS}
#          ${BOOST_DYNAMIC_BITSET_INCLUDE_DIRS}
           )
target_link_libraries(
  ${arg} PRIVATE project_options project_warnings fmt::fmt-header-only
                Threads::Threads   range-v3 range-v3-meta range-v3::meta range-v3-concepts ${Boost_LIBRARIES} )
                   endfunction()
#                   aoc(game24)
#                   aoc(aoc201801)
#                   aoc(aoc201802)
#                   aoc(aoc201901)
#                   aoc(aoc162001)
#                   aoc(aoc162002)
#aoc(aoc202301)
#aoc(aoc202302)
#aoc(aoc150701)
#aoc(aoc150702)
#aoc(aoc200701)
#aoc(aoc200702)
#aoc(aoc170601)
#aoc(aoc170602)
#aoc(aoc171001)
#aoc(aoc171002)
#aoc(aoc171201)
#aoc(aoc171202)
#aoc(aoc171301)
#aoc(aoc171302)
#aoc(aoc171401)
#aoc(aoc171402)
#aoc(aoc171501)
#aoc(aoc171502)
#aoc(aoc171601)
#aoc(aoc171802)
#aoc(aoc171602)
#aoc(aoc170701)
#aoc(aoc170801)
#aoc(aoc170802)
#aoc(aoc180302)
#aoc(aoc180401)
#aoc(aoc180402)
#aoc(aoc172401)
#aoc(aoc172402)
            #       aoc(aoc201902)
                   #aoc(aoc161601)#bitset
