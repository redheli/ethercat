SET (CMAKE_C_FLAGS "${CMAKE_CFLAGS} ${XNPOSIX_USER_CFLAGS}")
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
ADD_EXECUTABLE(master_test master_test.cpp)
TARGET_LINK_LIBRARIES(master_test eml)
# removed eval_test
#ADD_EXECUTABLE(eval_test eval_test.cpp process_data.cpp)
#TARGET_LINK_LIBRARIES(eval_test eml)
TARGET_LINK_LIBRARIES(master_test pthread rt)
SET_TARGET_PROPERTIES(master_test PROPERTIES LINK_FLAGS "${POSIX_USER_LDFLAGS}")
