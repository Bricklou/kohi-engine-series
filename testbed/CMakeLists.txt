SET(SOURCES
    src/main.c
)

add_executable(testbed ${SOURCES})

target_compile_definitions(testbed PUBLIC _DEBUG=1 KIMPORT=1)

target_link_libraries(testbed PUBLIC engine)
target_include_directories(testbed PRIVATE
    src
)