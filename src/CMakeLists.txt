set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
add_library(CExceptions c-except.cpp)
target_compile_features(
    CExceptions
    PRIVATE cxx_std_17
    PUBLIC c_std_11)
target_include_directories(
    CExceptions
    PRIVATE ${INCLUDE_DIR}
    INTERFACE ${INCLUDE_DIR})

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    find_library(BlocksRuntime NAMES BlocksRuntime)
    target_compile_definitions(CExceptions PUBLIC -DCEXCEPT_BLOCKS)
    target_compile_options(CExceptions PUBLIC -fblocks)
    target_link_libraries(CExceptions PUBLIC ${BlocksRuntime})
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_definitions(CExceptions PUBLIC -DCEXCEPT_NESTED_FUNCTIONS)
endif()
