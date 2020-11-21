find_package(range-v3 CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

# Generic test that uses conan libs
add_executable(intro main.cpp)
target_link_libraries(
  intro PRIVATE project_options project_warnings 
                fmt::fmt fmt::fmt-header-only meta range-v3 )
