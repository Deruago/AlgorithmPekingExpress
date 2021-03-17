add_subdirectory("${PROJECT_SOURCE_DIR}/extern/jsoncpp" "extern/jsoncpp")

file(GLOB_RECURSE HEADER_LIST "${PekingExpressProject_SOURCE_DIR}/include/*.h")
file(GLOB_RECURSE SOURCE_LIST "${PekingExpressProject_SOURCE_DIR}/lib/*.cpp")

add_library(PekingExpress STATIC ${SOURCE_LIST} ${HEADER_LIST})

target_include_directories(PekingExpress PRIVATE ../include)
target_compile_features(PekingExpress PRIVATE cxx_std_17)
set_target_properties(PekingExpress PROPERTIES LINKER_LANGUAGE CXX)

set_target_properties(jsoncpp_lib PROPERTIES FOLDER extern)

target_link_libraries(PekingExpress jsoncpp_lib)

add_executable(PekingExpressProjectMain ${SOURCE_LIST} ../main.cpp ${HEADER_LIST})

target_compile_features(PekingExpressProjectMain PRIVATE cxx_std_17)
set_target_properties(PekingExpressProjectMain PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(PekingExpressProjectMain PekingExpress)