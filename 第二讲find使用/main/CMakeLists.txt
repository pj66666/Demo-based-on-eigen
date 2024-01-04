include_directories("../include")

SET(CMAKE_BUILD_TYPE "Release")
SET(LIBHELLO_SRC ../src/hello.cpp)

ADD_LIBRARY(hello SHARED ${LIBHELLO_SRC})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

INSTALL(FILES ../include/hello.h DESTINATION include)
INSTALL(TARGETS hello 
	LIBRARY DESTINATION lib 
	ARCHIVE DESTINATION lib)


set(CMAKE_MODULE_PATH "../cmake")
message(${CMAKE_MODULE_PATH})  

find_package(HELLO REQUIRED)

message(STATUS "HELLO_INCLUDE_DIRS " ${HELLO_INCLUDE_DIR} )
message(STATUS " HELLO_LIBRARY " ${HELLO_LIBRARY} )

if(HELLO_FOUND)
    MESSAGE(${CMAKE_MODULE_PATH})
    add_executable(aaa main.cpp)
    target_include_directories(aaa PRIVATE ${HELLO_INCLUDE_DIR})
    target_link_libraries(aaa ${HELLO_LIBRARY})  
# else(HELLO_FOUND)
    # message(FATAL_ERROR "HELLO library not found")
endif(HELLO_FOUND)












