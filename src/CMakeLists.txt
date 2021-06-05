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
