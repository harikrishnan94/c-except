add_executable(CExceptionsTest test-c-except.c)
target_link_libraries(CExceptionsTest PRIVATE CExceptions)

enable_testing()
add_test(NAME CExceptionsTest COMMAND CExceptionsTest)
