cmake_minimum_required(VERSION 3.7)
project(glish)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE HPP_FILES inc/glish/*.hpp inc/glish/*.tpp)
file(GLOB_RECURSE CPP_FILES src/*.cpp)

set(SOURCE_FILES ${HPP_FILES} ${CPP_FILES} )



include_directories(BEFORE_SYSTEM PRIVATE inc )
include_directories(BEFORE_SYSTEM PRIVATE inc/glish)
include_directories(BEFORE_SYSTEM PRIVATE ../utils/inc/)
include_directories(BEFORE_SYSTEM PRIVATE ../)
if(WIN32)
    include_directories(BEFORE_SYSTEM PRIVATE ../inc/)
    MESSAGE("OS is Windows")
else(WIN32)
    add_compile_options(-Wall -pedantic -Wextra)

endif(WIN32)
add_library(glish STATIC ${SOURCE_FILES})


target_link_libraries(glish PUBLIC SDL2 PUBLIC SDL2_image )

install(
        TARGETS glish
        ARCHIVE DESTINATION lib
)
install(
        DIRECTORY inc/glish
        DESTINATION include
)
