add_executable(CExceptionsTest testbase.cpp test-c-except.cpp)
target_include_directories(CExceptionsTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(CExceptionsTest PRIVATE CExceptions)

enable_testing()
add_test(NAME CExceptionsTest COMMAND CExceptionsTest -d yes)
