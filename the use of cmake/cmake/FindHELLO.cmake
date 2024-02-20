#find_path(HELLO_INCLUDE_DIR hello.h /usr/local/include/hello /usr/local/include/)
#find_library(HELLO_LIBRARY NAMES hello PATH /usr/local/lib )
#if (HELLO_INCLUDE_DIR AND HELLO_LIBRARY)
#	set(HELLO_FOUND TRUE)
#endif (HELLO_INCLUDE_DIR AND HELLO_LIBRARY)

FIND_PATH(HELLO_INCLUDE_DIR hello.h /usr/local/include/ )  # ./include
FIND_LIBRARY(HELLO_LIBRARY NAMES hello PATH  /usr/local/lib)  # /usr/lib
IF(HELLO_INCLUDE_DIR AND HELLO_LIBRARY)
    SET(HELLO_FOUND TRUE)
ENDIF(HELLO_INCLUDE_DIR AND HELLO_LIBRARY)

