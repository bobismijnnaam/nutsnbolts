set(TESTSOURCES
	${TESTSOURCES}
	${CMAKE_CURRENT_SOURCE_DIR}/StringTests.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/RectTests.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ImageTests.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/testmain.cpp
	PARENT_SCOPE
)

add_executable(nutsnbolts_test_runner
	tests.cpp
)
set_target_properties(nutsnbolts_test_runner
	PROPERTIES
	OUTPUT_NAME run
)
