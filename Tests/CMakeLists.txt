project(tests)

set(SRC_LIST
    main.cpp
    TestBigNum.cpp
    TestEllipticCurves.cpp
    TestKeyGenerator.cpp
)

add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBRARY_NAME})
