include(CTest)

# catkin compatibility
if(NOT TARGET run_tests)
  add_custom_target(run_tests)
endif()

if(BUILD_TESTING)
  set(TESTS
    testCategory testFixedContextCategory testNDC testPattern
    testErrorCollision testPriority testFilter testProperties
    testConfig testPropertyConfig testRollingFileAppender testDailyRollingFileAppender
  )

  set(DATA log4cpp.init log4cpp.properties testProperties.properties
    testConfig.log4cpp.properties testConfig.log4cpp.dailyroll.properties
  )

  # copy test data
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
  foreach(file ${DATA})
    configure_file(${file} ${CMAKE_CURRENT_BINARY_DIR}/${file} COPYONLY)
  endforeach()

  include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
  )

  add_executable(testmain EXCLUDE_FROM_ALL testmain.cpp)
  target_link_libraries(testmain ${LOG4CPP_LIBRARY_NAME} -pthread)
  #add_test(NAME testmain COMMAND testmain)

  add_executable(testbench EXCLUDE_FROM_ALL Clock.cpp Clock.hh testbench.cpp)
  target_link_libraries(testbench ${LOG4CPP_LIBRARY_NAME} -pthread)
  #add_test(NAME testbench COMMAND testbench)

  foreach(test ${TESTS})
    add_executable(${test} EXCLUDE_FROM_ALL ${test}.cpp)
    target_link_libraries(${test} ${LOG4CPP_LIBRARY_NAME} -pthread)
    add_test(NAME ${test} COMMAND ${test})
  endforeach()

  add_custom_target(check
    COMMAND ctest -V
    DEPENDS ${TESTS}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  )

  add_dependencies(run_tests check)
endif()
